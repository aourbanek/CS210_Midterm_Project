#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

//template<typename T>
//struct Node
//{
//    T data;
//    Node* next;
//    Node(T val) : data(val), next(nullptr) {}
//};

struct School
{
    string name;
    string address;
    string city;
    string state;
    string county;
    School* next;
    School(string val1, string val2, string val3, string val4, string val5) : name(val1), address(val2), city(val3), state(val4), county(val5), next(nullptr) {}
};

class SchoolList
{
    School* head;

public:
    SchoolList() : head(nullptr) {}

    void insertFirst(string name, string address, string city, string state, string county)
    {
        School* newSchool = new School(name, address, city, state, county);
        if (head == nullptr)
        {
            head = newSchool;
        }
        else
        {
            newSchool->next = head;
            head = newSchool;
        }
    }
    void insertLast(string name, string address, string city, string state, string county)
    {
        School* newSchool = new School(name, address, city, state, county);
        if (head == nullptr)
        {
            head = newSchool;
        }
        else
        {
            School* temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newSchool;
        }
    }
    void printList()
    {
        School* temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "nullptr" << endl;
    }
};

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