// array_concat.cpp
#include "array_concat.h"
#include <omp.h>
#include <iostream>
using namespace std;

// Function to concatenate two arrays in parallel
void concatenate(int arr1[], int arr2[], int n1, int n2, int arr3[]) {
    #pragma omp parallel for
    for (int i = 0; i < n1; i++) {
        arr3[i] = arr1[i];
    }
    
    #pragma omp parallel for
    for (int i = 0; i < n2; i++) {
        arr3[n1 + i] = arr2[i];
    }
}

int main() {
    int n1 = 5, n2 = 5;
    int arr1[n1] = {1, 2, 3, 4, 5};
    int arr2[n2] = {6, 7, 8, 9, 10};
    int arr3[n1 + n2];

    // Set the number of threads
    omp_set_num_threads(2);

    // Concatenate the arrays
    concatenate(arr1, arr2, n1, n2, arr3);

    // Print the concatenated array
    for (int i = 0; i < n1 + n2; i++) {
        cout << arr3[i] << " ";
    }
    cout << endl;

    return 0;
}