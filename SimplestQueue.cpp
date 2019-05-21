#include <wangle/channel/Handler.h>
#include <folly/ProducerConsumerQueue.h>
#include <folly/init/Init.h>
#include <wangle/bootstrap/ServerBootstrap.h>
#include <wangle/channel/AsyncSocketHandler.h>
#include <wangle/codec/LineBasedFrameDecoder.h>
#include <wangle/codec/StringCodec.h>

#include "TypeDefinitions.h"
#include "IQueue.h"
#include "WangleQueue.h"

#include <iostream>
#include <memory>

using namespace std;

int main(int argc, char **argv) {
    google::InitGoogleLogging(argv[0]);
    LOG(INFO) << "Starting Queue";
    unique_ptr<IQueue> q(new WangleQueue(4004, 4005));
    q->start();

    return 0;
}
