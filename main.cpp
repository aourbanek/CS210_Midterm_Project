#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

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
    void deleteByName(string name)
    {
        School* current = head;
        School* prev = nullptr;

        while (current && current->name != name)
        {
            prev = current;
            current = current->next;

            prev->next = current->next;
            delete current;
        }

        if (!current)
        {
            cout << "Error: School not found.";
            return;
        }
    }
    void findByName(string name)
    {
        School* current = head;

        while (current && current->name != name)
        {
            current = current->next;
        }

        cout << "School found: " << current->name    << endl;
        cout << "Address: "      << current->address << endl;
        cout << "City   : "      << current->city    << endl;
        cout << "State  : "      << current->state   << endl;
        cout << "County : "      << current->county  << endl;

        if (!current)
        {
            cout << "Error: School not found.";
            return;
        }
    }
    void display()
    {
        School* temp = head;
        cout << "List of Schools:" << endl;
        while (temp != nullptr)
        {
            cout << temp->name << endl;
            temp = temp->next;
        }
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

int main()
{
    CSVReader fileReading;
    string filename = "schools.csv";
    vector<vector<string>> data = fileReading.readCSV("schools.csv");
}