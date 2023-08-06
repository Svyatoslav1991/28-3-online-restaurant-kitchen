# 28-3-online-restaurant-kitchen

It is required to implement a simplified model of the kitchen of a restaurant operating in the online delivery mode.
An online order arrives every 5-10 seconds.
This is a random dish of five: pizza, soup, steak, salad, sushi.
The waiter who took the order online leaves it by the kitchen.
If the kitchen is free, it takes the order and after 5-15 seconds returns the already prepared dish for delivery.
The time is determined randomly using the std::rand() function within the specified ranges.
The courier arrives every 30 seconds, picks up ready-made dishes at the checkout and delivers them to customers.
The program ends after 10 successful deliveries.
At each stage, whether it is an order, or cooking, or order delivery, the corresponding messages are displayed in the console.
