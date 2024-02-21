// some added methods might have been added, but hasn't been used in te program
#pragma once
#include "Player.h"
#include "Deck.h"
#include "DiscardPile.h"
#include "TradeArea.h"
#include "CardFactoryAndDeck.h"
#include <iostream>
using namespace std;

class Table {
public :
	vector<Player*> players;
	Deck* deck;
	DiscardPile* discardPile;
	TradeArea* tradeArea;
	CardFactory* cardFactory;
	bool win(std::string&);
	void printHand(bool);
	Table(string, string);
	Table(istream&, const CardFactory*);
	friend ostream& operator<<(ostream&, Table&);
	void display();
};

bool Table::win(string & name) {
	if (deck->empty()) {
		if (players[0]->getNumCoins() > players[1]->getNumCoins()) {
			name = players[0]->getName();
		}
		else {
			name = players[1]->getName();
		}
		return 1;
	}
	else {
		return 0;
	}
}


//print either the full hand or the first card of both players
void Table::printHand(bool showHand) {
	/*if (!showHand) { // show only first card
		cout << players[0]->getName() << "'s first card is " << players[1]->hand->top() << endl;
		cout << players[1]->getName() << "'s first card is " << players[1]->hand->top() << endl;
	}
	else { // show all hand
		cout << players[0]->getName() << "'s first card is " << players[0]->hand->printCards() << endl;
		cout << players[1]->getName() << "'s first card is " << players[1]->hand->printCards() << endl;
	}*/
	cout << "---------- Player1 ----------" << endl;
	players[0]->printHand(cout, showHand);
	cout << "---------- Player2 ----------" << endl;
	players[1]->printHand(cout, showHand);
	cout << "-------------------------------" << endl;
}

//Create a table with two users, a deck, a trade area and a discardpile
Table::Table(string name1, string name2) {
	players.push_back( new Player(name1));
	players.push_back(new Player(name2));
	cardFactory = new CardFactory();
	deck = new Deck(cardFactory->getDeck());
	discardPile = new DiscardPile();
	tradeArea = new TradeArea();
}

//Create a table previously described, but from an input
Table :: Table(istream& input, const CardFactory* cardFactory) {
	this->players.push_back(new Player(input, cardFactory));
	this->players.push_back(new Player(input, cardFactory));
	this->discardPile = new DiscardPile(input, cardFactory);
	this->tradeArea = new TradeArea(input, cardFactory);
};

//output data in a stream
ostream& operator<<(ostream& output, Table& table) {
	output << *table.players[0];
	output << *table.players[1];
	output << *table.discardPile;
	output << *table.tradeArea;
	output << *table.deck;
	return output;
};


//display data 
void Table::display() {

	cout << "-------------- PLAYERS -------------" << endl;
	players[0]->display();
	cout << "------------------------------------" << endl;
	players[1]->display();
	cout << "--------------- DECK ---------------" << endl;
	deck->display();
	cout << "------------ TRADE AREA ------------" << endl;
	tradeArea->display();
	cout << "----------- DISCARD PILE -----------" << endl;
	discardPile->display();
	cout << "------------------------------------" << endl << endl;

}