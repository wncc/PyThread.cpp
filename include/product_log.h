// product_log.h
#ifndef PRODUCT_LOG_H
#define PRODUCT_LOG_H

#include <cmath> // Include cmath for log and exp functions

// Function declarations
void initialize_array(int* a, int size, int value);
double compute_log_sum(int* a, int size, int num_threads);
double compute_product(double log_sum);

#endif // PRODUCT_LOG_H
