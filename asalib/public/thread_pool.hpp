/// @file thread_pool.hpp
/// @author James R Swift
/// @date 20/06/2019
/// @brief Common header for library, implementing asychronous threaded ability used to mitigate expensive function calls.

#pragma once
#include "library.h"

#include <vector>
#include <thread>
#include <future>
#include <functional>
#include <chrono>

namespace AbelianSquaresAnalysis {
	

	/// @brief Helper class for running asynchronous tasks on multiple threads.
	/// Used to speed up certain expensive functions
	/// @tparam _argsIn Type of argument that will be supplied to worker function.
	/// @tparam _argsOut Type of return value from worker functions.
	template<typename _argsIn, typename _argsOut>
	class ThreadPool {
	public:

		/// @brief Add a task onto the pool, and execute as soon as possible, with the given input arguments.
		/// @param[in] callable Worker funcitons.
		/// @param[in] _IN Input argument for worker.
		void AddTask(std::function<_argsOut(_argsIn)> callable, _argsIn _IN) {
			futures_pool.push_back(std::async(std::launch::async, callable, _IN));
		}

		/// @brief Block the main thread until all pooled tasks are sucessfully complete.
		void WaitForTasks() {
			bool _anyTasksRunning = true;
			while (_anyTasksRunning) {
				_anyTasksRunning = false;
				for (auto& future : futures_pool) {
					std::future_status status = future.wait_for(std::chrono::nanoseconds(1));
					if (status != std::future_status::ready)
						_anyTasksRunning = true;
					//if (status == std::future_status::timeout)
						//throw std::exception(); // Program breaking problems if this happens
				}
			}

		}

		/// @brief Get a list of results from pooled workers.
		/// @warning All tasks must be finished first!
		/// @return vector of all results, in no particular order.
		std::vector<_argsOut> GetResults() {
			std::vector<_argsOut> output;
			for (auto& future : futures_pool) {
				output.push_back(future.get());
			}
			return output;
		}

		/// @brief Push to a list the results of pooled workers.
		/// @param[in] output List to push results to, in no particular order.
		void GetResults(std::vector<_argsOut>& output) {
			for (auto& future : futures_pool) {
				output.push_back(future.get());
			}
		}

	private:
		std::vector<std::future<_argsOut>> futures_pool; ///< Private vector of futures for asynchronous tasks.
	};

};
