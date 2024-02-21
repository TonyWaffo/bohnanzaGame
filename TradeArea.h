// some added methods might have been added, but hasn't been used in te program
#pragma once
#include <list>
#include "Card.h"
#include "CardFactoryAndDeck.h"
#include <iostream>

using namespace std;

class TradeArea {
public:
	list<Card*> cards;
	TradeArea& operator+=(Card*);
	bool legal(Card*);
	Card* trade(string);
	int numCards();
	friend ostream& operator << (ostream&, TradeArea);
	TradeArea(istream&, const CardFactory*);
	TradeArea(){};
	void display();
	bool contains(Card*);
	void remove(Card* card);
	void removeIndex(int);
};

//Add a card to the tradeArea
TradeArea& TradeArea :: operator+=(Card* card) {
	cards.push_back(card);
	return *this;
};


//Tell if a card can be added to the trade area
bool TradeArea::legal(Card* card) {
	if (cards.size() == 0) {
		return true;
	}

	for (Card* tradeAreaCard : cards) {
		if (tradeAreaCard->getName() == card->getName()) {
			return true;
		}
	}

	return false;

};


//remove from the trade a card with the corresponding name
Card* TradeArea::trade(string cardName) {
	Card* result = nullptr;

	if (cards.empty()) {
		cout << "Empty Trade area !";
	}
	for (Card* card : cards) {
		if (card->getName() == cardName) {
			cards.remove(card);
			result = card;
		}
	}
	return result;
};

//return the number of card of the trade area
int TradeArea::numCards() {
	return (int) cards.size();
};

ostream& operator << (ostream& output, TradeArea tradeArea) {
	for (Card* card : tradeArea.cards) {
		card->print(output);
	}
	return output;
};

TradeArea :: TradeArea(istream& input, const CardFactory* cardFactory) {
	char line[1026];
	char card;
	int index = 0;
	input.getline(line, 1026);
	card = line[index];

	while (card != NULL) {
		this->cards.push_back(cardFactory->getCard(card));
		card = line[++index];
	}
};


//Display the trade adrea
void TradeArea::display() {
	for (Card* card : cards) {
		cout << card->getName() << " ";
	}
	cout << endl;
}


//Check if trade Area contain a specific card
bool TradeArea :: contains(Card* card) {
	if (card == nullptr) return false;
	for (Card* tradeAreaCard : this->cards) {
		if (tradeAreaCard->getName() == card->getName()) {
			return true;
		}
	}
	return false;
}


//remove card from the tradeArea
void TradeArea::remove(Card* card2) {
	char answer;
	bool matched = false;
	Card* card = nullptr;
	int index = 0;


	for (Card* card : this->cards) {
		index++;
		if (card->getName() == card2->getName()) {

			removeIndex(index);
			break;
		}
	}
}

//Use by the method remove(Card*) to remove a card at a specific position
void TradeArea::removeIndex(int index) {
	auto iterator = this->cards.begin();
	advance(iterator, index - 1);
	this->cards.erase(iterator);
}