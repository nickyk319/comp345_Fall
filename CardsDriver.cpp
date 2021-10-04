#include <iostream>
#include <time.h>
#include "Cards.h"

using namespace std;

int main() {
//    Card* card = new Card();
//    cout << *card << endl;
    Deck* my_deck = new Deck();
    cout << *my_deck << endl;
//    Card* card = my_deck->draw();
//    cout << '\n';
//    cout << *card << endl;
    Hand* hand = new Hand(my_deck);
    cout << *hand << endl;
//    Card* my_card = new Card();
//    printCard(my_card);
    return 0;
}
