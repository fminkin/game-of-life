#include <iostream>
#include "Field.h"
#include "SimpleAlgorithm.h"
#include "Barrier.h"
#include "SequentialAlgorithm.h"
#include <unistd.h>
int main(int argc, char** argv) {
    //std::ifstream f1("input.txt");
    SimpleAlgorithm f(std::ifstream("input.txt"), 16);
    f.getState(100000).getLog(std::ofstream("output.txt"));
    
    return 0;
}