#ifndef IQUEUE_H_
#define IQUEUE_H_

#include <stdint.h>

enum QueueStatus {
    Running, NotRunning
};

struct CurrentState {
    uint16_t receivers, senders;
    uint32_t messages;
    QueueStatus status;
};

class IQueue {
public:
    virtual ~IQueue() = default;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual CurrentState getCurrentState() = 0;
};

#endif /* IQUEUE_H_ */
