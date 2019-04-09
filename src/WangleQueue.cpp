/*
 * WangleQueue.cpp
 *
 *  Created on: Mar 17, 2019
 *      Author: titusen
 */
#include <chrono>

#include "WangleQueue.h"

void threadFunction(folly::BlockingQueue<std::string> *queue, VectorContextStorage *ctxStorage, std::atomic<bool> *isRunning) {
    while (*isRunning) {
        std::string msg = queue->take();
        std::cout << msg << std::endl;
        Context *ctx = ctxStorage->getRandomContext();
        while (*isRunning && ctx == nullptr) {
            std::this_thread::sleep_for(std::chrono::milliseconds(400));
            ctx = ctxStorage->getRandomContext();
        }
        ctx->fireWrite(msg);
    }
}

void WangleQueue::start() {
    const size_t numThreads = 4;
    workerThreads.reserve(numThreads);
    isRunning = true;
    for (size_t i = 0; i < numThreads; ++i) {
        workerThreads.push_back(std::thread(threadFunction, &queue, &storage, &isRunning));
    }

    inboundServer.childPipeline(std::make_shared<InQueuePipelineFactory>(InQueuePipelineFactory(queue)));
    inboundServer.bind(4004);
    outboundServer.childPipeline(std::make_shared<OutQueuePipelineFactory>(OutQueuePipelineFactory(storage)));
    outboundServer.bind(4005);
    inboundServer.waitForStop();
    outboundServer.waitForStop();

}

void WangleQueue::stop() {
}

CurrentState WangleQueue::getCurrentState() {
    CurrentState c;
    return c;
}
