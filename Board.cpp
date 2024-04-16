//
// Created by noah3 on 4/16/2024.
//

#include <vector>
#include <iostream>
#include "headers/Board.h"
#include "headers/Bug.h"


void Board::displayAllBugs(const vector<Bug *> &bug_vector, int size) {
    cout << "Displaying all Bugs..." << endl;

    for (int i = 0; i < size; i++) {
        cout << "id: " << bug_vector.at(i)->getId() << endl;
        cout << "direction: " << bug_vector.at(i)->getDirection() << endl;
        cout << "X position: " << bug_vector.at(i)->getPosition().getX() << endl;
        cout << "Y position: " << bug_vector.at(i)->getPosition().getY() << endl;
        cout << "alive: " << bug_vector.at(i)->getAlive() << endl;
        cout << "size: " << bug_vector.at(i)->getSize() << endl;
        cout << endl;
        cout << endl;
    }
}

void Board::findBugById(const vector<Bug *> &bug_vector, int size) {
    cout << "Finding a Bug by ID..." << endl;
    cout << "Enter bug id to find: ";
    int userID;
    cin >> userID;
    bool idFound = false;
    cout << endl;

    for (int i = 0; i < size; i++) {
        int id = bug_vector.at(i)->getId();
        if (id == userID) {
            cout << "id: " << bug_vector.at(i)->getId() << endl;
            cout << "direction: " << bug_vector.at(i)->getDirection() << endl;
            cout << "X position: " << bug_vector.at(i)->getPosition().getX() << endl;
            cout << "Y position: " << bug_vector.at(i)->getPosition().getY() << endl;
            cout << "alive: " << bug_vector.at(i)->getAlive() << endl;
            cout << "size: " << bug_vector.at(i)->getSize() << endl;
            idFound = true;
        }
    }

    if (!idFound) {
        cout << "Bug not found." << endl;
    }
    cout << endl;
    cout << endl;
}

void Board::tapBugBoard(const vector<Bug *> &bug_vector, int size) {
    cout<< endl;
    cout << "Tapping the Bug Board..." << endl;
    for (int i = 0; i < size; i++) {
        bug_vector[i]->move();
        cout<< endl;
    }
}




//Tutorial: auto iterator
        //https://stackoverflow.com/questions/3434256/use-the-auto-keyword-in-c-stl

void Board::displayLifeHistory(const vector<Bug *> &bug_vector, int size) {
    list<int>::iterator it;

    for(int i = 0; i<size;i++){
        string bugStringLine ="";

        bugStringLine+= to_string(bug_vector.at(i)->getId());

        if(bug_vector.at(i)->getType() == 'C'){
            bugStringLine+= " Crawler Path:";
        }else if(bug_vector.at(i)->getType() == 'H'){
            bugStringLine+= " Hopper Path:";
        }else{
            bugStringLine+= " El Diagonal Path:";
        }

            for (auto it = bug_vector.at(i)->getPath().begin(); it != bug_vector.at(i)->getPath().end(); it++) {
                bugStringLine+= "(";
                bugStringLine+= to_string(it->getX());
                bugStringLine+= ",";
                bugStringLine+= to_string(it->getY());
                bugStringLine+= "), ";
            }

            cout<<bugStringLine<<endl;
    }
}