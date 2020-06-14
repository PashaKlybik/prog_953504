#ifndef BOOK_STORE_CSV_H
#define BOOK_STORE_CSV_H

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class CSV {
public:
    static vector<vector<string>> read(string filePath) {
        if(!std::ifstream(filePath)) {
            std::ofstream o(filePath);
        }

        ifstream csvFile(filePath);
        if(!csvFile.is_open())
            throw runtime_error("Файл не может быть открыт");

        vector<vector<string>> data;

        string buf;

        while(getline(csvFile, buf))
        {
            vector<string> rec;
            istringstream iss(buf);
            string field;

            while(getline(iss, field, ','))
                rec.push_back(field);

            if (rec.size() != 0)
                data.push_back(rec);
        }

        csvFile.close();

        return data;
    }

    static void write(string filePath, string line) {
        std::ofstream csvFile;
        csvFile.open(filePath, ios::out | ios::app);
        if (csvFile.fail())
            throw ios_base::failure(std::strerror(errno));

        csvFile.exceptions(csvFile.exceptions() | ios::failbit | ifstream::badbit);

        csvFile << line << endl;
    }

    static void update(string filePath, string row, string newRow) {
        std::ifstream csvFile(filePath);
        if(!csvFile.is_open())
            throw runtime_error("Файл не может быть открыт");

        std::vector<std::string> lines;
        std::string input;
        while (std::getline(csvFile, input))
            lines.push_back(input);

        for (auto& line : lines)
        {
            if (line == row)
                line = newRow;
        }

        csvFile.close();

        std::ofstream csvOutputFile((filePath));

        for (auto const& line : lines)
            csvOutputFile << line << '\n';
    }
};


#endif //BOOK_STORE_CSV_H
