#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>

using namespace std;

const int TABLESIZE = 100;

struct Variable {
    string name;
    int value;
    Variable(string name, int value) : name(name), value(value) {}
};

int computeHash(string varName) {
    int sum = 0;
    for (int i = 0; i < varName.size(); i++) {
        sum += (varName[i] * (i+1));
    }
    return sum % TABLESIZE;
}

int main() {
    vector<unordered_map<int, Variable>> scopes;
    ifstream infile("borg_program.borg");
    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        string command;
        iss >> command;
        if (command == "START") {
            scopes.push_back(unordered_map<int, Variable>());
        } else if (command == "FINISH") {
            if (!scopes.empty()) {
                scopes.pop_back();
            }
        } else if (command == "COM") {
            continue;
        } else if (command == "VAR") {
            string varName, equalSign;
            int value;
            iss >> varName >> equalSign >> value;
            int hash = computeHash(varName);
            scopes.back().insert({hash, Variable(varName, value)});
        } else if (command == "PRINT") {
            string varName;
            iss >> varName;
            int hash = computeHash(varName);
            for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
                auto varIt = it->find(hash);
                if (varIt != it->end()) {
                    cout << varIt->second.name << " IS " << varIt->second.value << endl;
                    break;
                }
            }
            if (scopes.empty() || scopes.back().find(hash) == scopes.back().end()) {
                cout << varName << " IS UNDEFINED" << endl;
            }
        } else {
            string varName = command;
            string operation;
            iss >> operation;
            int hash = computeHash(varName);
            if (operation == "=") {
                int value;
                iss >> value;
                for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
                    auto varIt = it->find(hash);
                    if (varIt != it->end()) {
                        varIt->second.value = value;
                        break;
                    }
                }
            } else if (operation == "++") {
                for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
                    auto varIt = it->find(hash);
                    if (varIt != it->end()) {
                        varIt->second.value++;
                        break;
                    }
                }
            } else if (operation == "--") {
                for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
                    auto varIt = it->find(hash);
                    if (varIt != it->end()) {
                    varIt->second.value--;
                    break;
                }
            } 
        }
        else if (operation == "*") {
                int factor;
                iss >> factor;
                for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
                    auto varIt = it->find(hash);
                    if (varIt != it->end()) {
                        cout << varIt->second.name << " * 2 IS " << varIt->second.value * factor << endl;
                        break;
                    }
                }
            }
    }
    return 0;
}
}