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
	getline(ifs, tmp);
	int q = stoi(tmp);

	double totalWork = 0;
	
	for (int i = 0; i < q;i++) {
		getline(ifs, tmp);
		int x = stoi(tmp);

		//intiation
		int low = 0;  // begin of the range
		int high = n; // end of the range
		int count = 0; //counting 

		//binary
		while (low < high) {
			int mid = (low + high) / 2;
			count++;
			
			if (staff[mid]->id >= x) {
				high = mid; // search narrow to A[low:mid]
			}
			else {
				low = mid + 1;  //search narrow to A[mid+1:high]
			}
		}
		if (low < n && staff[low]->id == x) {
			staff[low]->printInfo();
			cout << "at index" << low << "after " << count << "comparison" << endl;
		}
		else {
			cout << "Emplyee with the ID" << x << "can not found" << endl;
		}
		totalWork += count;
	}

	
	
	/*for (int i = 0; i < q; i++) {
		getline(ifs, tmp);
		int x = stoi(tmp);
		for (int j = 0; j < n; j++) {
			if (staff[j]->id == x) {
				cout << "FOUND! ";
				staff[j]->printOneLiner();
				cout << " at index " << j << " after " << (j + 1) << " comparisons." << endl;
				totalWork += (j + 1);
			}
		}
	}*/
	//the average is the total number of comparisons divided by the number of queries
	cout << "Done! Average amount of work per query: " << (totalWork / q) << " comparisons." << endl;


	return 0;
}

