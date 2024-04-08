//
// Created by noah3 on 4/8/2024.
//

#include "../headers/Hopper.h"
#include <iostream>
#include <random>
using namespace std;


void Hopper::move() {
    random_device rd;
    mt19937 gen(rd());
    switch (direction) {
        case 1: //north
            if(isWayBlocked() || getPosition().getX() -hopLength <0 || getPosition().getX() ==0){
                uniform_int_distribution<> dist(2, 4);
                int randomInt = dist(gen);
                updatePositionDependingOnDirection(randomInt, hopLength);
            }else if(!isWayBlocked()){
             updatePositionDependingOnDirection(1,hopLength);
            }
            break;
        case 2: //east
            if(isWayBlocked() || getPosition().getX() -hopLength >9 || getPosition().getX() ==9){
                int numbers[] = {1, 3, 4};
                uniform_int_distribution<> dist(0, 2);
                int randomIndex = dist(gen);
                int randomNumber = numbers[randomIndex];
                updatePositionDependingOnDirection(randomNumber, hopLength);
            }else if(!isWayBlocked()){
                updatePositionDependingOnDirection(2,hopLength);
            }
            break;
        case 3: //south
            if(isWayBlocked() || getPosition().getX() -hopLength >9 || getPosition().getX() ==9){
                int numbers[] = {1, 2, 4};
                uniform_int_distribution<> dist(0, 2);
                int randomIndex = dist(gen);
                int randomNumber = numbers[randomIndex];
                updatePositionDependingOnDirection(randomNumber, hopLength);
            }else if(!isWayBlocked()){
                updatePositionDependingOnDirection(3,hopLength);
            }
            break;
        case 4: //west
            if(isWayBlocked() || getPosition().getX() -hopLength <0 || getPosition().getX() ==0){
                uniform_int_distribution<> dist(1, 3);
                int randomInt = dist(gen);
                updatePositionDependingOnDirection(randomInt, hopLength);
            }else if(!isWayBlocked()){
                updatePositionDependingOnDirection(4,hopLength);
            }
            break;
    }
    path.push_back(position);
}

void Hopper::updatePositionDependingOnDirection(int direction, int hop){
    switch (direction) {
        case 1: //north
            position.setX(position.getX() - hop);
            break;
        case 2: //east
            position.setY(position.getY() + hop);
            break;
        case 3: //south
            position.setX(position.getX() + hop);
            break;
        case 4: //west
            position.setY(position.getY() - hop);
            break;
    }
};




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


