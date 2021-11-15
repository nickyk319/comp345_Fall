//
// Created by 40061670_Yaqi Kang on 2021-10-03.
//

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <random>
#include <iterator>
#include <ctime>
#include "Cards.h"
#include "Order.h"


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

Deck::Deck() {
    initializeDeck();
    shuffleDeck();
}

//initialize 50 cards to deck
void Deck::initializeDeck() {
    for(int i = 0; i < max_deck_size/CARD_TYPE_ITEMS; i++){
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
    srand(time(nullptr));
    int card_size = cards.size();
    int random = rand() % card_size;
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

void Deck::add_card_to_deck(Card * card)
{
    cards.push_back(card);
}

Hand::Hand() {}


Hand::~Hand() {
    for (auto & card : handCards) {
        delete card;
        card = nullptr;
    }
}

Hand::Hand(const Hand &hand) {
    for (auto & card : hand.handCards) {
        handCards.emplace_back(new Card(*card));
        handCards_to_play.emplace_back(new Card(*card));
    }
}

Hand &Hand::operator=(const Hand &hand) {
    handCards.clear();
    handCards_to_play.clear();
    for (auto & card : hand.handCards) {
        handCards.emplace_back(new Card(*card));
        handCards_to_play.emplace_back(new Card(*card));
    }
    return *this;
}

std::ostream &operator<<(ostream &output, const Hand &hand) {

    output << "\nCards in hand are:\n";
    for (auto & card : hand.handCards) {
        output << card->cardTypeToString(card->getType());
        output << '\n';
    }
    if(hand.handCards.empty()){
        cout << "No more cards in hand." << endl;
    }

    output << "\n" << endl;
    return output;
}

void Hand::setHandCards(Card * card)
{
    //add the card to the hand
    handCards.push_back(card);

}

vector<Card*> Hand::getHandCards() {
    return handCards;
}

void Hand::remove_played_handCards(Card* card)
{
    //remove a card from hand if played
    for (int p = 0; p < handCards.size(); p++) {
        if (handCards.at(p)->getType() == card->getType()) {
            handCards.erase(handCards.begin() + p);
            cout << "...deleting the card " << card->cardTypeToString(card->getType()) << " from the Hand\n"<<  endl;
            return;
        }
    }
}

//return the played card to deck
void Hand::return_card_to_deck(Deck* deck)
{
    for (int n = 0; n < handCards_to_play.size(); n++) {
        //add the played card of vec_play_cards to Deck cards
        deck->add_card_to_deck(handCards_to_play.at(n));
    }

}

void Hand::play(OrdersList* olist, Card *card, Deck* deck){

    handCards_to_play.push_back(card);

    //add card corresponding order to order list
//    if(card->cardTypeToString(card->getType()) == "bomb"){
//        olist->add(new Bomb(2));
//        cout << "Bomb add to the order list" << endl;
//    }else if(card->cardTypeToString(card->getType()) == "reinforcement"){
//        olist->add(new Deploy(2,2,3));
//        cout << "reinforcement add to the order list" << endl;
//    }else if(card->cardTypeToString(card->getType()) == "blockade"){
//        olist->add(new Blockade(2));
//        cout << "blockade add to the order list" << endl;
//    }else if(card->cardTypeToString(card->getType()) == "airlift"){
//        olist->add(new Airlift(2,2,3,4));
//        cout << "airlift add to the order list" << endl;
//    }else if(card->cardTypeToString(card->getType()) == "diplomacy"){
//        olist->add(new Negotiate(2, 3));
//        cout << "diplomacy add to the order list" << endl;
//    }

    //remove card from hand
    remove_played_handCards(card);
    //return this card back to deck
    return_card_to_deck(deck);

    handCards_to_play.pop_back();


}
