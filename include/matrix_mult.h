#ifndef MATRIX_MULT_H
#define MATRIX_MULT_H

#include <sys/time.h>

// Matrix dimensions
#define N 1000

// Global matrix variables
extern int A[N][N];
extern int B[N][N];
extern int C[N][N];

// Function to initialize matrices A and B
void initializeMatrices();

// Function to perform matrix multiplication in parallel
void matrixMultiply();

// Function to print matrix C
void printResult();

// Function to calculate and print the elapsed time
double calculateElapsedTime(struct timeval tv1, struct timeval tv2);

#endif // MATRIX_MULT_H
