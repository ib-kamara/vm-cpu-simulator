#include "Clock.h"

Clock::Clock(int frameCount) {
    frames.resize(frameCount);

    for (size_t i = 0; i < frames.size(); i++) {
        frames[i].pid = -1;
        frames[i].pageNumber = -1;
        frames[i].referenced = false;
        frames[i].modified = false;
    }

    clockHand = 0;
}

int Clock::evictAndReplace(int pid, int pageNum, int& evictedPage, bool isModified) {
    while (true) {
        if (!frames[clockHand].referenced) {
            evictedPage = frames[clockHand].pageNumber;

            frames[clockHand].pid = pid;
            frames[clockHand].pageNumber = pageNum;
            frames[clockHand].referenced = true;
            frames[clockHand].modified = isModified;

            int usedFrame = (int)clockHand;
            clockHand = (clockHand + 1) % frames.size();

            return usedFrame;
        } else {
            frames[clockHand].referenced = false;
            clockHand = (clockHand + 1) % frames.size();
        }
    }
}