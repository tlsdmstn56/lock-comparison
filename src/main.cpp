#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <atomic>

struct TASLock {
    TASLock(): _lock(0) {}
    void lock() {
        // TODO: inline asm TAS
    }
    void unlock() {
        _lock = 0;
    }
private:
    int32_t _lock;
};

struct TATASLock {
    TATASLock(): _lock(0) {}
    void lock() {
        // non-atomic lock read
        while (_lock == 0) {
            // TODO: inline asm TAS
        }
    }
    void unlock() {
        _lock = 0;
    }
private:
    int32_t _lock;
};


struct SampleLock {
    SampleLock(): _lock(0) {}
    void lock() {
        _lock = 1;
    }
    void unlock() {
        _lock = 0;
    }
private:
    int32_t _lock;
};

template<class LockType>
class TestCase {
public:
    TestCase(size_t num_threads, size_t num_increase): num_threads(num_threads), num_increase(num_increase), counter(0){}

    void run() {
        using namespace std::chrono;
        std::vector<std::thread> threads;
        threads.reserve(num_threads);
        auto begin = std::chrono::steady_clock::now();
        for (size_t i=0; i<num_threads; ++i) {
            threads.emplace_back(&TestCase<LockType>::increase_counter, this);
        }

        for (auto& thread : threads) {
            thread.join();
        }
        auto end = steady_clock::now();
        std::cout << "Expected counter: " << num_threads * num_increase << '\n';
        std::cout << "Actual counter: " << counter << '\n';
        std::cout << "Time: " << duration_cast<milliseconds>(end - begin).count() << " ms\n" ;
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
};

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "ERROR: missing arguments\n";
        std::cerr << argv[0] << " [num_threads] [num_loops]\n";
        return 1;
    }
    size_t num_threads = std::atoi(argv[1]);
    size_t num_increase = std::atoi(argv[2]);
    {
        TestCase<TASLock> testcase(num_threads, num_increase);  
        testcase.run();
    }
    {
        TestCase<TATASLock> testcase(num_threads, num_increase);  
        testcase.run();
    }

    return 0;
}
