/*
 * WangleQueue.h
 *
 *  Created on: Mar 17, 2019
 *      Author: titusen
 */

#ifndef WANGLEQUEUE_H_
#define WANGLEQUEUE_H_

#include <atomic>
#include <vector>
#include <thread>
#include <wangle/bootstrap/ServerBootstrap.h>
#include <folly/executors/task_queue/UnboundedBlockingQueue.h>
#include <folly/executors/ThreadedExecutor.h>

#include "IQueue.h"
#include "InboundHandler.h"
#include "OutboundHandler.h"
#include "VectorContextStorage.h"

class WangleQueue : public IQueue {
public:
    virtual ~WangleQueue() = default;
    virtual void start();
    virtual void stop();
    virtual CurrentState getCurrentState();
protected:
    virtual void sendFunction();
//    friend class folly::ThreadedExecutor;
private:
    VectorContextStorage storage;
    folly::ThreadedExecutor threadPool;
    std::atomic<bool> isRunning;
    folly::UnboundedBlockingQueue<std::string> queue;
    wangle::ServerBootstrap<QueuePipeline> inboundServer, outboundServer;
};

#endif /* WANGLEQUEUE_H_ */
