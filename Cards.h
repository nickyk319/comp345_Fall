//
// Created by 40061670_Yaqi Kang on 2021-10-03.
//
#pragma once
//runable version master
#include <iostream>
#include <vector>
#include <string>
#include "Order.h"



using namespace std;

enum CardType{
    bomb, reinforcement, blockade, airlift, diplomacy
};

const int CARD_TYPE_ITEMS = 5;



class Card{
public:
    Card();
    explicit Card(CardType cardType);
    Card(const Card&);
    ~Card();
    friend ostream& operator<<(ostream& output, const Card& card);
    Card& operator=(const Card& card);
    CardType getType() const;
    static string cardTypeToString(CardType cardTypeToString);

private:
    CardType cardType;
};


class Deck{
public:
    //default constructor
    Deck();
    //destructor
    ~Deck();
    //copy constructor
    Deck(const Deck&);
    //assignment operator
    Deck& operator=(const Deck& obj);
    //stream insertion operator
    friend ostream& operator<<(ostream& output, const Deck& deck);
    //get method
    vector<Card*> getCards();
    friend ostream& operator<<(ostream& output, const Deck& deck);
    //draw method
    Card* draw();
    void shuffleDeck();
    void add_card_to_deck(Card * card);
private:
    vector<Card*> cards;
    int max_deck_size = 50;
    void initializeDeck();
};

class Hand: public Card{
public:
    Hand();
    ~Hand();
    Hand(const Hand& obj);
    Hand& operator= (const Hand& obj);
    friend ostream& operator<<(ostream& output, const Hand& hand);
    void setHandCards(Card *card);
    vector<Card*> getHandCards();
    void remove_played_handCards(Card* r_card);
    void return_card_to_deck(Deck* deck);
    void play(OrdersList* olist, Card* card, Deck* deck);
private:
    vector<Card*> handCards;
    vector<Card*> handCards_to_play;
};