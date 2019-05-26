#include "OutboundHandler.h"

void OutboundHandler::transportActive(Context *ctx) {
#ifdef DEBUG
    std::cout << "I have a receiver\n";
#endif
    storage->insert(ctx);
    ++*contextCounter;
}

void OutboundHandler::transportInactive(Context *ctx) {
#ifdef DEBUG
    std::cout << "I lost a receiver\n";
#endif
    storage->remove(ctx);
    --*contextCounter;
}

void OutboundHandler::readException(Context *ctx, folly::exception_wrapper e) {
  LOG(INFO)<< folly::exceptionStr(e);
  //close(ctx);
}
void OutboundHandler::readEOF(Context *ctx) {
  //close(ctx);
}

//folly::Future<folly::Unit> OutboundHandler::writeException(Context* ctx,
//        folly::exception_wrapper e) {
//    std::cout << folly::exceptionStr(e);
//}
