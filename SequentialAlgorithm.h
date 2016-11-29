//
// Created by fedor on 10/17/16.
//

#ifndef LIFE_SEQUENTIALALGORITHM_H
#define LIFE_SEQUENTIALALGORITHM_H

#include <fstream>
#include "BaseAlgorithm.h"

class SequentialAlgorithm : public BaseAlgorithm{
public:
    Field fields[2];
    int currentField;
    SequentialAlgorithm() {
        currentField = 0;
    }
    SequentialAlgorithm(std::basic_ifstream<char, std::char_traits<char>> &&ifstream, unsigned int count = 1) {
        currentField = 0;
        fields[0] = Field(std::move(ifstream));
        fields[1] = Field(std::move(ifstream));
    }
    Field& getState(int roundsCount){
       for (int rounds = 0; rounds < roundsCount; ++rounds) {
           for (unsigned int i = 0; i < fields[currentField].getVerticalSize(); ++i) {
               for (unsigned int j = 0; j < fields[currentField].getHorizontalSize(); ++j) {
                   fields[currentField^1][i][j] = fields[currentField].getState(i, j);
               }
           }
           currentField ^= 1;
        }
        return fields[currentField^1];
    }
};


#endif //LIFE_SEQUENTIALALGORITHM_H
