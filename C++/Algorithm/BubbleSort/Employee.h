#pragma once

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Employee {
public:
	string name;
	int id;
	int age;
	string job;
	int year;

	Employee();
	Employee(string n, int i, int a, int y, string j);

	void say(ofstream o);
	void say();
	void printInfo();
	void printOneLiner();
};




