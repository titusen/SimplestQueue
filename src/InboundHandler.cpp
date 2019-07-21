#include "InboundHandler.h"

#include <thread>
#include <chrono>

void InboundHandler::read(Context* ctx, std::string msg) {

    LOG_DEBUG( "Recevied massage: \"" << msg << "\"\n")

    queue.add(std::move(msg));
}

void InboundHandler::readException(Context* ctx, folly::exception_wrapper e) {
    LOG(INFO) << exceptionStr(e) << std::endl;
    close(ctx);
}
void InboundHandler::readEOF(Context* ctx) {
    close(ctx);
}

void InboundHandler::transportActive(Context* ctx) {
    LOG_DEBUG("Got a sender\n")
    ++*contextCounter;
}

void InboundHandler::transportInactive(Context* ctx) {
    LOG_DEBUG("Lost a sender\n")
    --*contextCounter;
}
