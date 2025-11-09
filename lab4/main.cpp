#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <chrono>
#include "data_struct.h"

using namespace std;
using namespace chrono;

void processFile(DataStruct& ds, const string& filename) {
    ifstream fin(filename);
    string cmd;
    int field, value;

    while (fin >> cmd) {
        if (cmd == "write") {
            fin >> field >> value;
            ds.write_field(field, value);
        }
        else if (cmd == "read") {
            fin >> field;
            ds.read_field(field);
        }
        else if (cmd == "string") {
            ds.to_string();
        }
    }
}

int main() {
    DataStruct ds;

    vector<string> files = { "input_thread1.txt", "input_thread2.txt", "input_thread3.txt" };

    for (int threadCount = 1; threadCount <= 3; ++threadCount) {
        cout << "\n Test with " << threadCount << " thread(s)\n";

        auto start = high_resolution_clock::now();

        vector<thread> threads;
        for (int i = 0; i < threadCount; ++i) {
            threads.emplace_back(processFile, ref(ds), files[i]);
        }

        for (auto& t : threads) t.join();

        auto end = high_resolution_clock::now();
        double duration = duration_cast<milliseconds>(end - start).count();

        cout << "Final structure state: " << ds.to_string() << endl;
        cout << "Execution time: " << duration << " ms\n";
    }

    return 0;
}
