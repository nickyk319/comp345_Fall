#include <iostream>
#include <time.h>
#include "Cards.h"
#include "Orders.cpp"
#include "OrdersList.cpp"

using namespace std;

int main() {

    Deck* my_deck = new Deck();
    cout << *my_deck << endl;
    OrdersList* olist = new OrdersList();
    Card* my_card = new Card();
    Hand* hand = new Hand(my_deck);
    cout << *hand << endl;
    for(auto &card : hand->getHandCards()){
        card->play(olist, my_deck, my_card);
    }
//    Card* my_card = new Card();
//    printCard(my_card);
    return 0;
}
