#ifndef GEAROENIX_CORE_SYNC_KERNEL_WORKERS_HPP
#define GEAROENIX_CORE_SYNC_KERNEL_WORKERS_HPP
#include <functional>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

namespace gearoenix::core::sync {
class Semaphore;
class KernelWorkers {
private:
    enum struct State : int {
        Running,
        Terminating,
        Terminated,
    };
    struct Worker {
        const std::vector<std::shared_ptr<Semaphore>> waits;
        const std::function<void()> sender;
        const std::function<void(const unsigned int)> worker;
        const std::function<void()> meanwhile;
        const std::function<void()> receiver;
        const std::vector<std::shared_ptr<Semaphore>> signals;
    };
    std::vector<std::shared_ptr<Semaphore>> signals;
    std::vector<std::thread> threads;
    std::vector<Worker> workers;
    // For each thread there is a separate mutex to do not lock all threads by one mutex
    std::vector<std::shared_ptr<std::mutex>> workers_syncers;
    State state = State::Running;

    void thread_loop(unsigned int) noexcept;

public:
    KernelWorkers() noexcept;
    ~KernelWorkers() noexcept;
    void add_step(
        std::function<void(const unsigned int)> worker,
        std::function<void()> receiver = [] {}) noexcept;
    void add_step(
        std::function<void()> sender,
        std::function<void(const unsigned int)> worker,
        std::function<void()> meanwhile,
        std::function<void()> boss) noexcept;
    void do_steps() noexcept;
    [[nodiscard]] unsigned int get_threads_count() const noexcept;
};
}
#endif