#pragma once
#include "Card.h"
class Green : public Card {
public :
	int getCardsPerCoin(int coins);
	string getName();
	void print(ostream& out);
};

int Green::getCardsPerCoin(int coins) {
	if (coins < 3) {
		return 0;
	}
	else if (coins >= 3 && coins <= 7) {
		switch (coins) {
		case 3:
		case 4:
			return 1;
			break;
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
}

string Green::getName() {
    return "green";

};

void Green::print(ostream& output) { output << 'g'; }