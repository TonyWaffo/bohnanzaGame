// some added methods might have been added, but hasn't been used in te program
#pragma once
#include <vector>
#include <iostream>
#include "Card.h"
#include "CardFactoryAndDeck.h"
using namespace std;

class Chain_Base : public vector<Card*>{
public :
	virtual int sell() = 0;
	int numCards = 0;
	string type = "Empty";//set type of the Chain to empty
	void display();
	Chain_Base& operator+=(Card*);
};

template <class T> class Chain: public Chain_Base{
public :
	Chain<T>& operator+=(Card*);
	friend ostream& operator << (ostream&,Chain&);
	int sell();
	Chain(istream&,const CardFactory*);
	Chain();
};

class IllegalType : public exception {
	virtual const char* what() const throw() {
		return " No matching type";
	}
};

template <class T> Chain<T>& Chain<T>:: operator +=(Card* card) {
	T myCard;
	if (myCard.getName() != card->getName()) {
		throw IllegalType();
	}
	else {
		this->push_back(card);
		numCards++;
	}
	return *this;
};

//sell cards for coins
template <class T> int Chain<T> :: sell() {
	T card;
	int totalCoins;
	if (this->size() >= card.getCardsPerCoin(4)) {
		totalCoins = 4;
	}
	else if (this->size() >= card.getCardsPerCoin(3)) {
		totalCoins = 3;
	}
	else if (this->size() >= card.getCardsPerCoin(2)) {
		totalCoins = 2;
	}
	else if (this->size() >= card.getCardsPerCoin(1)) {
		totalCoins = 1;
	}
	else {
		totalCoins = 0;
	}

	this->clear();		//clear the chain
	numCards = 0;
	return totalCoins;
}



template <class T>ostream&  operator << (ostream& output, Chain<T>& chain) {
	output << chain.type << " ";

	for (auto card : chain) {
		card.print(output);
	}
	return output;
};





template <class T> Chain<T> ::Chain() {
	T card;
	type = card.getName();
};


template <class T>  Chain<T> ::Chain(istream& input,const CardFactory* cardFactory) {
	char line[1026];
	input.getline(line, 1026);
	int index = 0;
	

	while (line[index] != ' ') {
		this->type += line[index++];
	}
	int no = line[++index];

	for (int i = 0; i < no; i++) {
		this->push_back(cardFactory->getCard(this->type.at(0)));
	}
};


//Display the number of card and the type of the chain
void Chain_Base :: display() {
	cout << numCards << " " << type << endl;
}





