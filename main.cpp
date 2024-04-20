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

    void setX(int xInput){
        x =xInput;
    }


    void setY(int yInput){
        y =yInput;
    }

    void setPopulated(int inputPop){
        populated = inputPop;
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

    vector<Bug *> bug_vector;

    Crawler *craw = new Crawler('C', 1, 5, 5, 1, 3);
    bug_vector.push_back(craw);



//    Hopper *hopp = new Hopper('H', 2, 2, 2, 4, 4, 6);
//    bug_vector.push_back(hopp);
//    Hopper *hopp2 = new Hopper('H', 2, 5, 2, 4, 4, 6);
//    bug_vector.push_back(hopp2);
//
//    El_Diagonal *eldi = new El_Diagonal('E', 3, 3, 3, 5, 7);
//    bug_vector.push_back(eldi);

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
    txt_StartGame.setPosition(200,100);

    sf::Text txt_Exit;
    txt_Exit.setFont(font);
    txt_Exit.setString("Exit");
    txt_Exit.setCharacterSize(24);
    txt_Exit.setFillColor(sf::Color::Red);
    txt_Exit.setPosition(200,150);

    bool showExitButton = true;
    bool wasNotYetTapped= false;

    for (int x = 1; x <= 9; ++x) {

        for (int y = 1; y <= 9; ++y) {
            typeOfPupulationNumber=0;

            for(int w=0;w<bug_vector.size();w++){

                if(bug_vector.at(w)->getPosition().getX() == x
                   && bug_vector.at(w)->getPosition().getX() == y
                        ){
                    typeOfBugCheck = bug_vector.at(w)->getType();
                    if(typeOfBugCheck == 'C'){
                        typeOfPupulationNumber = 1;
                    }else if(typeOfBugCheck == 'H'){
                        typeOfPupulationNumber = 2;
                    }else{
                        typeOfPupulationNumber = 3;
                    }
                }
            }
            Tile newTile(x, y, typeOfPupulationNumber);
            tiles.push_back(newTile);
        }
    }


    while (window.isOpen())
    {
        Sleep(1000);


        for (int i = 0; i < bug_vector.size(); i++) {
            bug_vector.at(i)->move();
            cout<<bug_vector.at(i)->getPosition().getX()<<endl;
            cout<<bug_vector.at(i)->getPosition().getY()<<endl;
        }


        tiles.clear();

        for(int i=0; i<tiles.size();i++){

            for(int j=0;j<bug_vector.size();j++){
                if(tiles.at(i).getX() == bug_vector.at(j)->getPosition().getX()
                && tiles.at(i).getY() == bug_vector.at(j)->getPosition().getY()
                ){
                    typeOfBugCheck = bug_vector.at(j)->getType();
                    if(typeOfBugCheck == 'C'){
                        typeOfPupulationNumber = 1;
                    }else if(typeOfBugCheck == 'H'){
                        typeOfPupulationNumber = 2;
                    }else if(typeOfBugCheck == 'E'){
                        typeOfPupulationNumber = 3;
                    }else{
                        typeOfPupulationNumber = 0;
                    }


                }
            }
            tiles.at(i).setPopulated(typeOfPupulationNumber);

        }


        //Tiles


        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            //exit button functionallity done
            if (txt_Exit.getGlobalBounds().contains(mousePosition))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    // left mouse button is pressed: shoot
                    window.close();
                }
            }else if (txt_StartGame.getGlobalBounds().contains(mousePosition))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    showExitButton = false;
                }
            }


        }

        window.clear();


        //start game screen clear
        if(showExitButton){
            window.draw(txt_Exit);
            window.draw(txt_StartGame);
        }
            //draw a board
        else{
            //tutorial: https://www.sfml-dev.org/tutorials/2.0/graphics-shape.php
            wasNotYetTapped = true;
            int tileSize = 50;
            int padding = 5;

            for (int tileLoop = 0; tileLoop< tiles.size();tileLoop++) {
                sf::RectangleShape tileShape(sf::Vector2f(tileSize, tileSize));
                sf::RectangleShape singleTileShape(sf::Vector2f(50, 50));
                singleTileShape.setPosition(tiles.at(tileLoop).getX() * (tileSize + padding), tiles.at(tileLoop).getY() * (tileSize + padding));
                if(tiles.at(tileLoop).getPopulated()==0){
                    singleTileShape.setFillColor(sf::Color::White);
                }else  if(tiles.at(tileLoop).getPopulated()==1){
                    singleTileShape.setFillColor(sf::Color::Red);
                }else  if(tiles.at(tileLoop).getPopulated()==2){
                    singleTileShape.setFillColor(sf::Color::Blue);
                }else  if(tiles.at(tileLoop).getPopulated()==3){
                    singleTileShape.setFillColor(sf::Color::Cyan);
                }
                window.draw(singleTileShape);
            }
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
            if (bugsString.at(0) == "C") {
                Crawler *craw = new Crawler('C', id, xValue, yValue, direction, size);
                bug_vector.push_back(craw);
            } else if (bugsString.at(0) == "H") {
                int hopLength = stoi(bugsString.at(6));
                Hopper *hopp = new Hopper('H', id, xValue, yValue, direction, size, hopLength);
                bug_vector.push_back(hopp);
            } else if (bugsString.at(0) == "E") {
                El_Diagonal *eldi = new El_Diagonal('E', id, xValue, yValue, direction, size);
                bug_vector.push_back(eldi);
            }
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

