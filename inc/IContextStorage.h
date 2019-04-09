/*
 * IContextStorage.h
 *
 *  Created on: Mar 21, 2019
 *      Author: titusen
 */

#ifndef INC_ICONTEXTSTORAGE_H_
#define INC_ICONTEXTSTORAGE_H_

#include <iostream>
#include <wangle/channel/Handler.h>

typedef wangle::HandlerContext<std::string, std::string> Context;

class IContextStorage {
public:
    ~IContextStorage() = default;
    virtual void insert(Context*) = 0;
    virtual void remove(Context*) = 0;
    virtual Context* getRandomContext() = 0;
};

#endif /* INC_ICONTEXTSTORAGE_H_ */
