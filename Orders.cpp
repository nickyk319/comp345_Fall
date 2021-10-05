#pragma once
#include <string>
#include <iostream>

class Order
{
private:
    std::string info = "this is an order";
public:
    Order() {}

    ~Order() {}
    virtual bool validate() {
        return true;
    }

    virtual void execute() {
    }
};

class Deploy : public Order {
private:
    std::string info = "place some armies on one of the current players territories.";
public:
    int playid;
    int territoryid;
    int num;
    Deploy(int playID, int territoryID, int num) {
        this->playid = playID;
        this->territoryid = territoryID;
        this->num = num;
    }
    bool validate() {
        return true;
    }

    void execute() {
        // need map.set_armies(current_player, territories, number)
        std::cout << info << std::endl;
        std::cout << " -> PlayID " << playid << " put " << num << " armies " << " on " << territoryid << " territory" << std::endl;
    }
};

class Advance : public Order {
private:
    std::string info = "move some armies from one of the current players territories (source) to an adjacent territory (target).If the target territory belongs to the current player, the armies are moved to the target territory. If the target territory belongs to another player, an attack happens between the two territories.";
public:
    int playid;
    int territoryid;
    int new_territoryid;
    Advance(int playID, int territoryID, int new_territoryID) {
        this->playid = playID;
        this->territoryid = territoryID;
        this->new_territoryid = new_territoryID;
    }
    bool validate() {
        return true;
    }

    void execute() {
        // map.clear_armies(current_player, source_territories)
        // map.add_armies(current_player, target_territories)
        std::cout << info << std::endl;
        std::cout << " -> PlayID " << playid << " move all armies " << " from " << territoryid << " territory to " << new_territoryid << " territory" << std::endl;
    }

};

class Bomb : public Order {
private:
    std::string info = "destroy half of the armies located on an opponents territory that is adjacent to one of the current players territories.";
public:
    int territoryid;
    Bomb(int territoryID) {
        this->territoryid = territoryID;
    }
    bool validate() {
        return true;
    }

    void execute() {
        // map.update_armies(target_player, territories, 0.5)
        std::cout << info << std::endl;
        std::cout << "the armies on " << territoryid << " territory is reduced.";
    }

};

class Blockade : public Order {
private:
    std::string info = "triple the number of armies on one of the current players territories and make it a neutral territory.";
public:
    int territoryid;
    Blockade(int territoryID) {
        this->territoryid = territoryID;
    }
    bool validate() {
        return true;
    }

    void execute() {
        // map.update_armies(target_player, territories, 3)
        // map.set_flag(-1); // neutral territory
        std::cout << info << std::endl;
        std::cout << "the armies on " << territoryid << " territory is triple, but this territory is marked as a neutral territory";
    }

};

class Airlift : public Order {
private:
    std::string info = "advance some armies from one of the current players territories to any another territory.";
public:
    int playid;
    int territoryid;
    int new_territoryid;
    int num;
    Airlift(int playID, int territoryID, int new_territoryID, int num) {
        this->playid = playID;
        this->territoryid = territoryID;
        this->new_territoryid = new_territoryID;
        this->num = num;
    }
    bool validate() {
        return true;
    }

    void execute() {
        // map.add_armies(current_player, target_territories)
        std::cout << info << std::endl;
        std::cout << " -> PlayID " << playid << " move "<< num <<" armies " << " from " << territoryid << " territory to " << new_territoryid << " territory" << std::endl;

    }

};

class Negotiate : public Order {
private:
    std::string info = "prevent attacks between the current player and another player until the end of the turn.";
public:
    int play1id;
    int play2id;
    Negotiate(int play1ID, int play2ID) {
        this->play1id = play1ID;
        this->play2id = play2ID;
    }
    bool validate() {
        return true;
    }

    void execute() {
        // map.add_negotiate(current_player, target_player)
        std::cout << info << std::endl;
        std::cout << "Negotiate built between Player "<< play1id << " and Player " << play2id << std::endl;
    }
};


