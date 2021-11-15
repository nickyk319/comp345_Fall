// worte by HAO MEI 40074373
#include "Order.h"
#include "Player.h"
#include "ctime"

Order::Order() {}

Order::Order(const Order& o1) {

}

Order::~Order() {}

bool Order::validate() {
	return true;
}

void Order::execute() {
}

Deploy::Deploy(Player* player, int territoryID, int num) {
	this->player = player;
	this->territoryid = territoryID;
	this->num = num;
}
Deploy::Deploy(const Deploy& o1) {
	this->player = o1.player;
	this->territoryid = o1.territoryid;
	this->num = o1.num;
}
bool Deploy::validate() {
	Territory* terr = this->player->getTerritoryByID(this->territoryid);
	if (!player->ownTerritory(terr) || this->player->reinforcements < this->num) {
		return false;
	}
	return true;
}

void Deploy::execute() {
	// need map.set_armies(current_player, territories, number)
	// std::cout << info << std::endl;
	// std::cout << " -> PlayID " << player->playerName << " put " << num << " armies " << " on " << territoryid << " territory" << std::endl;
	this->player->reinforcements = this->player->reinforcements - this->num;
	Territory* terr = this->player->getTerritoryByID(this->territoryid);
	terr->numArmy = terr->numArmy + this->num;
}


Advance::Advance(Player* player, int territoryID, int new_territoryID, int numSoldiers) {
	this->player = player;
	this->territoryid = territoryID;
	this->new_territoryid = new_territoryID;
	this-> numSoldiers = numSoldiers;
}
Advance::Advance(const Advance& o1) {
	this->player = o1.player;
	this->territoryid = o1.territoryid;
	this->new_territoryid = o1.new_territoryid;
	this->numSoldiers = o1.numSoldiers;
}
bool Advance::validate() {
	Territory* terr = this->player->getTerritoryByID(this->territoryid);
	Territory* new_terr = this->player->getTerritoryByID(this->new_territoryid);
	if (!player->ownTerritory(terr) || player->ownTerritoryByFriend(new_terr) || terr->isAdjTerritory(new_terr) == false || terr->numArmy < this->numSoldiers) {
		return false;
	}
	return true;
}

void Advance::execute() {
	// map.clear_armies(current_player, source_territories)
	// map.add_armies(current_player, target_territories)
	// std::cout << info << std::endl;
	// std::cout << " -> PlayID " << player->playerName << " move all armies " << " from " << territoryid << " territory to " << new_territoryid << " territory" << std::endl;
	Territory* terr = this->player->getTerritoryByID(this->territoryid);
	Territory* new_terr = this->player->getTerritoryByID(this->new_territoryid);
	if (player->ownTerritory(terr) && player->ownTerritory(new_terr)) {
		terr->numArmy -= this->numSoldiers;
		new_terr->numArmy += this->numSoldiers;
	}
	else {
		terr->numArmy -= this->numSoldiers;
		while (this->numSoldiers != 0 && new_terr->numArmy != 0) {
			float p = (rand() % (10 + 1)) / 10.0;
			if (p < 0.6) {
				this->numSoldiers--;
			}
			p = (rand() % (10 + 1)) / 10.0;
			if (p < 0.7) {
				new_terr->numArmy--;
			}
		}
		if (this->numSoldiers != 0 && new_terr->numArmy == 0) {
			*new_terr = *terr;
			new_terr->numArmy = this->numSoldiers;
		}
	}
}

Bomb::Bomb(Player* player, int oppTerritory) {
	this->player = player;
	this->oppTerritory = oppTerritory;
}
Bomb::Bomb(const Bomb& o1) {
	this->player = o1.player;
	this->oppTerritory = o1.oppTerritory;
}
bool Bomb::validate() {
	Territory* terr = this->player->getTerritoryByID(this->oppTerritory);
	if (this->player->ownTerritory(terr) || this->player->ownTerritoryByFriend(terr)) {
		return false;
	}
	return true;
}

void Bomb::execute() {
	// map.update_armies(target_player, territories, 0.5)
	// std::cout << info << std::endl;
	// std::cout << "the armies on " << oppTerritory << " territory is reduced.";
	Territory* terr = this->player->getTerritoryByID(this->oppTerritory);
	terr->numArmy = terr->numArmy / 2;
}


Blockade::Blockade(Player* player, int territoryID) {
	this->player = player;
	this->territoryid = territoryID;
}
Blockade::Blockade(const Blockade& o1) {
	this->player = o1.player;
	this->territoryid = o1.territoryid;
}
bool Blockade::validate() {
	Territory* terr = this->player->getTerritoryByID(this->territoryid);
	if (this->player->ownTerritory(terr)) {
		return true;
	}
	return true;
}

void Blockade::execute() {
	// map.update_armies(target_player, territories, 3)
	// map.set_flag(-1); // neutral territory
	// std::cout << info << std::endl;
	// std::cout << "the armies on " << territoryid << " territory is triple, but this territory is marked as a neutral territory";
	Territory* terr = this->player->getTerritoryByID(this->territoryid);
	terr->numArmy *= 2;
	this->player->setNeutral(terr);
}


Airlift::Airlift(Player* player, int territoryID, int new_territoryID, int num) {
	this->player = player;
	this->territoryid = territoryID;
	this->new_territoryid = new_territoryID;
	this->num = num;
}
Airlift::Airlift(const Airlift& o1) {
	this->player = o1.player;
	this->territoryid = o1.territoryid;
	this->new_territoryid = o1.new_territoryid;
	this->num = o1.num;
}
bool Airlift::validate() {
	Territory* terr = this->player->getTerritoryByID(this->territoryid);
	Territory* new_terr = this->player->getTerritoryByID(this->new_territoryid);
	if (this->player->ownTerritory(terr) && this->player->ownTerritory(new_terr) && terr->numArmy >= this->num) {
		return true;
	}
	return false;
}

void Airlift::execute() {
	// map.add_armies(current_player, target_territories)
	// std::cout << info << std::endl;
	// std::cout << " -> PlayID " << player->playerName << " move " << num << " armies " << " from " << territoryid << " territory to " << new_territoryid << " territory" << std::endl;

	Territory* terr = this->player->getTerritoryByID(this->territoryid);
	Territory* new_terr = this->player->getTerritoryByID(this->new_territoryid);
	terr->numArmy -= this->num;
	new_terr->numArmy += this->num;
}


Negotiate::Negotiate(Player* player1, Player* player2) {
	this->player1 = player1;
	this->player2 = player2;
}
Negotiate::Negotiate(const Negotiate& o1) {
	this->player1 = o1.player1;
	this->player2 = o1.player2;
}
bool Negotiate::validate() {
	if (this->player1 == this->player2) {
		return false;
	}
	return true;
}

void Negotiate::execute() {
	// map.add_negotiate(current_player, target_player)
	// std::cout << info << std::endl;
	// std::cout << "Negotiate built between Player " << player1->playerName << " and Player " << player2->playerName << std::endl;
	this->player1->addFriends(this->player2);
	this->player2->addFriends(this->player1);
}

// new an order list
OrdersList::OrdersList() {
	olist = new std::vector<Order*>();
}

OrdersList::OrdersList(const OrdersList& ol) {
	this->olist = new std::vector<Order*>();
	for (int i = 0; i < ol.olist->size(); i++) {
		this->olist->push_back((*ol.olist)[i]);
	}
}

// free the order list
OrdersList::~OrdersList() {
	delete olist;
}

// remove an order from the order list
void OrdersList::remove(Order* order) {
	std::remove(olist->begin(), olist->end(), order);
}

// insert an order to the order list
void OrdersList::add(Order* order) {
	olist->push_back(order);
}

// move 
void OrdersList::move(Order* order, int index) {
	int size = olist->size();
	if (index >= size) {
		std::cout << "unable to move" << std::endl;
		return;
	}
	std::remove(olist->begin(), olist->end(), order);
	olist->insert(olist->begin() + index, order);
}
