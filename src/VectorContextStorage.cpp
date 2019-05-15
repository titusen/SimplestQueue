#include "VectorContextStorage.h"

#include <assert.h>
#include <algorithm>

using namespace std;

void VectorContextStorage::insert(Context* ctx) {
    lock_guard<shared_mutex> g(access);
    assert(nullptr != ctx);
    storage.push_back(ctx);
}

void VectorContextStorage::remove(Context* ctx) {
    lock_guard<shared_mutex> g(access);
    for (auto it = storage.begin(); it != storage.end(); ++it) {
        if (*it == ctx) {
            iter_swap(it, storage.rbegin());
            storage.pop_back();
            break;
        }
    }
}

Context* VectorContextStorage::getRandomContext() {
    shared_lock<shared_mutex> lock(access);
    if (storage.empty()) {
        return nullptr;
    }
    std::uniform_int_distribution<int> distribution(0, storage.size() - 1);
    return storage.at(distribution(generator));
}

