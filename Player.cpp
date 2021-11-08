#include<iostream>
#include <list>
#include "Player.h"
using namespace std;

Player::Player()
{
    name = "default";
    reinforcementPool = 50;

}

//added constructor
Player::Player(string s)
{
    this->name = s;

}
string Player::getName() {
    return this->name;
}

//Four parameter constructor
Player::Player(int reinforcementPool,string name, vector<Territory*> t, vector<Card*> h, vector<Order*> o)
{
    this->reinforcementPool = reinforcementPool;
    this->name = name;
    this->territory = t;
    this->handCard = h;
    this->orderList = o;
}



//Copy constructor (Deep copy)
Player::Player(const Player& p)
{
    this->reinforcementPool = p.reinforcementPool;
    this->name = p.name;
    this->territory = p.territory;
    this->handCard = p.handCard;
    this->orderList = p.orderList;

}

//added assignment operator
Player& Player::operator=(const Player& player)
{
    this->name = player.name;
    this->reinforcementPool = player.reinforcementPool;
    this->territory = player.territory;
    this->handCard = player.handCard;
    this->orderList = player.orderList;
    return *this;
}

//Destructor
Player::~Player()
{
    name = "";
    reinforcementPool = 0;
    territory.clear();
    handCard.clear();
    for (auto order : orderList)
    {
        delete order;
    }
    orderList.clear();
    //release memory
    vector<Territory*>().swap(territory);
    vector<Card*>().swap(handCard);
    vector<Order*>().swap(orderList);
}






