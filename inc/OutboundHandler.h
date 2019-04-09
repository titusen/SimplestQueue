/*
 * OutboundHandler.h
 *
 *  Created on: Mar 21, 2019
 *      Author: titusen
 */

#ifndef INC_OUTBOUNDHANDLER_H_
#define INC_OUTBOUNDHANDLER_H_


#include <iostream>
#include <wangle/channel/Handler.h>
#include <folly/ProducerConsumerQueue.h>
#include "TypeDefinitions.h"
#include "IContextStorage.h"

class OutboundHandler : public wangle::HandlerAdapter<std::string> {
public:
    OutboundHandler(IContextStorage &storage) : storage(storage) {}
    void transportActive(Context *ctx) override;
    void transportInactive(Context *ctx) override;
private:
    IContextStorage &storage;
};

class OutQueuePipelineFactory: public wangle::PipelineFactory<QueuePipeline> {
public:
    OutQueuePipelineFactory(IContextStorage &storage) : storage(storage) {}
    QueuePipeline::Ptr newPipeline(
            std::shared_ptr<folly::AsyncTransportWrapper> sock) override {
        auto pipeline = QueuePipeline::create();
        pipeline->addBack(wangle::AsyncSocketHandler(sock));
        pipeline->addBack(wangle::LineBasedFrameDecoder(8192));
        pipeline->addBack(wangle::StringCodec());
        pipeline->addBack(OutboundHandler(storage));
        pipeline->finalize();

        return pipeline;
    }
    IContextStorage &storage;

};

#endif /* INC_OUTBOUNDHANDLER_H_ */
