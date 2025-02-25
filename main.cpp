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

        return;
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

        return;
    }
    void deleteByName(string name)
    {
        School* current = head;
        School* prev = nullptr;

        while (current && current->name != name)
        {
            prev = current;
            current = current->next;
        }

        if (!current)
        {
            cout << "Error: School not found." << endl << endl;
            return;
        }

        prev->next = current->next;
        delete current;

        cout << "School deleted." << endl << endl;

        return;
    }
    void findByName(string name)
    {
        School* current = head;

        while (current && current->name != name)
        {
            current = current->next;
        }

        if (!current)
        {
            cout << "Error: School not found." << endl;
            return;
        }

        cout << "School found: " << current->name << endl;
        cout << "Address: " << current->address << endl;
        cout << "City   : " << current->city << endl;
        cout << "State  : " << current->state << endl;
        cout << "County : " << current->county << endl << endl;

        return;
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

        cout << endl;

        return;
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

void interface(int choice, SchoolList list)
{
    int input = -1;
    char doMore = ' ';
    string searchKey = "";

    if (choice < 0 || choice > 4)
    {
        cout << "Error: Invalid choice." << endl;
        interface(0, list);
    }

    switch (choice)
    {
    case 0: // Initial call and "doing more" case
        cout << "What would you like to do? (Enter number)" << endl;
        cout << "1. Search for a school by name" << endl;
        cout << "2. Delete a school by name" << endl;
        cout << "3. Display stored schools" << endl;
        cout << "4. Quit" << endl;

        cin >> input;
        interface(input, list);
        break;
    case 1: // School search
        cout << "Enter the name of a school (in all caps):" << endl;
        // This getline() took many attempts to properly include whitespaces;
        // solution found @ https://www.reddit.com/r/cpp_questions/comments/15n91xf/how_do_i_store_user_input_with_spaces_in_a_string/
        std::getline(std::cin >> std::ws, searchKey);
        list.findByName(searchKey);

        cout << "Would you like to do more? (y/n)" << endl;
        cin >> doMore;
        switch (doMore)
        {
        case 'y':
            interface(0, list);
            break;
        case 'n':
            interface(4, list);
            break;
        }
        break;
    case 2: // School deletion
        cout << "Enter the name of a school (in all caps):" << endl;
        std::getline(std::cin >> std::ws, searchKey);
        list.deleteByName(searchKey);

        cout << "Would you like to do more? (y/n)" << endl;
        cin >> doMore;
        switch (doMore)
        {
        case 'y':
            interface(0, list);
            break;
        case 'n':
            interface(4, list);
            break;
        }
        break;
    case 3: // School display
        list.display();

        cout << "Would you like to do more? (y/n)" << endl;
        cin >> doMore;
        switch (doMore)
        {
        case 'y':
            interface(0, list);
            break;
        case 'n':
            interface(4, list);
            break;
        }
        break;
    case 4: // Quit
        break;
    }
}

int main()
{
    CSVReader fileReading;
    string filename = "schools.csv";
    vector<vector<string>> data = fileReading.readCSV("schools.csv");

    SchoolList list;
    for (vector<string> item : data)
    {
        if (item != data[0]) // Skips first line of data labels
        {
            list.insertLast(item[0], item[1], item[2], item[3], item[4]);
        }
    }

    cout << "ALAN URBANEK" << endl;
    cout << "CS 210 MIDTERM MILESTONE 2" << endl;
    cout << "SCHOOL DATABASE" << endl << endl;

    interface(0, list);

    return 0;
}