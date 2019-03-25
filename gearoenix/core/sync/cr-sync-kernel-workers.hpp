#ifndef GEAROENIX_CORE_SYNC_KERNEL_WORKERS_HPP
#define GEAROENIX_CORE_SYNC_KERNEL_WORKERS_HPP
#include <memory>
#include <vector>
#include <thread> 
#include <functional>
#include <mutex>

namespace gearoenix {
	namespace core {
		namespace sync {
			class Signaler;
			class KernelWorker {
			private:
				struct Worker {
					const std::vector<std::shared_ptr<Signaler>> waits;
					const std::function<void(const unsigned int)> worker;
					const std::function<void()> boss;
					const std::vector<std::shared_ptr<Signaler>> signals;
				};
				std::vector<std::shared_ptr<Signaler>> signals;
				std::vector<std::thread> threads;
				std::vector<Worker> workers;
				std::mutex workers_syncer;
				volatile bool running = true;
				volatile bool terminated = false;

				void thread_loop(const unsigned int);

			public:
				KernelWorker();
				~KernelWorker();
				void add_step(std::function<void(const unsigned int)> worker, std::function<void()> boss = [] {});
				void do_steps();
			};
		}
	}
}
#endif