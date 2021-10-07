#include <iostream>
#include "Cards.h"
#include "Order.h"
#include "OrdersList.h"

using namespace std;

int main() {

    Deck* my_deck = new Deck();
    cout << *my_deck << endl;

    Hand* my_hand = new Hand();

    cout << "\n*****************************************" << endl;
    cout << "\nTake 5 cards from deck to hand:" << endl;
    for(int i = 0; i < 5; i++){
        my_hand->setHandCards(my_deck->draw());
    }
    cout << *my_hand << endl;

    auto* olist = new OrdersList();

    cout << "*****************************************" << endl;
    cout << "Add cards to order list:\n" << endl;

    //implement play method
    for(auto card : my_hand->getHandCards()){
        my_hand->play(olist, card, my_deck);
    }
    cout << "*****************************************" << endl;
    cout << "After played all cards in hand" << endl;
    cout << *my_hand << endl;

    //prevent memory leak
    delete my_deck;
    delete my_hand;

    return 0;
}
