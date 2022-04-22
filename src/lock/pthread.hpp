#pragma once

#include <pthread.h>

struct PThreadSpinLock
{
    void lock()
    {
        while (pthread_mutex_trylock(&_lock))
            ;
    }
    void unlock()
    {
        pthread_mutex_unlock(&_lock);
    }
 
private:
    pthread_mutex_t _lock = PTHREAD_MUTEX_INITIALIZER;
};

struct PThreadSleepLock
{
    void lock()
    {
        pthread_mutex_lock(&_lock);
    }
    void unlock()
    {
        pthread_mutex_unlock(&_lock);
    }
 
private:
    pthread_mutex_t _lock = PTHREAD_MUTEX_INITIALIZER;
};