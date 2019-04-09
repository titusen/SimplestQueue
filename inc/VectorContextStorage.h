/*
 * VectorContextStorage.h
 *
 *  Created on: Mar 22, 2019
 *      Author: titusen
 */

#ifndef INC_VECTORCONTEXTSTORAGE_H_
#define INC_VECTORCONTEXTSTORAGE_H_

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



#endif /* INC_VECTORCONTEXTSTORAGE_H_ */
