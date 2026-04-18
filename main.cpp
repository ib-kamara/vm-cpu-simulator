#include <iostream>
#include "Process.h"
#include "CPU.h"
#include "Scheduler.h"
#include "TLB.h"
#include "TwoLevelPageTable.h"
#include "Clock.h"

int main() {
    std::cout << "Virtual Memory and CPU Simulation" << std::endl;

    TLB tlb(4);
    TwoLevelPageTable pageTable(16);
    Clock clockReplacer(8);
    CPU cpu;
    Scheduler scheduler(SchedulingPolicy::FCFS, 4);

    std::cout << "Setup complete." << std::endl;

    return 0;
}