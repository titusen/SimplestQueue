#include <iostream>
#include <memory>
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

using namespace std;

int main(int argc, char **argv) {

    unique_ptr<IQueue> q(new WangleQueue());
    q->start();


    return 0;
}
