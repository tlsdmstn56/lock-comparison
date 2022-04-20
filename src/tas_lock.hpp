#pragma once
#include <cstdint>

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