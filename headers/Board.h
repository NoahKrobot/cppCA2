//
// Created by noah3 on 4/16/2024.
//

#ifndef CPPCA2_BOARD_H
#define CPPCA2_BOARD_H


#include "Bug.h"

class Board {

public:
    void displayAllBugs(const vector<Bug *> &bug_vector, int size);
    void findBugById(const vector<Bug *> &bug_vector, int size);
    void displayLifeHistory(const vector<Bug *> &bug_vector, int size);
    void exitProgram(const vector<Bug *> &bug_vector, int size);
    string historyMainFunction(const vector<Bug *> &bug_vector, int size);


    void tapBugBoard(const vector<Bug *> &bug_vector, int size);
};


#endif //CPPCA2_BOARD_H
