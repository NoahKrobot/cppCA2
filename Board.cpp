//
// Created by noah3 on 4/16/2024.
//

#include <vector>
#include <iostream>
#include <fstream>
#include "headers/Board.h"
#include "headers/Bug.h"
#include <random>

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
        bug_vector.at(i)->move();
        cout<< endl;
    }

    for(int j=0;j<size;j++){
        int x = bug_vector.at(j)->getPosition().getX();
        int y = bug_vector.at(j)->getPosition().getY();
        int id = bug_vector.at(j)->getId();
        int bugSize = bug_vector.at(j)->getSize();
        for(int k=0;k<size;k++){
            int x2 = bug_vector.at(k)->getPosition().getX();
            int y2 = bug_vector.at(k)->getPosition().getY();
            int id2 = bug_vector.at(k)->getId();
            int bugSize2 = bug_vector.at(k)->getSize();
            if(id2!=id){
                if(x == x2 && y ==y2){
                    if(bugSize==bugSize2){
                        random_device rd;
                        mt19937 gen(rd());
                        uniform_int_distribution<> dist(1, 2);
                        int randomInt = dist(gen);
                        if(randomInt ==1){
                            bug_vector.at(j)->setAlive(false);
                        }else{
                            bug_vector.at(k)->setAlive(false);
                        }
                    }else if(bugSize<bugSize2){
                        bug_vector.at(j)->setAlive(false);
                    }else{
                        bug_vector.at(k)->setAlive(false);
                    }
                }
            }
        }
    }
}




//Tutorial: auto iterator
        //https://stackoverflow.com/questions/3434256/use-the-auto-keyword-in-c-stl

void Board::displayLifeHistory(const vector<Bug *> &bug_vector, int size) {
    cout<<historyMainFunction(bug_vector, size)<<endl;
}


//Tutorial: getting date and time: https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
void Board::exitProgram(const vector<Bug *> &bug_vector, int size) {
    string toPasteInFile = historyMainFunction(bug_vector, size);
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string filename = "../bugs_life_history_" + to_string(ltm->tm_mday)
                                                +"-"
                                                + to_string(1 + ltm->tm_mon)
                                                  +"-"
                                                  + to_string(1900 + ltm->tm_year)
                                                    +"-"
                                                    + to_string(ltm->tm_hour)
                                                      +"-"
                                                      + to_string(ltm->tm_min)
                                                        +"-"
                                                        + to_string(ltm->tm_sec)
            + ".txt";
    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << toPasteInFile;
        outFile.close();
        cout << "bug path history written to: " << filename << endl;
    } else {
        cout << "Error creating history file" << endl;
    }
//    else {
//       cout<<"error creating history file"<<endl;
//    }

}

string Board::historyMainFunction(const vector<Bug *> &bug_vector, int size){
    list<int>::iterator it;
    string bugStringLine;
    for(int i = 0; i<size;i++){
        bugStringLine+= "\n";

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

    }
    return bugStringLine;
}