#ifndef __CONTEXT__
#define __CONTEXT__

#include "kernel/config.h"

class Context {

public:
    Context();

    void setState(State state);
    State getState();
    void reset();
  
private:
    State state;
};

#endif
