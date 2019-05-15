#ifndef WANGLEQUEUE_H_
#define WANGLEQUEUE_H_

#include "IQueue.h"
#include "InboundHandler.h"
#include "OutboundHandler.h"
#include "IContextStorage.h"

#include <wangle/bootstrap/ServerBootstrap.h>
#include <folly/executors/task_queue/UnboundedBlockingQueue.h>
#include <folly/executors/ThreadedExecutor.h>

#include <atomic>
#include <vector>
#include <thread>
#include <memory>

class WangleQueue : public IQueue {
public:
    WangleQueue(uint32_t receivePort, uint32_t sendPort);
    ~WangleQueue() override;
    void start() override;
    void stop() override;
    State getCurrentState() override;
protected:
    virtual void sendFunction();
private:
    std::unique_ptr<IContextStorage> storage;
    folly::ThreadedExecutor threadPool;
    std::atomic<bool> isRunning;
    std::atomic<uint16_t> sendersCounter, receiversCounter;
    folly::UnboundedBlockingQueue<std::string> queue;
    wangle::ServerBootstrap<QueuePipeline> inboundServer, outboundServer;
    uint32_t receivePort, sendPort;
};

#endif /* WANGLEQUEUE_H_ */
