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
    School(string val1, string val2, string val3, string val4, string val5) : name(val1), address(val2), city(val3), state(val4), county(val5) {}

    void displayPrivate() const
    {
        cout << name << endl;
    }
};

class SchoolHashTable
{
private:
    // Hash Table initialization
    vector<vector<School>> table;
    int size;

    int hashFunction(string key, int tableSize) {
        int hash = 0;
        for (char ch : key) {
            hash += ch;
        }
        return hash % tableSize;
    }

public:
    SchoolHashTable(int size = 10) : size(size)
    {
        table.resize(size);
    }

    // TODO: Allow duplicate names
    void insert(const School& school)
    {
        int key = hashFunction(school.name, size);
        for (const School& existingSchool : table[key])
        {
            if (existingSchool.name == school.name)
            {
                cout << "Error: School " << school.name << " is already in the hash table." << endl;
                return;
            }
        }

        table[key].push_back(school);
        cout << "School " << school.name << " successfully inserted into hash table." << endl;
    }

    void deleteByName(const string& name)
    {
        int key = hashFunction(name, size);
        auto& bucket = table[key];

        for (auto it = bucket.begin(); it != bucket.end(); ++it)
        {
            if (it->name == name)
            {
                bucket.erase(it);
                cout << "School " << name << " successfully deleted from hash table." << endl;
                return;
            }
        }

        cout << "School " << name << " not found in hash table." << endl;
        return;
    }

    void findByName(const string& name)
    {
        int key = hashFunction(name, size);
        for (School& school : table[key])
        {
            if (school.name == name)
            {
                cout << "School " << name << " found:" << endl;
                cout << "Address: " << school.address << endl;
                cout << "City   : " << school.city << endl;
                cout << "State  : " << school.state << endl;
                cout << "County : " << school.county << endl << endl;

                return;
            }
        }

        cout << "School " << name << " not found in hash table." << endl;
        return;
    }

    void display() const
    {
        cout << "Displaying all schools:" << endl;
        for (int i = 0; i < size; ++i)
        {
            if (!table[i].empty())
            {
                cout << "Bucket " << i << ": " << endl;
                for (const School& school : table[i])
                {
                    school.displayPrivate();
                }
            }
        }

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

void interface(int choice, SchoolHashTable& table)
{
    int input = -1;
    char doMore = ' ';
    string searchKey = "";

    if (choice < 0 || choice > 4)
    {
        cout << "Error: Invalid choice." << endl;
        interface(0, table);
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
        interface(input, table);
        break;
    case 1: // School search
        cout << "Enter the name of a school (in all caps):" << endl;
        // This getline() took many attempts to properly include whitespaces;
        // solution found @ https://www.reddit.com/r/cpp_questions/comments/15n91xf/how_do_i_store_user_input_with_spaces_in_a_string/
        std::getline(std::cin >> std::ws, searchKey);
        table.findByName(searchKey);

        cout << "Would you like to do more? (y/n)" << endl;
        cin >> doMore;
        switch (doMore)
        {
        case 'y':
            interface(0, table);
            break;
        case 'n':
            interface(6, table);
            break;
        }
        break;
    case 2: // School deletion
        cout << "Enter the name of a school (in all caps):" << endl;
        std::getline(std::cin >> std::ws, searchKey);
        table.deleteByName(searchKey);

        cout << "Would you like to do more? (y/n)" << endl;
        cin >> doMore;
        switch (doMore)
        {
        case 'y':
            interface(0, table);
            break;
        case 'n':
            interface(6, table);
            break;
        }
        break;
    case 3: // School display (pre-order)
        cout << "List of Schools:" << endl;
        table.display();

        cout << "Would you like to do more? (y/n)" << endl;
        cin >> doMore;
        switch (doMore)
        {
        case 'y':
            interface(0, table);
            break;
        case 'n':
            interface(6, table);
            break;
        }
        break;
    case 4: // Quit
        cout << "Ok. Goodbye!";
        return;
        break;
    }
}

int main()
{
    CSVReader fileReading;
    string filename = "Illinois_Schools.csv";
    vector<vector<string>> data = fileReading.readCSV("Illinois_Schools.csv");

    SchoolHashTable hashTable(20); // 20 buckets
    for (vector<string> item : data)
    {
        if (item != data[0]) // Skips first line of data labels
        {
            hashTable.insert(School(item[0], item[1], item[2], item[3], item[4]));
        }
    }

    cout << "ALAN URBANEK" << endl;
    cout << "CS 210 MIDTERM MILESTONE 4" << endl;
    cout << "SCHOOL DATABASE" << endl << endl;

    interface(0, hashTable);

    return 0;
}