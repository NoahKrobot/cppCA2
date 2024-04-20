#include <iostream>
#include "../headers/Bug.h"
#include <random>
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

char Bug::getType() const{
    return type;
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



bool Bug::isWayBlocked(){

    switch(Bug::getDirection()){
        //north
        case 1:{
            if (Bug::getPosition().getX() == 1){
                return true;
            }
            break;
        }

        //east
        case 2:{
            if (Bug::getPosition().getY() == 9){
                return true;
            }
            break;
        }

        //south
        case 3:{
            if (Bug::getPosition().getX() == 9){
                return true;
            }
            break;
        }

        //west
        case 4:{
            if (Bug::getPosition().getY()  == 1){
                return true;
            }
        }


        case 5: //northeast
            if(Bug::getPosition().getX()-1 == -1 || Bug::getPosition().getY()+1 == 10){
                return true;
            }
            break;
        case 6: //northwest
            if(Bug::getPosition().getX()-1 == -1 || Bug::getPosition().getY()-1 == -1){
                return true;
            }
            break;
        case 7: //southeast
            if(Bug::getPosition().getX()+1 == 10 || Bug::getPosition().getY()+1 == 10){
                return true;
            }
            break;
        case 8: //southwest
            if(Bug::getPosition().getX()+1 == 10 || Bug::getPosition().getY()-1 == -1){
                return true;
            }
            break;
    }












    return false;

}

