#pragma once
#include <string>
#include <iostream>

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
	Advance(int playID, int territoryID, int new_territoryID);
	Advance(const Advance& o1);
	bool validate() override;
	void execute() override;

};

class Bomb : public Order {
private:
	std::string info = "destroy half of the armies located on an opponents territory that is adjacent to one of the current players territories.";
public:
	int territoryid;
	Bomb(int territoryID);
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
