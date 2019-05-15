#include "VectorContextStorage.h"
#include "WangleQueue.h"

#include <chrono>

DEFINE_int32(waitTimeForContext, 400, "A wait time for context");

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
            std::this_thread::sleep_for(
                    std::chrono::milliseconds(FLAGS_waitTimeForContext));
            ctx = storage->getRandomContext();
        }
        ctx->fireWrite(std::move(msg));
    }
}

void WangleQueue::start() {
    const size_t numThreads = 4;
    isRunning = true;
    for (size_t i = 0; i < numThreads; ++i) {
        threadPool.add([this]() {this->sendFunction();});
    }

    inboundServer.childPipeline(
            std::make_shared<InQueuePipelineFactory>(
                    InQueuePipelineFactory(queue, &receiversCounter)));
    inboundServer.bind(receivePort);
    outboundServer.childPipeline(
            std::make_shared<OutQueuePipelineFactory>(
                    OutQueuePipelineFactory(storage.get(), &sendersCounter)));
    outboundServer.bind(sendPort);

    LOG(INFO) << "Queue started";

    inboundServer.waitForStop();
    outboundServer.waitForStop();

}

void WangleQueue::stop() {
    inboundServer.stop();
    outboundServer.stop();
}

State WangleQueue::getCurrentState() {
    State c = {
            .receivers = receiversCounter,
            .senders = sendersCounter,
            .messages = queue.size(),
            .status = (isRunning ? QueueStatus::Running :
                                    QueueStatus::NotRunning) };
    return c;
}
