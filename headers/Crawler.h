//
// Created by noah3 on 4/8/2024.
//

#ifndef CPPCA2_CRAWLER_H
#define CPPCA2_CRAWLER_H

#include <string>
#include "Bug.h"
class Crawler : public Bug {
public:
    string getBugDetails() override;
    void displayBug() override;
    void move() override;
    Crawler(int id, int x, int y, int direction, int size, bool alive);

};


#endif //CPPCA2_CRAWLER_H
