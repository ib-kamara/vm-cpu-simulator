#include "CPU.h"

CPU::CPU() {
    cyclesExecuted = 0;
    contextSwitches = 0;
    threadSwitches = 0;
}

void CPU::execute(Process& p, int threadId) {
    cyclesExecuted++;
    p.tick(threadId);
}

void CPU::printStats() const {
    std::cout << "CPU Cycles: " << cyclesExecuted << std::endl;
    std::cout << "Context Switches: " << contextSwitches << std::endl;
    std::cout << "Thread Switches: " << threadSwitches << std::endl;
}