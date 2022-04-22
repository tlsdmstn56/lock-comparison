#pragma once

#include <atomic>

struct TATASSampleLock {
    TATASSampleLock(): _lock(false) {}
    void lock() {
        bool val;
        do {
            while((val = _lock.load(std::memory_order_relaxed)))
                ;
        } while(!_lock.compare_exchange_weak(val, true, std::memory_order_acquire));
        
        
    }
    void unlock() {
        _lock.store(false, std::memory_order_release);
    }
private:
    std::atomic_bool _lock;
};