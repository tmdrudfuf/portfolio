#pragma once
#include <string>

using namespace std;

class Info
{//field
private:
	string name;
	int id;
	int year;
	int age;
	string position;


public:
	Info(string, int, int, string, int);
	void printInfo();
};

