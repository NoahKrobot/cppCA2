//
// Created by noah3 on 4/8/2024.
//

#include "../headers/Crawler.h"
#include <iostream>
#include <random>
using namespace std;

Crawler::Crawler(char type, int id,int x,int y, int direction, int size, string stateIn){
    Pair coordinates(x,y);
    this->type = type;
    this->size = size;
    this->position = coordinates;
    this->direction = direction;
    this->id = id;
    this->state = stateIn;
}


void Crawler::move() {
// 1 north
// 2 east
// 3 south
// 4 west

    random_device rd;
    mt19937 gen(rd());

    switch (direction) {

        case 1: //x,y-1
            if (!isWayBlocked()) {
                int positionY1 = this->getPosition().getY();
                this->position.setY(positionY1 - 1);
            } else {
                uniform_int_distribution<> dist(2, 4);
                int randomInt = dist(gen);
                this->setDirection(randomInt);
            }
            break;
        case 2: //x+1,y
            if (!isWayBlocked()) {
                int positionX1 = this->getPosition().getX();
                this->position.setX(positionX1 + 1);
            } else {
                int numbers[] = {1, 3, 4};
                uniform_int_distribution<> dist(0, 2);
                int randomIndex = dist(gen);
                int randomNumber = numbers[randomIndex];
                cout<<"random number for east: "<<randomNumber<<endl;
                this->setDirection(randomNumber);
            }
            break;

        case 3: //x,y+1
            if (!isWayBlocked()) {
                int positionY2 = this->getPosition().getY();
                this->position.setY(positionY2 + 1);
            } else {
                int numbers[] = {1, 2, 4};
                uniform_int_distribution<> dist(0, 2);
                int randomIndex = dist(gen);
                int randomNumber = numbers[randomIndex];
                cout<<"random number for south: "<<randomNumber<<endl;
                this->setDirection(randomNumber);
            }
            break;
        case 4: //x-1,y
            if (!isWayBlocked()) {
                int positionX2 = this->getPosition().getX();
                this->position.setX(positionX2 - 1);
            } else {
                uniform_int_distribution<> dist(1, 3);
                int randomInt = dist(gen);
                cout<<"random number for west: "<<randomInt<<endl;
                this->setDirection(randomInt);
            }
            break;
    }

    path.push_back(position);
}



string Crawler::getBugDetails() {
    string detailsToPush;

    detailsToPush = to_string(id) + " Crawler(" + to_string(position.getX()) + "," + to_string(position.getY()) +
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

