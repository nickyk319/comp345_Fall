#include<iostream>
#include<list>
#include <vector>
#include"Player.h"
#include "Map.h"
#include "Order.h"
using namespace std;




void Order::setcountry(int country) {
	m_country = country;
}
void Order::setorder(string order) {
	m_order = order;
}
void Order::settarget(int target) {
	m_target = target;
}
	
void player::printList(const list<int>& L) {
			for (list<int>::const_iterator it = L.begin(); it != L.end(); it++) {
				cout << *it << " ";
			}
			cout << endl;
		}
int player::getsize() {
			int size = sizeof(territories) / sizeof(territories[0]);
			return size;
		}

void player::showPlayer() {
			cout << "This player has:\ncountry:" << getsize() << " card:" << ahandofCards << endl;
		}

void player::showCards() {
			for (auto i : cards)
			cout << i << endl;
		}

std::list<int> player::todefend(const string& s) {
			vector<int> defends = parseStringToInt(s);
			for (auto i : defends) 
					todefendlist.push_back(i);
			
			return todefendlist;
		}

std::list<int> player::toAttack(const string& s) {
			vector<int> attacks = parseStringToInt(s);
			for (auto i : attacks) 
					toAttacklist.push_back(i);
			
			return toAttacklist;
		}

std::list<Order> player::issueOrder(string order) {
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
			cout << "\n" << worldMap.territories[tID-1];
			int numDeploy;
			cin >> numDeploy;

			reinforcements-=numDeploy;
			Deploy* d = new Deploy(pID, tID, numDeploy);
			cout << "\nAdded " << numDeploy << " Reinforcements!";
			cout << "\n" << worldMap.territories[tID-1];
			OrderList.push_back(*d);
			}

			//Advance
			cout << "ADVANCE ORDER: \n" << endl;
			for (auto i : todefendlist) {
				cout << "Defending " << worldMap.territories[i-1];
				cout << "\nWhich Territory are you advancing to?\n";
				worldMap.territories[i-1]->displayBorders();
				int tID;
				int num;
				cin >> tID;
				for (auto j : territories) {
					if (j->tID == tID) {
						cout << "\nHow many troops are being moved?\n";
						cin >> num;
						Advance* a = new Advance(pID, worldMap.territories[i-1]->getTID(), worldMap.territories[tID-1]->getTID(), num);
						OrderList.push_back(*a);
						cout << "Success!";
						break;
					}
					cout << "\nTerritory does not belong to you...\n";
				}
			}
			for (auto i : toAttacklist) {
				cout << "Attacking with " << worldMap.territories[i-1];
				cout << "\nWhich Territory are you attacking?\n";
				worldMap.territories[i-1]->displayBorders();
				int tID;
				cin >> tID;
				for (auto j : territories) {
					if (j->tID == tID) {
						cout << "\nTerritory belongs to you...\n";
						break;
					}
					Bomb* b = new Bomb(worldMap.territories[tID-1]->getTID());
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
					Bomb* b = new Bomb(worldMap.territories[tID-1]->getTID());
					OrderList.push_back(*b);
				}
				case reinforcement: {
					cout << "\nSelect a destination";
					int tID;
					cin >> tID;
					Deploy* d = new Deploy(pID, worldMap.territories[tID-1]->getTID(), 5);
					OrderList.push_back(*d);
				}
				case blockade: {
					cout << "\nSelect a target";
					int tID;
					cin >> tID;
					Blockade* b = new Blockade(worldMap.territories[tID-1]->getTID());
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
					Airlift* a = new Airlift(pID, worldMap.territories[tID2-1]->getTID(), worldMap.territories[tID-1]->getTID(), num);
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
		}
		
		void player::printOrder(list<Order> &L) {
			cout << " listoforder: \n" << endl;
			for (list<Order>::iterator t = L.begin(); t != L.end();t++) {
				cout << (*t).m_country << " is going to"<<(*t).m_order<<" coutry "<<(*t).m_target<<endl;
			}
			cout << endl;
		}

		void player::printAdjacentTerritories() {
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

		void player::printTerritories() {
			cout << "Player " << pID << "'s Defendable Territories: ";
			
			for (auto i : territories)
				cout << i->getTID() << " ";



