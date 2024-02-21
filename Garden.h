#pragma once
#include "Card.h"
class Garden : public Card
{
public:
	int getCardsPerCoin(int coins);
	string getName();
	void print(ostream& out);

};

int Garden::getCardsPerCoin(int coins) {
	if (coins <= 2) {
		return 0;
	}
	else if (coins > 2 && coins <= 3) {
		switch (coins) {
		case 2:
			return 2;
			break;
		case 3:
			return 3;
			break;
		}
	}
	else {
		return 3 + getCardsPerCoin(coins - 3);
	}
};

string Garden::getName() {
    return "Garden";

}

void Garden::print(ostream& output) { output << 'G'; }