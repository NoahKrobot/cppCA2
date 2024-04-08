//
// Created by noah3 on 4/8/2024.
//

#include "../headers/Crawler.h"
#include <iostream>
#include <random>
using namespace std;

void Crawler::move() {


    random_device rd;
    mt19937 gen(rd());
    switch (direction) {
        case 1: //north
            if(!isWayBlocked()){
                updatePositionDependingOnDirection(1);
            }else{
               uniform_int_distribution<> dist(2, 4);
               int randomInt = dist(gen);
               updatePositionDependingOnDirection(randomInt);
            }
            break;
        case 2: //east
            if(!isWayBlocked()){
                updatePositionDependingOnDirection(1);
            }else{

                int numbers[] = {1, 3, 4};
                uniform_int_distribution<> dist(0, 2);
                int randomIndex = dist(gen);
                int randomNumber = numbers[randomIndex];
                updatePositionDependingOnDirection(randomNumber);
            }
            break;
        case 3: //south
            if(!isWayBlocked()){
                updatePositionDependingOnDirection(3);
            }else{

                int numbers[] = {1, 2, 4};
                uniform_int_distribution<> dist(0, 2);
                int randomIndex = dist(gen);
                int randomNumber = numbers[randomIndex];
                updatePositionDependingOnDirection(randomNumber);
            }
            break;
        case 4: //west
            if(!isWayBlocked()){
                updatePositionDependingOnDirection(4);
            }else{
                uniform_int_distribution<> dist(1, 3);
                int randomInt = dist(gen);
                updatePositionDependingOnDirection(randomInt);
            }
            break;
    }
}

void Crawler::updatePositionDependingOnDirection(int direction){
    switch (direction) {
        case 1: //north
            position.setX(position.getX() - 1);
            break;
        case 2: //east
            position.setY(position.getY() + 1);
            break;
        case 3: //south
            position.setX(position.getX() + 1);
            break;
        case 4: //west
            position.setY(position.getY() - 1);
            break;
    }
};


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

void Crawler::displayCrawlerDetails() {
    string details = getBugDetails();
    cout<<details<<endl;
}

