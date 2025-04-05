#include <iostream>
#include <fstream>
#include "Employee.h"

using namespace std;

int partition(Employee** employees, int p, int r, int& count, int n) {
	Employee* pivot = employees[r];
	int i = p - 1;
	for (int j = p; j < r; j++) {
		count++; // Increment comparison count
		if (employees[j]->id <= pivot->id) {
			i++;
			swap(employees[i], employees[j]);
			/*for (int j = 0; j < n; j++) {
				cout << employees[j]->id << " ";
			}
			cout << endl;*/
		}
	}
	swap(employees[i + 1], employees[r]);
	/*for (int j = 0; j < n; j++) {
		cout << employees[j]->id << " ";
	}
	cout << endl;*/
	return i + 1;
}

void quickSort(Employee** employees, int p, int r, int& count, int n) {
	
	if (p < r) {
		
		int q = partition(employees, p, r, count, n);
		quickSort(employees, p, q - 1, count, n);
		
		quickSort(employees, q + 1, r, count, n);
		
	}
	
}

int randomPartition(Employee** employees, int p, int r, int& count, int n) {
	//random number
	srand(time(0) + rand());
	int i = p + rand() % (r - p + 1);
	
	swap(employees[r], employees[i]);
	return partition(employees, p, r, count,n);
}

void randomQ(Employee** employees, int p, int r, int& count, int n) {
	if (p < r) {
		int q = randomPartition(employees, p, r, count, n);

		randomQ(employees, p, q - 1, count, n);
		randomQ(employees, q + 1, r, count, n);
	}
}
void treQ(Employee** employees, int p, int r, int& count, int n) {
	while (p < r) {

		int q = partition(employees, p, r, count, n);

		treQ(employees, p, q - 1, count, n); // Tail recursive call
		p = q + 1;
	}
}
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
	int count = 0;

	//choose which sort I want to use this time
	//quickSort(staff, 0, n - 1, count, n);
	randomQ(staff, 0, n - 1, count, n);
	//treQ(staff, 0, n - 1, count, n);
	double totalWork = 0;

	for (int i = 0; i < q;i++) {
		/*getline(ifs, tmp);*/
		/*int x = stoi(tmp);*/

		//intiation
		int low = 0;  // begin of the range
		int high = n; // end of the range
		int count = 0; //counting 

		//buble sort
		for (int i = 0; i < n - 1; i++) {
			for (int j = n - 1; j >= i + 1;j--) {
				count++;
				if (staff[j]->id < staff[j - 1]->id) {
					Employee* tem = staff[j];
					staff[j] = staff[j - 1];
					staff[j - 1] = tem;
					for (int k = 0;k < n;k++) {
						cout << staff[k]->id << " ";

					}
					cout << endl;

				}
			}
		}

		totalWork += count;
	}
	//the average is the total number of comparisons divided by the number of queries
	cout << "It took " << count << " comparisons to sort this list" << endl;

	for (int i = 0; i < n; i++) {
		ky << staff[i]->name << "|" << staff[i]->id << "|" << staff[i]->age << "|" << staff[i]->job << "|" << staff[i]->year << endl;
	}
	//ofs << "ky" << endl;
	ky.close();
	//cout << staff[2] << endl;


	return 0;
}

