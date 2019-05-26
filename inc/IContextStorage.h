#ifndef ICONTEXTSTORAGE_H_
#define ICONTEXTSTORAGE_H_

#include "ContextWrapper.h"

#include <iostream>
#include <shared_mutex>
#include <memory>



class IContextStorage {
public:
    ~IContextStorage() = default;
    virtual void insert(Context*) = 0;
    virtual void remove(Context*) = 0;
    virtual std::shared_ptr<ContextWrapper> getRandomContext() = 0;
};

#endif /* INC_ICONTEXTSTORAGE_H_ */
