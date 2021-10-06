//
// Created by Yaqi Kang on 2021-10-03.
//

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <iterator>
#include <ctime>
#include "Cards.h"
#include "Order.h"
#include "OrdersList.h"

using namespace std;

Card::Card() {
    cardType = bomb;

}

Card::Card(CardType type) {
    this->cardType = type;

}

Card::Card(const Card &card) {
    cardType = card.cardType;

}

Card::~Card() {
}

std::ostream &operator<<(std::ostream &output, const Card &card) {
    output << "The card type is " << Card::cardTypeToString(card.getType()) << endl;
    return output;
}

Card &Card::operator=(const Card &card) {
    cardType = card.cardType;
    return *this;
}

CardType Card::getType() const {
    return cardType;
}

string Card::cardTypeToString(CardType cardTypeToString) {
    switch (cardTypeToString) {
        case 0:
            return "bomb";
        case 1:
            return "reinforcement";
        case 2:
            return "blockade";
        case 3:
            return "airlift";
        case 4:
            return "diplomacy";
    }
    return "";
}

//void Card::play(vector<Order *> &olist, vector<Card *> &cards, vector<Card *> &handCards) {
//    Card* card;
    //add card corresponding order to order list
//    if(cardTypeToString(getType()) == "bomb"){
//        olist.add(new Bomb(2));
//    }else if(cardTypeToString(getType()) == "reinforcement"){
//        olist.add(new Deploy(2,2,3));
//    }else if(cardTypeToString(getType()) == "blockade"){
//        olist.add(new Blockade(2));
//    }else if(cardTypeToString(getType()) == "airlift"){
//        olist.add(new Airlift(2,2,3,4));
//    }else if(cardTypeToString(getType()) == "diplomacy"){
//        olist.add(new Negotiate(2, 3));
//    }

    //remove this card from hand
//    auto it = std::find(handCards.begin(), handCards.end(), card);
//
//    if(it != handCards.end()){
//        handCards.erase(it);
//    }
//    //return it back to deck
//    cards.emplace_back(new Card(*card));
//}

Deck::Deck() {
    initializeDeck();
    shuffleDeck();
}

void Deck::initializeDeck() {
    for(int i = 0; i < max_deck_size/CardTYPE_ITEMS; i++){
            cards.emplace_back(new Card(bomb));
            cards.emplace_back(new Card(reinforcement));
            cards.emplace_back(new Card(blockade));
            cards.emplace_back(new Card(airlift));
            cards.emplace_back(new Card(diplomacy));
    }
}

Deck::~Deck() {
    for (auto & card : cards) {
        delete card;
        card = nullptr;
    }
}

Deck::Deck(const Deck &deck) {
    for (auto & card : deck.cards) {
        cards.emplace_back(new Card(*card));
    }
}

Deck &Deck::operator=(const Deck &deck) {
    cards.clear();
    for (auto & card : deck.cards) {
        cards.emplace_back(new Card(*card));
    }
    return *this;
}

ostream &operator<<(std::ostream &output, const Deck &deck) {
    int size = deck.cards.size();
    output << "The cards on the deck is:" << endl;
    for (int i = 0; i < size; ++i) {
        if(i % 5 == 0){
            cout << '\n';
        }
        output << Card::cardTypeToString(deck.cards[size - 1 - i]->getType()) << " ";

    }
    return output;
}

vector<Card*> Deck::getCards() {
    return cards;
}

Card* Deck::draw() {
    //generate a random index of size
    srand((unsigned int)time(NULL));
    int random = rand() % cards.size();
    Card* card;
    //take out the random selected element
    if (!cards.empty()) {
        card = cards[random];
    } else {
        card = nullptr;
    }
    cards.erase(cards.begin() + random);
    return card;
}

void Deck::shuffleDeck() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

Hand::Hand() {
        //handCards.emplace_back(new Card());
}

//Hand::Hand(Deck *deck) {
//        handCards.emplace_back(deck->draw());
//}

Hand::~Hand() {
    for (auto & card : handCards) {
        delete card;
        card = nullptr;
    }
}

Hand::Hand(const Hand &hand) {
    for (auto & card : hand.handCards) {
        handCards.emplace_back(new Card(*card));
    }
}

Hand &Hand::operator=(const Hand &hand) {
    handCards.clear();
    for (auto & card : hand.handCards) {
        handCards.emplace_back(new Card(*card));
    }
    return *this;
}

std::ostream &operator<<(ostream &output, const Hand &hand) {

    output << "\nCards in hand are:\n";
    for (auto & card : hand.handCards) {
        output << card->cardTypeToString(card->getType());
        output << '\n';
    }
    output << "\n" << endl;
    return output;
}

void Hand::setHandCards(Card * card)
{
    //add the card into the handcards,we can recall the deck->draw() to get a card
    handCards.push_back(card);

}

vector<Card*> Hand::getHandCards() {
    return handCards;
}

void Hand::remove_played_handCards(Card* card)
{
    //traverse the hand cards, find a same type card, then delete it.
    //we don't need to find the specific card because it is hard, just delete one same type card from handcards
    for (int p = 0; p < handCards.size(); p++) {
        if (handCards.at(p)->getType() == card->getType()) {
            //find a same type card, then delete, and return.
            //vec_hand_cards.erase(vec_hand_cards.begin() + p);
            handCards.erase(handCards.begin() + p);
            cout << "...deleting the card " << card->cardTypeToString(card->getType()) << " from the Hand\n"<<  endl;
            return;
        }
    }
}
void Hand::play(OrdersList* olist, Card *card, Deck* deck){

    //add card corresponding order to order list
    if(card->cardTypeToString(card->getType()) == "bomb"){
        olist->add(new Bomb(2));
        cout << "Bomb add to the order list" << endl;
    }else if(card->cardTypeToString(card->getType()) == "reinforcement"){
        olist->add(new Deploy(2,2,3));
        cout << "reinforcement add to the order list" << endl;
    }else if(card->cardTypeToString(card->getType()) == "blockade"){
        olist->add(new Blockade(2));
        cout << "blockade add to the order list" << endl;
    }else if(card->cardTypeToString(card->getType()) == "airlift"){
        olist->add(new Airlift(2,2,3,4));
        cout << "airlift add to the order list" << endl;
    }else if(card->cardTypeToString(card->getType()) == "diplomacy"){
        olist->add(new Negotiate(2, 3));
        cout << "diplomacy add to the order list" << endl;
    }

    //return this card back to deck
    deck->getCards().emplace_back(card);

    //remove this card from hand
//    auto it = find(handCards.begin(), handCards.end(), card);
//    if(it != handCards.end()){
//        handCards.erase(it);
//    }
    remove_played_handCards(card);


}
