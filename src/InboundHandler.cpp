/*
 * InboundHandler.cpp
 *
 *  Created on: Mar 18, 2019
 *      Author: titusen
 */
#include <iostream>
#include "InboundHandler.h"

void InboundHandler::read(Context* ctx, std::string msg) {
    std::cout << "Recevied massage: \"" << msg << "\"\n";
    queue.add(msg);
}
