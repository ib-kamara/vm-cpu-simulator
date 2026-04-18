#include "TLB.h"

TLB::TLB(int size) {
    maxSize = size;
    currentTime = 0;
}

bool TLB::lookup(int pid, int pageNumber, int& frameNumber) {
    currentTime++;

    for (size_t i = 0; i < tlbEntries.size(); i++) {
        if (tlbEntries[i].pid == pid && tlbEntries[i].pageNumber == pageNumber) {
            tlbEntries[i].lastUsed = currentTime;
            frameNumber = tlbEntries[i].frameNumber;
            return true;
        }
    }

    return false;
}

void TLB::insert(int pid, int pageNumber, int frameNumber) {
    currentTime++;

    if ((int)tlbEntries.size() < maxSize) {
        TLBEntry entry;
        entry.pid = pid;
        entry.pageNumber = pageNumber;
        entry.frameNumber = frameNumber;
        entry.lastUsed = currentTime;
        tlbEntries.push_back(entry);
    } else {
        int lruIndex = 0;

        for (size_t i = 1; i < tlbEntries.size(); i++) {
            if (tlbEntries[i].lastUsed < tlbEntries[lruIndex].lastUsed) {
                lruIndex = i;
            }
        }

        tlbEntries[lruIndex].pid = pid;
        tlbEntries[lruIndex].pageNumber = pageNumber;
        tlbEntries[lruIndex].frameNumber = frameNumber;
        tlbEntries[lruIndex].lastUsed = currentTime;
    }
}

void TLB::printStats() const {
    std::cout << "TLB Size: " << tlbEntries.size() << std::endl;
}