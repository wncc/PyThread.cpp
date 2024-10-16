#include <iostream>
#include <omp.h>
#include <cstdlib>
using namespace std;

void montecarlo(int n, int num_threads) {
    int pCircle = 0, pSquare = 0;
    double x, y, d;
    int i;

    #pragma omp parallel for private(x, y, d, i) reduction(+:pCircle, pSquare) num_threads(num_threads)
    for(i = 0; i < n; i++) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        d = x * x + y * y;
        if(d <= 1) {
            pCircle++;
        }
        pSquare++;
    }

    double pi = 4 * (double)pCircle / (double)pSquare;
    cout << "Pi: " << pi << endl;
}

int main() {
    int n = 1000000; // Number of points
    int num_threads = 4; // Number of threads
    montecarlo(n, num_threads);
    return 0;
}