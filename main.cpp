#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "sll.cpp"
using namespace std;

class CSVReader {
public:
    static vector<vector<string>> readCSV(const string& filename) {
        ifstream file(filename);
        vector<vector<string>> data;
        string line, word;

        if (!file.is_open()) {
            cerr << "Error: Could not open file " << filename << endl;
            return data;
        }

        while (getline(file, line)) {
            stringstream ss(line);
            vector<string> row;
            while (getline(ss, word, ',')) {
                row.push_back(word);
            }
            data.push_back(row);
        }
        file.close();
        return data;
    }
};

template<typename T>
struct School
{
    string name;
    string address;
    string city;
    string state;
    string county;
    Node<T>* next;
};