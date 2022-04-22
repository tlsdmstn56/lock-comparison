#pragma once

#include <cstdint>

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