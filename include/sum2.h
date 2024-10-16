#ifndef PARALLEL_SUM_H
#define PARALLEL_SUM_H

#include <omp.h>
#include <stdio.h>

#define ARR_SIZE 10000000

// Global array declaration
extern int a[ARR_SIZE];

// Function declarations
void initialize_array();  // Initialize the array with values
int compute_parallel_sum();  // Compute the sum using OpenMP

#endif
