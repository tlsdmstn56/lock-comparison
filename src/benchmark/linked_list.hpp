#pragma once

#include "result.hpp"

template<typename LockType>
struct Node {
    int val;
    Node* next;
    LockType lock;
};

template<typename LockType>
struct List {
    List(): head(nullptr) {}
    Node<LockType>* head;
    LockType lock;
    void Push(int val) {
        
    }
};

template<class LockType>
class LinkedListBenchmark {
public:
    LinkedListBenchmark(const std::string& test_name, size_t num_threads, size_t num_increase): num_threads(num_threads), num_increase(num_increase), counter(0), test_name(test_name){}

    BenchmarkResult run() {
        using namespace std::chrono;

        std::vector<std::thread> threads;
        threads.reserve(num_threads-1);
        
        auto begin = std::chrono::steady_clock::now();
        for (size_t i=1; i<num_threads; ++i) {
            threads.emplace_back(&LinkedListBenchmark<LockType>::increase_counter, this);
        }
        increase_counter();
        for (auto& thread : threads) {
            thread.join();
        }
        auto end = steady_clock::now();
        auto status = BenchmarkResult::BenchmarkStatus::SUCCESS;
        if (num_threads * num_increase != counter) {
            status = BenchmarkResult::BenchmarkStatus::FAIL;
        }
        uint64_t elapsed = duration_cast<milliseconds>(end - begin).count();
        return {test_name, status, elapsed};
    }

private:

    void increase_counter() {
        for (size_t i=0; i<num_increase; ++i) {
            lock.lock();
            ++counter;
            lock.unlock();
        }
    }

    size_t num_threads;
    size_t num_increase;
    uint64_t counter = 0;
    LockType lock;
    std::string test_name;
};