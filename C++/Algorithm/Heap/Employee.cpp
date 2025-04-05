#include "Employee.h"

Employee::Employee() : name(""), id(99999999), age(0), year(0), job("") {}

Employee::Employee(std::string n, int i, int a, int y, std::string j) :
    name(n), id(i), age(a), year(y), job(j) {
}

void Employee::say(std::ofstream& o) {
    o << name << "|" << id << "|" << age << "|" << job << "|" << year << std::endl;
}

void Employee::say() {
    std::cout << name << "|" << id << "|" << age << "|" << job << "|" << year << std::endl;
}

void Employee::printInfo() {
    std::cout << "Name: " << name << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Job title: " << job << std::endl;
    std::cout << "Hire year: " << year << std::endl;
}

void Employee::printOneLiner() {
    std::cout << "Name: " << name
        << ", Age: " << age
        << ", Job: " << job
        << ", Hired: " << year << std::endl;
}