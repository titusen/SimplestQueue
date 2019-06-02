#ifndef INC_OUTBOUNDHANDLER_H_
#define INC_OUTBOUNDHANDLER_H_

#include "TypeDefinitions.h"
#include "IContextStorage.h"

#include <wangle/channel/Handler.h>
#include <folly/ProducerConsumerQueue.h>
#include <wangle/channel/EventBaseHandler.h>

#include <iostream>
#include <atomic>

class OutboundHandler: public wangle::HandlerAdapter<std::string> {
public:
    OutboundHandler(IContextStorage *storage, std::atomic<uint16_t> *contextCounter) :
            storage(storage), contextCounter(contextCounter) {
    }
    void transportActive(Context *ctx) override;
    void transportInactive(Context *ctx) override;
    void readException(Context *ctx, folly::exception_wrapper e) override;
private:
    IContextStorage *storage;
    std::atomic<uint16_t> *contextCounter;
};

class OutQueuePipelineFactory: public wangle::PipelineFactory<QueuePipeline> {
public:
    OutQueuePipelineFactory(IContextStorage *storage, std::atomic<uint16_t> *contextCounter) :
            storage(storage), contextCounter(contextCounter) {
    }
    QueuePipeline::Ptr newPipeline(
            std::shared_ptr<folly::AsyncTransportWrapper> sock) override {
        auto pipeline = QueuePipeline::create();
        pipeline->addBack(wangle::AsyncSocketHandler(sock));
        pipeline->addBack(wangle::EventBaseHandler());
        pipeline->addBack(wangle::LineBasedFrameDecoder(8192));
        pipeline->addBack(wangle::StringCodec());
        pipeline->addBack(OutboundHandler(storage, contextCounter));
        pipeline->finalize();

        return pipeline;
    }
private:
    IContextStorage *storage;
    std::atomic<uint16_t> *contextCounter;

};

#endif /* INC_OUTBOUNDHANDLER_H_ */
