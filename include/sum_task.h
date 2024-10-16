// sum_task.h
#ifndef SUM_TASK_H
#define SUM_TASK_H

#include <iostream>
#include <omp.h>

// Constants
#define ARR_SIZE 600
#define STEP_SIZE 100

// Function declarations
void initialize_array(int* a, int size);
void parallel_sum(int* a, int size, int step_size, int& sum);

#endif // SUM_TASK_H
