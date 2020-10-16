#pragma once
#ifndef asalib2_public_multithreading_latch_hpp
#define asalib2_public_multithreading_latch_hpp

#include <asalib2\public\library.hpp>

#include <cstddef>
#include <condition_variable>
#include <mutex>

namespace asalib2_ns
{

	namespace async
	{

		class latch
		{
		private:
			std::mutex critical;
			std::ptrdiff_t internalCounter;
			std::condition_variable wait_mechanism;

		public:

			latch(std::ptrdiff_t expected)
				: internalCounter(expected),
				wait_mechanism(),
				critical ()
			{

			}

			latch(const latch&) = delete;

			~latch() {
				try_wait();
			}

			latch& operator=(latch arg) = delete;

			void count_down(std::ptrdiff_t n = 1)
			{
				{
					std::lock_guard<std::mutex> lock(critical);
					internalCounter = (internalCounter - n) < 0 ? 0 : internalCounter - n;
				}
				wait_mechanism.notify_all();
			}

			bool try_wait() noexcept
			{
				if (internalCounter <= 0)
					return true;
				wait();
				return false;
			}

			void wait()
			{
				if (internalCounter <= 0)
					return;
				std::mutex lock;
				std::unique_lock<std::mutex> uni_lock(lock);
				wait_mechanism.wait(uni_lock, [this] () -> bool {return internalCounter <= 0; });
			}

			void arrive_and_wait(std::ptrdiff_t n = 1)
			{
				count_down(n);
				try_wait();
			}	

		};

	} // namespace async

} // namespace asalib2_public_multithreading_latch_hpp

#endif // asalib2_public_multithreading_latch_hpp