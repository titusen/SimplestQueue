/*
 * VectorContextStorage.cpp
 *
 *  Created on: Mar 22, 2019
 *      Author: titusen
 */

#include <algorithm>
#include "VectorContextStorage.h"

using namespace std;

void VectorContextStorage::insert(Context* ctx) {
    lock_guard<shared_mutex> g(access);
    storage.push_back(ctx);
}

void VectorContextStorage::remove(Context* ctx) {
    lock_guard<shared_mutex> g(access);
    for (auto it = storage.begin(); it != storage.end(); ++it) {
        if (*it == ctx) {
            iter_swap(it, storage.rbegin());
            break;
        }
    }
    storage.pop_back();
}

Context* VectorContextStorage::getRandomContext() {
    shared_lock<shared_mutex> lock(access);
    if (storage.empty()) {
        return nullptr;
    }
    return *(storage.begin() + (rand() % storage.size()));
}



