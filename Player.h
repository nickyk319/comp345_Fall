#pragma once
#include<list>
#include<iostream>
#include "Order.h"
#include "Map.h"
#include "Cards.h"

using namespace std;

class Player {

private:
    string name;
    int reinforcementPool;
    vector<Territory*> territory;
    vector<Card*> handCard;
    vector<Order*> orderList;

    //friend classes
    friend class Card;
    friend class GameEngine;
    friend class Map;

public:
    Player();       // Default constructor
    Player(string); //added
    Player(int,string, vector<Territory*> territories, vector<Card*> handCard, vector<Order*> order); //Constructor
    Player(const Player &p); //Copy constructor
    friend std::ostream &operator<<(std::ostream &output, const Player &player);
    Player& operator = (const Player& ); //added
    ~Player(); //Destructor

    string getName();
    int getReinforcementPool();
    void setReinforcementPool(int);
	void printList(const list<int>& L);

	int getsize();



	std::list<int> todefend(int* territories);

	std::list<int>toAttack(int* territories);

	std::list<Order> issueOrder(int country, string order, int target);

	void printOrder(list<Order>& L);

};
