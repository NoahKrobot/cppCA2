//for sfml i used tutorials from this website: https://www.sfml-dev.org/tutorials/2.6/
// https://en.sfml-dev.org/forums/index.php?topic=22084.0


#include <iostream>
#include "headers/Bug.h"
#include <vector>
#include <fstream>
#include <sstream>
#include "headers/Crawler.h"
#include "headers/Hopper.h"
#include "headers/El_Diagonal.h"
#include "headers/Board.h"

#include <SFML/Graphics.hpp>
#include <synchapi.h>
#include <random>

using namespace std;

void initializeBugBoard();

void displayLifeHistory();

void displayAllCells();

void runSimulation();

void exitProgram();

void readBugsFromFile(vector<Bug *> &bug_vector, const string &file_name);


sf::Font font;

struct Tile {
    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    int getPopulated() const {
        return populated;
    }

    void setPopulation(int population) {
        populated = population;
    }

    int x;
    int y;
    int populated;
    //0 - empty
    //1 - crawler - red
    //2 - hopper - blue
    //3 - el diagonal - yellow

    Tile(int inputX, int inputY, int populationType) {
        x = inputX;
        y = inputY;
        populated = populationType;
    }

};


int main() {


    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML Application");


    //bug vector
    vector<Bug *> bug_vectorEat;
    vector<Bug *> bug_vectorBigEquals;
    vector<Bug *> bug_vectorSmallBugs;

    vector<Bug *> bug_vector;

    Crawler *craw = new Crawler('C', 1, 5, 5, 1, 3, "ALIVE");
    bug_vector.push_back(craw);
    Hopper *hopp = new Hopper('H', 2, 2, 2, 4, 4, 2, "ALIVE");
    bug_vector.push_back(hopp);
    El_Diagonal *eldi = new El_Diagonal('E', 3, 3, 3, 5, 7, "ALIVE");
    bug_vector.push_back(eldi);

    Crawler *craw2 = new Crawler('C', 4, 8, 7, 1, 3, "ALIVE");
    bug_vector.push_back(craw2);

    //tiles vector
    vector<Tile> tiles;
    int typeOfPupulationNumber = 0;
    char typeOfBugCheck = ' ';


    sf::Font font;
    if (!font.loadFromFile("C:/Users/noah3/OneDrive/CAs/cppCA2/Roboto-Medium.ttf")) {
        std::cerr << "Error loading font\n";
        return 1;
    }


    sf::Text txt_StartGame;
    txt_StartGame.setFont(font);
    txt_StartGame.setString("Start Game");
    txt_StartGame.setCharacterSize(24);
    txt_StartGame.setFillColor(sf::Color::Red);
    txt_StartGame.setPosition(200, 100);

    sf::Text txt_Exit;
    txt_Exit.setFont(font);
    txt_Exit.setString("Exit");
    txt_Exit.setCharacterSize(24);
    txt_Exit.setFillColor(sf::Color::Red);
    txt_Exit.setPosition(200, 150);

    bool showExitButton = true;
    bool wasNotYetTapped = false;

    for (int x = 1; x <= 9; ++x) {

        for (int y = 1; y <= 9; ++y) {
            Tile newTile(x, y, typeOfPupulationNumber);
            tiles.push_back(newTile);
        }
    }


    while (window.isOpen()) {

        //Tiles


        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            //exit button functionallity done
            if (txt_Exit.getGlobalBounds().contains(mousePosition)) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    // left mouse button is pressed: shoot
                    window.close();
                }
            } else if (txt_StartGame.getGlobalBounds().contains(mousePosition)) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    showExitButton = false;
                }
            }


        }

        window.clear();

        //start game screen clear
        if (showExitButton) {
            window.draw(txt_Exit);
            window.draw(txt_StartGame);
        } else {
            //draw a board


            //tutorial: https://www.sfml-dev.org/tutorials/2.0/graphics-shape.php
            wasNotYetTapped = true;
            int tileSize = 50;
            int padding = 5;



            //1. moving a bug
            for (int i = 0; i < bug_vector.size(); i++) {
                if(bug_vector.at(i)->getState()== "ALIVE"){
                    bug_vector.at(i)->move();
                }
            }





            for (int tileLoop = 0; tileLoop < tiles.size(); tileLoop++) {
                typeOfPupulationNumber = 0;

                //2.1. checking which bug populates the tile
                for (int j = 0; j < bug_vector.size(); j++) {

                    if(bug_vector.at(j)->getState()=="ALIVE"){

                    if (bug_vector.at(j)->getPosition().getX() == tiles.at(tileLoop).getX()
                        && bug_vector.at(j)->getPosition().getY() == tiles.at(tileLoop).getY()
                            ) {
                        typeOfBugCheck = bug_vector.at(j)->getType();
                        if (typeOfBugCheck == 'C') {
                            typeOfPupulationNumber = 1;
                        } else if (typeOfBugCheck == 'H') {
                            typeOfPupulationNumber = 2;
                        } else {
                            typeOfPupulationNumber = 3;
                        }
                    }
                    tiles.at(tileLoop).setPopulation(typeOfPupulationNumber);
                    }

                }
                //2.2. checking the color

                sf::RectangleShape tileShape(sf::Vector2f(tileSize, tileSize));
                sf::RectangleShape singleTileShape(sf::Vector2f(50, 50));
                singleTileShape.setPosition(tiles.at(tileLoop).getX() * (tileSize + padding),
                                            tiles.at(tileLoop).getY() * (tileSize + padding));


                if (tiles.at(tileLoop).getPopulated() == 0) {
                    singleTileShape.setFillColor(sf::Color::White);
                } else if (tiles.at(tileLoop).getPopulated() == 1) {
                    singleTileShape.setFillColor(sf::Color::Red);
                } else if (tiles.at(tileLoop).getPopulated() == 2) {
                    singleTileShape.setFillColor(sf::Color::Blue);
                } else if (tiles.at(tileLoop).getPopulated() == 3) {
                    singleTileShape.setFillColor(sf::Color::Cyan);
                }
                window.draw(singleTileShape);
            }


            //eating the bug
            int tileX=0;
            int tileY=0;

            for(int tileC=0;tileC<tiles.size();tileC++){
                bug_vectorBigEquals.clear();
                bug_vectorEat.clear();
                bug_vectorSmallBugs.clear();

                tileX= tiles.at(tileC).getX();
                tileY= tiles.at(tileC).getY();

                for(int bugC=0;bugC<bug_vector.size();bugC++){
                    if(bug_vector.at(bugC)->getPosition().getX() == tileX
                    && bug_vector.at(bugC)->getPosition().getY() == tileY
                    ) bug_vectorEat.push_back(bug_vector.at(bugC));
                }

                if(bug_vectorEat.size()>1){

                    int maxSize=bug_vectorEat.at(0)->getSize();
                    int maxID=bug_vectorEat.at(0)->getId();

                    for(int eat1=1;eat1<bug_vectorEat.size();eat1++){
                        if(maxSize > bug_vectorEat.at(eat1)->getSize()){
                            bug_vectorSmallBugs.push_back(bug_vectorEat.at(eat1));
                        }else if(maxSize == bug_vectorEat.at(eat1)->getSize()){
                            bug_vectorBigEquals.push_back(bug_vectorEat.at(eat1));
                        }else{
                            for(int idc=0;idc<bug_vectorEat.size();idc++){
                                if(maxID == bug_vectorEat.at(idc)->getId()){
                                    bug_vectorSmallBugs.push_back(bug_vectorEat.at(idc));
                                }
                            }
                        }
                    }

                    for(int sma=0;sma<bug_vectorSmallBugs.size();sma++){
                        bug_vectorSmallBugs.at(sma)->setState("Dead");
                    }





                }
            }



            window.display();

            Sleep(1000);


        }
        window.display();
    }

//    int choice = -1;
//    do {
//
//        cout << "Menu Items" << endl;
//
//
//        cout << "1. Initialize Bug Board (load data from file)" << endl;
//        cout << "2. Display all Bugs" << endl;
//        cout << "3. Find a Bug (given an id)" << endl;
//        cout << "4. Tap the Bug Board (causes move all, then fight/eat)" << endl;
//        cout << "5. Display Life History of all Bugs (path taken)" << endl;
//        cout << "6. Display all Cells listing their Bugs" << endl;
//        cout << "7. Run simulation (generates a Tap every second)" << endl;
//        cout << "8. Exit (write Life History of all Bugs to file)" << endl;
//        cout << "Enter your choice: ";
//        cin >> choice;
//
//        switch (choice) {
//            case 1:
//                initializeBugBoard();
//                break;
//            case 2:
//                (new Board())->displayAllBugs(bug_vector, 3);
//                break;
//            case 3:
//                (new Board())->findBugById(bug_vector, 3);
//                break;
//            case 4:
//                (new Board())->tapBugBoard(bug_vector, bug_vector);
//                break;
//            case 5:
//                (new  Board())->displayLifeHistory(bug_vector, 3);
//                break;
//            case 6:
//                displayAllCells();
//                break;
//            case 7:
//                runSimulation();
//                break;
//            case 8:
//                (new  Board())->exitProgram(bug_vector, 3);
//                break;
//            default:
//                cout << "Invalid choice. Please enter a number between 1 and 8." << endl;
//        }
//    } while (choice != 8);
    return 0;
}




void readBugsFromFile(vector<Bug *> &bug_vector, const string &fileName) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "File cant be opened" << endl;
    } else {


        while (!file.eof()) {
            string line;
            char delimiter = ';';
            stringstream ss(line);
            string partOfTheLine;
            vector<string> bugsString;

            getline(ss, partOfTheLine, delimiter);

            while (getline(ss, partOfTheLine, delimiter)) {
                bugsString.push_back(partOfTheLine);
            }


            int id = stoi(bugsString.at(1));
            int xValue = stoi(bugsString.at(2));
            int yValue = stoi(bugsString.at(3));
            int direction = stoi(bugsString.at(4));
            int size = stoi(bugsString.at(5));

            //bug_vector.push_back(New Crawler (...))
//            if (bugsString.at(0) == "C") {
//                Crawler *craw = new Crawler('C', id, xValue, yValue, direction, size);
//                bug_vector.push_back(craw);
//            } else if (bugsString.at(0) == "H") {
//                int hopLength = stoi(bugsString.at(6));
//                Hopper *hopp = new Hopper('H', id, xValue, yValue, direction, size, hopLength);
//                bug_vector.push_back(hopp);
//            } else if (bugsString.at(0) == "E") {
//                El_Diagonal *eldi = new El_Diagonal('E', id, xValue, yValue, direction, size);
//                bug_vector.push_back(eldi);
//            }
        }
    }
}

void initializeBugBoard() {
    cout << "Initializing Bug Board..." << endl;
}


void displayLifeHistory() {
    cout << "Displaying Life History of all Bugs..." << endl;
}

void displayAllCells() {
    cout << "Displaying all Cells listing their Bugs..." << endl;
}

void runSimulation() {
    cout << "Running simulation..." << endl;
}

void exitProgram() {
    cout << "Exiting program..." << endl;
}

