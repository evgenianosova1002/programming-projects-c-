#ifndef PARALLEL_REDUCE_H
#define PARALLEL_REDUCE_H

#include <vector>

long long parallel_reduce(const std::vector<int>& data, int num_threads);

double measure_parallel_reduce(const std::vector<int>& data, int num_threads);

#endif