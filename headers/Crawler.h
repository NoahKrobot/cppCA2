//
// Created by noah3 on 4/8/2024.
//

#ifndef CPPCA2_CRAWLER_H
#define CPPCA2_CRAWLER_H

#include <string>
#include "Bug.h"
class Crawler : public Bug {
public:
    string getBugDetails();
    void displayCrawlerDetails();
    void move() override;
    void updatePositionDependingOnDirection(int direction);
    Crawler(char type, int id, int xValue, int yValue, int direction, int size, string state);
};


#endif //CPPCA2_CRAWLER_H
