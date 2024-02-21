#pragma once

class Card {
	
public :

	int cardCount;

	virtual int getCardsPerCoin(int coins) = 0;
	virtual string getName() = 0;
	virtual void print(ostream& out) = 0;

};