//
// Created by noah3 on 4/8/2024.
//

#include "../headers/Hopper.h"
#include <iostream>
#include <random>
using namespace std;

string Hopper::getBugDetails() {
    string detailsToPush;
    detailsToPush = to_string(id) + " Hopper (" + to_string(position.getX()) + "," + to_string(position.getY()) +
                 ") " + to_string(size) +" "+ to_string(direction) + " " + to_string(hopLength);
    if (alive){
        detailsToPush += " ALIVE ";
    } else {
        detailsToPush += " DEAD ";
    }
    return detailsToPush;
}

void Hopper::displayCrawlerDetails() {
    string details = getBugDetails();
    cout<<details<<endl;
}


