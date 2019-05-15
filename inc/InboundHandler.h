#ifndef INBOUNDHANDLER_H_
#define INBOUNDHANDLER_H_

#include "TypeDefinitions.h"

#include <wangle/channel/Handler.h>
#include <folly/ProducerConsumerQueue.h>
#include <wangle/channel/EventBaseHandler.h>

#include <iostream>

class InboundHandler: public wangle::HandlerAdapter<std::string> {
public:
    InboundHandler(folly::BlockingQueue<std::string> &queue, std::atomic<uint16_t> *contextCounter) :
            queue(queue), contextCounter(contextCounter) {
    }
    void transportActive(Context *ctx) override;
    void transportInactive(Context *ctx) override;
    void read(Context* ctx, std::string msg) override;
    void readException(Context* ctx, folly::exception_wrapper e) override;
    void readEOF(Context* ctx) override;
private:
    folly::BlockingQueue<std::string> &queue;
    std::atomic<uint16_t> *contextCounter;
};

class InQueuePipelineFactory: public wangle::PipelineFactory<QueuePipeline> {
public:
    InQueuePipelineFactory(folly::BlockingQueue<std::string> &queue, std::atomic<uint16_t> *contextCounter) :
            queue(queue), contextCounter(contextCounter) {
    }
    QueuePipeline::Ptr newPipeline(
            std::shared_ptr<folly::AsyncTransportWrapper> sock) override {
        auto pipeline = QueuePipeline::create();
        pipeline->addBack(wangle::AsyncSocketHandler(sock));
        pipeline->addBack(wangle::EventBaseHandler());
        pipeline->addBack(wangle::LineBasedFrameDecoder(8192));
        pipeline->addBack(wangle::StringCodec());
        pipeline->addBack(InboundHandler(queue, contextCounter));
        pipeline->finalize();

        return pipeline;
    }
private:
    folly::BlockingQueue<std::string> &queue;
    std::atomic<uint16_t> *contextCounter;
};

#endif /* INBOUNDHANDLER_H_ */
