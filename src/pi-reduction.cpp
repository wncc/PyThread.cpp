// pi_calculator.cpp
#include "pi_calculator.h"
#include <omp.h>
#include <iostream>
using namespace std;

#define THREAD_COUNT 4
// Function to calculate Pi using the given number of threads
double calculate_pi(int num_threads) {
    double pi = 0.0;
    double step = 1.0 / step_count;

    #pragma omp parallel for reduction(+ : pi) num_threads(num_threads)
    for (long i = 0; i < step_count; i++) {
        double x = (i + 0.5) * step;
        pi += 4.0 / (1 + x * x);
    }

    pi *= step;
    return pi;
}


int main() {
    // Calculate Pi using the specified number of threads
    double pi = calculate_pi(THREAD_COUNT);

    // Print the result
    cout << "Pi = " << pi << endl;

    return 0;
}
