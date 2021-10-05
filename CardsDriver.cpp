#include <iostream>
#include <time.h>
#include "Cards.h"
#include "Order.h"
#include "OrdersList.h"

using namespace std;

int main() {

    Deck* my_deck = new Deck();
    cout << *my_deck << endl;


    Hand* hand = new Hand(my_deck);
    cout << *hand << endl;

    OrdersList* olist = new OrdersList();

    for(auto &card : hand->getHandCards()){
        card->play(olist, my_deck->getCards(), hand->getHandCards());
    }

    return 0;
}
