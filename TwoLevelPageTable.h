#ifndef TWO_LEVEL_PAGE_TABLE_H
#define TWO_LEVEL_PAGE_TABLE_H

#include <map>
#include <set>
#include <utility>
#include <iostream>

class TwoLevelPageTable {
private:
    std::map<std::pair<int, int>, int> pageMap;
    std::set<std::pair<int, int>> memoryPages;

public:
    TwoLevelPageTable(int pageCount);
    bool isInMemory(int pid, int pageNum) const;
    int getFrame(int pid, int pageNum) const;
    void loadPage(int pid, int pageNum, int frameNum);
    void printStats() const;
};

#endif