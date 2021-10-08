#include<iostream>
#include<list>
#include"Player.h"
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

std::list<int> player::todefend(int* territories) {

			for (int i = 0; i < getsize() - 1; i++) {
				if (territories != 0) {
					todefendlist.push_back(territories[i]);
				}
			}
			
			return todefendlist;
		}

std::list<int> player::toAttack(int* territories) {

			for (int i = 0; i < getsize() - 1; i++) {
				if (territories != 0) {
					toAttacklist.push_back(territories[i]+1);
				}
			}
			
			return toAttacklist;
		}

std::list<Order> player::issueOrder(int country, string order, int target) {
			Order x;
			x.setcountry(country);
			x.setorder(order);
			x.settarget(target);
			OrderList.push_back(x);
			return OrderList;
		}
		
		void player::printOrder(list<Order> &L) {
			cout << " listoforder: \n" << endl;
			for (list<Order>::iterator t = L.begin(); t != L.end();t++) {
				cout << (*t).m_country << " is going to"<<(*t).m_order<<" coutry "<<(*t).m_target<<endl;
			}
			cout << endl;
		}




