#include <iostream>
#include "../headers/Bug.h"

// getters
int Bug::getId() const {
    return id;
}

const Pair Bug::getPosition() const{
    return position;
}

int Pair::getX() const {
    return toPushX;
}

int Pair::getY() const {
    return toPushY;
}

int Bug::getSize() const{
    return size;
}

bool Bug::getAlive() const{
    return alive;
}

int Bug::getDirection() const{
    return direction;
}

const list<Pair> & Bug::getPath()  {
    return path;
}

// setters

void Bug::setPosition(const Pair &pos) {
    Bug::position = pos;
}

void Bug::setSize(int size) {
    Bug::size = size;
}

void Bug::setAlive(bool alive) {
    Bug::alive = alive;
}














bool isWayBlocked(){

}

