// dot_product.c

#include "dot_product.h"

int calculate_dot_product(int A[], int B[], int size) {
    int dot = 0;

    // Parallel for loop with dynamic scheduling and reduction
    #pragma omp parallel for schedule(dynamic, 100) reduction(+:dot)
    for (int i = 0; i < size; i++) {
        dot += A[i] * B[i];
    }

    return dot;
}


int main(int argc, char* argv[]) {
    int A[1000], B[1000];

    // Initialize arrays
    for (int i = 0; i < 1000; i++) {
        A[i] = 1;
        B[i] = 1;
    }

    // Calculate dot product
    int dot = calculate_dot_product(A, B, 1000);

    // Print the result
    printf("Dot product = %d\n", dot);

    return 0;
}
