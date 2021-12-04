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
    PlayerStrategy(const PlayerStrategy& copy);
    PlayerStrategy& operator=(const PlayerStrategy& op);
    friend std::ostream& operator<<(std::ostream& out, const PlayerStrategy& output);
    virtual void issueOrder() = 0;
    virtual std::vector<Territory*> toAttack(const string& s) = 0;
    virtual std::vector<Territory*> todenfend(const string& s) = 0;
    void setPlayer(Player* player);

protected:
    Player* player;
};

//5 ConcreteStrategies that implements abstract strategy
class HumanPlayerStrategy : public PlayerStrategy {
    HumanPlayerStrategy();
    HumanPlayerStrategy(const HumanPlayerStrategy& copy);
    HumanPlayerStrategy& operator=(const HumanPlayerStrategy& op);
    virtual ~HumanPlayerStrategy();
    friend std::ostream& operator<<(std::ostream& out, const HumanPlayerStrategy& output);
    virtual void issueOrder();
    virtual std::vector<Territory*> toAttack(const string& s);
    virtual std::vector<Territory*> todenfend(const string& s);

};

class AggressivePlayerStrategy : public PlayerStrategy {
    AggressivePlayerStrategy();
    AggressivePlayerStrategy(const AggressivePlayerStrategy& copy);
    AggressivePlayerStrategy& operator=(
            const AggressivePlayerStrategy& op);
    virtual ~AggressivePlayerStrategy();
    friend std::ostream& operator<<(std::ostream& out, const AggressivePlayerStrategy& output);
    virtual void issueOrder();
    virtual std::vector<Territory*> toAttack(const string& s);
    virtual std::vector<Territory*> todenfend(const string& s);
};

class BenevolentPlayerStrategy : public PlayerStrategy {
    BenevolentPlayerStrategy();
    BenevolentPlayerStrategy(const BenevolentPlayerStrategy& copy);
    BenevolentPlayerStrategy& operator=(
            const BenevolentPlayerStrategy& op);
    virtual ~BenevolentPlayerStrategy();
    friend std::ostream& operator<<(std::ostream& out, const BenevolentPlayerStrategy& output);
    virtual void issueOrder();
    virtual std::vector<Territory*> toAttack(const string& s);
    virtual std::vector<Territory*> todenfend(const string& s);
};

class NeutralPlayerStrategy : public PlayerStrategy {
    NeutralPlayerStrategy();
    NeutralPlayerStrategy(const NeutralPlayerStrategy& copy);
    NeutralPlayerStrategy& operator=(const NeutralPlayerStrategy& op);
    virtual ~NeutralPlayerStrategy();
    friend std::ostream& operator<<(std::ostream& out, const NeutralPlayerStrategy& output);
    virtual void issueOrder();
    virtual std::vector<Territory*> toAttack(const string& s);
    virtual std::vector<Territory*> todenfend(const string& s);
};

class CheaterPlayerStrategy : public PlayerStrategy {
    virtual void issueOrder();
    virtual std::vector<Territory*> toAttack(const string& s);
    virtual std::vector<Territory*> todenfend(const string& s);
};