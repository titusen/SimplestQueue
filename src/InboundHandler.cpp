/*
 * InboundHandler.cpp
 *
 *  Created on: Mar 18, 2019
 *      Author: titusen
 */
#include <iostream>
#include "InboundHandler.h"

void InboundHandler::read(Context* ctx, std::string msg) {
#ifdef DEBUG
    std::cout << "Recevied massage: \"" << msg << "\"\n";
#endif
    queue.add(msg);
}
