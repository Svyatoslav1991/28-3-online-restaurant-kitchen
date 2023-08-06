#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>

using Sec = std::chrono::seconds;

class Kitchen
{
public:
	Kitchen();
	void acceptOrder(std::string order);
	void cookFood(std::string Order);
	void deliverFood();
	bool allDeliveriesDone() const;
	int64_t getDeliveries() const;

private:
	std::mutex m_mtx;
	std::condition_variable m_cv;
	std::queue<std::string> m_qOrders;
	std::queue<std::string> m_qReadyMeals;
	std::atomic<int64_t> m_deliveries;
};