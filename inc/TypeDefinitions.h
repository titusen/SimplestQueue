/*
 * TypeDefinitions.h
 *
 *  Created on: Mar 21, 2019
 *      Author: titusen
 */

#ifndef INC_TYPEDEFINITIONS_H_
#define INC_TYPEDEFINITIONS_H_

#include <folly/init/Init.h>
#include <wangle/bootstrap/ServerBootstrap.h>
#include <wangle/channel/AsyncSocketHandler.h>
#include <wangle/codec/LineBasedFrameDecoder.h>
#include <wangle/codec/StringCodec.h>

typedef wangle::Pipeline<folly::IOBufQueue&, std::string> QueuePipeline;



#endif /* INC_TYPEDEFINITIONS_H_ */
