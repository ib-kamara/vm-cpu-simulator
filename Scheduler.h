#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <map>
#include <queue>
#include <vector>
#include "Process.h"

enum class SchedulingPolicy {
    FCFS,
    RoundRobin,
    Priority,
    MLFQ
};

class Scheduler {
private:
    SchedulingPolicy policy;
    std::map<int, Process> processes;
    std::vector<std::queue<int>> readyQueues;
    int quantum;

public:
    Scheduler(SchedulingPolicy policy, int tlbSize);
    void addProcessIfNotExists(int pid);
    Process& getProcess(int pid);
    void tick();
    void adjustPriority(int pid, int threadId);
};

#endif