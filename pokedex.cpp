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

std::string lowercase(std::string word) {
    for (int i=0; i<word.size(); i++) {
        word[i] = tolower(word[i]);
    }
    return word;
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
            if (!(lowercase(temp[operan1]) == lowercase(operan2))) {
                filteredData.remove(filteredData.getIndex(temp));
            }
            else i++;
        }
    }
}

template<class T, class U>
void dataFiltering(T &filteredSource, U &filterList) {
    vector<std::string> filter;
    std::string column[14] = {"no", "id", "name", "type1", "type2", "total", "hp", "attack", 
                              "defend", "spatt", "spdef", "speed", "generation", "legendary"};
    std::string operan, operasi, operan2str;
    int operan1 = -1, operan2int;

    getline(std::cin, operasi);
    std::stringstream s(operasi);
    while (getline(s, operan, ' ')){
        filter.push_back(operan);
    }

    for (int i=0; i<14; i++) {
        if (lowercase(filter[0]) == column[i])
            operan1 = i;
    }

    if (((operan1 >= 0 and operan1 <= 1) or (operan1 >= 5 and operan1 <= 12)) and 
        (filter[1] == "=" or filter[1] == "<" or filter[1] == ">" or filter[1] == "<=" or filter[1] == ">=")) {
        filterList.push_back(operasi);
        filterProcessing(filteredSource, filter[1], operan1, std::stoi(filter[2]));
    }
    else if (((operan1 >= 2 and operan1 <= 4) or operan1 == 13) and filter[1] == "=") {
        filterList.push_back(operasi);
        filterProcessing(filteredSource, filter[1], operan1, filter[2]);
    }
}

template<class T, class U>
void dataUnfiltering(T &source, U &filteredSource) {
    filteredSource.clear();
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

    int panjang = 13;
    for (int i=0; i<numOfSpace.size(); i++) {
        panjang += numOfSpace[i];
    }

    vector<std::string> cell;
    for (int i=0; i<view.size(); i++) {
        cell = view.getData(i);
        for (int j=0; j<cell.size(); j++) {
            std::cout << std::setw(numOfSpace[j]) << cell[j] << " ";
        }
        if (i==0) { 
            std::cout << std::endl;
            for (int garis=0; garis<panjang; garis++) std::cout << "-";
        }
        std::cout << std::endl;
    }
    view.removeHead();
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

template <class T>
vector<string> searchData(T &source, int column, std::string val) {
    vector<string> temp;
    bool is_available = false;
    for (int i=0; i<source.size(); i++) {
        temp = source.getData(i);
        if (temp[column] == val) {
            is_available = true;
            return temp;
            break;
        }
    }
    if (is_available == false) std::cout << "Data tidak ditemukan" << std::endl;
}

template <class T>
vector<std::string> createData(T column) {
    vector<std::string> temp;
    std::string input;
    int total=0;

    do {
        temp.clear();
        for (int i=0; i<column.size(); i++) {
            if (i==4) {
                temp.push_back("0");
            }
            else {
                std::cout << column[i] << ": ";
                getline(std::cin, input);
                temp.push_back(input);
            }
        }
        for (int i=5; i<=10; i++) {
            total += std::stoi(temp[i]);
        }
        temp[4] = to_string(total);

        std::cout << "\n[1]For Continue" << std::endl;
        std::cout << "[Any Key]For Retry" << std::endl;
        std::cout << ">> " <<;
        total = streamInt(1, 1);
    } while (total != 1);
    
    return temp;
}

void removeData() {

}

int main() {
    clearScreen();
    using namespace std;
    vector<std::string> col;
    vector<std::string> filterList;
    singgleLinkedList<vector<std::string>> dataBase;
    doubleLinkedList<vector<std::string>> filteredData;
    readCSV("Pokemon.csv", col, dataBase);

    int input;

    // writeCSV("dummy.csv", col, dataBase);
    // dataUnfiltering(dataBase, filteredData);
    // dataFiltering(filteredData, filterList);
    // std::cout << filteredData.size() << std::endl;
    //viewTable(filteredData, col);

    do {
        std::cout << "Pokémon data management v1.0" << endl;
        std::cout << "\nPokémon in Database: " << dataBase.size() << " Species";
        std::cout << "\nLatest Generation  : Gen " << highestData(dataBase, 11) << "\n";
        std::cout << "\nNavigation Menu:";
        std::cout << "\n[1]Show Database";
        std::cout << "\n[2]Update Database";
        std::cout << "\n[3]Make Team";
        std::cout << "\n[4]Help";
        std::cout << "\n[5]About";
        std::cout << "\n[6]Exit\n";
        std::cout << "\n>> ";

        input = streamInt(1, 6);
                clearScreen();
        switch (input) {
        case 1:
            dataUnfiltering(dataBase, filteredData);
            do {
                std::cout << "Filter : ";
                if (filterList.size() == 0) {
                    std::cout << "None" << endl;
                }
                else {
                    for (int i=0; i<filterList.size()-1; i++) {
                        std::cout << filterList[i] << ", ";
                    }
                    std::cout << filterList[filterList.size()-1] << endl;
                }
                std::cout << "Matches: " << filteredData.size() << " result\n";
                std::cout << "\n[1]Set filter [2]Show result [3]Reset filter [4]Back\n>> ";
                
                input = streamInt(1, 4);
                switch (input) {
                case 1:
                    std::cout << "\nAvailable:";
                    std::cout << "\nno id name type1 type2 total hp attack defend"; 
                    std::cout << "\nspatt spdef speed generation legendary\n";
                    std::cout << "\n= > < >= <=\n";
                    std::cout << "\nExample: name = Pikachu";
                    std::cout << "\n         attack >= 150\n";
                    std::cout << "\n>> ";
                    dataFiltering(filteredData, filterList);
                    clearScreen();
                   break;
                
                case 2:
                    clearScreen();
                    viewTable(filteredData, col);
                    std::cout << std::endl;
                    break;
                
                case 3:
                    dataUnfiltering(dataBase, filteredData);
                    filterList.clear();
                    clearScreen();
                    break;

                case 4:
                    clearScreen();
                    break;
                
                default:
                    clearScreen();
                    break;
                }
            } while (input != 4);
            break;

        case 2:
            do {
                clearScreen();
                std::cout << "[1]Add new data" << endl;
                std::cout << "[2]Change data" << endl;
                std::cout << "[3]Remove data" << endl;
                std::cout << "[4]Back" << endl;
                std::cout << "\n>> ";
                input = streamInt(1, 4);
                
                switch (input) {
                case 1:
                    clearScreen();
                    dataBase.insertTail(createData(col));
                    break;

                case 2:
                    clearScreen();
                    dataUnfiltering(dataBase, filteredData);
                    do {
                        std::cout << "[1]Search by No" << endl;
                        std::cout << "[2]Search by Name" << endl;
                        std::cout << "[3]Cancel" << endl;
                        std::cout << "\n>> ";
                        input = streamInt(1, 3);

                        switch (input) {
                        case 1:
                            {
                                int no;
                                do {
                                    std::cout << "Insert the database number: ";
                                    no = streamInt(1, dataBase.size());
                                } while (no == -1);
                                filterProcessing(filteredData, "=", 0, no);
                                do {
                                    clearScreen();
                                    viewTable(filteredData, col);
                                    vector<std::string> temp;
                                    temp = filteredData.getData(0);
                                    std::cout << "\nAre you sure want to change this data?\n";
                                    std::cout << "[1]Continue\n";
                                    std::cout << "[2]Cancel\n";
                                    std::cout << "\n>> ";
                                    input = streamInt(1, 2);

                                    switch (input) {
                                    case 1:
                                        dataBase.change(dataBase.getIndex(temp), createData(col));
                                        clearScreen();
                                        break;

                                    case 2:
                                        clearScreen();
                                        break;

                                    default:
                                        clearScreen();
                                        break;
                                    }
                                } while (input!=1 or input!=2);
                            }
                            break;

                        case 2:
                            {
                                std::string name;
                                std::cout << "Insert Pokemon name: ";
                                getline(std::cin, name);
                                filterProcessing(filteredData, "=", 2, name);
                                do {
                                    clearScreen();
                                    viewTable(filteredData, col);
                                    vector<std::string> temp;
                                    temp = filteredData.getData(0);
                                    std::cout << "\nAre you sure want to change this data?\n";
                                    std::cout << "[1]Continue\n";
                                    std::cout << "[2]Cancel\n";
                                    std::cout << "\n>> ";
                                    input = streamInt(1, 2);

                                    switch (input) {
                                    case 1:
                                        dataBase.change(dataBase.getIndex(temp), createData(col));
                                        clearScreen();
                                        break;

                                    case 2:
                                        clearScreen();
                                        break;

                                    default:
                                        clearScreen();
                                        break;
                                    }
                                } while (input!=1 or input!=2);
                            }
                            break;

                        case 3:
                            break;

                        default:
                            break;
                        }
                    } while (input != 3);

                    break;

                case 3:
                    break;

                case 4:
                    clearScreen();
                    break;
                
                default:
                    clearScreen();
                    break;
                }

            } while (input != 4);
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
            writeCSV("dummy.csv", col, dataBase);
            break;

        default:
            std::cout << "Pilihan tidak ada" << endl;
            break;
        }
    } while (input != 6);

    std::cout << endl;
    return 0;
}