//Variant 13 – std::reduce, made by Nosova Yevheniia

#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include "algorithm_utils.h"
#include "parallel_reduce.h"

using namespace std;

vector<int> generate_data(size_t n) {
    vector<int> data(n);
    mt19937 gen(42);
    uniform_int_distribution<int> dist(1, 100);
    for (auto& x : data) x = dist(gen);
    return data;
}

int main() {
    vector<size_t> sizes = { 100000, 1000000, 5000000 };
    vector<int> threads = { 1, 2, 4, 8 };

    cout << left << setw(10) << "Size"
        << setw(12) << "Seq"
        << setw(12) << "Par"
        << setw(12) << "Par_unseq";

    for (int k : threads)
        cout << setw(14) << ("Parallel(" + to_string(k) + ")");

    cout << "\n\n";

    for (auto n : sizes) {
        auto data = generate_data(n);
        double t_seq = test_std_reduce_seq(data);
        double t_par = test_std_reduce_par(data);
        double t_par_unseq = test_std_reduce_par_unseq(data);

        cout << left << setw(10) << n
            << setw(12) << t_seq
            << setw(12) << t_par
            << setw(12) << t_par_unseq;

        for (int k : threads) {
            double t_custom = measure_parallel_reduce(data, k);
            cout << setw(14) << t_custom;
        }
        cout << "\n";
    }

    return 0;
}

