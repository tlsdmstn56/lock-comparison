#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#include "lock/tas_lock.hpp"
#include "lock/tas_sample_lock.hpp"
#include "lock/tatas_lock.hpp"
#include "lock/tatas_sample_lock.hpp"
#include "lock/amd_spinlock.hpp"
#include "lock/ticket_spinlock.hpp"
#include "lock/pthread.hpp"

#include "benchmark/counter.hpp"
#include "benchmark/linked_list.hpp"

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "ERROR: missing arguments\n";
        std::cerr << argv[0] << " [num_threads] [num_loops]\n";
        return 1;
    }
    size_t num_threads = std::atoi(argv[1]);
    size_t num_increase = std::atoi(argv[2]);
    {
        CounterIncrementBenchmark<TASSampleLock> testcase("TASSampleLock", num_threads, num_increase);  
        testcase.run().print();
    }
    {
        CounterIncrementBenchmark<TASLock> testcase("TASLock", num_threads, num_increase);  
        testcase.run().print();
    }
    // TODO: uncomment
    // {
    //     CounterIncrementBenchmark<TATASLock> testcase(num_threads, num_increase);  
    //     testcase.run().print();
    // }
    {
        // TODO: fix
        CounterIncrementBenchmark<TATASSampleLock> testcase("TATASSampleLock", num_threads, num_increase);  
        testcase.run().print();
    }
    {
        CounterIncrementBenchmark<spinlock_amd> testcase("spinlock_amd", num_threads, num_increase);  
        testcase.run().print();
    }
    {
        CounterIncrementBenchmark<ticket_spinlock> testcase("ticket_spinlock", num_threads, num_increase);  
        testcase.run().print();
    }
    {
        CounterIncrementBenchmark<PThreadSpinLock> testcase("PThreadSpinLock", num_threads, num_increase);  
        testcase.run().print();
    }
    {
        CounterIncrementBenchmark<PThreadSleepLock> testcase("PThreadSleepLock", num_threads, num_increase);  
        testcase.run().print();
    }
    return 0;
}
