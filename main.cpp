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

    void setBugIdInTile(Bug *newBug) {
        bugsIdVector.push_back(newBug);
    }

    vector<Bug *> getBugsIdInTile() const {
        return bugsIdVector;
    }



    int x;
    int y;
    int populated;
    vector<Bug *> bugsIdVector;
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


void
moveBugsAndDisplayThem(sf::RenderWindow &window, int typeOfPupulationNumber, vector<Bug *> bug_vector, int tileSize,
                       int padding, vector<Tile> tiles, char typeOfBugCheck, int tileLoop);


void
eatBugsAndDisplayThat(vector<Bug *> bug_vectorEat, vector<Bug *> bug_vectorBigEquals, vector<Bug *> bug_vectorSmallBugs,
                      int tileX,
                      vector<Tile> tiles, int tileC, int tileY, vector<Bug *> bug_vector);


int main() {
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML Application");

    //bug vector
    vector<Bug *> bug_vectorEat;
    vector<Bug *> bug_vectorBigEquals;
    vector<Bug *> bug_vectorSmallBugs;
    vector<Bug *> bug_vector;



    ifstream file("../bugsFile.txt");

    if (!file.is_open()) {
        cout << "File cant be opened" << endl;
    } else {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            char delimiter = ';';
            string partOfTheLine;
            vector<string> bugsString;

            while (getline(ss, partOfTheLine, delimiter)) {
                bugsString.push_back(partOfTheLine);
            }

            int id = stoi(bugsString.at(1));
            int xValue = stoi(bugsString.at(2));
            int yValue = stoi(bugsString.at(3));
            int direction = stoi(bugsString.at(4));
            int size = stoi(bugsString.at(5));

            if (bugsString.at(0) == "C") {
                Crawler *craw = new Crawler('C', id, xValue, yValue, direction, size, "ALIVE");
                bug_vector.push_back(craw);
            } else if (bugsString.at(0) == "H") {
                int hopLength = stoi(bugsString.at(6));
                Hopper *hopp = new Hopper('H', id, xValue, yValue, direction, size, hopLength, "ALIVE");
                bug_vector.push_back(hopp);
            } else if (bugsString.at(0) == "D") {
                El_Diagonal *eldi = new El_Diagonal('D', id, xValue, yValue, direction, size, "ALIVE");
                bug_vector.push_back(eldi);
            }
        }
    }














    //tiles vector
    vector<Tile> tiles;
    int typeOfPupulationNumber = 0;
    char typeOfBugCheck = ' ';
    bool runDisplayAllCells = true;

    sf::Font font;
    if (!font.loadFromFile("../Roboto-Medium.ttf")) {
        std::cerr << "Error loading font\n";
        return 1;
    }

    sf::Text txt_StartGame;
    txt_StartGame.setFont(font);
    txt_StartGame.setString("Start Game");
    txt_StartGame.setCharacterSize(24);
    txt_StartGame.setFillColor(sf::Color::Red);
    txt_StartGame.setPosition(200, 100);

    sf::Text txt_dispAllBugs;
    txt_dispAllBugs.setFont(font);
    txt_dispAllBugs.setString("Display All Bugs");
    txt_dispAllBugs.setCharacterSize(24);
    txt_dispAllBugs.setFillColor(sf::Color::Red);
    txt_dispAllBugs.setPosition(200, 150);

    sf::Text txt_findByID;
    txt_findByID.setFont(font);
    txt_findByID.setString("Find Bug By ID");
    txt_findByID.setCharacterSize(24);
    txt_findByID.setFillColor(sf::Color::Red);
    txt_findByID.setPosition(200, 200);

    sf::Text txt_displayAllCells;
    txt_displayAllCells.setFont(font);
    txt_displayAllCells.setString("Display All Cells");
    txt_displayAllCells.setCharacterSize(24);
    txt_displayAllCells.setFillColor(sf::Color::Red);
    txt_displayAllCells.setPosition(200, 250);

    sf::Text txt_goBack;
    txt_goBack.setFont(font);
    txt_goBack.setString("<- Go Back");
    txt_goBack.setCharacterSize(24);
    txt_goBack.setFillColor(sf::Color::Red);
    txt_goBack.setPosition(20, 20);

    sf::Text txt_Exit;
    txt_Exit.setFont(font);
    txt_Exit.setString("Exit");
    txt_Exit.setCharacterSize(24);
    txt_Exit.setFillColor(sf::Color::Red);
    txt_Exit.setPosition(200, 300);

    bool showExitButton = true; //only one to be true to return home screen
    bool showDisplayBugs = true;
    bool showFindByID = true;
    bool shodDisplayCells = true;
    bool wasNotYetTapped = false;

    int idInteger = 0;
    bool idFinder = true;


    for (int x = 1; x <= 9; ++x) {

        for (int y = 1; y <= 9; ++y) {
            Tile newTile(x, y, typeOfPupulationNumber);
            tiles.push_back(newTile);
        }
    }

    vector<sf::Text> idDisplays;

    for (int idLoop = 0; idLoop < bug_vector.size(); idLoop++) {
        std::string idMenu = std::to_string(bug_vector.at(idLoop)->getId());
        sf::Text idDisplay;
        idDisplay.setFont(font);
        idDisplay.setCharacterSize(22);
        idDisplay.setFillColor(sf::Color::White);
        idDisplay.setString(idMenu);
        idDisplay.setPosition(200, 50 + (idLoop * 100));

        if (idLoop % 2 == 0) {
            idDisplay.setPosition(200, 50 + (idLoop * 100));
        } else {
            idDisplay.setPosition(400, 50 + ((idLoop - 1) * 100));
        }
        idDisplays.push_back(idDisplay);
    }


    while (window.isOpen()) {

        //Menu
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                (new Board())->exitProgram(bug_vector, bug_vector.size());
                window.close();
            }

            sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));


            if (txt_Exit.getGlobalBounds().contains(mousePosition)) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    // left mouse button is pressed: shoot
                    window.close();
                }
            } else if (txt_StartGame.getGlobalBounds().contains(mousePosition)) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    showExitButton = false;
                }
            } else if (txt_dispAllBugs.getGlobalBounds().contains(mousePosition)) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    showDisplayBugs = false;
                    showExitButton = false;
                }
            } else if (txt_findByID.getGlobalBounds().contains(mousePosition)) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    showFindByID = false;
                    showExitButton = false;
                }
            } else if (txt_displayAllCells.getGlobalBounds().contains(mousePosition)) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    shodDisplayCells = false;
                    showExitButton = false;
                }
            } else if (txt_goBack.getGlobalBounds().contains(mousePosition)) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    showDisplayBugs = true;
                    showFindByID = true;
                    shodDisplayCells = true;
                    showExitButton = true;
                    idFinder = true;
                    runDisplayAllCells= true;
                }
            }

            for (int i = 0; i < idDisplays.size(); i++) {
                if (idDisplays.at(i).getGlobalBounds().contains(mousePosition)) {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        string idString = idDisplays.at(i).getString();
                        idInteger = stoi(idString);
                        idFinder = false;
                    }
                }
            }
        }

        window.clear();

        //start game screen clear
        if (showExitButton) {
            window.draw(txt_Exit);
            window.draw(txt_StartGame);
            window.draw(txt_dispAllBugs);
            window.draw(txt_findByID);
            window.draw(txt_displayAllCells);
        } else if (!showDisplayBugs) {
            window.clear();
            window.draw(txt_goBack);
            (new Board())->displayAllBugs(window, bug_vector, bug_vector.size());

        } else if (!showFindByID) {
            window.clear();
            window.draw(txt_goBack);

            if (idFinder) {
                for (int i = 0; i < idDisplays.size(); i++) {
                    window.draw(idDisplays.at(i));
                }
            } else {
                sf::Text singleBugText;
                singleBugText.setFont(font);
                singleBugText.setCharacterSize(36);
                singleBugText.setFillColor(sf::Color::White);

                for (int j = 0; j < bug_vector.size(); j++) {

                    if (bug_vector.at(j)->getId() == idInteger) {
                        string bug_info = "";

                        if (bug_vector.at(j)->getType() == 'C') {
                            bug_info = "Crawler: \n\n";
                        } else if (bug_vector.at(j)->getType() == 'H') {
                            bug_info = "Hopper: \n\n";
                        } else {
                            bug_info = "El Diagonal: \n\n";
                        }
                        bug_info += "id: " + to_string(bug_vector.at(j)->getId()) + "\n"
                                    + "direction: " + to_string(bug_vector.at(j)->getDirection()) + "\n"
                                    + "X position: " + to_string(bug_vector.at(j)->getPosition().getX()) + "\n"
                                    + "Y position: " + to_string(bug_vector.at(j)->getPosition().getY()) + "\n"
                                    + "alive: " + (bug_vector.at(j)->getAlive() ? "true" : "false") + "\n"
                                    + "size: " + to_string(bug_vector.at(j)->getSize()) + "\n";

                        singleBugText.setString(bug_info);
                    }
                }

                singleBugText.setPosition(200, 200);
                window.draw(singleBugText);
            }


        } else if (!shodDisplayCells) {
            window.clear();
            window.draw(txt_displayAllCells);
            window.draw(txt_goBack);


            if(runDisplayAllCells){
            for (int tileLoop = 0; tileLoop < tiles.size(); tileLoop++) {
                typeOfPupulationNumber= 0;
                for (int j = 0; j < bug_vector.size(); j++) {
                    if (bug_vector.at(j)->getState() == "ALIVE") {
                        if (bug_vector.at(j)->getPosition().getX() == tiles.at(tileLoop).getX()
                            && bug_vector.at(j)->getPosition().getY() == tiles.at(tileLoop).getY()
                            ) {
                            typeOfBugCheck = bug_vector.at(j)->getType();
                            if (typeOfBugCheck == 'C') {
                                typeOfPupulationNumber = 1;
                                tiles.at(tileLoop).setBugIdInTile(bug_vector.at(j));

                            } else if (typeOfBugCheck == 'H') {
                                typeOfPupulationNumber = 2;
                                tiles.at(tileLoop).setBugIdInTile(bug_vector.at(j));

                            } else {
                                typeOfPupulationNumber = 3;
                                tiles.at(tileLoop).setBugIdInTile(bug_vector.at(j));

                            }
                        }
                        tiles.at(tileLoop).setPopulation(typeOfPupulationNumber);
                    }
                }
            }

            for (int i = 0; i < tiles.size(); i++) {
                string tileData = "\n(";
                tileData += to_string(tiles.at(i).getX());
                tileData += ", ";
                tileData += to_string(tiles.at(i).getY());
                tileData += ")";
                tileData += ": ";


                //0 - empty
                //1 - crawler - red
                //2 - hopper - blue
                //3 - el diagonal - yellow

                if (tiles.at(i).getPopulated() == 0) {
                    tileData += "empty";
                } else {
                    for (int j = 0; j < tiles.at(i).getBugsIdInTile().size(); j++) {

                        if (tiles.at(i).getBugsIdInTile().at(j)->getType() == 'C'
                                ) {
                            tileData += "Crawler ";
                        } else if (tiles.at(i).getBugsIdInTile().at(j)->getType() == 'H'
                                ) {
                            tileData += "Hopper ";
                        } else if (tiles.at(i).getBugsIdInTile().at(j)->getType() == 'D'
                                ) {
                            tileData += "El Diagonal ";
                        }
                        tileData += to_string(tiles.at(i).getBugsIdInTile().at(j)->getId());

                        if(j != tiles.at(i).getBugsIdInTile().size() - 1){
                            tileData += ", ";
                        }
                    }
                }
                cout << tileData << endl;
            }
            runDisplayAllCells= false;
        }


        } else if (!showExitButton) {

            //draw a board
            //tutorial: https://www.sfml-dev.org/tutorials/2.0/graphics-shape.php
            wasNotYetTapped = true;
            int tileSize = 50;
            int padding = 5;


            //1. moving a bug

            for (int tileLoop = 0; tileLoop < tiles.size(); tileLoop++) {
                moveBugsAndDisplayThem(window, typeOfPupulationNumber, bug_vector, tileSize, padding, tiles,
                                       typeOfBugCheck, tileLoop);
            }

            //eating the bug
            int tileX = 0;
            int tileY = 0;

            for (int tileC = 0; tileC < tiles.size(); tileC++) {
                eatBugsAndDisplayThat(

                        bug_vectorEat, bug_vectorBigEquals, bug_vectorSmallBugs, tileX, tiles,
                        tileC, tileY, bug_vector);
            }
            window.display();

            for (int i = 0; i < bug_vector.size(); i++) {
                if (bug_vector.at(i)->getState() == "ALIVE") {
                    bug_vector.at(i)->move();
                }
            }

            Sleep(1000);

        }
        window.display();
    }
    return 0;
}


void
eatBugsAndDisplayThat(vector<Bug *> bug_vectorEat, vector<Bug *> bug_vectorBigEquals, vector<Bug *> bug_vectorSmallBugs,
                      int tileX,
                      vector<Tile> tiles, int tileC, int tileY, vector<Bug *> bug_vector
) {

    bug_vectorBigEquals.clear();
    bug_vectorEat.clear();
    bug_vectorSmallBugs.clear();

    tileX = tiles.at(tileC).getX();
    tileY = tiles.at(tileC).getY();

    for (int bugC = 0; bugC < bug_vector.size(); bugC++) {
        if (bug_vector.at(bugC)->getPosition().getX() == tileX
            && bug_vector.at(bugC)->getPosition().getY() == tileY
                )
            bug_vectorEat.push_back(bug_vector.at(bugC));
    }

    if (bug_vectorEat.size() > 1) {

        int maxSize = bug_vectorEat.at(0)->getSize();
        int maxID = bug_vectorEat.at(0)->getId();

        for (int eat1 = 1; eat1 < bug_vectorEat.size(); eat1++) {
            //push smaller bug to new smaller vector
            if (maxSize > bug_vectorEat.at(eat1)->getSize()) {
                bug_vectorSmallBugs.push_back(bug_vectorEat.at(eat1));
                //push previous big which is now smaller to small vector
            } else if (maxSize < bug_vectorEat.at(eat1)->getSize()) {
                for (int idc = 0; idc < bug_vectorEat.size(); idc++) {
                    if (maxID == bug_vectorEat.at(idc)->getId()) {
                        bug_vectorSmallBugs.push_back(bug_vectorEat.at(idc));
                    }
                }
                maxID = bug_vectorEat.at(eat1)->getId();
                maxSize = bug_vectorEat.at(eat1)->getSize();
            }
            cout << "maxID " << maxID << endl;
        }


        //push equal vectors in new array
        for (int eat2 = 0; eat2 < bug_vectorEat.size(); eat2++) {
            if (maxSize == bug_vectorEat.at(eat2)->getSize()) {
                bug_vectorBigEquals.push_back(bug_vectorEat.at(eat2));
            }
        }

        int winnerSize = maxSize;
        int winnerID = maxID;

        if (bug_vectorEat.size() > 1) {

            for (int equalsRand = 0; equalsRand < bug_vectorBigEquals.size(); equalsRand++) {
                cout << "bug_vectorBigEquals" << endl;
                cout << bug_vectorBigEquals.at(equalsRand)->getId() << endl;
            }

            random_device equalRand;
            mt19937 gen(equalRand());
            uniform_int_distribution<> dist(0, bug_vectorBigEquals.size() - 1);
            int randomEqualBugIndex = dist(gen);

            for (int big = 0; big < bug_vectorBigEquals.size(); big++) {
                if (big != randomEqualBugIndex) {
                    bug_vectorSmallBugs.push_back(bug_vectorBigEquals.at(big));
                } else {
                    winnerID = bug_vectorBigEquals.at(big)->getId();
                }
            }
        }

        for (int sma = 0; sma < bug_vectorSmallBugs.size(); sma++) {
            string stateString;
            stateString += "Eaten by ";
            stateString += to_string(winnerID);
            bug_vectorSmallBugs.at(sma)->setState(stateString);
            cout << "state: " << bug_vectorSmallBugs.at(sma)->getState();
        }
    }
}

void
moveBugsAndDisplayThem(sf::RenderWindow &window, int typeOfPupulationNumber, vector<Bug *> bug_vector, int tileSize,
                       int padding, vector<Tile> tiles, char typeOfBugCheck, int tileLoop) {


    typeOfPupulationNumber = 0;

    //2.1. checking which bug populates the tile
    for (int j = 0; j < bug_vector.size(); j++) {

        if (bug_vector.at(j)->getState() == "ALIVE") {

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
            tiles.at(tileLoop).setBugIdInTile(bug_vector.at(j));


        } else {
            Pair newPos = *new Pair(20, 20);
            bug_vector.at(j)->setPosition(newPos);
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

        sf::Texture texture;
        texture.loadFromFile("../sprites/buggy.jpg");
        sf::Sprite Sprite;
        Sprite.setTexture(texture);
        singleTileShape.setTexture(reinterpret_cast<const sf::Texture *>(&Sprite));

    } else if (tiles.at(tileLoop).getPopulated() == 2) {
        singleTileShape.setFillColor(sf::Color::Blue);
    } else if (tiles.at(tileLoop).getPopulated() == 3) {
        singleTileShape.setFillColor(sf::Color::Cyan);
    }
    window.draw(singleTileShape);
}





















