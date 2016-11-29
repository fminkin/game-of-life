//
// Created by fedor on 10/15/16.
//

#ifndef LIFE_BASEALGORITHM_H
#define LIFE_BASEALGORITHM_H


#include "Field.h"

class BaseAlgorithm {
public:
    virtual Field& getState(int roundsElapsed) = 0;
};


#endif //LIFE_BASEALGORITHM_H
