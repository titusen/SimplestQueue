#include "OutboundHandler.h"

void OutboundHandler::transportActive(Context *ctx) {
    LOG_DEBUG("Got a receiver\n")
    storage->insert(ctx);
    ++*contextCounter;
}

void OutboundHandler::transportInactive(Context *ctx) {
    LOG_DEBUG( "Lost a receiver\n")
    storage->remove(ctx);
    --*contextCounter;
}

void OutboundHandler::readException(Context *ctx, folly::exception_wrapper e) {
  LOG(INFO)<< folly::exceptionStr(e);
}

