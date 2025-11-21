#include <barrier>
#include <functional>
#include <iostream>
#include <syncstream>
#include <thread>
#include <vector>

constexpr int kThreadCount = 5;
constexpr int kSteps = 15;

const char kSchedule[kThreadCount][kSteps] = {
    { 'a', 'a', 'b', 'c', 'c', 'd', 'e', 'f', 'f', 'g', 'h', 'i', 'i', 'j', 'j' },
    { 'a', 'b', 'b', 'c', 'c', 'd', 'e', 'f', 'g', 'g', 'h', 'i', '-', 'j', 'j' },
    { 'a', 'b', 'b', 'c', 'c', 'd', 'e', 'f', 'g', 'g', 'h', 'i', '-', 'j', 'j' },
    { 'a', 'b', 'b', 'c', 'd', 'd', 'e', 'f', 'g', 'g', 'h', 'i', '-', 'j', '-' },
    { 'a', 'b', 'b', 'c', 'd', 'd', 'e', 'f', 'g', 'h', 'h', 'i', '-', 'j', '-' },
};

const int kIndexSchedule[kThreadCount][kSteps] = {
    { 1, 6, 5, 1, 6, 3, 1, 1, 6, 5, 2, 1, 6, 1, 6 },
    { 2, 1, 6, 2, 7, 4, 2, 2, 1, 6, 3, 2, 0, 2, 7 },
    { 3, 2, 7, 3, 8, 5, 3, 3, 2, 7, 4, 3, 0, 3, 8 },
    { 4, 3, 8, 4, 1, 6, 4, 4, 3, 8, 5, 4, 0, 4, 0 },
    { 5, 4, 9, 5, 2, 7, 5, 5, 4, 1, 6, 5, 0, 5, 0 },
};

void f(char set_name, int action_index)
{
    std::osyncstream out(std::cout);
    out << "From set " << set_name
        << " executed action " << action_index << ".\n";
}

void worker(int tid, std::barrier<>& sync_point)
{
    for (int step = 0; step < kSteps; ++step)
    {
        char set_name = kSchedule[tid][step];
        int  action_index = kIndexSchedule[tid][step];

        if (set_name != '-')
        {
            f(set_name, action_index);
        }

        sync_point.arrive_and_wait();
    }
}

int main()
{
    {
        std::osyncstream out(std::cout);
        out << "Computation started.\n";
    }

    std::barrier sync_point(kThreadCount);

    {
        std::vector<std::jthread> threads;
        threads.reserve(kThreadCount);

        for (int tid = 0; tid < kThreadCount; ++tid)
        {
            threads.emplace_back(worker, tid, std::ref(sync_point));
        }
    }

    {
        std::osyncstream out(std::cout);
        out << "Computation finished.\n";
    }

    return 0;
}
