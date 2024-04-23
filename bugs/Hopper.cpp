//
// Created by noah3 on 4/8/2024.
//

#include "../headers/Hopper.h"
#include <iostream>
#include <random>
using namespace std;

Hopper::Hopper(char type, int id,int x,int y, int direction, int size, int hopLength, string stateIn){
    Pair coordinates(x,y);
    this->type = type;
    this->size = size;
    this->position = coordinates;
    this->direction = direction;
    this->id = id;
    this->hopLength = hopLength;
    this->state = stateIn;

}

void Hopper::move() {
    random_device rd;
    mt19937 gen(rd());
    int calculationNorth = getPosition().getY() - hopLength;
    int calculationSouth = getPosition().getY() + hopLength;
    int calculationWest = getPosition().getX() - hopLength;
    int calculationEast = getPosition().getX() + hopLength;

    int currentPositionX= 0;
    int currentPositionY= 0;

    switch (direction) {

        case 1: //north
            if(isWayBlocked() || calculationNorth <1){
                uniform_int_distribution<> dist(2, 4);
                int randomInt = dist(gen);
                setDirection(randomInt);
//                updatePositionDependingOnDirection(randomInt, hopLength);
            }else if(!isWayBlocked()){
//             updatePositionDependingOnDirection(1,hopLength);
                currentPositionY =  position.getY() -hopLength;
                position.setY(currentPositionY);
            }
            break;
        case 2: //east
            if(isWayBlocked() || calculationEast >9){
                int numbers[] = {1, 3, 4};
                uniform_int_distribution<> dist(0, 2);
                int randomIndex = dist(gen);
                int randomNumber = numbers[randomIndex];
                setDirection(randomNumber);

//                updatePositionDependingOnDirection(randomNumber, hopLength);
            }else if(!isWayBlocked()){
//                updatePositionDependingOnDirection(2,hopLength);
            currentPositionX = position.getX() + hopLength;
            position.setX(currentPositionX);
            }
            break;
        case 3: //south
            if(isWayBlocked() || calculationSouth>9){
                int numbers[] = {1, 2, 4};
                uniform_int_distribution<> dist(0, 2);
                int randomIndex = dist(gen);
                int randomNumber = numbers[randomIndex];
//                updatePositionDependingOnDirection(randomNumber, hopLength);
                setDirection(randomNumber);
            }else if(!isWayBlocked()){
//                updatePositionDependingOnDirection(3,hopLength);
                currentPositionY =  position.getY() +hopLength;
                position.setY(currentPositionY);
            }

            break;
        case 4: //west
            if(isWayBlocked() || calculationWest <1){
                uniform_int_distribution<> dist(1, 3);
                int randomInt = dist(gen);
                setDirection(randomInt);
//                updatePositionDependingOnDirection(randomInt, hopLength);
            }else if(!isWayBlocked()){
//                updatePositionDependingOnDirection(4,hopLength);
                currentPositionX = position.getX() - hopLength;
                position.setX(currentPositionX);
            }
            break;
    }
    path.push_back(position);
}

//void Hopper::updatePositionDependingOnDirection(int direction, int hop){
//    switch (direction) {
//        case 1: //north
//            position.setX(position.getX() - hop);
//            break;
//        case 2: //east
//            position.setY(position.getY() + hop);
//            break;
//        case 3: //south
//            position.setX(position.getX() + hop);
//            break;
//        case 4: //west
//            position.setY(position.getY() - hop);
//            break;
//    }
//};




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


