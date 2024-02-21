#pragma once
#include "Card.h"
class Chili : public Card
{
public:


	int getCardsPerCoin(int coins);
	string getName();
	void print(ostream& out);

};



int Chili::getCardsPerCoin(int coins) {
	if (coins < 3) {
		return 0;
	}
	else if (coins >= 3 && coins <= 9) {
		switch (coins) {
		case 3:
		case 4:
		case 5:
			return 1;
			break;
		case 6:
		case 7:
			return 2;
			break;
		case 8:
			return 3;
			break;
		case 9:
			return 4;
			break;
		}
	}
	else {
		return 4 + getCardsPerCoin(coins - 9);
	}
}

string Chili::getName() {
    return "Chili";
}

void Chili::print(ostream& output) { output << 'C'; }