#include "matrix_mult.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Define matrices A, B, and C as global variables
int A[N][N];
int B[N][N];
int C[N][N];

// Function to initialize matrices A and B
void initializeMatrices() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = 2;
            B[i][j] = 2;
            C[i][j] = 0;  // Initialize C to 0
        }
    }
}

// Function to perform matrix multiplication in parallel
void matrixMultiply() {
    #pragma omp parallel for private(int i, int j, int k)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Function to print matrix C
void printResult() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d\t", C[i][j]);
        }
        printf("\n");
    }
}

// Function to calculate and return elapsed time
double calculateElapsedTime(struct timeval tv1, struct timeval tv2) {
    return (double)(tv2.tv_sec - tv1.tv_sec) + (double)(tv2.tv_usec - tv1.tv_usec) * 1.e-6;
}

int main() {
    // Declare time structs for timing
    struct timeval tv1, tv2;
    struct timezone tz;
    double elapsed;

    // Initialize matrices A and B
    initializeMatrices();

    // Get start time
    gettimeofday(&tv1, &tz);

    // Perform matrix multiplication
    matrixMultiply();

    // Get end time
    gettimeofday(&tv2, &tz);

    // Calculate and print elapsed time
    elapsed = calculateElapsedTime(tv1, tv2);
    printf("Elapsed time = %f seconds.\n", elapsed);

    // Optionally, print result matrix C
    printResult();

    return 0;
}
