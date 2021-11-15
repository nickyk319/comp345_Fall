#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

class Order
{
private:
	std::string info = "this is an order";
public:
	Order();
	~Order();
	Order(const Order& o1);
	virtual bool validate();
	virtual void execute();
	Order& operator = (const Order& t)
	{
		return *this;
	}
};

class Deploy : public Order {
private:
	std::string info = "place some armies on one of the current players territories.";
public:
	int playid;
	int territoryid;
	int num;
	Deploy(int playID, int territoryID, int num);
	Deploy(const Deploy& o1);
	bool validate() override;
	void execute() override;
};

class Advance : public Order {
private:
	std::string info = "move some armies from one of the current players territories (source) to an adjacent territory (target).If the target territory belongs to the current player, the armies are moved to the target territory. If the target territory belongs to another player, an attack happens between the two territories.";
public:
	int playid;
	int territoryid;
	int new_territoryid;
	int numSoldiers;
	Advance(int playID, int territoryID, int new_territoryID, int numSoldiers);
	Advance(const Advance& o1);
	bool validate() override;
	void execute() override;

};

class Bomb : public Order {
private:
	std::string info = "destroy half of the armies located on an opponents territory that is adjacent to one of the current players territories.";
public:
	int oppTerritory;
	Bomb(int oppTerritory);
	Bomb(const Bomb& o1);
	bool validate() override;
	void execute() override;
};

class Blockade : public Order {
private:
	std::string info = "triple the number of armies on one of the current players territories and make it a neutral territory.";
public:
	int territoryid;
	Blockade(int territoryID);
	Blockade(const Blockade& o1);
	bool validate() override;
	void execute() override;
};

class Airlift : public Order {
private:
	std::string info = "advance some armies from one of the current players territories to any another territory.";
public:
	int playid;
	int territoryid;
	int new_territoryid;
	int num;
	Airlift(int playID, int territoryID, int new_territoryID, int num);
	Airlift(const Airlift& o1);
	bool validate() override;
	void execute() override;

};

class Negotiate : public Order {
private:
	std::string info = "prevent attacks between the current player and another player until the end of the turn.";
public:
	int play1id;
	int play2id;
	Negotiate(int play1ID, int play2ID);
	Negotiate(const Negotiate& o1);
	bool validate() override;
	void execute() override;
};

class OrdersList
{
public:
	std::vector<Order*>* olist;
public:
	// new an order list
	OrdersList();
	OrdersList(const OrdersList& ol);

	// free the order list
	~OrdersList();

	// remove an order from the order list
	void remove(Order* order);

	// insert an order to the order list
	void add(Order* order);

	// move 
	void move(Order* order, int index);
};

/**
ostream& Deploy::operator << (ostream& out, const Deploy& t);
ostream& Advance::operator << (ostream& out, const Advance& t);
ostream& Bomb::operator << (ostream& out, const Bomb& t);
ostream& Blockade::operator << (ostream& out, const Blockade& t);
ostream& Airlift::operator << (ostream& out, const Airlift& t);
ostream& Negotiate::operator << (ostream& out, const Negotiate& t);
**/