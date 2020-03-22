#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
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
        for (int j=0; j<row.size(); j++) {
            database << row[j] << ',';
        }
        database << "\n";
    }

    database.close();
}

int main() {
    vector<std::string> col;
    singgleLinkedList<vector<std::string>> dataBase;

    readCSV("Pokemon.csv", col, dataBase);
    writeCSV("dummy.csv", col, dataBase);

    return 0;
}