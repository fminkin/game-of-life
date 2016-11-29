#include <iostream>
#include "Field.h"
#include "SimpleAlgorithm.h"
#include "Barrier.h"
#include "SequentialAlgorithm.h"
#include <unistd.h>
int main(int argc, char** argv) {
    //std::ifstream f1("input.txt");
    SimpleAlgorithm f(std::ifstream("input.txt"), 8);
    SequentialAlgorithm alg(std::ifstream("input.txt"));
    for (int i = 0; i < 10000; ++i) {
        f.getState(i).getLog(std::ofstream("output.txt"));
        alg.getState(i).getLog(std::ofstream("output_true.txt"));
        usleep(1e6*1.5); 
    }
    return 0;
}