#include "Process.h"

Process::Process(int pid, int priority) {
    this->pid = pid;
    this->priority = priority;
    cpuBurstRemaining = 0;
    accessIndex = 0;
}

bool Process::hasMoreAccesses() const {
    return accessIndex < memoryAccesses.size();
}

std::pair<int, unsigned int> Process::nextAccess() {
    if (hasMoreAccesses()) {
        return memoryAccesses[accessIndex++];
    }
    return {-1, 0};
}

void Process::tick(int threadId) {
    if (cpuBurstRemaining > 0) {
        cpuBurstRemaining--;
    }
}

void Process::addThread(int threadId, int threadPriority) {
    threadPriorities[threadId] = threadPriority;
}