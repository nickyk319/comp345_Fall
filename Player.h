#pragma once
#include<list>
#include<iostream>
#include<vector>
#include "Order.h"
#include "Map.h"
#include "Cards.h"

using namespace std;

class Player {

public:
    vector <Territory*> territories;

    int ahandofCards;

    vector <Card*> cards;
    vector<Card*> handCard;
    vector<Order*> orderList;

    string playerName;

    int reinforcements;

    int pID;

    list<int>toAttacklist;

    list<int>todefendlist;

    list<Order>OrderList;

    //friend classes
    friend class Card;
    friend class GameEngine;
    friend class Map;

public:
    Player();       // Default constructor
    Player(int, string);
    Player(int, int, string, vector<Territory*> territories, vector<Card*> handCard, vector<Order*> order);
    Player(const Player &p); //Copy constructor
    friend std::ostream &operator<<(std::ostream &output, const Player &player);
    Player& operator = (const Player& );
    ~Player(); //Destructor

    string getName();
    int getReinforcementPool();
    void setReinforcementPool(int);
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
