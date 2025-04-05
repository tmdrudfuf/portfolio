#include "sort.h"
#include <vector>
#include <iostream>

using namespace std;

int sort::heap_comparisons = 0;

int sort::parent(int i) {
    return (i / 2);
}

int sort::left(int i) {
    return (2 * i + 1);
}

int sort::right(int i) {
    return (2 * (i + 1));
}

void sort::max_heapify(std::vector<Employee>& arr, int i) {
    int l = left(i);
    int r = right(i);
    int largest;
    if (l <= arr.size() && arr[l].id > arr[i].id) {
        largest = l;
        heap_comparisons++;
    }
    else {
        largest = i;
    }
    if (r <= arr.size() && arr[r].id > arr[largest].id) {
        largest = r;
        heap_comparisons++;
    }
    if (largest != i) {
        //std::swap(arr[i], arr[largest]);
        int tmp = largest;
        largest = arr[i].id;
        arr[i].id = tmp;
        max_heapify(arr, largest);
    }
}

void sort::build_max_heap(std::vector<Employee>& arr,int n) {
    n = arr.size()-1;
    for (int i = n / 2 ; i >= 0; i--) {
        max_heapify(arr, i);
    }
}

void sort::heapsort(std::vector<Employee>& arr) {
    for (auto g : arr) {
        cout << g.id << " ";
    }
    cout << endl;
    build_max_heap(arr, n);
    int n = arr.size();
    for (int i = n - 1; i >=1; i--) {
        for (auto g : arr) {
            cout << g.id << " ";
        }
        cout << endl;
        //std::swap(arr[0], arr[i]);
        int tmp = arr[1].id;
        arr[1].id = arr[i].id;
        arr[i].id = tmp;
        n--;
        max_heapify(arr, i);
    }
    for (auto g : arr) {
        cout << g.id << " ";
    }
    cout << endl;
}

int sort::get_comparisons() {
    return heap_comparisons;
}