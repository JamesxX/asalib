#include <asalib2\public\multithreading\cThreadManager.hpp>

asalib2_ns::async::threadPool::threadPool(unsigned int numThreads)
	:	m_pool(),
		m_lock(),
		soft_stop(),
		hard_stop(),
		m_finish_latch(numThreads)
{
	m_pool.reserve(numThreads);

	for (unsigned int i = 0; i < numThreads; i++)
	{
		m_pool.push_back(
			std::thread(&threadPool::threadWorker, this, 
				soft_stop.get_token(),
				hard_stop.get_token()
			)
		);
	}
}

asalib2_ns::async::threadPool::~threadPool()
{
	close();
}

void asalib2_ns::async::threadPool::push(std::function<void()> task)
{
	// Critical section
	std::unique_lock<std::mutex> lock(m_lock);
	m_function_queue.push(task);
}

void asalib2_ns::async::threadPool::close()
{
	soft_stop.request_stop();
	m_finish_latch.try_wait();

	for (std::thread& thread : m_pool)
	{
		if (thread.joinable())
		{
			thread.join();
		}
	}
}

void asalib2_ns::async::threadPool::force_close()
{
	hard_stop.request_stop();
	m_finish_latch.try_wait();

	for (std::thread& thread : m_pool)
	{
		if (thread.joinable())
		{
			thread.join();
		}
	}
}

void asalib2_ns::async::threadPool::threadWorker(std::stop_token soft_stop_token, std::stop_token hard_stop_token)
{
	std::function<void()> func;
	while ( true )
	{

		{

			std::scoped_lock<std::mutex> lock(m_lock);

			if (soft_stop_token.stop_requested() && m_function_queue.empty())
			{
				break;
			}

			func = m_function_queue.front();
			m_function_queue.pop();
		}

		// execute task asynchronously
		func();

		if (hard_stop_token.stop_requested())
		{
			break;
		}
	}

	// Thread execution has finished
	m_finish_latch.count_down();
}