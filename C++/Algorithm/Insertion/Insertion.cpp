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

	double totalWork = 0;
	//insertion sort
	for (int i = 0; i < q; i++) {
		int count = 0;

		for (int j = 1; j < n; j++) {
			Employee* key = staff[j];
			int k = j - 1;

			while (k >= 0 && staff[k]->id > key->id) {
				staff[k + 1] = staff[k];
				k--;
				count++;
			}
			staff[k + 1] = key;

			// Only print if it's NOT the last pass (when the sort is complete)
			if (k + 1 != j) { // Only print if a shift occurred.
				for (int l = 0; l < n; l++) {
					cout << staff[l]->id << " ";
				}
				cout << endl;
			}
				
			
		}
		

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

