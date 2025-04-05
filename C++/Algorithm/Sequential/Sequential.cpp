// InputFile.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "Info.h"
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
    if (argc < 2) {
        cout << "Please include a command line parameter" << endl;
        exit(1);
    }// check error
    ifstream ifs;
    ifs.open(argv[1], ios::in);

    string tmp;
    getline(ifs, tmp);
    int n = stoi(tmp);
    Info** getInfo = new Info * [n];
    //Info** emp = new emp * [n];
    
  
    cout << "There are " << n << " people in this roster" << endl;
    /*for (int i = 0; i < n, i++) {
        string name, position;
        int age, year, id;
        getline(ifs, name, '|');
        emp[i] = name;

    }*/
    for (int i = 0; i < n; i++) {
        string name, position;
        int age, year, id;
        //get information and organize
        getline(ifs, name, '|');
        getline(ifs, tmp, '|');
        id = stoi(tmp);
        getline(ifs, tmp, '|');
        age = stoi(tmp);
        getline(ifs, position, '|');
        getline(ifs, tmp);
        year = stoi(tmp);
        getInfo[i] = new Info(name, id, age, position, year);
        getInfo[i]->printInfo();
        //emp[i] = new Info(age);
        

    }
    const Info* agee = getInfo[2];
    for (int i = 0; i < n;i++) {
        const Info* agee = getInfo[i];
        cout << agee << endl;
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
