#include "Orders.cpp"
#include <vector>
#include <algorithm>
class OrdersList
{
public:
    std::vector<Order*> *olist;
public:
    // new an order list
    OrdersList() {
        olist = new std::vector<Order*>();
    }

    // free the order list
    ~OrdersList() {
        delete olist;
    }

    // remove an order from the order list
    void remove(Order* order) {
        std::remove(olist->begin(), olist->end(), order);
    }

    // insert an order to the order list
    void move(Order* order) {
        olist->push_back(order);
    }
};

