#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Employee.h"
#include "sort.h"

int main(int argc, char** argv) {
    //checking the errors that can be occured
    if (argc < 2) {
        std::cout << "Please include a command line parameter" << std::endl;
        return 1;
    }

    std::ifstream ifs(argv[1]);
    if (!ifs.is_open()) {
        std::cerr << "Could not find file: " << argv[1] << std::endl;
        return 1;
    }

    std::string tmp;
    std::getline(ifs, tmp);
    int n = std::stoi(tmp);

    std::vector<Employee> staff(n);

    for (int i = 0; i < n; i++) {
        std::getline(ifs, staff[i].name, '|');
        std::getline(ifs, tmp, '|');
        staff[i].id = std::stoi(tmp);
        std::getline(ifs, tmp, '|');
        staff[i].age = std::stoi(tmp);
        std::getline(ifs, staff[i].job, '|');
        std::getline(ifs, tmp);
        staff[i].year = std::stoi(tmp);
    }
    // call method merge
    sort sorter;
    sorter.mergesort(staff, 0, staff.size() - 1);

    std::ofstream ky("output.txt");
    ky << n << std::endl;

    for (const auto& emp : staff) {
        ky << emp.name << "|" << emp.id << "|" << emp.age << "|" << emp.job << "|" << emp.year << std::endl;
    }
    ky.close();

    std::cout << "It took " << sorter.get_comparisons() << " comparisons to sort this list" << std::endl;

    return 0;
}