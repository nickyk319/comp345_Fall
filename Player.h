#pragma once
#include<list>
#include<iostream>
#include<vector>
#include "Map.h"
#include "Cards.h"
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
	vector <Territory*> territories;

	int ahandofCards;
	vector <Card*> cards;

	int reinforcements;

	int pID;

	list<int>toAttacklist;

	list<int>todefendlist;

	list<Order>OrderList;

public:
	void printList(const list<int>& L);

	void printAdjacentTerritories();

	void printTerritories();

	int getsize();

	void showPlayer();

	void showCards();

	std::list<int> todefend(const string& s);

	std::list<int>toAttack(const string& s);

	std::list<Order> issueOrder(string order);

	void printOrder(list<Order>& L);

};
