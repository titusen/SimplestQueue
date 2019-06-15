#ifndef VECTORCONTEXTSTORAGE_H_
#define VECTORCONTEXTSTORAGE_H_

#include "IContextStorage.h"

#include <vector>
#include <random>

class VectorContextStorage : public IContextStorage {
public:
    virtual ~VectorContextStorage() = default;
    virtual void insert(Context *ctx);
    virtual void remove(Context *xtx);
    virtual std::shared_ptr<ContextWrapper> getRandomContext();
private:
    std::vector<std::shared_ptr<ContextWrapper>> storage;
    std::shared_mutex access;
    std::default_random_engine generator;
};



#endif /* VECTORCONTEXTSTORAGE_H_ */
