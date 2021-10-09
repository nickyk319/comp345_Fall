#pragma once
#include "Order.h"
#include <vector>
#include <algorithm>
class OrdersList
{
public:
	std::vector<Order*> *olist;
public:
	// new an order list
	OrdersList();
	OrdersList(const OrdersList &ol);

	// free the order list
	~OrdersList();

	// remove an order from the order list
	void remove(Order* order);

	// insert an order to the order list
	void add(Order* order);

	// move 
	void move(Order* order, int index);
};

