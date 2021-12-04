#pragma once
#include<list>
#include<iostream>
#include<vector>
#include "Order.h"
#include "Map.h"
#include "Cards.h"
#include "PlayerStrategies.h"
//runable version master
using namespace std;

class PlayerStrategy;

class Player {

public:
    vector <Territory*> territories;
    vector <Player*> friends;

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

    PlayerStrategy* playerStrategy;

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
    void setPlayerStrategy(PlayerStrategy* strategy);
	void printList(const list<int>& L);

    void printAdjacentTerritories();

    void printTerritories();
    int getPID();
    int getsize();

    void showPlayer();

    void showCards();

    std::list<int> todefend(const string& s);

    std::list<int>toAttack(const string& s);

    bool remove();

    bool lose();

    bool win();

    void issueOrder();

	

    Territory* getTerritoryByID(int id);

    bool ownTerritory(Territory* terr);

    bool ownTerritoryByFriend(Territory* terr);

    void addFriends(Player*);

    void setNeutral(Territory* terr);

    Player* getPlayerByID(int id);

};