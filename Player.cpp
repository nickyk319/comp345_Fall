#include<iostream>
#include <list>
#include "Player.h"
using namespace std;

Player::Player()
{
    playerName = "default";
    reinforcements = 0;
    pID = 0;
}

Player::Player(int id, string name)
{
    this->pID = id;
    this->playerName = name;

}
string Player::getName() {
    return this->playerName;
}

//Four parameter constructor
Player::Player(int PID, int reinforcements,string playerName, vector<Territory*> t, vector<Card*> h, vector<Order*> o)
{
    this->reinforcements = reinforcements;
    this->playerName = playerName;
    this->territories = t;
    this->handCard = h;
    this->orderList = o;
}

//Copy constructor (Deep copy)
Player::Player(const Player& p)
{
    this->reinforcements = p.reinforcements;
    this->playerName = p.playerName;
    this->territories = p.territories;
    this->handCard = p.handCard;
    this->orderList = p.orderList;
}

//added assignment operator
Player& Player::operator=(const Player& player)
{
    this->playerName = player.playerName;
    this->reinforcements = player.reinforcements;
    this->territories = player.territories;
    this->handCard = player.handCard;
    this->orderList = player.orderList;
    return *this;
}
std::ostream &operator<<(std::ostream &output, const Player &player) {
    output << "\nThe player name is: " << player.playerName << endl;
    output << "\nThe cards in hand are:"  << endl;
    for (auto & card : player.handCard) {
        output << card->cardTypeToString(card->getType());
        output << '\n';
    }
    return output;
}

//Destructor
Player::~Player()
{
    playerName = "";
    reinforcements = 0;
    territories.clear();
    handCard.clear();
    for (auto order : orderList)
    {
        delete order;
    }
    orderList.clear();
    //release memory
    vector<Territory*>().swap(territories);
    vector<Card*>().swap(handCard);
    vector<Order*>().swap(orderList);
}

int Player:: getReinforcementPool(){
    return reinforcements;
}

void Player:: setReinforcementPool(int army){
    this->reinforcements = army;
}








