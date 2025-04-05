#include "sort.h"
#include "Employee.h"
#include <vector>
#include <iostream>

int sort::merge_comparisons = 0;
int sort::mergesort_calls = 0;
int sort::merge_calls = 0;

//merge
void sort::merge(std::vector<Employee>& mi, int p, int q, int r) {
    merge_calls++;
    int n1 = q - p + 1;
    int n2 = r - q;

    std::vector<Employee> L(n1);
    std::vector<Employee> R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = mi[p + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = mi[q + j + 1];
    }

    int i = 0, j = 0, k = p;
    while (i < n1 && j < n2) {
        merge_comparisons++;
        if (L[i].id <= R[j].id) {
            mi[k] = L[i];
            i++;
        }
        else {
            mi[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        merge_comparisons++;
        mi[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        merge_comparisons++;
        mi[k] = R[j];
        j++;
        k++;
    }
    /*for (auto g : mi) {
        cout << g.id << " ";
     }
    cout << endl;*/
}
//merge sort 
void sort::mergesort(std::vector<Employee>& wi, int p, int r) {
    mergesort_calls++;
    if (p >= r) {
        return;
    }
    int q = (p + r) / 2;
    mergesort(wi, p, q);
    mergesort(wi, q + 1, r);
    merge(wi, p, q, r);
}

int sort::get_comparisons() {
    return merge_comparisons;
}

int sort::get_mergesort_calls() {
    return mergesort_calls;
}

int sort::get_merge_calls() {
    return merge_calls;
}