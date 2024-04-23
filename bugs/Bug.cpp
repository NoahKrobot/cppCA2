#include <iostream>
#include "../headers/Bug.h"
#include <random>

// getters
int Bug::getId() const {
    return id;
}

const Pair Bug::getPosition() const {
    return position;
}

int Pair::getX() const {
    return toPushX;
}

int Pair::getY() const {
    return toPushY;
}

int Bug::getSize() const {
    return size;
}

bool Bug::getAlive() const {
    return alive;
}

int Bug::getDirection() const {
    return direction;
}

string Bug::getState() const {
    return state;
}

char Bug::getType() const {
    return type;
}

const list<Pair> &Bug::getPath() {
    return path;
}

// setters

void Bug::setPosition(const Pair &pos) {
    Bug::position = pos;
}

void Bug::setSize(int size) {
    Bug::size = size;
}

void Bug::setState(string stateIn) {
    Bug::state = state;
}

void Bug::setAlive(bool alive) {
    Bug::alive = alive;
}

void Bug::setDirection(int directionVariable) {
    Bug::direction = directionVariable;
}


bool Bug::isWayBlocked() {
    cout << "Direction: " << Bug::getDirection() << endl;


    if (Bug::getType() == 'C' ) {

        switch (Bug::getDirection()) {
            //north
            case 1: {
                if (Bug::getPosition().getY() == 1) {
                    return true;
                }
                break;
            }

                //east
            case 2: {
                if (Bug::getPosition().getX() == 9) {
                    return true;
                }
                break;
            }

                //south
            case 3: {
                if (Bug::getPosition().getY() == 9) {
                    return true;
                }
                break;
            }

                //west
            case 4: {
                if (Bug::getPosition().getX() == 1) {
                    return true;
                }
            }

        }
    } else if(Bug::getType() == 'H') {

        switch (Bug::getDirection()) {
            //north
            case 1: {
                if (Bug::getPosition().getY() == 1) {
                    return true;
                }
                break;
            }

                //east
            case 2: {
                if (Bug::getPosition().getX() == 9) {
                    return true;
                }
                break;
            }

                //south
            case 3: {
                if (Bug::getPosition().getY() == 9) {
                    return true;
                }
                break;
            }

            //west
            case 4: {
                if (Bug::getPosition().getX() == 1) {
                    return true;
                }
            }
        }
    }else{

        switch (Bug::getDirection()) {

            case 5: //northeast x+1, y-1
                if (Bug::getPosition().getY() == 1 || Bug::getPosition().getX() == 9) {
                    return true;
                }
                break;
            case 6: //northwest x-1, y-1
                if (Bug::getPosition().getY() == 1 || Bug::getPosition().getX() == 1) {
                    return true;
                }
                break;
            case 7: //southeast x+1, y+1
                if (Bug::getPosition().getY() == 9 || Bug::getPosition().getX() == 9) {
                    return true;
                }
                break;
            case 8: //southwest x-1, y+1
                if (Bug::getPosition().getY() == 9 || Bug::getPosition().getX() == 1) {
                    return true;
                }
                break;
        }

    }

    return false;

}


