//
// Created by noah3 on 4/8/2024.
//

#ifndef CPPCA2_EL_DIAGONAL_H
#define CPPCA2_EL_DIAGONAL_H

#include <string>
#include "Bug.h"
class El_Diagonal : public Bug{
public:
    void displayEl_DiagonalDetails();
    string getBugDetails();
    void move();
    void updatePositionDependingOnDirection(int direction);
    El_Diagonal(char type, int id, int xValue, int yValue, int direction, int size);
};

#endif //CPPCA2_EL_DIAGONAL_H
