#include <iostream>
#include <fstream>
#include "Employee.h"

int main(int argc, char** argv)
{

	//first, make sure we didn't forget the filename
	if (argc < 2) {
		cout << "Please include a command line parameter" << endl;
		exit(1);
	}

	ifstream ifs;
	ifs.open(argv[1], ios::in);

	//next, make sure the file really exists
	if (!ifs) {
		cout << "Could not find file: " << argv[1] << endl;
		exit(1);
	}

	//read the first line of the file, to see how many employees there are
	string tmp;
	getline(ifs, tmp);
	int n = stoi(tmp);
	ofstream ky("output.txt");
	ky << n << endl;

	//allocate an array of the correct size, to store the employee objects
	Employee** staff = new Employee * [n];

	//read each line of the file, and instantiate a new employee object. Put it into the array.
	for (int i = 0; i < n; i++) {
		staff[i] = new Employee();
		string tmp;
		getline(ifs, staff[i]->name, '|');
		getline(ifs, tmp, '|');
		staff[i]->id = stoi(tmp);
		getline(ifs, tmp, '|');
		staff[i]->age = stoi(tmp);
		getline(ifs, staff[i]->job, '|');
		getline(ifs, tmp);
		staff[i]->year = stoi(tmp);
	}

	//how many queries will there be?
	int q = n;
	int t = 0;
	double totalWork = 0;
	
	//selection sort
	for (int i = 0;i < n - 1;i++) {
		int minIndex = i;
		int count = 0;
		for (int j = i + 1;j < n;j++) {
			count++;
			if (staff[j]->id < staff[minIndex]->id) {
				minIndex = j;

			}

		}
		t = staff[i]->id;
		staff[i]->id = staff[minIndex]->id;
		staff[minIndex]->id = t;
		/*for (int l = 0; l < n; l++) {
			cout << staff[l]->id << " ";
		}cout << endl;*/
		totalWork += count;
	}	
	
	//the average is the total number of comparisons divided by the number of queries
	cout << "It took " << totalWork << " comparisons to sort this list" << endl;

	for (int i = 0; i < n; i++) {
		ky << staff[i]->name << "|" << staff[i]->id << "|" << staff[i]->age << "|" << staff[i]->job << "|" << staff[i]->year << endl;
	}
	ky.close();


	return 0;
}

