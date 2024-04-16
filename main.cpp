#include <iostream>
#include "headers/Bug.h"
#include <vector>
#include <fstream>
#include <sstream>

#include "headers/Crawler.h"
#include "headers/Hopper.h"
#include "headers/El_Diagonal.h"
#include "headers/Board.h"

using namespace std;

void initializeBugBoard();


void displayLifeHistory();

void displayAllCells();

void runSimulation();

void exitProgram();

void readBugsFromFile(vector<Bug *> &bug_vector, const string &file_name);

int main() {

    vector<Bug *> bug_vector;
    readBugsFromFile(bug_vector, "bugsFile.txt");

    Crawler *craw = new Crawler('C', 1, 1, 1, 3, 3);
    bug_vector.push_back(craw);

    Hopper *hopp = new Hopper('H', 2, 2, 2, 4, 4, 6);
    bug_vector.push_back(hopp);

    El_Diagonal *eldi = new El_Diagonal('E', 3, 3, 3, 5, 7);
    bug_vector.push_back(eldi);
//
    for (int i = 0; i < bug_vector.size(); i++) {
        cout << bug_vector.at(i)->getId() << endl;
    }

    int choice = -1;
    do {

        cout << "Menu Items" << endl;


        cout << "1. Initialize Bug Board (load data from file)" << endl;
        cout << "2. Display all Bugs" << endl;
        cout << "3. Find a Bug (given an id)" << endl;
        cout << "4. Tap the Bug Board (causes move all, then fight/eat)" << endl;
        cout << "5. Display Life History of all Bugs (path taken)" << endl;
        cout << "6. Display all Cells listing their Bugs" << endl;
        cout << "7. Run simulation (generates a Tap every second)" << endl;
        cout << "8. Exit (write Life History of all Bugs to file)" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                initializeBugBoard();
                break;
            case 2:
               (new Board())->displayAllBugs(bug_vector, 3);
                break;
            case 3:
                (new Board())->findBugById(bug_vector, 3);
                break;
            case 4:
                (new Board())->tapBugBoard(bug_vector, 3);
                break;
            case 5:
                (new  Board())->displayLifeHistory(bug_vector, 3);
                break;
            case 6:
                displayAllCells();
                break;
            case 7:
                runSimulation();
                break;
            case 8:
                exitProgram();
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 8." << endl;
        }
    } while (choice != 8);
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


