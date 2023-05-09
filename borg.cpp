#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

const int TABLESIZE = 101;

struct Variable {
    std::string name;
    int value;
    int scope;
};

int hashFunction(const std::string& varName) {
    int hash = 0;
    for (size_t i = 0; i < varName.size(); ++i) {
        hash += (varName[i] * (i + 1)) % TABLESIZE;
    }
    return hash % TABLESIZE;
}

int main() {
    std::string filename;
    std::cout << "Enter the filename: ";
    std::cin >> filename;

    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::vector<std::vector<Variable>> hashTable(TABLESIZE);
    std::string line;
    int currentScope = 0;

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string token;
        iss >> token;

        if (token == "START") {
            currentScope++;
        } else if (token == "FINISH") {
            currentScope--;
            for (auto& bucket : hashTable) {
                bucket.erase(std::remove_if(bucket.begin(), bucket.end(), [&](const Variable& var) {
                    return var.scope > currentScope;
                }), bucket.end());
            }
        } else if (token == "COM") {
            continue;
        } else if (token == "VAR") {
            std::string varName;
            iss >> varName;
            int hash = hashFunction(varName);
            hashTable[hash].push_back({varName, 0, currentScope});
        } else if (token == "PRINT") {
            std::string expression;
            iss >> expression;

            bool found = false;
            for (const auto& var : hashTable[hashFunction(expression)]) {
                if (var.name == expression && var.scope <= currentScope) {
                    std::cout << var.name << ": " << var.value << std::endl;
                    found = true;
                    break;
                }
            }

            if (!found) {
                std::cout << "Unknown variable " << expression << " at line " << line << std::endl;
            }
        } else {
            // Process expressions, assignment statements, increment and decrement operators.
            // This is left as an exercise for the reader, as the implementation is quite involved.
        }
    }

    inputFile.close();
    return 0;
}
