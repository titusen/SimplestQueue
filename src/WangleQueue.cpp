/*
 * WangleQueue.cpp
 *
 *  Created on: Mar 17, 2019
 *      Author: titusen
 */
#include <chrono>

#include "WangleQueue.h"

void WangleQueue::sendFunction() {
    while (isRunning) {
        std::string msg = queue.take();
#ifdef DEBUG
        std::cout << msg << std::endl;
#endif
        Context *ctx = storage.getRandomContext();
        while (isRunning && ctx == nullptr) {
            std::this_thread::sleep_for(std::chrono::milliseconds(400));
            ctx = storage.getRandomContext();
        }
        ctx->fireWrite(std::forward<std::string>(msg));
    }
}

void WangleQueue::start() {
    const size_t numThreads = 4;
    isRunning = true;
    for (size_t i = 0; i < numThreads; ++i) {
        threadPool.add([this](){this->sendFunction();});
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
