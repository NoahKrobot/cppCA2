#include <iostream>
#include "headers/Bug.h"
#include <vector>
#include <fstream>
#include <sstream>

#include "headers/Crawler.h"
#include "headers/Hopper.h"
#include "headers/El_Diagonal.h"

using namespace std;

void initializeBugBoard();

void displayAllBugs();

void findBugById();

void tapBugBoard();

void displayLifeHistory();

void displayAllCells();

void runSimulation();

void exitProgram();

void readBugsFromFile(vector<Bug *> bug_vector);

int main() {

//    Therefore, we must declare a vector of pointers to Bug objects [ in main() ], and populate it by
//    reading data from a text file (“bugs.txt”), instantiating Bug objects dynamically on the Heap, and
//    adding their addresses to the vector. The owner of these object must also remember to free the
//    associated memory.
    vector<Bug *> bug_vector;
    readBugsFromFile(bug_vector);


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
                displayAllBugs();
                break;
            case 3:
                findBugById();
                break;
            case 4:
                tapBugBoard();
                break;
            case 5:
                displayLifeHistory();
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

void readBugsFromFile(vector<Bug *> bug_vector) {
    ifstream file("bugs.txt");
    if (!file.is_open()) {
        cout << "Failed to open file";
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
                Crawler *craw = new Crawler(id, xValue, yValue, direction, size);
                bug_vector.push_back(craw);
            } else if (bugsString.at(0) == "H") {
                int hopLength = stoi(bugsString.at(6));
                Hopper *hopp = new Hopper(id, xValue, yValue, direction, size, hopLength);
                bug_vector.push_back(hopp);
            } else if (bugsString.at(0) == "E") {
                El_Diagonal *eldi = new El_Diagonal(id, xValue, yValue, direction, size);
                bug_vector.push_back(eldi);
            }
        }
    }
}


        void initializeBugBoard() {
            cout << "Initializing Bug Board..." << endl;
        }

        void displayAllBugs() {
            cout << "Displaying all Bugs..." << endl;
        }

        void findBugById() {
            cout << "Finding a Bug by ID..." << endl;
        }

        void tapBugBoard() {
            cout << "Tapping the Bug Board..." << endl;
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


