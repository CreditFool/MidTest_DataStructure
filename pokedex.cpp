#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <typeinfo>
#include "linkedList.h"

struct information {
    unsigned int no, hp, total, att, def, spAtt, spDef, spd, gen;
    std::string name, type1, type2, legendary;
};

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
    for (int i=0; i<data.size(); i++) {
        database << data[i] << ',';
    }
    database << "\n";

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

template<class T, class U>
void filterProcessing(T &data, U &filteredData, std::string operasi, int operan1, int operan2) {
    //filteredData.clear();
    vector<std::string> temp;
    //#define KOLOM ((operan1 == 0 or (operan1 >= 3 and operan1 < 12)) ? std::stoi(temp(operan1)) : temp(operan1))
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

template<class T, class U>
void dataFilter(T &source, U &filteredSource) {
    vector<std::string> temp;
    for (int i=0; i<source.size(); i++) {
        temp = source.getData(i);
        temp.insert(temp.begin(), to_string(i+1));
        filteredSource.insertTail(temp);
    }
    filterProcessing(source, filteredSource, "=", 12, 1);
    
    // filteredSource.clear();
    // vector<std::string> temp;
    // temp = source.getData(0);
    // std::cout << temp[0] << std::endl;

    // int total = 500;
    // // temp = source.getData(0);
    // // std::cout << temp[4] << std::endl;

    // for (int i=0; i<source.size(); i++) {
    //     temp = source.getData(i);
    //     //std::cout << std::stoi(temp[4]) << std::endl;
    //     if (std::stoi(temp[4]) >= total) {
    //         filteredSource.insertTail(temp);
    //     }
    // }
}

template <class T>
void viewTable(T &view) {
    vector<int> numOfSpace;
    vector<std::string> row;
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
            std::cout << std::setw(numOfSpace[j]) << cell[j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    vector<std::string> col;
    singgleLinkedList<vector<std::string>> dataBase;
    singgleLinkedList<vector<std::string>> filteredData;

    readCSV("Pokemon.csv", col, dataBase);
    writeCSV("dummy.csv", col, dataBase);
    
    dataFilter(dataBase, filteredData);
    std::cout << filteredData.size() << std::endl;
    col.insert(col.begin(), "No");
    filteredData.insertHead(col);
    viewTable(filteredData);

    return 0;
}