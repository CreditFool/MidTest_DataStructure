#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <typeinfo>
#include <cstdlib>
#include "linkedList.h"

void clearScreen() {
    #ifdef WINDOWS
        std::system("cls");
    #else
        std::system ("clear");
    #endif
}

void readCSV(std::string filename, vector<std::string> &data, singgleLinkedList<vector<std::string>> &db) {
    std::ifstream database(filename, ios::in);
    std::string line, cell, temp;
    vector<std::string> row;

        db.clear();
        data.clear();
        getline(database, line);

        stringstream s(line);
        while (getline(s, cell, ',')) {
            data.push_back(cell);
        }
        
        while (getline(database, line)) {
            row.clear();

            stringstream s(line);
            while (getline(s, cell, ',')) {
                row.push_back(cell);
            }
            db.insertTail(row);
        }

    database.close();
}

void writeCSV(std::string filename, vector<std::string> &data, singgleLinkedList<vector<std::string>> &db) {
    std::ofstream database(filename);
    for (int i=0; i<data.size()-1; i++) {
        database << data[i] << ',';
    }
    database << data[data.size()-1] << "\n";

    vector<std::string> row;

    for (int i=0; i<db.size(); i++) {
        row = db.getData(i);
        for (int j=0; j<row.size()-1; j++) {
            database << row[j] << ',';
        }
        database << row[row.size()-1] << "\n";
    }

    database.close();
}

void updateCSV(singgleLinkedList<vector<std::string>> &db) {
    
}

int streamInt(int low, int high) {
    std::string input;
    int choice = 0;

    while (true) {
        std::getline(std::cin, input, '\n');
        std::stringstream ss(input);

        if ((ss >> choice) && (choice >= low) && (choice <= high)) {
            return choice;
        }
        return -1;
    }
}

template<class T>
void filterProcessing(T &filteredData, std::string operasi, int operan1, int operan2) {
    vector<std::string> temp;
    if (operasi == "=") {
        int i=0;
        while (i < filteredData.size()) {
            temp = filteredData.getData(i);
            if (!(std::stoi(temp[operan1]) == operan2)) {
                filteredData.remove(filteredData.getIndex(temp));
            }
            else i++;
        }
    }
    else if (operasi == ">") {
        int i=0;
        while (i < filteredData.size()) {
            temp = filteredData.getData(i);
            if (!(std::stoi(temp[operan1]) > operan2)) {
                filteredData.remove(filteredData.getIndex(temp));
            }
            else i++;
        }
    }
    else if (operasi == "<") {
        int i=0;
        while (i < filteredData.size()) {
            temp = filteredData.getData(i);
            if (!(std::stoi(temp[operan1]) < operan2)) {
                filteredData.remove(filteredData.getIndex(temp));
            }
            else i++;
        }
    }
    else if (operasi == ">=") {
        int i=0;
        while (i < filteredData.size()) {
            temp = filteredData.getData(i);
            if (!(std::stoi(temp[operan1]) >= operan2)) {
                filteredData.remove(filteredData.getIndex(temp));
            }
            else i++;
        }
    }
    else if (operasi == "<=") {
        int i=0;
        while (i < filteredData.size()) {
            temp = filteredData.getData(i);
            if (!(std::stoi(temp[operan1]) <= operan2)) {
                filteredData.remove(filteredData.getIndex(temp));
            }
            else i++;
        }
    }
}

template<class T>
void filterProcessing(T &filteredData, std::string operasi, int operan1, std::string operan2) {
    vector<std::string> temp;
    if (operasi == "=") {
        int i=0;
        while (i < filteredData.size()) {
            temp = filteredData.getData(i);
            if (!(temp[operan1] == operan2)) {
                filteredData.remove(filteredData.getIndex(temp));
            }
            else i++;
        }
    }
}

template<class T>
void dataFiltering(T &filteredSource) {
    std::string operasi, operan2str;
    int operan1, operan2int;

    std::cout << ">> ";
    std::cin >> operan1 >> operasi;
    if ((operan1 >= 0 and operan1 <= 1) or (operan1 >= 5 and operan1 <= 12)) {
        std::cin >> operan2int;
        filterProcessing(filteredSource, operasi, operan1, operan2int);
    }
    else if ((operan1 >= 2 and operan1 <= 4) or operan1 == 13) {
        std::cin >> operan2str;
        filterProcessing(filteredSource, operasi, operan1, operan2str);
    }
}

template<class T, class U>
void dataUnfiltering(T &source, U &filteredSource) {
    vector<std::string> temp;
    for (int i=0; i<source.size(); i++) {
        temp = source.getData(i);
        temp.insert(temp.begin(), to_string(i+1));
        filteredSource.insertTail(temp);
    }
}

template <class T>
void viewTable(T &view, vector<std::string> column) {
    vector<int> numOfSpace;
    vector<std::string> row;
    column.insert(column.begin(), "No");
    view.insertHead(column);

    numOfSpace.assign(view.getData(0).size(), 0);

    for (int i=0; i<view.size(); i++) {
        row = view.getData(i);
        for (int j=0; j<row.size(); j++) {
            if (numOfSpace[j] < row[j].size()) {
                numOfSpace[j] = row[j].size();
            }
        }
    }

    vector<std::string> cell;
    for (int i=0; i<view.size(); i++) {
        cell = view.getData(i);
        for (int j=0; j<cell.size(); j++) {
            std::cout << std::setw(numOfSpace[j]) << cell[j] << "   ";
        }
        std::cout << std::endl;
    }
}

template <class T>
int highestData(T &db, int col) {
    vector<std::string> temp = db.getData(0);
    int highest = std::stoi(temp[col]);

    for (int i=1; i<db.size(); i++) {
        temp = db.getData(i);
        if (highest < std::stoi(temp[col])) {
            highest = std::stoi(temp[col]);
        }
    }

    return highest;
}

int main() {
    clearScreen();
    using namespace std;
    vector<std::string> col;
    singgleLinkedList<vector<std::string>> dataBase;
    doubleLinkedList<vector<std::string>> filteredData;
    readCSV("Pokemon.csv", col, dataBase);

    int input;

    // writeCSV("dummy.csv", col, dastaBase);
    // dataUnfiltering(dataBase, filteredData);
    // dataFiltering(filteredData);
    // viewTable(filteredData, col);

    do {
        std::cout << "Pokémon data management v1.0" << endl;
        std::cout << "\nPokémon in Database: " << dataBase.size() << " Species";
        std::cout << "\nLatest Generation  : Gen " << highestData(dataBase, 11) << "\n";
        std::cout << "\nNavigation Menu:";
        std::cout << "\n1. Show Database";
        std::cout << "\n2. Update Database";
        std::cout << "\n3. Make Team";
        std::cout << "\n4. Help";
        std::cout << "\n5. About";
        std::cout << "\n6. Exit\n";
        std::cout << "\n>> ";

        input = streamInt(1, 6);
        switch (input) {
        case 1:
            clearScreen();
            dataUnfiltering(dataBase, filteredData);
            std::cout << "Filter : None" << endl;
            std::cout << "Matches: " << filteredData.size() << " result";
            break;

        case 2:
            std::cout << "update database" << endl;
            break;

        case 3:
            std::cout << "make team" << endl;
            break;

        case 4:
            std::cout << "help" << endl;
            break;

        case 5:
            std::cout << "about" << endl;
            break;

        case 6:
            break;

        default:
            std::cout << "Pilihan tidak ada" << endl;
            break;
        }
    } while (input != 6);

    std::cout << endl;
    return 0;
}