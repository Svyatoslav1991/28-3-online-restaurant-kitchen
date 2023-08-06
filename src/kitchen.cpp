#include "..\include\kitchen.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <chrono>


Kitchen::Kitchen() : m_deliveries(0) 
{
}

//---------------------------------------------------------------------------------------

void Kitchen::acceptOrder(std::string order) 
{
    std::unique_lock<std::mutex> lock(m_mtx);
    m_qOrders.push(order);
    std::cout << "Order is accepted: " << order << "\n";
    m_cv.notify_one();
}

//---------------------------------------------------------------------------------------

void Kitchen::cookFood(std::string order) 
{
    std::this_thread::sleep_for(Sec(std::rand() % 11 + 5));
    {
        std::unique_lock<std::mutex> lock(m_mtx);
        std::cout << "Order is ready: " << order << "\n";
        std::string order = m_qOrders.front();
        m_qOrders.pop();
        m_qReadyMeals.push(order);
    }
    m_cv.notify_one();
}

//---------------------------------------------------------------------------------------

void Kitchen::deliverFood() 
{
    while (!allDeliveriesDone()) {
        std::this_thread::sleep_for(Sec(30));
        std::unique_lock<std::mutex> lock(m_mtx);

        if (m_qReadyMeals.empty())
        {
            m_cv.wait(lock);
        }

        while(!m_qReadyMeals.empty())
        {
            std::string order = m_qReadyMeals.front();
            m_qReadyMeals.pop();
            ++m_deliveries;
            std::cout << m_deliveries << " delivery completed: " << order << "\n";
        }
    }
}

//---------------------------------------------------------------------------------------

bool Kitchen::allDeliveriesDone() const 
{
    return m_deliveries >= 10;
}

//---------------------------------------------------------------------------------------

int64_t Kitchen::getDeliveries() const
{
    return m_deliveries;
}