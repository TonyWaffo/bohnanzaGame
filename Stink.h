#pragma once
#include "Card.h"
class Stink : public Card {
public:

    int getCardsPerCoin(int coins);
    string getName();
    void print(ostream& out);

};

int Stink::getCardsPerCoin(int coins) {
	if (coins < 3) {
		return 0;
	}
	else if (coins >= 3 && coins <= 8) {
		switch (coins) {
		case 3:
		case 4:
			return 1;
			break;
		case 5:
		case 6:
			return 2;
			break;
		case 7:
			return 3;
			break;
		case 8:
			return 4;
			break;
		}
	}
	else {
		return 4 + getCardsPerCoin(coins - 8);
	}
};


string Stink::getName() {
    return "stink";
};

void Stink::print(ostream& output) { output << 's'; }