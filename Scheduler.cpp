#include "Scheduler.h"

Scheduler::Scheduler(SchedulingPolicy policy, int tlbSize) {
    this->policy = policy;
    quantum = 4;
    readyQueues.resize(3);
}

void Scheduler::addProcessIfNotExists(int pid) {
    if (processes.find(pid) == processes.end()) {
        processes.emplace(pid, Process(pid, 0));
    }
}

Process& Scheduler::getProcess(int pid) {
    return processes.at(pid);
}

void Scheduler::tick() {
    // Will implement scheduling later
}

void Scheduler::adjustPriority(int pid, int threadId) {
    // For MLFQ later
}