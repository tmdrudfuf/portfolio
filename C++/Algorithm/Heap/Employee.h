#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>
#include <fstream>

class Employee {
public:
    std::string name;
    int id;
    int age;
    std::string job;
    int year;

    Employee();
    Employee(std::string n, int i, int a, int y, std::string j);

    void say(std::ofstream& o);
    void say();
    void printInfo();
    void printOneLiner();
};

#endif