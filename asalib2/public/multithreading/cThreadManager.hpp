#pragma once
#ifndef asalib2_public_multithreading_threadmanager_hpp
#define asalib2_public_multithreading_threadmanager_hpp

#include <asalib2\public\library.hpp>

#include <vector>
#include <queue>
#include <thread>
#include <functional>
#include <mutex>

#include <asalib2\public\multithreading\latch.hpp>
#include <asalib2\public\multithreading\stop_token.hpp>


namespace asalib2_ns
{

	namespace async
	{

		class threadPool
		{

		public:
			threadPool(unsigned int numThreads = std::thread::hardware_concurrency());
			~threadPool();

			void push(std::function<void()> task);

			void close();
			void force_close();

		private:

			std::vector<std::thread> m_pool; // replace with jthread
			std::queue<std::function<void()>> m_function_queue;

			// Execution halting mechanism
			std::stop_source soft_stop; // Wait for m_function_queue to be empty
			std::stop_source hard_stop; // Finish execution once all currently executed tasks finish
			::asalib2_ns::async::latch m_finish_latch; // Currently active thread counter.

			// Synchronisation mechanisms
			std::mutex m_lock;

			// Worker
			void threadWorker(std::stop_token soft_stop_token, std::stop_token hard_stop_token);


		}; // class threadPool


	} // namespace async


} // namespace asalib2_ns


#endif //asalib2_public_multithreading_threadmanager_hpp