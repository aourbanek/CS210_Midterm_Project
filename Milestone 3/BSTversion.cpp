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
    School* left;
    School* right;
    School(string val1, string val2, string val3, string val4, string val5) : name(val1), address(val2), city(val3), state(val4), county(val5), left(nullptr), right(nullptr) {}
};

class SchoolTree
{
    School* root;

private:
    // Implementation of similar function from CS 102
    // (For node deletion)
    School* replacementNode(School* node)
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            return nullptr;
        }
        else if (node->left != nullptr && node->right == nullptr)
        {
            return node->left;
        }
        else if (node->left == nullptr && node->right != nullptr)
        {
            return node->right;
        }

        School* parent = node;
        School* current = node->right;
        while (current->left != nullptr)
        {
            parent = current;
            current = current->left;
        }

        current->left = node->left;
        if (node->right != current)
        {
            parent->left = current->right;
            current->right = node->right;
        }

        return current;
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
        else
        {
            node->right = insert(node->right, name, address, city, state, county);
        }

        return node;
    }

    School* deleteByName(School* node, string name)
    {
        if (root == nullptr)
        {
            return root;
        }

        // Searching for correct node
        if (name < root->name) // Name "less" than current name?
        {
            root->left = deleteByName(root->left, name);
        }
        else if (name > root->name) // Name "greater" than current name?
        {
            root->right = deleteByName(root->right, name);
        }
        else // Node with correct name found
        {
            // Case 1: Leaf node
            if (root->left == nullptr && root->right == nullptr)
            {
                delete root;
                return nullptr;
            }

            // Case 2: 1 child (if one child is null, return the other)
            else if (root->left == nullptr)
            {
                School* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr)
            {
                School* temp = root->left;
                delete root;
                return temp;
            }

            // Case 3: 2 children
            else
            {
                School* temp = replacementNode(root->right);

                root->name = temp->name;
                root->address = temp->address;
                root->city = temp->city;
                root->state = temp->state;
                root->county = temp->county;

                root->right = deleteByName(root->right, temp->name);
            }
        }

        return node;
    }

    void findByName(string name)
    {
        School* current = root;

        while (current && current->name != name)
        {
            if (current->name < name)
            {
                current = current->left;
            }
            else if (current->name > name)
            {
                current = current->right;
            }
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

    void displayPreOrder(School* node)
    {
        School* temp = root;
        cout << "List of Schools (Pre-Order):" << endl;
        while (temp != nullptr)
        {
            cout << temp->name << endl;
            displayPreOrder(temp->left);
            displayPreOrder(temp->right);
        }

        cout << endl;

        return;
    }

    void displayInOrder(School* node)
    {
        School* temp = root;
        cout << "List of Schools (In-Order):" << endl;
        while (temp != nullptr)
        {
            displayPreOrder(temp->left);
            cout << temp->name << endl;
            displayPreOrder(temp->right);
        }

        cout << endl;

        return;
    }

    void displayPostOrder(School* node)
    {
        School* temp = root;
        cout << "List of Schools (In-Order):" << endl;
        while (temp != nullptr)
        {
            displayPreOrder(temp->left);
            displayPreOrder(temp->right);
            cout << temp->name << endl;
        }

        cout << endl;

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

void interface(int choice, SchoolTree tree)
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
            tree.insertPublic(item[0], item[1], item[2], item[3], item[4]);
        }
    }

    cout << "ALAN URBANEK" << endl;
    cout << "CS 210 MIDTERM MILESTONE 2" << endl;
    cout << "SCHOOL DATABASE" << endl << endl;

    interface(0, tree);

    return 0;
}
