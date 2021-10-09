#include <iostream>
#include "Order.h"
#include "OrdersList.h"

int main()
{
	OrdersList* ol = new OrdersList();
	Deploy* deploy_order = new Deploy(1, 1, 100); 
	Advance* advance_order = new Advance(1, 1, 2);
	Bomb* bomb_order = new Bomb(2);
	Blockade* blockade_order = new Blockade(2);
	Airlift* airlift_order = new Airlift(1, 2, 1, 50);
	Negotiate* negotiate_order = new Negotiate(1, 2);

	ol->add(deploy_order);
	ol->add(advance_order);
	ol->add(bomb_order);
	ol->add(blockade_order);
	ol->add(airlift_order);
	ol->add(negotiate_order);

	Order* order = (*(ol->olist))[0];
	ol->move(order, 4);

	int count = 0;
	while (count < 6) {
		Order* order = (*(ol->olist))[0];
		if (order->validate()) {
			order->execute();
		}
		else {
			std::cout << "Order is invalided." << std::endl;
		}
		ol->remove(order);
		count = count + 1;
	}
}