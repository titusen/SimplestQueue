/*
 * IQueue.h
 *
 *  Created on: Mar 9, 2019
 *      Author: titusen
 */

#ifndef IQUEUE_H_
#define IQUEUE_H_

enum QueueStatus {
    Running,
    NotRunning
};

class IQueue {
public:
    virtual ~IQueue() = default;
    virtual QueueStatus start() = 0;
    virtual void stop() = 0;
};

#endif /* IQUEUE_H_ */
