#include <iostream>
#include <syncstream>
#include <chrono>
#include <future>
#include <thread>
#include <string>

using namespace std;

void perform_task_with_delay(const string& task_name, int duration_seconds) {
    this_thread::sleep_for(chrono::seconds(duration_seconds));
    osyncstream(cout) << "Task " << task_name << " completed" << endl;
}

void perform_slow_task(const string& task_name) {
    perform_task_with_delay(task_name, 7);
}

void perform_fast_task(const string& task_name) {
    perform_task_with_delay(task_name, 1);
}

void work() {
    using chrono::steady_clock;
    using chrono::milliseconds;
    using chrono::duration_cast;

    steady_clock::time_point work_start_time = steady_clock::now();

    future<void> async_result_A1 = async(launch::async, []() {
        perform_slow_task("A1");
        });

    future<void> async_result_C2 = async(launch::async, []() {
        perform_slow_task("C2");
        });

    perform_fast_task("A2");
    perform_fast_task("C1");

    async_result_A1.wait();
    async_result_C2.wait();

    
    future<void> async_result_D2 = async(launch::async, []() {
        perform_fast_task("D2");
        });

    perform_fast_task("B");

    perform_fast_task("D1");

    async_result_D2.wait();

    steady_clock::time_point work_finish_time = steady_clock::now();

    double total_execution_seconds =
        duration_cast<milliseconds>(work_finish_time - work_start_time).count() / 1000.0;

    osyncstream(cout) << "Work is done!" << endl;
    osyncstream(cout) << "Total time: " << total_execution_seconds << " seconds" << endl;
}

int main() {
    work();
    return 0;
} 