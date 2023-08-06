#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <vector>

#include "Kitchen.h"

int main() {
	std::cout << "\tTASK 28.3 ONLINE RESTAURANT KITCHEN\n\n";

    std::srand(std::time(nullptr));

    Kitchen kitchen;
    std::thread thread(&Kitchen::deliverFood, &kitchen);

    while (kitchen.getDeliveries() < 10) {
        std::this_thread::sleep_for(Sec(std::rand() % 6 + 5));

        const std::vector<std::string> vFoods = {"pizza", "soup", "steak", "salad", "sushi"};

        std::string randomFood = vFoods[std::rand() % vFoods.size()];

        kitchen.acceptOrder(randomFood);

        std::thread cookThread(&Kitchen::cookFood, &kitchen, randomFood);

        cookThread.detach();
    }

    thread.detach();
    std::cout << "All orders have been delivered\n";

	return 0;
}