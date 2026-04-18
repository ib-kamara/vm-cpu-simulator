#include "TwoLevelPageTable.h"

TwoLevelPageTable::TwoLevelPageTable(int pageCount) {
}

bool TwoLevelPageTable::isInMemory(int pid, int pageNum) const {
    return memoryPages.find({pid, pageNum}) != memoryPages.end();
}

int TwoLevelPageTable::getFrame(int pid, int pageNum) const {
    auto it = pageMap.find({pid, pageNum});
    if (it != pageMap.end()) {
        return it->second;
    }
    return -1;
}

void TwoLevelPageTable::loadPage(int pid, int pageNum, int frameNum) {
    memoryPages.insert({pid, pageNum});
    pageMap[{pid, pageNum}] = frameNum;
}

void TwoLevelPageTable::printStats() const {
    std::cout << "Pages in memory: " << memoryPages.size() << std::endl;
}