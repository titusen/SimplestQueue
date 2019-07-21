#ifndef INC_TYPEDEFINITIONS_H_
#define INC_TYPEDEFINITIONS_H_

#include <folly/init/Init.h>
#include <wangle/bootstrap/ServerBootstrap.h>
#include <wangle/channel/AsyncSocketHandler.h>
#include <wangle/codec/LineBasedFrameDecoder.h>
#include <wangle/codec/StringCodec.h>
#include <iostream>
#include <gflags/gflags.h>

DECLARE_uint32(loglevel);

const uint32_t logLevelError = 1;
const uint32_t logLevelWarning = 2;
const uint32_t logLevelInfo = 3;
const uint32_t logLevelDebug = 4;

#define LOG_ERROR(x) \
    if (FLAGS_loglevel >= logLevelError) { \
        std::cout << __FILENAME__<< ":" << __LINE__ << " [ERROR] " << x << std::endl; \
    }

#define LOG_WARN(x) \
    if (FLAGS_loglevel >= logLevelWarning) { \
        std::cout << __FILENAME__<< ":" << __LINE__ << " [WARN] " << x << std::endl; \
    }

#define LOG_INFO(x) \
    if (FLAGS_loglevel >= logLevelInfo) { \
        std::cout << __FILENAME__<< ":" << __LINE__ << " [INFO] " << x << std::endl; \
    }

#define LOG_DEBUG(x) \
    if (FLAGS_loglevel >= logLevelDebug) { \
        std::cout << __FILENAME__<< ":" << __LINE__ << " [DEBUG] " << x << std::endl; \
    }

typedef wangle::Pipeline<folly::IOBufQueue&, std::string> QueuePipeline;

#endif /* INC_TYPEDEFINITIONS_H_ */
