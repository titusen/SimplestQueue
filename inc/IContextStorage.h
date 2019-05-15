#ifndef ICONTEXTSTORAGE_H_
#define ICONTEXTSTORAGE_H_

#include <wangle/channel/Handler.h>

#include <iostream>

typedef wangle::HandlerContext<std::string, std::string> Context;

class IContextStorage {
public:
    ~IContextStorage() = default;
    virtual void insert(Context*) = 0;
    virtual void remove(Context*) = 0;
    virtual Context* getRandomContext() = 0;
};

#endif /* INC_ICONTEXTSTORAGE_H_ */
