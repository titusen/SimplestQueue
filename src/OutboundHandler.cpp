/*
 * OutboundHandler.cpp
 *
 *  Created on: Mar 21, 2019
 *      Author: titusen
 */

#include "OutboundHandler.h"

void OutboundHandler::transportActive(Context* ctx) {
#ifdef DEBUG
    std::cout << "I have a receiver\n";
#endif
    storage.insert(ctx);
}

void OutboundHandler::transportInactive(Context* ctx) {
#ifdef DEBUG
    std::cout << "I lost a receiver\n";
#endif
    storage.remove(ctx);
}
