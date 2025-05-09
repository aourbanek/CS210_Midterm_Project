#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
using namespace std;

struct School
{
    string name;
    string address;
    string city;
    string state;
    string county;
    School* left;
    School* right;
    School(string val1, string val2, string val3, string val4, string val5) : name(val1), address(val2), city(val3), state(val4), county(val5), left(nullptr), right(nullptr) {}
};

class SchoolTree
{
    School* root;

private:
    School* replacementNode(School* node)
    {
        node = node->right;
        while (node != nullptr && node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }
public:
    SchoolTree() : root(nullptr) {}

    void insertPublic(string name, string address, string city, string state, string county)
    {
        root = insert(root, name, address, city, state, county);
    }

    School* insert(School* node, string name, string address, string city, string state, string county) {
        if (node == nullptr)
        {
            return new School(name, address, city, state, county);
        }

        if (name < node->name)
        {
            node->left = insert(node->left, name, address, city, state, county);
        }
        else if (name > node->name)
        {
            node->right = insert(node->right, name, address, city, state, county);
        }

        return node;
    }

    School* deleteByName(School* node, string name)
    {
        auto start_BSTdelete = chrono::high_resolution_clock::now();

        if (node == nullptr)
        {
            return node;
        }

        // Searching for correct node
        if (node->name > name) // Name "less" than current name?
        {
            node->left = deleteByName(node->left, name);
        }
        else if (node->name < name) // Name "greater" than current name?
        {
            node->right = deleteByName(node->right, name);
        }
        else // Node with correct name found
        {
            // Case 1: Leaf node
            if (node->left == nullptr)
            {
                School* temp = node->right;
                delete node;
                return temp;
            }

            // Case 2: 1 child (if one child is null, return the other)
            if (node->right == nullptr)
            {
                School* temp = node->left;
                delete node;
                return temp;
            }

            // Case 3: 2 children
            School* replacement = replacementNode(node);

            node->name = replacement->name;
            node->address = replacement->address;
            node->city = replacement->city;
            node->state = replacement->state;
            node->county = replacement->county;

            node->right = deleteByName(node->right, replacement->name);
        }

        auto end_BSTdelete = chrono::high_resolution_clock::now();
        auto time_BSTdelete = chrono::duration<double, micro>(end_BSTdelete - start_BSTdelete).count();

        cout << "Item deleted in " << time_BSTdelete << "us." << endl << endl;
        return node;
    }

    void findByName(string name)
    {
        auto start_BSTsearch = chrono::high_resolution_clock::now();

        School* current = root;

        while (current && current->name != name)
        {
            if (name < current->name)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }

        if (!current)
        {
            cout << "Error: School not found." << endl;
            return;
        }

        auto end_BSTsearch = chrono::high_resolution_clock::now();
        auto time_BSTsearch = chrono::duration<double, micro>(end_BSTsearch - start_BSTsearch).count();
        cout << "Item found in " << time_BSTsearch << "us." << endl;

        cout << "School found: " << current->name << endl;
        cout << "Address: " << current->address << endl;
        cout << "City   : " << current->city << endl;
        cout << "State  : " << current->state << endl;
        cout << "County : " << current->county << endl << endl;

        return;
    }

    void displayPreOrder(School* node)
    {
        if (node != nullptr)
        {
            cout << node->name << endl;
            displayPreOrder(node->left);
            displayPreOrder(node->right);
        }

        return;
    }

    void displayInOrder(School* node)
    {
        if (node != nullptr)
        {
            displayInOrder(node->left);
            cout << node->name << endl;
            displayInOrder(node->right);
        }

        return;
    }

    void displayPostOrder(School* node)
    {
        if (node != nullptr)
        {
            displayPostOrder(node->left);
            displayPostOrder(node->right);
            cout << node->name << endl;
        }

        return;
    }

    School* getRoot()
    {
        return root;
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

void interface(int choice, SchoolTree& tree)
{
    int input = -1;
    char doMore = ' ';
    string searchKey = "";

    if (choice < 0 || choice > 6)
    {
        cout << "Error: Invalid choice." << endl;
        interface(0, tree);
    }

    switch (choice)
    {
    case 0: // Initial call and "doing more" case
        cout << "What would you like to do? (Enter number)" << endl;
        cout << "1. Search for a school by name" << endl;
        cout << "2. Delete a school by name" << endl;
        cout << "3. Display stored schools (pre-order)" << endl;
        cout << "4. Display stored schools (in-order)" << endl;
        cout << "5. Display stored schools (post-order)" << endl;
        cout << "6. Quit" << endl;

        cin >> input;
        interface(input, tree);
        break;
    case 1: // School search
        cout << "Enter the name of a school (in all caps):" << endl;
        // This getline() took many attempts to properly include whitespaces;
        // solution found @ https://www.reddit.com/r/cpp_questions/comments/15n91xf/how_do_i_store_user_input_with_spaces_in_a_string/
        std::getline(std::cin >> std::ws, searchKey);
        tree.findByName(searchKey);

        cout << "Would you like to do more? (y/n)" << endl;
        cin >> doMore;
        switch (doMore)
        {
        case 'y':
            interface(0, tree);
            break;
        case 'n':
            interface(6, tree);
            break;
        }
        break;
    case 2: // School deletion
        cout << "Enter the name of a school (in all caps):" << endl;
        std::getline(std::cin >> std::ws, searchKey);
        tree.deleteByName(tree.getRoot(), searchKey);

        cout << "Would you like to do more? (y/n)" << endl;
        cin >> doMore;
        switch (doMore)
        {
        case 'y':
            interface(0, tree);
            break;
        case 'n':
            interface(6, tree);
            break;
        }
        break;
    case 3: // School display (pre-order)
        cout << "List of Schools (Pre-Order):" << endl;
        tree.displayPreOrder(tree.getRoot());

        cout << "Would you like to do more? (y/n)" << endl;
        cin >> doMore;
        switch (doMore)
        {
        case 'y':
            interface(0, tree);
            break;
        case 'n':
            interface(6, tree);
            break;
        }
        break;
    case 4: // School display (in-order)
        cout << "List of Schools (In-Order):" << endl;
        tree.displayInOrder(tree.getRoot());

        cout << "Would you like to do more? (y/n)" << endl;
        cin >> doMore;
        switch (doMore)
        {
        case 'y':
            interface(0, tree);
            break;
        case 'n':
            interface(6, tree);
            break;
        }
        break;
    case 5: // School display (post-order)
        cout << "List of Schools (Post-Order):" << endl;
        tree.displayPostOrder(tree.getRoot());

        cout << "Would you like to do more? (y/n)" << endl;
        cin >> doMore;
        switch (doMore)
        {
        case 'y':
            interface(0, tree);
            break;
        case 'n':
            interface(6, tree);
            break;
        }
        break;
    case 6: // Quit
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

    SchoolTree tree;
    for (vector<string> item : data)
    {
        if (item != data[0]) // Skips first line of data labels
        {
            auto start_BSTinsert = chrono::high_resolution_clock::now();
            tree.insertPublic(item[0], item[1], item[2], item[3], item[4]);
            auto end_BSTinsert = chrono::high_resolution_clock::now();
            auto time_BSTinsert = chrono::duration<double, micro>(end_BSTinsert - start_BSTinsert).count();
            cout << "Item inserted in " << time_BSTinsert << "us." << endl;
        }
    }

    cout << "ALAN URBANEK" << endl;
    cout << "CS 210 MIDTERM MILESTONE 3" << endl;
    cout << "SCHOOL DATABASE" << endl << endl;

    interface(0, tree);

    return 0;
}