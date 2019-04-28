#ifndef INBOUNDHANDLER_H_
#define INBOUNDHANDLER_H_

#include <iostream>
#include <wangle/channel/Handler.h>
#include <folly/ProducerConsumerQueue.h>
#include <wangle/channel/EventBaseHandler.h>
#include "TypeDefinitions.h"

class InboundHandler: public wangle::HandlerAdapter<std::string> {
public:
    InboundHandler(folly::BlockingQueue<std::string> &queue) :
            queue(queue) {
    }
    void read(Context* ctx, std::string msg) override;
    void readException(Context* ctx, folly::exception_wrapper e) override;
    void readEOF(Context* ctx) override;
private:
    folly::BlockingQueue<std::string> &queue;
};

class InQueuePipelineFactory: public wangle::PipelineFactory<QueuePipeline> {
public:
    InQueuePipelineFactory(folly::BlockingQueue<std::string> &queue) :
            queue(queue) {
    }
    QueuePipeline::Ptr newPipeline(
            std::shared_ptr<folly::AsyncTransportWrapper> sock) override {
        auto pipeline = QueuePipeline::create();
        pipeline->addBack(wangle::AsyncSocketHandler(sock));
        pipeline->addBack(wangle::EventBaseHandler());
        pipeline->addBack(wangle::LineBasedFrameDecoder(8192));
        pipeline->addBack(wangle::StringCodec());
        pipeline->addBack(InboundHandler(queue));
        pipeline->finalize();

        return pipeline;
    }
private:
    folly::BlockingQueue<std::string> &queue;
};

#endif /* INBOUNDHANDLER_H_ */
