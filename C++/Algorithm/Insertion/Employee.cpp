#include "Employee.h"


Employee::Employee()
{
	name = "";
	id = 99999999;
	age = year = 0;
	job = "";
}

Employee::Employee(string n, int i, int a, int y, string j) {
	name = n;
	id = i;
	age = a;
	year = y;
	job = j;
}

void Employee::say(ofstream o)
{
	o << name << "|" << id << "|" << age << "|" << job << "|" << year << endl;
}
void Employee::say()
{
	cout << name << "|" << id << "|" << age << "|" << job << "|" << year << endl;
}
void Employee::printInfo() {
	cout << "Name: " << name << endl;
	cout << "ID: " << id << endl;
	cout << "Age: " << age << endl;
	cout << "Job title: " << job << endl;
	cout << "Hire year: " << year << endl;
}

void Employee::printOneLiner() {
	cout << "Name: " << name
		<< ", Age: " << age
		<< ", Job: " << job
		<< ", Hired: " << year << endl;
}


