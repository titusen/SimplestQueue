#ifndef IQUEUE_H_
#define IQUEUE_H_

#include <stdint.h>

enum class QueueStatus {
    Running, NotRunning
};

struct State {
    uint16_t receivers, senders;
    size_t messages;
    QueueStatus status;
};

class IQueue {
public:
    virtual ~IQueue() = default;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual State getCurrentState() = 0;
};

#endif /* IQUEUE_H_ */
