// worte by HAO MEI 40074373
#include "Order.h"


Order::Order() {}

Order::Order(const Order& o1) {

}

Order::~Order() {}

bool Order::validate() {
	return true;
}

void Order::execute() {
}



Deploy::Deploy(int playID, int territoryID, int num) {
	this->playid = playID;
	this->territoryid = territoryID;
	this->num = num;
}
Deploy::Deploy(const Deploy& o1) {
	this->playid = o1.playid;
	this->territoryid = o1.territoryid;
	this->num = o1.num;
}
bool Deploy::validate() {
	return true;
}

void Deploy::execute() {
	// need map.set_armies(current_player, territories, number)
	std::cout << info << std::endl;
	std::cout << " -> PlayID " << playid << " put " << num << " armies " << " on " << territoryid << " territory" << std::endl;
}


Advance::Advance(int playID, int territoryID, int new_territoryID) {
	this->playid = playID;
	this->territoryid = territoryID;
	this->new_territoryid = new_territoryID;
}
Advance::Advance(const Advance& o1) {
	this->playid = o1.playid;
	this->territoryid = o1.territoryid;
	this->new_territoryid = o1.new_territoryid;
}
bool Advance::validate() {
	return true;
}

void Advance::execute() {
	// map.clear_armies(current_player, source_territories)
	// map.add_armies(current_player, target_territories)
	std::cout << info << std::endl;
	std::cout << " -> PlayID " << playid << " move all armies " << " from " << territoryid << " territory to " << new_territoryid << " territory" << std::endl;
}


Bomb::Bomb(int territoryID) {
	this->territoryid = territoryID;
}
Bomb::Bomb(const Bomb& o1) {
	this->territoryid = o1.territoryid;
}
bool Bomb::validate() {
	return true;
}

void Bomb::execute() {
	// map.update_armies(target_player, territories, 0.5)
	std::cout << info << std::endl;
	std::cout << "the armies on " << territoryid << " territory is reduced.";
}


Blockade::Blockade(int territoryID) {
	this->territoryid = territoryID;
}
Blockade::Blockade(const Blockade& o1) {
	this->territoryid = o1.territoryid;
}
bool Blockade::validate() {
	return true;
}

void Blockade::execute() {
	// map.update_armies(target_player, territories, 3)
	// map.set_flag(-1); // neutral territory
	std::cout << info << std::endl;
	std::cout << "the armies on " << territoryid << " territory is triple, but this territory is marked as a neutral territory";
}


Airlift::Airlift(int playID, int territoryID, int new_territoryID, int num) {
	this->playid = playID;
	this->territoryid = territoryID;
	this->new_territoryid = new_territoryID;
	this->num = num;
}
Airlift::Airlift(const Airlift& o1) {
	this->playid = o1.playid;
	this->territoryid = o1.territoryid;
	this->new_territoryid = o1.new_territoryid;
	this->num = o1.num;
}
bool Airlift::validate() {
	return true;
}

void Airlift::execute() {
	// map.add_armies(current_player, target_territories)
	std::cout << info << std::endl;
	std::cout << " -> PlayID " << playid << " move " << num << " armies " << " from " << territoryid << " territory to " << new_territoryid << " territory" << std::endl;

}


Negotiate::Negotiate(int play1ID, int play2ID) {
	this->play1id = play1ID;
	this->play2id = play2ID;
}
Negotiate::Negotiate(const Negotiate& o1) {
	this->play1id = o1.play1id;
	this->play2id = o1.play2id;
}
bool Negotiate::validate() {
	return true;
}

void Negotiate::execute() {
	// map.add_negotiate(current_player, target_player)
	std::cout << info << std::endl;
	std::cout << "Negotiate built between Player " << play1id << " and Player " << play2id << std::endl;
}