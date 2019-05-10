#include "InboundHandler.h"

#include <iostream>

void InboundHandler::read(Context* ctx, std::string msg) {
#ifdef DEBUG
    std::cout << "Recevied massage: \"" << msg << "\"\n";
#endif
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
    ++*contextCounter;
}

void InboundHandler::transportInactive(Context* ctx) {
    --*contextCounter;
}
