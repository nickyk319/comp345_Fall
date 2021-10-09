#include "OrdersList.h"


// new an order list
OrdersList::OrdersList() {
	olist = new std::vector<Order*>();
}

OrdersList::OrdersList(const OrdersList& ol) {
	this->olist = new std::vector<Order*>();
	for (int i = 0; i < ol.olist->size(); i++) {
		this->olist->push_back((*ol.olist)[i]);
	}
}

// free the order list
OrdersList::~OrdersList() {
	delete olist;
}

// remove an order from the order list
void OrdersList::remove(Order* order) {
	std::remove(olist->begin(), olist->end(), order);
}

// insert an order to the order list
void OrdersList::add(Order* order) {
	olist->push_back(order);
}

// move 
void OrdersList::move(Order* order, int index) {
	int size = olist->size();
	if (index >= size) {
		std::cout << "unable to move" << std::endl;
		return;
	}
	std::remove(olist->begin(), olist->end(), order);
	olist->insert(olist->begin() + index, order);
}