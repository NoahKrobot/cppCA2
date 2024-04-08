//
// Created by noah3 on 4/8/2024.
//

#ifndef CPPCA2_BUG_H
#define CPPCA2_BUG_H
#include <list>

using namespace std;

struct Pair {
    int getX() const;
    int getY() const;

    int toPushX;
    int toPushY;

    void setX(int inputX){
        toPushX = inputX;
    }

    void setY(int inputY){
        toPushY=inputY;
    }

    Pair(int userInputX, int userInputY){
        toPushX = userInputX;
        toPushY = userInputY;
    }
};



class Bug {
protected:
    Pair position = Pair(0,0);
    int size;
    bool alive;
    int direction;
    list<Pair> path;
    int id;
public:
    bool isWayBlocked();
    virtual void move();

    int getId() const;

    const Pair getPosition() const;

    int getSize() const;

    bool getAlive() const;

    int getDirection() const;

    const list<Pair> &getPath();

    void setAlive(bool alive);

    void setSize(int size);

    void setPosition(const Pair &pos);


};


#endif //CPPCA2_BUG_H
