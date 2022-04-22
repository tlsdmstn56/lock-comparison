#pragma once

#include <atomic>
#include <emmintrin.h>

/**
 * Borrowed from https://probablydance.com/2019/12/30/measuring-mutexes-spinlocks-and-how-bad-the-linux-scheduler-really-is/
 * 
 */
struct spinlock_amd
{
    void lock()
    {
        for (;;)
        {
            bool was_locked = locked.load(std::memory_order_relaxed);
            if (!was_locked && locked.compare_exchange_weak(was_locked, true, std::memory_order_acquire))
                break;
            _mm_pause();
        }
    }
    void unlock()
    {
        locked.store(false, std::memory_order_release);
    }
 
private:
    std::atomic<bool> locked{false};
};