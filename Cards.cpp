//
// Created by nicky on 2021-10-03.
//

#include <iostream>
#include <string>
#include <vector>       // std::vector
#include <random>
#include <iterator>
#include <time.h>
#include "Cards.h"

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
    // did not use new in the constructor.
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
    for(int i = 0; i < 5; i++){
        handCards.emplace_back(new Card());
    }
}

Hand::Hand(Deck *deck) {
    for(int i = 0; i < 5; i++) {
        handCards.emplace_back(deck->draw());
    }
}

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

vector<Card*> Hand::getHandCards() {
    return handCards;
}
