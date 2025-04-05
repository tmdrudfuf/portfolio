#include "Info.h"
#include <iostream>

//Info::emp(int ag) {
//	empAge = ag;
//}

Info::Info(string n, int i, int a, string p, int y) {
	name = n;
	id = i;
	age = a;
	position = p;
	year = y;
	//variable
}
void Info::printInfo() {
	//print out the text here
	/*cout << "Name: " << name << endl
		<< "ID: " << id << endl
		<< "Age: " << age << endl
		<< "Job: " << position << endl
		<< "Hire year: " << year << endl;*/
	cout << "Name:         " << name << endl;
	cout << "ID:           " << id << endl;
	cout << "Age:          " << age << endl;
	cout << "Job:          " << position << endl;
	cout << "Hire Year:    " << year << endl;
}