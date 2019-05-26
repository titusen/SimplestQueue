#ifndef INC_CONTEXTWRAPPER_H_
#define INC_CONTEXTWRAPPER_H_

#include <wangle/channel/Handler.h>

typedef wangle::HandlerContext<std::string, std::string> Context;

class ContextWrapper {
public:
    ContextWrapper(Context* context) : context(context){};
    ~ContextWrapper() {
        context->fireClose();
    }

    Context* getContext() {
        return context;
    }
private:
    Context *context;
};

#endif /* INC_CONTEXTWRAPPER_H_ */
