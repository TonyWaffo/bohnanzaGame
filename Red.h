#pragma once
#include "Card.h"
class Red : public Card {
public:
	int getCardsPerCoin(int coins);
	string getName();
	void print(ostream& out);
};

int Red::getCardsPerCoin(int coins) {
	if (coins < 2) {
		return 0;
	}
	else if (coins >= 2 && coins <= 5) {
		switch (coins) {
		case 2:
			return 1;
			break;
		case 3:
			return 2;
			break;
		case 4:
			return 3;
			break;
		case 5:
			return 4;
			break;
		}
	}
	else {
		return 4 + getCardsPerCoin(coins - 5);
	}
};

string Red::getName() {
    return "Red";

};

void Red::print(ostream& output) { output << 'R'; }

