#ifndef GEAROENIX_CORE_SYNC_STOP_POINT_HPP
#define GEAROENIX_CORE_SYNC_STOP_POINT_HPP
#include <memory>
#include <mutex>

namespace gearoenix::core::sync {
class Semaphore;
class StopPoint {
private:
    const std::shared_ptr<Semaphore> sem;
    const int stoper;
    volatile int counter = 0;
    std::mutex counter_lock;

public:
    StopPoint(int walkers_count);
    void all_reach();
};
}
#endif
