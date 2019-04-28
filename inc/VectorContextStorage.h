#ifndef VECTORCONTEXTSTORAGE_H_
#define VECTORCONTEXTSTORAGE_H_

#include <vector>
#include <shared_mutex>
#include "IContextStorage.h"

class VectorContextStorage : public IContextStorage {
public:
    virtual ~VectorContextStorage() = default;
    virtual void insert(Context *ctx);
    virtual void remove(Context *xtx);
    virtual Context* getRandomContext();
private:
    std::vector<Context*> storage;
    std::shared_mutex access;
};



#endif /* VECTORCONTEXTSTORAGE_H_ */
