// statistics.h
#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>

// Function declarations
double computeMean(const std::vector<int>& data, int num_threads);
double computeStandardDeviation(const std::vector<int>& data, int num_threads);

#endif // STATISTICS_H
