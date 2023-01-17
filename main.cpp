#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "spinlock.hpp"

int main()
{
    std::vector<std::thread> threads{};
    std::uint64_t concurrency{std::thread::hardware_concurrency()};
    std::uint64_t counter{};
    spinlock spinLock{};

    auto threadTask = [&]() {
        std::lock_guard<spinlock> lockGuard{spinLock};

        for (std::uint64_t i = 0; i < 1000000; ++i) {
            ++counter;
        }
    };

    for (std::uint64_t i = 0; i < concurrency; ++i) {
        threads.emplace_back(threadTask);
    }

    for (auto &thread : threads) {
        thread.join();
    }

    std::cout << counter << std::endl;
}