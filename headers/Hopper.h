//
// Created by noah3 on 4/8/2024.
//

#ifndef CPPCA2_HOPPER_H
#define CPPCA2_HOPPER_H

#include <string>
#include "Bug.h"
class Hopper : public Bug{

private:
    int hopLength;

public:


    std::__cxx11::basic_string<char> getBugDetails();

    void displayCrawlerDetails();
};


#endif //CPPCA2_HOPPER_H
