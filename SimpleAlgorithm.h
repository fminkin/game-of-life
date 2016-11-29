//
// Created by fedor on 10/15/16.
//

#ifndef LIFE_SIMPLEALGORITHM_H
#define LIFE_SIMPLEALGORITHM_H

#include <thread>
#include "BaseAlgorithm.h"
#include "Barrier.h"
class SimpleAlgorithm : public BaseAlgorithm {
private:
    Field fields[2];
    int threadCount, currentField;
    std::mutex m;
    Barrier b;
    std::mutex x;
    void calculateField(int threadNumber, int from, int to, int lastRoundNumber) {
        for(int t = 0; t < lastRoundNumber; ++t) {
            for (int i = from; i < to; ++i) { 
                for (int j = 0; j < fields[currentField].getHorizontalSize(); ++j) {
                    fields[currentField^1][i][j] = fields[currentField].getState(i, j);
                }
            }
            b.enter(currentField, threadNumber);
        }
    }
public:
    Field& getState(int lastRoundNumber) {
        if (!lastRoundNumber) {
            return fields[currentField];
        }
        std::thread *threads = new std::thread[threadCount];
        int part = fields[0].getVerticalSize() / threadCount;
        for (int i = 0; i < threadCount; ++i) {
            int end = (i + 1) * part;
            if (i == threadCount - 1) {
                end = fields[0].getVerticalSize();
            }
            threads[i] = std::thread(&SimpleAlgorithm::calculateField, this, i, i * part, end, lastRoundNumber);
        }
        for (int i = 0; i < threadCount; ++i) {
            threads[i].join();
        }
        return fields[currentField^1];
    }

    SimpleAlgorithm(std::basic_ifstream<char, std::char_traits<char>> &&ifstream, int count = 1) {
        threadCount = count;
        currentField = 0;
        fields[0] = Field(std::move(ifstream));
        fields[1] = Field(std::move(ifstream));
        b.numThreads = count;
    }
};


#endif //LIFE_SIMPLEALGORITHM_H
