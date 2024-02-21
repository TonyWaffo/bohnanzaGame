#pragma once
#include "Card.h"
class Soy : public Card {
public:

	int getCardsPerCoin(int coins);
	string getName();
	void print(ostream& out);
};

int Soy::getCardsPerCoin(int coins) {
	if (coins < 2) {
		return 0;
	}
	else if (coins >= 2 && coins <= 7) {
		switch (coins) {
		case 2:
		case 3:
			return 1;
			break;
		case 4:
		case 5:
			return 2;
			break;
		case 6:
			return 3;
			break;
		case 7:
			return 4;
			break;
		}
	}
	else {
		return 4 + getCardsPerCoin(coins - 7);
	}
};


string Soy::getName() {
    return "Soy";

};

void Soy::print(ostream& output) { output << 'S'; }