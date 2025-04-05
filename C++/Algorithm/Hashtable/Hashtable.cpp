#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include "Employee.h"

using namespace std;

// Function to generate a hash key from a string (sum of ASCII values)
int generateHashKey(const string& name) {
    int key = 0;
    for (size_t i = 0; i < name.length(); ++i) {
        key += static_cast<int>(name[i]) * (i + 1); // 문자의 ASCII 값에 위치를 곱함
    }
    return key;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Please include a command line parameter" << endl;
        return 1;
    }

    ifstream ifs(argv[1]);
    if (!ifs) {
        cout << "Could not find file: " << argv[1] << endl;
        return 1;
    }

    int m, n;
    ifs >> m >> n;
    ifs.ignore(); // Consume the newline character after reading n

    vector<vector<Employee*>> staff(m);

    // Multiplication method constant
    const double A = (sqrt(5) - 1) / 2;

    // Part 1: Insert records into the hash table
    for (int i = 0; i < n; i++) {
        string name, sid, age, job, year;
        getline(ifs, name, '|');
        getline(ifs, sid, '|');
        getline(ifs, age, '|');
        getline(ifs, job, '|');
        getline(ifs, year);

        int id = stoi(sid);
        int key = generateHashKey(name);

        // Division method (주석 처리)
        // int index = key % m;

        // Multiplication method
        double ky = key * A;
        double frac = ky - floor(ky);
        int index = static_cast<int>(m * frac);

        int collisions = staff[index].size();
        cout << "Adding " << name << " to table at index " << index << " (" << collisions << " collisions)" << endl;
        Employee* emp = new Employee(name, id, stoi(age), job, stoi(year));
        staff[index].push_back(emp);
    }

    // Part 2: Look up records and count collisions
    string separator;
    getline(ifs, separator); // Read and ignore the "***" line

    int q;
    ifs >> q;
    ifs.ignore(); // Consume the newline character after reading q

    int totalSearchCollisions = 0;

    for (int i = 0; i < q; i++) {
        string queryName;
        getline(ifs, queryName);

        int queryKey = generateHashKey(queryName);

        // Division method 
        // int queryIndex = queryKey % m;

        // Multiplication method
        double queryKy = queryKey * A;
        double queryFrac = queryKy - floor(queryKy);
        int queryIndex = static_cast<int>(m * queryFrac);

        int collisions = 0;
        bool found = false;

        for (Employee* emp : staff[queryIndex]) {
            if (emp->name == queryName) {
                cout << "Found " << queryName << " after " << collisions << " collisions at index " << queryIndex << " in the hashtable." << endl;
                cout << "COMPLETE RECORD: " << emp->name << "|" << emp->id << "|" << emp->age << "|" << emp->job << "|" << emp->year << endl;
                found = true;
                break;
            }
            collisions++;
        }

        if (!found) {
            cout << queryName << " not found" << endl;
        }
        else {
            totalSearchCollisions += collisions;
        }
    }

    cout << "Total collisions during lookup phase: " << totalSearchCollisions << endl;

    // Clean up allocated memory
    for (auto& vec : staff) {
        for (Employee* emp : vec) {
            delete emp;
        }
    }

    return 0;
}
