#include "matrix_vector.h"
#include <omp.h>
#include <iostream>
void matrix_vector_multiply(int A[1000][1000], int B[1000], int y[1000]) {
    #pragma omp parallel for schedule(dynamic, 16)
    for(int i = 0; i < 1000; i++) {
        y[i] = 0;  // Initialize the result vector
        for(int j = 0; j < 1000; j++) {
            y[i] += A[i][j] * B[j];
        }
    }
}


int main(int argc, char *argv[]) {
    int A[1000][1000], B[1000], y[1000] = {0};

    // Initialize matrix A and vector B with ones
    for(int i = 0; i < 1000; i++) {
        for(int j = 0; j < 1000; j++) {
            A[i][j] = 1;
        }
    }

    for(int i = 0; i < 1000; i++) {
        B[i] = 1;
    }

    // Perform matrix-vector multiplication
    matrix_vector_multiply(A, B, y);

    // Print the result
    for(int i = 0; i < 1000; i++) {
        std::cout << y[i] << std::endl;
    }

    return 0;
}
