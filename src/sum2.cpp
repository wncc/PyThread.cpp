#include "parallel_sum.h"

// Global array definition
int a[ARR_SIZE];

// Function to initialize the array
void initialize_array() {
    for (int i = 0; i < ARR_SIZE; i++) {
        a[i] = 1;  // Fill the array with 1s
    }
}

// Function to compute the sum in parallel using OpenMP
int compute_parallel_sum() {
    int sum = 0;
    int numt, tid;

    // Start measuring time
    double t1 = omp_get_wtime();

    #pragma omp parallel default(shared) private(tid)
    {
        int from, to, psum = 0;
        tid = omp_get_thread_num();
        numt = omp_get_num_threads();
        from = (ARR_SIZE / numt) * tid;
        to = (ARR_SIZE / numt) * (tid + 1) - 1;

        for (int i = from; i <= to; i++) {
            psum += a[i];
        }

        #pragma omp critical
        {
            sum += psum;
        }
    }

    double t2 = omp_get_wtime();  // End time

    printf("Time taken = %f seconds\n", t2 - t1);
    return sum;
}

// Main function
int main(int argc, char *argv[]) {
    // Initialize array
    initialize_array();

    // Compute sum
    int sum = compute_parallel_sum();

    // Print the result
    printf("Sum = %d\n", sum);
    return 0;
}
