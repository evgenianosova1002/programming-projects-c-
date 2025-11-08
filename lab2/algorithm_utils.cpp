#include "algorithm_utils.h"

using namespace std;
using namespace std::chrono;

double test_std_reduce_seq(const vector<int>& data) {
    auto start = high_resolution_clock::now();
    volatile long long sum = reduce(execution::seq, data.begin(), data.end(), 0LL);
    auto end = high_resolution_clock::now();
    return duration<double>(end - start).count();
}

double test_std_reduce_par(const vector<int>& data) {
    auto start = high_resolution_clock::now();
    volatile long long sum = reduce(execution::par, data.begin(), data.end(), 0LL);
    auto end = high_resolution_clock::now();
    return duration<double>(end - start).count();
}

double test_std_reduce_par_unseq(const vector<int>& data) {
    auto start = high_resolution_clock::now();
    volatile long long sum = reduce(execution::par_unseq, data.begin(), data.end(), 0LL);
    auto end = high_resolution_clock::now();
    return duration<double>(end - start).count();
}
