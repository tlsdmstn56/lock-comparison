#pragma once

#include <atomic>
#include <thread>
#include <cstdint>

/**
 * Borrowed from https://probablydance.com/2019/12/30/measuring-mutexes-spinlocks-and-how-bad-the-linux-scheduler-really-is/
 * 
 */
struct ticket_spinlock
{
    void lock()
    {
        unsigned my = in.fetch_add(1, std::memory_order_relaxed);
        for (int spin_count = 0; out.load(std::memory_order_acquire) != my; ++spin_count)
        {
            if (spin_count < 16)
                _mm_pause();
            else
            {
                std::this_thread::yield();
                spin_count = 0;
            }
        }
    }
    void unlock()
    {
        out.store(out.load(std::memory_order_relaxed) + 1, std::memory_order_release);
    }
 
private:
    std::atomic<uint32_t> in{0};
    std::atomic<uint32_t> out{0};
};