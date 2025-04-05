#ifndef SORT_H
#define SORT_H

#include <vector>
#include "Employee.h"

class sort {
public:
    void merge(std::vector<Employee>& mi, int p, int q, int r);
    void mergesort(std::vector<Employee>& wi, int p, int r);
    int get_comparisons();
    int get_mergesort_calls();
    int get_merge_calls();

private:
    static int merge_comparisons;
    static int mergesort_calls;
    static int merge_calls;
};

#endif