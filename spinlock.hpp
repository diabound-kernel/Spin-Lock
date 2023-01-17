#ifndef SPINLOCK_HPP
#define SPINLOCK_HPP

#include <atomic>
#include <cstdint>
#include <ctime>

class spinlock
{
public:
    void lock()
    {
        for (std::uint64_t i = 0; flag.load(std::memory_order::relaxed) ||
             flag.exchange(true, std::memory_order::acquire);
             ++i) {
            if (i == 4) {
                timespec ts{};
                nanosleep(&ts, nullptr);
            }
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