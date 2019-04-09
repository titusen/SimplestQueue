/*
 * OutboundHandler.cpp
 *
 *  Created on: Mar 21, 2019
 *      Author: titusen
 */

#include "OutboundHandler.h"

void OutboundHandler::transportActive(Context* ctx) {
    storage.insert(ctx);
}

void OutboundHandler::transportInactive(Context* ctx) {
    storage.remove(ctx);
}
