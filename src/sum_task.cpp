// sum_task.cpp
#include "sum_task.h"

// Function to initialize the array
void initialize_array(int* a, int size) {
    for (int i = 0; i < size; i++) {
        a[i] = 1;
    }
}

// Function to compute the parallel sum using tasks
void parallel_sum(int* a, int size, int step_size, int& sum) {
    sum = 0;

    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < size; i += step_size) {
            int start = i, end = i + step_size - 1;
            std::cout << "Thread computing Sum(" << start << "," << end 
                      << ") from " << omp_get_thread_num() 
                      << " of " << omp_get_num_threads() << std::endl;

            #pragma omp task
            {
                int psum = 0;
                std::cout << "Task computing Sum(" << start << "," << end 
                          << ") from " << omp_get_thread_num() 
                          << " of " << omp_get_num_threads() << std::endl;
                for (int j = start; j <= end; j++) {
                    psum += a[j];
                }

                #pragma omp critical
                sum += psum;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    int a[ARR_SIZE];
    int sum = 0;

    // Initialize array
    initialize_array(a, ARR_SIZE);

    // Compute sum using OpenMP tasks
    parallel_sum(a, ARR_SIZE, STEP_SIZE, sum);

    // Print result
    std::cout << "Sum=" << sum << std::endl;

    return 0;
}
