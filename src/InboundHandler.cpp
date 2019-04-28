#include <iostream>
#include "InboundHandler.h"

void InboundHandler::read(Context* ctx, std::string msg) {
#ifdef DEBUG
    std::cout << "Recevied massage: \"" << msg << "\"\n";
#endif
    queue.add(msg);
}

void InboundHandler::readException(Context* ctx, folly::exception_wrapper e) {
    std::cout << exceptionStr(e) << std::endl;
    close(ctx);
}
void InboundHandler::readEOF(Context* ctx) {
    close(ctx);
}
