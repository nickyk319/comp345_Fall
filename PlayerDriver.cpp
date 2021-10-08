#include<iostream>
#include"Player.h"
int main() {
	player x;
	x.territories[0]=2;
	x.todefend(&x.territories[0]);
	x.toAttack(&x.territories[0]);
	list<Order>s1=x.issueOrder(32,"attack", 34);
	x.printOrder(s1);

	x.showPlayer();
	cout << "\ncountry to attack:" << endl;
	x.printList(x.toAttacklist);
	cout << "\ncountry to defend: " << endl;
	x.printList(x.todefendlist);
	return 0;
}
