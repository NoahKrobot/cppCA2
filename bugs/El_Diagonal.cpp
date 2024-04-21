//
// Created by noah3 on 4/8/2024.
//


//directions are: 5,6,7,8
//5 = northeast
//6 = northwest
//7 = southeast
//8 = southwest
#include "../headers/El_Diagonal.h"
#include <iostream>
#include <random>
using namespace std;

El_Diagonal::El_Diagonal(char type, int id,int x,int y, int direction, int size){
    Pair coordinates(x,y);
    this->size = size;
    this->alive = true;
    this->position = coordinates;
    this->direction = direction;
    this->id = id;
}

void El_Diagonal::move() {



    random_device rd;
    mt19937 gen(rd());
    int positionY =this->getPosition().getY();;
    int positionX =this->getPosition().getX();;

    switch (direction) {

        case 5: //northeast x+1, y-1
            if (!isWayBlocked()) {
                this->position.setX(positionX + 1);
                this->position.setY(positionY - 1);
            } else {
                uniform_int_distribution<> dist(6, 8);
                int randomInt = dist(gen);
                this->setDirection(randomInt);
            }
            break;
        case 6: //northwest x-1, y-1
            if (!isWayBlocked()) {
                this->position.setX(positionX - 1);
                this->position.setY(positionY - 1);
            } else {
                int numbers[] = {5, 7, 8};
                uniform_int_distribution<> dist(0, 2);
                int randomIndex = dist(gen);
                int randomNumber = numbers[randomIndex];
                this->setDirection(randomNumber);
            }
            break;

        case 7: //southeast x+1, y+1
            if (!isWayBlocked()) {
                this->position.setX(positionX + 1);
                this->position.setY(positionY + 1);
            } else {
                int numbers[] = {5, 6, 8};
                uniform_int_distribution<> dist(0, 2);
                int randomIndex = dist(gen);
                int randomNumber = numbers[randomIndex];
                this->setDirection(randomNumber);
            }
            break;
        case 8: //southwest x-1, y+1
            if (!isWayBlocked()) {
                this->position.setX(positionX - 1);
                this->position.setY(positionY + 1);
            } else {
                uniform_int_distribution<> dist(5, 7);
                int randomInt = dist(gen);
                this->setDirection(randomInt);
            }
            break;
    }







//    random_device rd;
//    mt19937 gen(rd());
//    switch (direction) {
//        case 5: //north
//            if(!isWayBlocked()){
//                updatePositionDependingOnDirection(5);
//            }else{
//                uniform_int_distribution<> dist(6, 8);
//                int randomInt = dist(gen);
//                updatePositionDependingOnDirection(randomInt);
//            }
//            break;
//        case 6: //east
//            if(!isWayBlocked()){
//                updatePositionDependingOnDirection(6);
//            }else{
//
//                int numbers[] = {5, 7, 8};
//                uniform_int_distribution<> dist(0, 2);
//                int randomIndex = dist(gen);
//                int randomNumber = numbers[randomIndex];
//                updatePositionDependingOnDirection(randomNumber);
//            }
//            break;
//        case 7: //south
//            if(!isWayBlocked()){
//                updatePositionDependingOnDirection(7);
//            }else{
//
//                int numbers[] = {5, 6, 8};
//                uniform_int_distribution<> dist(0, 2);
//                int randomIndex = dist(gen);
//                int randomNumber = numbers[randomIndex];
//                updatePositionDependingOnDirection(randomNumber);
//            }
//            break;
//        case 8: //west
//            if(!isWayBlocked()){
//                updatePositionDependingOnDirection(8);
//            }else{
//                uniform_int_distribution<> dist(5, 7);
//                int randomInt = dist(gen);
//                updatePositionDependingOnDirection(randomInt);
//            }
//            break;
//    }
//    path.push_back(position);
}


void El_Diagonal::updatePositionDependingOnDirection(int direction){
    switch (direction) {
        case 5: //northeast
            position.setX(position.getX() - 1); //north
            position.setY(position.getY() + 1); //east
            break;
        case 6: //northwest
            position.setX(position.getX() - 1); //north
            position.setY(position.getY() - 1); //west
            break;
        case 7: //southeast
            position.setX(position.getX() + 1); //south
            position.setY(position.getY() + 1); //east

            break;
        case 8: //southwest
            position.setX(position.getX() + 1); //south
            position.setY(position.getY() - 1); //west
            break;
    }
};

string El_Diagonal::getBugDetails() {
    string detailsToPush;

    detailsToPush = to_string(id) + " El Diagonal (" + to_string(position.getX()) + "," + to_string(position.getY()) +
                    ") " + to_string(size) +" "+ to_string(direction);
    if (alive){
        detailsToPush += " ALIVE";
    } else {
        detailsToPush += " DEAD";
    }
    return detailsToPush;
}

void El_Diagonal::displayEl_DiagonalDetails() {
    string details = getBugDetails();
    cout<<details<<endl;
}

