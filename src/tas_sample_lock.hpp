#pragma once

#include <atomic>

struct TASSampleLock {
    TASSampleLock(): _lock(ATOMIC_FLAG_INIT) {}
    void lock() {
        while(_lock.test_and_set());
    }
    void unlock() {
        _lock.clear(std::memory_order_relaxed);
    }
private:
    std::atomic_flag _lock;
};