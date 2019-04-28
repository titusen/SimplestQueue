#include <chrono>

#include "WangleQueue.h"
#include "VectorContextStorage.h"

WangleQueue::WangleQueue(uint32_t receivePort, uint32_t sendPort) :
        storage(new VectorContextStorage()), receivePort(receivePort), sendPort(
                sendPort) {
}

WangleQueue::~WangleQueue() {
    stop();
}

void WangleQueue::sendFunction() {
    while (isRunning) {
        std::string msg = queue.take();
#ifdef DEBUG
        std::cout << msg << std::endl;
#endif
        Context *ctx = storage->getRandomContext();
        while (isRunning && ctx == nullptr) {
            std::this_thread::sleep_for(std::chrono::milliseconds(400));
            ctx = storage->getRandomContext();
        }
        ctx->fireWrite(std::forward<std::string>(msg));
    }
}

void WangleQueue::start() {
    const size_t numThreads = 4;
    isRunning = true;
    for (size_t i = 0; i < numThreads; ++i) {
        threadPool.add([this]() {this->sendFunction();});
    }

    inboundServer.childPipeline(
            std::make_shared < InQueuePipelineFactory
                    > (InQueuePipelineFactory(queue)));
    inboundServer.bind(receivePort);
    outboundServer.childPipeline(
            std::make_shared < OutQueuePipelineFactory
                    > (OutQueuePipelineFactory(&(*storage.get()))));
    outboundServer.bind(sendPort);
    inboundServer.waitForStop();
    outboundServer.waitForStop();

}

void WangleQueue::stop() {
    inboundServer.stop();
    outboundServer.stop();
}

CurrentState WangleQueue::getCurrentState() {
    CurrentState c;
    return c;
}
