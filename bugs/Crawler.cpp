//
// Created by noah3 on 4/8/2024.
//

#include "../headers/Crawler.h"

string Crawler::getBugDetails() {
    string detailsToPush;

    detailsToPush = to_string(id) + " CRAWLER (" + to_string(position.getX()) + "," + to_string(position.getY()) +
                 ") " + to_string(size) +" "+ to_string(direction);
    if (alive){
        detailsToPush += " ALIVE";
    } else {
        detailsToPush += " DEAD";
    }

    return detailsToPush;
}


