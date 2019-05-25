#ifndef VECTORCONTEXTSTORAGE_H_
#define VECTORCONTEXTSTORAGE_H_

#include "IContextStorage.h"

#include <vector>
#include <shared_mutex>
#include <random>

class VectorContextStorage : public IContextStorage {
public:
    virtual ~VectorContextStorage() = default;
    virtual void insert(Context *ctx);
    virtual void remove(Context *xtx);
    virtual Context* getRandomContext();
private:
    std::vector<Context*> storage;
    std::shared_mutex access;
    std::default_random_engine generator;
};



#endif /* VECTORCONTEXTSTORAGE_H_ */
