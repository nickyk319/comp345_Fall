#include <iostream>
#include <list>
#include <vector>
#include "Player.h"
#include "Map.h"
#include "Order.h"
using namespace std;
//runable version master
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
Player::Player(int PID, int reinforcements,string playerName, vector<Territory*> t, vector<Card*> h, vector<Order*> o)
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
    int x = 0;
    for (auto i : handCard){
        cout << i->cardTypeToString(i->getType()) << " id:" << x << endl;
    x++;
}
}

std::list<int> Player::todefend(const string& s) {
    vector<int> defends = parseStringToInt(s);
    for (auto i : defends) {
        todefendlist.push_back(i);
        cout << "\nYou selected: " << Map::worldMap.territories[i - 1]->getTName();
    }
    return todefendlist;
}

std::list<int> Player::toAttack(const string& s) {
    vector<int> attacks = parseStringToInt(s);
    for (auto i : attacks){

            cout << "\nYou selected: " << Map::worldMap.territories[i-1]->getTName();

    toAttacklist.push_back(i);
}

    return toAttacklist;
}

bool Player::remove() {
    if (territories.size() == 0) {
        cout << "player: " << pID << " elimated" << endl;

        return true;
    }
}
bool Player::lose() {
    if (territories.size() == 0) {
        cout << "player: " << pID << " elimated" << endl;

        return true;
    }
}
bool Player::win() {
    if (territories.size() == Map::worldMap.getNumTerritory()){
        cout << "player: " << pID << " win" << endl;
        return true;
        }
}
void Player::issueOrder() {
    cout << "\nISSUE ORDER: \n" << endl;
    cout << "Enter Order of Territories to Attack\n";

    printAdjacentTerritories();
    cout << "\n";
    string attackInput;
    cin >> attackInput;
    toAttack(attackInput);
    cout << "\nYou selected: " << attackInput;

    cout << "\n\nEnter Order of Territories to Defend\n";
    printTerritories();
    cout << "\n";
    string defendInput;
    cin >> defendInput;
    todefend(defendInput);
    cout << "\nYou selected: " << defendInput;

    //Deploy
    cout << "\nDEPLOY ORDER: \n" << endl;
    while (reinforcements > 0) {
        cout << "Reinforcements: " << reinforcements;
        cout << "\nSelect a Territory to Deploy to\n";
        printTerritories();
        int tID;
        cin >> tID;

        cout << "\nHow many reinformcements would you like to deploy?";
        cout << "\n" << *(Map::worldMap.territories[tID - 1]);
        int numDeploy;
        cin >> numDeploy;

        reinforcements -= numDeploy;
        Deploy *d = new Deploy(this, tID, numDeploy);
        cout << "\nAdded " << numDeploy << " Reinforcements!";
        cout << "\n" << Map::worldMap.territories[tID - 1]->getTName();
        OrderList.push_back(*d);
    }

    //Advance
    cout << "ADVANCE ORDER: \n" << endl;
    for (auto i: todefendlist) {
        cout << "Defending " << Map::worldMap.territories[i - 1]->getTName();
        cout << "\nWhich Territory are you advancing to?\n";
        Map::worldMap.territories[i - 1]->displayBorders();
        int tID;
        int num;
        cin >> tID;
        for (auto j: territories) {
            if (j->tID == tID) {
                cout << "\nHow many troops are being moved?\n";
                cin >> num;
                Advance *a = new Advance(this, Map::worldMap.territories[i - 1]->getTID(),
                                         Map::worldMap.territories[tID - 1]->getTID(), num);
                OrderList.push_back(*a);
                cout << "Success!";
                break;
            }
            cout << "\nTerritory does not belong to you...\n";
        }
    }
    for (auto i: toAttacklist) {
        cout << "Attacking with " << Map::worldMap.territories[i - 1]->getTName();
        cout << "\nWhich Territory are you attacking?\n";
        Map::worldMap.territories[i - 1]->displayBorders();
        int tID;
        cin >> tID;
        for (auto j: territories) {
            if (j->tID == tID) {
                cout << "\nTerritory belongs to you...\n";
                break;
            }
            Bomb *b = new Bomb(this, Map::worldMap.territories[tID - 1]->getTID());
            OrderList.push_back(*b);
            cout << "\nSuccess!\n";
        }
    }

    //Cards
    bool flag = false;
    while (!flag) {
        cout << "\nChoose a card\n";
        showCards();
        int cardIndex;
        cin >> cardIndex;
        switch (handCard[cardIndex]->getType()) {
            case bomb: {
                cout << "\nbomb";
                cout << "\nSelect a target";
                int tID;
                cin >> tID;
                Bomb *b = new Bomb(this, Map::worldMap.territories[tID - 1]->getTID());
                OrderList.push_back(*b);
                flag = true;
                break;
            }
            case reinforcement: {
                cout << "\nreinforcement";
                cout << "\nSelect a destination";
                int tID;
                cin >> tID;
                Deploy *d = new Deploy(this, Map::worldMap.territories[tID - 1]->getTID(), 5);
                OrderList.push_back(*d);
                flag = true;
                break;
            }
            case blockade: {
                cout << "\nblockade";
                cout << "\nSelect a target";
                int tID;
                cin >> tID;
                Blockade *b = new Blockade(this, Map::worldMap.territories[tID - 1]->getTID());
                OrderList.push_back(*b);
                flag = true;
                break;
            }
            case airlift: {
                cout << "\nairlift";
                cout << "\nSelect a destination";
                int tID;
                cin >> tID;
                cout << "\nHow many troops are being moved?";
                int num;
                cin >> num;
                cout << "\nWhere are they being taken from?";
                int tID2;
                cin >> tID2;
                Airlift *a = new Airlift(this, Map::worldMap.territories[tID2 - 1]->getTID(),
                                         Map::worldMap.territories[tID - 1]->getTID(), num);
                OrderList.push_back(*a);
                flag = true;
                break;
            }
            case diplomacy: {
                cout << "\ndiplomacy";
                cout << "\nSelect a Player";
                int pID2;
                cin >> pID2;
                Negotiate *n = new Negotiate(this, this->getPlayerByID(pID2));
                OrderList.push_back(*n);
                flag = true;
                break;
            }
            default: {
                cout << "invild input, try again!\n\n" << endl;

            }
        }
    }
}
//void player::printOrder(list<Order> &L) {
//    cout << " listoforder: \n" << endl;
//    for (list<Order>::iterator t = L.begin(); t != L.end();t++) {
//        cout << (*t).m_country << " is going to"<<(*t).m_order<<" coutry "<<(*t).m_target<<endl;
//    }
//    cout << endl;
//}

void Player::printAdjacentTerritories() {
    cout << "Player " << playerName << "'s Attackable Territories: \n";
    for (int i = 0; i < Map::worldMap.territories.size(); i++) {
        string territoryPlayer = Map::worldMap.territories[i]->getTerritoryPlayer();
        string territoryName = Map::worldMap.territories[i]->getTName();
        int id =Map::worldMap.territories[i]->tID;
        if (territoryPlayer != (playerName)) {
            cout << "Territory: " << territoryName << ", owned by " << territoryPlayer << " id: "<<id<<endl;
        }
    }
}

void Player::printTerritories() {
    cout << "Player " << playerName << "'s Defendable Territories: \n";

    for (int i = 0; i < Map::worldMap.territories.size(); i++) {
        string territoryPlayer = Map::worldMap.territories[i]->getTerritoryPlayer();
        string territoryName = Map::worldMap.territories[i]->getTName();
        int id = Map::worldMap.territories[i]->tID;
        if(territoryPlayer == (playerName)){
        cout << "Territory: " << territoryName << ", owned by " << territoryPlayer << " id: " << id << endl;}
    }
}

Territory* Player::getTerritoryByID(int id) {
    return NULL;
}

bool Player::ownTerritory(Territory* terr) {
    return false;
}

bool Player::ownTerritoryByFriend(Territory* terr) {
    return false;
}

void Player::addFriends(Player* p1) {
    friends.push_back(p1);
}

void Player::setNeutral(Territory* terr) {
    // change ownership
}

Player* Player::getPlayerByID(int id) {
    return this;
}


