#include "VectorContextStorage.h"
#include "WangleQueue.h"

#include <chrono>
#include <shared_mutex>

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
        std::cout << "Proccessing: " << msg << std::endl;
#endif
        std::shared_ptr<ContextWrapper> ctxWrapper;
        try
        {
            ctxWrapper = storage->getRandomContext();
            while (isRunning && ctxWrapper == nullptr) {
                std::this_thread::sleep_for(
                        std::chrono::milliseconds(FLAGS_waitTimeForContext));
                ctxWrapper = storage->getRandomContext();
            }
            ctxWrapper->getContext()->fireWrite(std::move(msg)).get(std::chrono::milliseconds(100));

        }
        catch (const folly::AsyncSocketException& e) {
            LOG(WARNING) << "AsyncSocket exception caught\n";
            storage->remove(ctxWrapper->getContext());
            ctxWrapper = nullptr;
        }
        catch (const std::exception& e) {
            LOG(ERROR) << " exception caught\n";
            storage->remove(ctxWrapper->getContext());
            ctxWrapper = nullptr;
        }
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
    isRunning = false;
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
