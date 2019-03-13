/*
 * FollyQueue.h
 *
 *  Created on: Mar 9, 2019
 *      Author: titusen
 */

#ifndef FOLLYQUEUE_H_
#define FOLLYQUEUE_H_

#include "IQueue.h"

class FollyQueue : public IQueue{
public:
    FollyQueue();
    virtual ~FollyQueue();
    virtual QueueStatus start();
    virtual void stop();
};

#endif /* FOLLYQUEUE_H_ */
