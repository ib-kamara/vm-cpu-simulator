#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "TLB.h"
#include "TwoLevelPageTable.h"
#include "Clock.h"

int main() {
    std::cout << "Virtual Memory and CPU Simulation" << std::endl;

    std::ifstream file("input/trace.txt");

    if (!file.is_open()) {
        std::cout << "Error: Could not open trace file" << std::endl;
        return 1;
    }

    const int PAGE_SIZE = 256;

    TLB tlb(4);
    TwoLevelPageTable pageTable(16);
    Clock clockReplacer(8);

    std::string line;

    int totalAccesses = 0;
    int tlbHits = 0;
    int tlbMisses = 0;
    int pageFaults = 0;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::stringstream ss(line);

        int pid, threadId;
        std::string addressString;
        char type;

        ss >> pid >> threadId >> addressString >> type;

        unsigned int address = std::stoul(addressString, nullptr, 16);
        unsigned int pageNumber = address / PAGE_SIZE;
        unsigned int offset = address % PAGE_SIZE;

        int frameNumber = -1;
        totalAccesses++;

        std::cout << "\nAccess: PID=" << pid
                  << " Thread=" << threadId
                  << " Address=" << addressString
                  << " Type=" << type
                  << " Page=" << pageNumber
                  << " Offset=" << offset
                  << std::endl;

        if (tlb.lookup(pid, pageNumber, frameNumber)) {
            tlbHits++;
            std::cout << "TLB Hit: Frame " << frameNumber << std::endl;
        } else {
            tlbMisses++;
            std::cout << "TLB Miss" << std::endl;

            if (pageTable.isInMemory(pid, pageNumber)) {
                frameNumber = pageTable.getFrame(pid, pageNumber);
                std::cout << "Page Table Hit: Frame " << frameNumber << std::endl;
                tlb.insert(pid, pageNumber, frameNumber);
            } else {
                pageFaults++;
                std::cout << "Page Fault" << std::endl;

                int evictedPid;
                int evictedPage;

                frameNumber = clockReplacer.evictAndReplace(
                    pid,
                    pageNumber,
                    evictedPid,
                    evictedPage,
                    type == 'W'
                );

                if (evictedPid != -1) {
                    pageTable.removePage(evictedPid, evictedPage);
                    std::cout << "Evicted PID " << evictedPid
                              << " Page " << evictedPage << std::endl;
                }

                pageTable.loadPage(pid, pageNumber, frameNumber);
                tlb.insert(pid, pageNumber, frameNumber);

                std::cout << "Loaded into Frame " << frameNumber << std::endl;
            }
        }

        unsigned int physicalAddress = frameNumber * PAGE_SIZE + offset;
        std::cout << "Physical Address: " << physicalAddress << std::endl;
    }

    file.close();

    std::cout << "\n===== Simulation Summary =====" << std::endl;
    std::cout << "Total Accesses: " << totalAccesses << std::endl;
    std::cout << "TLB Hits: " << tlbHits << std::endl;
    std::cout << "TLB Misses: " << tlbMisses << std::endl;
    std::cout << "Page Faults: " << pageFaults << std::endl;

    double tlbHitRate = 0.0;
    if (totalAccesses > 0) {
        tlbHitRate = (double) tlbHits / totalAccesses * 100.0;
    }

    std::cout << "TLB Hit Rate: " << tlbHitRate << "%" << std::endl;

    return 0;
}