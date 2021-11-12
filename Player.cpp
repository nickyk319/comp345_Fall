#include<iostream>
#include <list>
#include <vector>
#include "Player.h"
#include "Map.h"
#include "Order.h"
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
int Player::getPID() {
    return this->pID;
}
string Player::getName() {
    return this->playerName;
}

//Four parameter constructor
Player::Player(int pID, int reinforcements,string playerName, vector<Territory*> t, vector<Card*> h, vector<Order*> o)
{
    this->pID = pID;
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
    this->pID = player.pID;
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
    pID = 0;
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

void Player::printList(const list<int>& L) {
    for (list<int>::const_iterator it = L.begin(); it != L.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}
int Player::getsize() {
    int size = sizeof(territories) / sizeof(territories[0]);
    return size;
}

void Player::showPlayer() {
    cout << "This player has:\ncountry:" << getsize() << " card:" << ahandofCards << endl;
}

void Player::showCards() {
    for (auto i : cards)
        cout << i << endl;
}

std::list<int> Player::todefend(const string& s) {
    vector<int> defends = parseStringToInt(s);
    for (auto i : defends)
        todefendlist.push_back(i);

    return todefendlist;
}

std::list<int> Player::toAttack(const string& s) {
    vector<int> attacks = parseStringToInt(s);
    for (auto i : attacks)
        toAttacklist.push_back(i);

    return toAttacklist;
}

std::list<Order> Player::issueOrder(string order) {
    cout << "ISSUE ORDER: \n" << endl;
    cout << "Enter Order of Territories to Attack" ;
    printAdjacentTerritories();
    string attackInput;
    cin >> attackInput;
    toAttack(attackInput);
    cout << "\nYou selected: " << attackInput;

    cout << "\n\nEnter Order of Territories to Defend" ;
    printTerritories();
    string defendInput;
    cin >> defendInput;
    todefend(defendInput);
    cout << "\nYou selected: " << defendInput;

    //Deploy
    cout << "DEPLOY ORDER: \n" << endl;
    while (reinforcements >= 0) {
        cout << "Reinforcements: " << reinforcements;
        cout << "\nSelect a Territory to Deploy to";
        printTerritories();
        int tID;
        cin >> tID;

        cout << "\nHow many reinformcements would you like to deploy?";
        cout << "\n" << Map::worldMap.territories[tID-1];
        int numDeploy;
        cin >> numDeploy;

        reinforcements-=numDeploy;
        Deploy* d = new Deploy(pID, tID, numDeploy);
        cout << "\nAdded " << numDeploy << " Reinforcements!";
        cout << "\n" << Map::worldMap.territories[tID-1];
        OrderList.push_back(*d);
    }

    //Advance
    cout << "ADVANCE ORDER: \n" << endl;
    for (auto i : todefendlist) {
        cout << "Defending " << Map::worldMap.territories[i-1];
        cout << "\nWhich Territory are you advancing to?\n";
        Map::worldMap.territories[i-1]->displayBorders();
        int tID;
        int num;
        cin >> tID;
        for (auto j : territories) {
            if (j->tID == tID) {
                cout << "\nHow many troops are being moved?\n";
                cin >> num;
                Advance* a = new Advance(pID, Map::worldMap.territories[i-1]->getTID(), Map::worldMap.territories[tID-1]->getTID(), num);
                OrderList.push_back(*a);
                cout << "Success!";
                break;
            }
            cout << "\nTerritory does not belong to you...\n";
        }
    }
    for (auto i : toAttacklist) {
        cout << "Attacking with " << Map::worldMap.territories[i-1];
        cout << "\nWhich Territory are you attacking?\n";
        Map::worldMap.territories[i-1]->displayBorders();
        int tID;
        cin >> tID;
        for (auto j : territories) {
            if (j->tID == tID) {
                cout << "\nTerritory belongs to you...\n";
                break;
            }
            Bomb* b = new Bomb(Map::worldMap.territories[tID-1]->getTID());
            OrderList.push_back(*b);
            cout << "\nSuccess!\n";
        }
    }

    //Cards
    cout << "\nChoose a card\n";
    showCards();
    int cardIndex;
    cin >> cardIndex;
    switch(cards[cardIndex]->getType()) {
        case bomb: {
            cout << "\nSelect a target";
            int tID;
            cin >> tID;
            Bomb* b = new Bomb(Map::worldMap.territories[tID-1]->getTID());
            OrderList.push_back(*b);
        }
        case reinforcement: {
            cout << "\nSelect a destination";
            int tID;
            cin >> tID;
            Deploy* d = new Deploy(pID, Map::worldMap.territories[tID-1]->getTID(), 5);
            OrderList.push_back(*d);
        }
        case blockade: {
            cout << "\nSelect a target";
            int tID;
            cin >> tID;
            Blockade* b = new Blockade(Map::worldMap.territories[tID-1]->getTID());
            OrderList.push_back(*b);
        }
        case airlift: {
            cout << "\nSelect a destination";
            int tID;
            cin >> tID;
            cout << "\nHow many troops are being moved?";
            int num;
            cin >> num;
            cout << "\nWhere are they being taken from?";
            int tID2;
            cin >> tID2;
            Airlift* a = new Airlift(pID, Map::worldMap.territories[tID2-1]->getTID(), Map::worldMap.territories[tID-1]->getTID(), num);
            OrderList.push_back(*a);
        }
        case diplomacy: {
            cout << "\nSelect a Player";
            int pID2;
            cin >> pID2;
            Negotiate* n = new Negotiate(pID, pID2);
            OrderList.push_back(*n);
        }
    }
	return OrderList;
}

//void player::printOrder(list<Order> &L) {
//    cout << " listoforder: \n" << endl;
//    for (list<Order>::iterator t = L.begin(); t != L.end();t++) {
//        cout << (*t).m_country << " is going to"<<(*t).m_order<<" coutry "<<(*t).m_target<<endl;
//    }
//    cout << endl;
//}

void Player::printAdjacentTerritories() {
    cout << "Player " << pID << "'s Attackable Territories: ";
    vector <int> adjTerritories;

    for (auto i : territories) {
        for (auto j : i->adjTerritoryOnMap) {
            adjTerritories.push_back(j);
        }
    }
    for (auto i : adjTerritories)
        cout << i << " ";
}

void Player::printTerritories() {
    cout << "Player " << pID << "'s Defendable Territories: ";

    for (auto i: territories)
        cout << i->getTID() << " ";
}

