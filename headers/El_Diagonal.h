//
// Created by noah3 on 4/8/2024.
//

#ifndef CPPCA2_EL_DIAGONAL_H
#define CPPCA2_EL_DIAGONAL_H

#include <string>
#include "Bug.h"
class El_Diagonal : public Bug{

    void displayEl_DiagonalDetails();

    string getBugDetails();

    void move();

    void updatePositionDependingOnDirection(int direction);
};


#endif //CPPCA2_EL_DIAGONAL_H
