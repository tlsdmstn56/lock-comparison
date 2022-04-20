#pragma once

#include <atomic>

struct TATASSampleLock {
    TATASSampleLock(): _lock(0) {}
    void lock() {
        int expected= 0;
        while(_lock.load() == 0) {
            while(!_lock.compare_exchange_weak(expected, 1));
        }
    }
    void unlock() {
        _lock.store(0);
    }
private:
    std::atomic_int32_t _lock;
};