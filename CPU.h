#ifndef CPU_H
#define CPU_H

#include "Process.h"
#include <iostream>

class CPU {
private:
    int cyclesExecuted;
    int contextSwitches;
    int threadSwitches;

public:
    CPU();
    void execute(Process& p, int threadId);
    void printStats() const;
};

#endif