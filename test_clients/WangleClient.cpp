/*
 * Copyright 2017-present Facebook, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>
#include <sstream>

#include <folly/portability/GFlags.h>

#include <folly/init/Init.h>
#include <wangle/bootstrap/ClientBootstrap.h>
#include <wangle/channel/AsyncSocketHandler.h>
#include <wangle/channel/EventBaseHandler.h>
#include <wangle/codec/LineBasedFrameDecoder.h>
#include <wangle/codec/StringCodec.h>

using namespace folly;
using namespace wangle;

DEFINE_int32(port, 4004, "echo server port");
DEFINE_string(host, "::1", "echo server address");
DEFINE_bool(stdin, false, "input automatic or stdin");
DEFINE_uint32(sleep_time_millis, 500, "sleep time between autmatic input generation");

typedef Pipeline<folly::IOBufQueue&, std::string> EchoPipeline;

// the handler for receiving messages back from the server
class EchoHandler: public HandlerAdapter<std::string> {
public:
    void read(Context*, std::string msg) override {
        std::cout << "received from queue: " << msg;
    }
    void readException(Context* ctx, exception_wrapper e) override {
        std::cout << folly::exceptionStr(e) << std::endl;
        close(ctx);
    }
    void readEOF(Context* ctx) override {
        std::cout << "EOF received :(" << std::endl;
        close(ctx);
    }
};

// chains the handlers together to define the response pipeline
class EchoPipelineFactory: public PipelineFactory<EchoPipeline> {
public:
    EchoPipeline::Ptr newPipeline(std::shared_ptr<AsyncTransportWrapper> sock)
            override {
        auto pipeline = EchoPipeline::create();
        pipeline->addBack(AsyncSocketHandler(sock));
        pipeline->addBack(EventBaseHandler()); // ensure we can write from any thread
        pipeline->addBack(LineBasedFrameDecoder(8192, false));
        pipeline->addBack(StringCodec());
        pipeline->addBack(EchoHandler());
        pipeline->finalize();
        return pipeline;
    }
};

int main(int argc, char** argv) {
    folly::Init init(&argc, &argv);

    ClientBootstrap<EchoPipeline> client;
    client.group(std::make_shared<folly::IOThreadPoolExecutor>(1));
    client.pipelineFactory(std::make_shared<EchoPipelineFactory>());
    auto pipeline = client.connect(SocketAddress(FLAGS_host, FLAGS_port)).get();

    unsigned counter = 0;

    try {
        while (true) {
            std::string line;
            if (FLAGS_stdin) {
                std::getline(std::cin, line);
                if (line == "") {
                    break;
                }
            }
            else {
                std::this_thread::sleep_for(std::chrono::milliseconds(FLAGS_sleep_time_millis));
                std::stringstream ss;
                ss << getpid() << "  " << counter++ << std::endl;
                line = ss.str();
            }

            pipeline->write(line).get();
            if (line == "bye") {
                pipeline->close();
                break;
            }
        }
    }
    catch (const std::exception& e) {
        std::cout << exceptionStr(e) << std::endl;
    }

    return 0;
}
