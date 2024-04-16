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