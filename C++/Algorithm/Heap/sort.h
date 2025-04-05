#ifndef SORT_H
#define SORT_H

#include <vector>
#include "Employee.h"

class sort {
public:
    int n;
    int tmp;
    int parent(int i);
    int left(int i);
    int right(int i);
    void max_heapify(std::vector<Employee>& arr, int i);
    void build_max_heap(std::vector<Employee>& arr, int n);
    void heapsort(std::vector<Employee>& arr);
    int get_comparisons();

private:
    static int heap_comparisons;
};

#endif