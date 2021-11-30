#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Player.h"

using namespace std;
class Player;

//abstract strategy
class PlayerStrategy
{
public:
    PlayerStrategy();
    virtual ~PlayerStrategy();
    virtual void issueOrder() = 0;
    virtual std::list<int> toAttack(const string& s) = 0;
    virtual std::list<int> todenfend(const string& s) = 0;
    void setPlayer(Player* player);

protected:
    Player* player;
};

//5 ConcreteStrategies that implements abstract strategy
class HumanPlayerStrategy : public PlayerStrategy {
    virtual void issueOrder();
    virtual std::list<int> toAttack(const string& s);
    virtual std::list<int> todenfend(const string& s);

};

class AggressivePlayerStrategy : public PlayerStrategy {
    virtual void issueOrder();
    virtual std::list<int> toAttack(const string& s);
    virtual std::list<int> todenfend(const string& s);
};

class BenevolentPlayerStrategy : public PlayerStrategy {
    virtual void issueOrder();
    virtual std::list<int> toAttack(const string& s);
    virtual std::list<int> todenfend(const string& s);
};

class NeutralPlayerStrategy : public PlayerStrategy {
    virtual void issueOrder();
    virtual std::list<int> toAttack(const string& s);
    virtual std::list<int> todenfend(const string& s);
};

class CheaterPlayerStrategy : public PlayerStrategy {
    virtual void issueOrder();
    virtual std::list<int> toAttack(const string& s);
    virtual std::list<int> todenfend(const string& s);
};