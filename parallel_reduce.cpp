#include "parallel_reduce.h"
#include <numeric>
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;
using namespace std::chrono;

long long parallel_reduce(const vector<int>& data, int num_threads) {
    vector<thread> threads;
    vector<long long> partial(num_threads, 0);

    size_t n = data.size();
    size_t chunk = n / num_threads;

    for (int i = 0; i < num_threads; ++i) {
        size_t start = i * chunk;
        size_t end = (i == num_threads - 1) ? n : (i + 1) * chunk;

        threads.emplace_back([&, i, start, end]() {
            partial[i] = accumulate(data.begin() + start, data.begin() + end, 0LL);
            });
    }

    for (auto& t : threads) t.join();

    return accumulate(partial.begin(), partial.end(), 0LL);
}

double measure_parallel_reduce(const vector<int>& data, int num_threads) {
    auto start = high_resolution_clock::now();
    volatile long long sum = parallel_reduce(data, num_threads);
    auto end = high_resolution_clock::now();
    return duration<double>(end - start).count();
}
