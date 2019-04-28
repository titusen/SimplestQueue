#include "OutboundHandler.h"

void OutboundHandler::transportActive(Context *ctx) {
#ifdef DEBUG
    std::cout << "I have a receiver\n";
#endif
    storage->insert(ctx);
}

void OutboundHandler::transportInactive(Context *ctx) {
#ifdef DEBUG
    std::cout << "I lost a receiver\n";
#endif
    storage->remove(ctx);
}

void OutboundHandler::readException(Context *ctx, folly::exception_wrapper e) {
  LOG(INFO)<< folly::exceptionStr(e);
  close(ctx);
}
void OutboundHandler::readEOF(Context *ctx) {
  close(ctx);
}
