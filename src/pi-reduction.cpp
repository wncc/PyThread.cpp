#include <iostream>
using namespace std;
#include <omp.h>
#include <cstdlib>

#define THREAD_COUNT 4
#define CACHE_PAD 8


static long step_count = 1e8;

using namespace std;

int main()
{
    double pi = 0.0;
    double step = 1.0 / step_count;

#pragma omp parallel for reduction(+ : pi)
    for (int i = 0; i < step_count; i++)
    {
        double x = (i + 0.5) * step;
        pi += 4.0 / (1 + x * x);
    }

    pi *= step;
    cout << "Pi = " << pi << endl;
}