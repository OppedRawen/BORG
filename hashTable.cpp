#include <iostream>
#include <vector>

using namespace std;
// hasth table that uses linear probing
class HashTable {
public:
    HashTable(size_t size) : table(size, -1), num_elements(0) {}

    int Hash(int value) {
        return value % table.size();
    }

    int Add(int value) {
        if (num_elements >= table.size()) {
            return -1;
        }

        int index = Hash(value);
        while (table[index] != -1) {
            index = (index + 1) % table.size();
        }

        table[index] = value;
        num_elements++;
        return index;
    }

    int Find(int value) {
        int index = Hash(value);
        int count = 0;

        while (table[index] != value) {
            if (table[index] == -1 || count >= table.size()) {
                return -1;
            }

            index = (index + 1) % table.size();
            count++;
        }

        return index;
    }

private:
    vector<int> table;
    size_t num_elements;
};

int main() {
    HashTable hashTable(27);

    int choice, value, result;

    while (true) {
        cout << "1. Add value 2. Find value 3. Exit. Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter the value to add: ";
            cin >> value;
            result = hashTable.Add(value);
            if (result == -1) {
                cout << "The table is full, cannot add value.\n";
            } else {
                cout << "Value added at index " << result << ".\n";
            }
            break;
        case 2:
            cout << "Enter the value to find: ";
            cin >> value;
            result = hashTable.Find(value);
            if (result == -1) {
                cout << "Value not found in the table.\n";
            } else {
                cout << "Value found at index " << result << ".\n";
            }
            break;
        case 3:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

