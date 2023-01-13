#ifndef SPINLOCK_HPP
#define SPINLOCK_HPP

#include <atomic>
#include <time.h>

class spinlock
{
public:
    void lock()
    {
        while (flag.load(std::memory_order::relaxed) ||
               flag.exchange(true, std::memory_order::acquire)) {
            timespec ts{};
            nanosleep(&ts, nullptr);
        }
    }

    void unlock()
    {
        flag.store(false, std::memory_order::release);
    }

private:
    std::atomic<bool> flag{};
};

#endif