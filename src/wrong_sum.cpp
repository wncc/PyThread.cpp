#include "paralle_sum.h"
#include <omp.h>
#include <iostream>

int parallel_sum(const int arr[], int size, int step_size) {
    int sum = 0;

    #pragma omp parallel
    {
        #pragma omp single // Ensure only one thread creates tasks
        {
            for (int i = 0; i < size; i += step_size) {
                int start = i, end = i + step_size - 1;

                // Ensure end index is within bounds
                if (end >= size) end = size - 1;

                #pragma omp task // Create a task for summation
                {
                    int psum = 0;
                    std::cout << "Task computing Sum(" << start << "," << end << ") from "
                              << omp_get_thread_num() << " of " << omp_get_num_threads() << std::endl;
                    
                    for (int j = start; j <= end; j++) {
                        psum += arr[j];
                    }

                    #pragma omp critical // Critical section to update global sum
                    {
                        sum += psum;
                    }
                }
            }

            // Ensure all tasks are completed before returning the final sum
            #pragma omp taskwait
        }
    }

    return sum;
}


int main(int argc, char* argv[]) {
    #define ARR_SIZE 600
    #define STEP_SIZE 100

    int a[ARR_SIZE];
    
    // Initialize array with values
    for (int i = 0; i < ARR_SIZE; i++) {
        a[i] = 1;
    }

    // Call the parallel sum function
    int sum = parallel_sum(a, ARR_SIZE, STEP_SIZE);

    std::cout << "Sum = " << sum << std::endl;

    return 0;
}
