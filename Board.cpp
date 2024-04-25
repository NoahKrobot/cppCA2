//
// Created by noah3 on 4/16/2024.
//

#include <vector>
#include <iostream>
#include <fstream>
#include "headers/Board.h"
#include "headers/Bug.h"
#include <random>
#include <synchapi.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>


void Board::displayAllBugs(sf::RenderWindow& window, const vector<Bug*>& bug_vector, int size) {
    sf::Font font;
    if (!font.loadFromFile("C:/Users/noah3/OneDrive/CAs/cppCA2/Roboto-Medium.ttf")) {
        std::cerr << "Error loading font\n";
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);

    for (int i = 0; i < size; i++) {
        string bug_info = "id: " + to_string(bug_vector.at(i)->getId()) + "\n"
                          + "direction: " + to_string(bug_vector.at(i)->getDirection()) + "\n"
                          + "X position: " + to_string(bug_vector.at(i)->getPosition().getX()) + "\n"
                          + "Y position: " + to_string(bug_vector.at(i)->getPosition().getY()) + "\n"
                          + "alive: " + (bug_vector.at(i)->getAlive() ? "true" : "false") + "\n"
                          + "size: " + to_string(bug_vector.at(i)->getSize()) + "\n";

        text.setString(bug_info);

        if(i%2==0){
            text.setPosition(200, 50+ (i * 100 ));
        }else{
            text.setPosition(400, 50+ ((i-1) * 100 ));
        }
        window.draw(text);
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


//Tutorial sleep: https://stackoverflow.com/questions/10807681/loop-every-10-second
void Board::tapBugBoard(const vector<Bug *> &bug_vector, int size) {

    vector<Bug *> bug_vectorEat;
    vector<Bug *> bug_vectorBigEquals;
    //check if there's more than 1 bug alive:
    int aliveCount = 0;
    while (aliveCount < 1) {
        aliveCount++;
        for (int bugAliveCount = 0; bugAliveCount < size; bugAliveCount++) {
            if(bug_vector.at(bugAliveCount)->getAlive()){
                aliveCount++;
            }
        }

        //move bugs
        cout << endl;
        cout << "Tapping the Bug Board..." << endl;
        for (int i = 0; i < size; i++) {
            bug_vector.at(i)->move();
            cout << endl;
        }

        //eat
        for (int j = 0; j < size; j++) {
            bug_vectorEat.clear();

            int x = bug_vector.at(j)->getPosition().getX();
            int y = bug_vector.at(j)->getPosition().getY();
            int id = bug_vector.at(j)->getId();

            bug_vectorEat.push_back(bug_vector.at(j));


            for (int k = 0; k < size; k++) {
                int x2 = bug_vector.at(k)->getPosition().getX();
                int y2 = bug_vector.at(k)->getPosition().getY();
                int id2 = bug_vector.at(k)->getId();
                int bugSize2 = bug_vector.at(k)->getSize();
                if (id2 != id) {
                    if (x == x2 && y == y2) {
                        bug_vectorEat.push_back(bug_vector.at(k));
                    }
                }
            }
            int maxBugSize =0;
            int finalSizeForBigBug = 0;
            //find the biggest one
            for(int i = 0; i< bug_vectorEat.size();i++){
                maxBugSize = bug_vectorEat.at(i)->getSize();
                for(int j=0;j<bug_vectorEat.size();j++){
                    if(maxBugSize < bug_vectorEat.at(j)->getSize()){
                        maxBugSize= bug_vectorEat.at(j)->getSize();
                    }
                }
            }

            //unalive every bug that sized less than max,
            //but add the others to another vector

            for(int k=0;k<bug_vectorEat.size();k++){
                if(bug_vectorEat.at(k)->getSize()<maxBugSize){
                    finalSizeForBigBug = finalSizeForBigBug+ bug_vectorEat.at(k)->getSize();
                    bug_vectorEat.at(k)->setAlive(false);
                } if(bug_vectorEat.at(k)->getSize() == maxBugSize){
                    bug_vectorBigEquals.push_back(bug_vectorEat.at(k));
                }
            }

            for(int q=0; q<bug_vectorBigEquals.size();q++){

            }

            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dist(0, bug_vectorBigEquals.size());
            int randomInt = dist(gen);

            for(int randoms=0; randoms<bug_vectorBigEquals.size();randoms++){
                if(randomInt != randoms){
                    bug_vectorBigEquals.at(randoms)->setAlive(false);
                    finalSizeForBigBug = finalSizeForBigBug+ bug_vectorBigEquals.at(randoms)->getSize();
                }else{
                    bug_vectorBigEquals.at(randoms)->setSize(bug_vectorBigEquals.at(randoms)->getSize() +  finalSizeForBigBug);
                }
            }
            //add method to check every id as well
        }
        Sleep(10000);
    }
}

//Tutorial: auto iterator
//https://stackoverflow.com/questions/3434256/use-the-auto-keyword-in-c-stl

void Board::displayLifeHistory(const vector<Bug *> &bug_vector, int size) {
    cout << historyMainFunction(bug_vector, size) << endl;
}

//Tutorial: getting date and time: https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
void Board::exitProgram(const vector<Bug *> &bug_vector, int size) {
    string toPasteInFile = historyMainFunction(bug_vector, bug_vector.size());
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string filename = "../bugs_life_history_" + to_string(ltm->tm_mday)
                      + "-"
                      + to_string(1 + ltm->tm_mon)
                      + "-"
                      + to_string(1900 + ltm->tm_year)
                      + "-"
                      + to_string(ltm->tm_hour)
                      + "-"
                      + to_string(ltm->tm_min)
                      + "-"
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

}

string Board::historyMainFunction(const vector<Bug *> &bug_vector, int size) {
    list<int>::iterator it;
    string bugStringLine;
    for (int i = 0; i < size; i++) {
        bugStringLine += "\n";

        bugStringLine += to_string(bug_vector.at(i)->getId());

        if (bug_vector.at(i)->getType() == 'C') {
            bugStringLine += " Crawler Path:";
        }
        else if (bug_vector.at(i)->getType() == 'H') {
            bugStringLine += " Hopper Path:";
        } else if (bug_vector.at(i)->getType() == 'D') {
            bugStringLine += " El Diagonal Path:";
        }

        for (auto it = bug_vector.at(i)->getPath().begin(); it != bug_vector.at(i)->getPath().end(); it++) {
            bugStringLine += "(";
            bugStringLine += to_string(it->getX());
            bugStringLine += ",";
            bugStringLine += to_string(it->getY());
            bugStringLine += "), ";
        }

        bugStringLine += bug_vector.at(i)->getState();


    }
    return bugStringLine;
}