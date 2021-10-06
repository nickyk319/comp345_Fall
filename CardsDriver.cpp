#include <iostream>
#include "Cards.h"
#include "Order.h"
#include "OrdersList.h"

using namespace std;

int main() {

    Deck* my_deck = new Deck();
    cout << *my_deck << endl;

    Hand* hand = new Hand();

    cout << "\n*****************************************" << endl;
    cout << "\nTake 5 cards from deck to hand:" << endl;
    for(int i = 0; i < 5; i++){
        hand->setHandCards(my_deck->draw());
    }
    cout << *hand << endl;

    OrdersList* olist = new OrdersList();

    cout << "*****************************************" << endl;
    cout << "Add cards to order list:\n" << endl;
    //implement play method
    for(auto card : hand->getHandCards()){
        hand->play(olist, card, my_deck);
    }


    return 0;
}
