#pragma once
#include "Card.h"
class Blue : public Card
{
public:

	int getCardsPerCoin(int coins);
	string getName();
	void print(ostream& out) ;

};


int Blue::getCardsPerCoin(int coins) {
	if (coins < 4) {
		return 0;
	}
	else if (coins >= 4 && coins <= 10) {
		switch (coins) {
		case 4:
		case 5:
			return 1;
			break;
		case 6:
		case 7:
			return 2;
			break;
		case 8:
		case 9:
			return 3;
			break;
		case 10:
			return 4;
			break;
		}
	}
	else {
		return 4 + getCardsPerCoin(coins - 10);
	}
};

string Blue::getName() {
    return "blue";

}

void Blue::print(ostream& output) { output << 'b'; }