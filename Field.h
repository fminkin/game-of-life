//
// Created by fedor on 10/15/16.
//

#ifndef LIFE_FIELD_H
#define LIFE_FIELD_H
#include<vector>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <string>

class Field {
private:
    class Field1D {
    public:
        std::vector<bool> a;
        std::vector<bool>::reference operator [](int j){
            return a[(j + a.size()) % a.size()];
        }
        Field1D() {}
        void resize(int n) {
            a.resize(n);
        }
        void push_back(bool element) {
            a.push_back(static_cast<bool>(element));
        }
        int size() {
            return a.size();
        }
    };
    char getSymbol(bool a) {
        return a ? 'o' : ' ';

    }
public:
    std::vector<Field1D> data;
    Field() {}
    Field(std::basic_ifstream<char, std::char_traits<char>> &&ifstream) {
        ifstream.clear();
        ifstream.seekg(0);
        int n = 0, m = 0;
        ifstream >> n >> m;
        data.resize(n);
        std::string s;
        for (int i = 0; i < n; ++i) {
            ifstream >> s;
            for (int j = 0; j < m; ++j){
                data[i].push_back(s[j] != '0');
            }

        }
    }
    Field1D& operator[] (int i) {
        return data[(i + data.size()) % data.size()];
    }
    
    int getVerticalSize() {
        return data.size();
    }
    int getHorizontalSize() {
        return data[0].size();
    }
    void getLog(std::basic_ofstream<char, std::char_traits<char>> &&ofstream) {
        for (int i = 0; i < getVerticalSize(); ++i) {
            for (int j = 0; j < getHorizontalSize(); ++j) {
                ofstream << getSymbol(data[i][j]) << ' ';
            }
            ofstream << std::endl;
        }
    }
    bool getState(int i, int j) {
        int aliveCount = 0;
        for (int dx = -1; dx < 2; ++dx) {
            for (int dy = -1; dy < 2; ++dy) {
                if (dx == dy) {
                    continue;
                }
                if ((*this)[i + dy][j + dx]) {
                    aliveCount++;
                }
            }
        }
        if ((*this)[i][j]) {
            return !(aliveCount < 2 || aliveCount > 3);
        } else {
            return aliveCount == 3;
        }

    }

};

#endif //LIFE_FIELD_H
