#ifndef ALGORITHM_UTILS_H
#define ALGORITHM_UTILS_H

#include <vector>
#include <execution>
#include <numeric>
#include <chrono>
#include <iostream>

double test_std_reduce_seq(const std::vector<int>& data);
double test_std_reduce_par(const std::vector<int>& data);
double test_std_reduce_par_unseq(const std::vector<int>& data);

#endif 
