//
// Created by fedor on 10/16/16.
//

#ifndef LIFE_BARRIER_H
#define LIFE_BARRIER_H
#include <condition_variable>
#include <mutex>
#include <iostream>
#include <thread>

class Barrier {
public:
    int firstGate, secondGate, numThreads;
    std::condition_variable condition, empty_condition;
    std::mutex change_mutex;
    bool high, low;
    explicit Barrier(int num_threads){
        numThreads = num_threads;
        firstGate = 0;
        secondGate = 0;
    }
    explicit Barrier() {
        firstGate = 0;
        secondGate = 0;
        high = low = false;
    }
    void enter(int &currentField, int &j) {
        std::unique_lock<std::mutex> lock(change_mutex);
        firstGate++;
        if (firstGate == numThreads) {
            firstGate = 0;
            secondGate = numThreads;
            high = true;
            low = false;
            currentField ^= 1;
            condition.notify_all();
        } else {
            while(!high) {
                condition.wait(lock);
            }
        }
        if (secondGate) {
            secondGate--;
            if (!secondGate) {
                low = true;
                empty_condition.notify_all();
            } else {
                while(!low) {
                    empty_condition.wait(lock);
                }
            }
        }
        high = false;
    }
};


#endif //LIFE_BARRIER_H
