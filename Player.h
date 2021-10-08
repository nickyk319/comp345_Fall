#pragma once
using namespace std;

class Order {
public:
	int m_country;

	string m_order;

	int m_target;

public:
	void setcountry(int country);


		void setorder(string order);


		void settarget(int target);
};
class player {
public:
	int territories[10];

	int ahandofCards;

	list<int>toAttacklist;

	list<int>todefendlist;

	list<Order>OrderList;
public:
	void printList(const list<int>& L);

	int getsize();

	void showPlayer();

	std::list<int> todefend(int* territories);

	std::list<int>toAttack(int* territories);

	std::list<Order> issueOrder(int country, string order, int target);

	void printOrder(list<Order>& L);

};