#pragma once
#include "Card.h"
class Black : public Card {
	
public :
	int getCardsPerCoin(int coins);
	string getName();
	void print(ostream& out);
};

int Black::getCardsPerCoin(int coins) {
	if (coins < 2) {
		return 0;
	}
	else if (coins >= 2 && coins <= 6) {
		switch (coins) {
		case 2:
		case 3:
			return 1;
			break;
		case 4:
			return 2;
			break;
		case 5:
			return 3;
			break;
		case 6:
			return 4;
			break;
		}
	}
	else {
		return 4 + getCardsPerCoin(coins - 6);
	}
};


string Black::getName() {
    return "Black";

};

void Black::print(ostream& output) { output << 'B'; }

