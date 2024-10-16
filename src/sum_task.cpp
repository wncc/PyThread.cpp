#include <iostream>
#include <omp.h>

#define ARR_SIZE 600
#define STEP_SIZE 100

int main(int argc, char *argv[]) {
    int a[ARR_SIZE];
    int sum = 0;

    for(int i = 0; i < ARR_SIZE; i++) {
        a[i] = 1;
    }

    #pragma omp parallel
    {
        #pragma omp for
        for(int i = 0; i < ARR_SIZE; i += STEP_SIZE) {
            int start = i, end = i + STEP_SIZE - 1;
            std::cout << "Thread computing Sum(" << start << "," << end << ") from " << omp_get_thread_num() << " of " << omp_get_num_threads() << std::endl;

            #pragma omp task
            {
                int psum = 0;
                std::cout << "Task computing Sum(" << start << "," << end << ") from " << omp_get_thread_num() << " of " << omp_get_num_threads() << std::endl;
                for(int j = start; j <= end; j++) {
                    psum += a[j];
                }
                #pragma omp critical
                sum += psum;
            }
        }
    }

    printf("Sum=%d\n", sum);
    return 0;
}