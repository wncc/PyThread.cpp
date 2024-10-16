#include <stdio.h>
#include <omp.h>
#include <iostream>
#include <cmath> // Include cmath for log and exp functions
using namespace std;

#define ARR_SIZE 100

int main(int argc, char *argv[]) {
    int a[ARR_SIZE];
    int i;
    double log_sum = 0.0; // Use double to store the sum of logarithms

    for (i = 0; i < ARR_SIZE; i++) {
        a[i] = 2;
    }

    #pragma omp parallel for default(shared) reduction(+:log_sum)
    for(i = 0; i < ARR_SIZE; i++) {
        log_sum += log(a[i]);
    }

    double prod = exp(log_sum); // Exponentiate the sum of logarithms to get the product

    cout << "Product=" << prod << endl;
    return 0;
}