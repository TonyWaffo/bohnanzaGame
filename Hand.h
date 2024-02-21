// some added methods might have been added, but hasn't been used in te program
#pragma once
#include "Card.h"
#include "CardFactoryAndDeck.h"
#include<queue>
#include<list>

class Hand: public queue<Card*>{
public :
	Hand& operator+=(Card*);
	Card* play();
	Card* top();
	Card* operator[](int);
	string printCards();
	friend ostream& operator << (ostream&, Hand);
	Hand(istream&,const CardFactory*);
	Hand() {};
	void display();
	Card* pickACard(CardFactory * cardFactory);
	void remove(int);
};

Hand& Hand :: operator+=(Card* card) {
	this->push(card);
	return *this;
};

Card* Hand :: play() {
	if (this->empty()) {
		cout << "Hand is empty" << endl;;
		return nullptr;
	}
	else {
		/*Card* firstCard = this->front();
		this->erase(this->begin());
		return firstCard;
		*/
		Card* cardToPlay = this->front();
		this->pop();
		return cardToPlay;
	}
};

Card* Hand :: top() {
	if (this->empty()) {
		cout << "Hand is empty" << endl;
		return nullptr;
	}
	else {
		return this->front();
	}
};

Card* Hand :: operator[](int index) {
	/*if (this->size() == 0) {
		cout << "Hand is empty" << endl;
		return nullptr;
	}
	Card* card = this->at(index);
	this->erase(begin() + index);
	return card;*/


	// Since queue does not provide random access, we need to iterate through
	// the elements to get the one at the specified index
	if (index >= 0 && index < this->size()) {
		if (index >= 0 && index < this->size()) {
			queue<Card*> tempQueue;

			// Pop and enqueue elements until the desired position
			for (int i = 0; i < index; ++i) {
				tempQueue.push(this->front());
				this->pop();
			}

			// Get the element at the desired position
			Card* removedCard = this->front();

			// Pop the element from the original queue
			this->pop();

			// Enqueue the remaining elements back to the original queue
			while (!tempQueue.empty()) {
				this->push(tempQueue.front());
				tempQueue.pop();
			}

			return removedCard;
		}
		else {
			cout << "Invalid index" << endl;
			return nullptr;
		}
	}
};

string Hand::printCards() {
	/*string result = " ";
	for (Card* card : *this) {
		result += card->getName();
	}
	return result;
	*/
	string cardToPrint = " ";
	queue<Card*> tempQueue = *this;
	while (!tempQueue.empty()) {
		cardToPrint += tempQueue.front()->getName();
		tempQueue.pop();
	}
	return cardToPrint;
};

ostream& operator << (ostream& output, Hand hand) {
	/*for (Card* card : hand) {
		card->print(output);
	}
	return output;
	*/
	queue<Card*> tempQueue = hand;
	while (!tempQueue.empty()) {
		tempQueue.front()->print(output);
		tempQueue.pop();
	}
	return output;
};

Hand :: Hand(istream& input,const CardFactory* cardFactory) {
	char line[1026];
	char card;
	int index = 0;
	input.getline(line, 1026);
	card = line[index];

	while (card != NULL) {
		this->push(cardFactory->getCard(card));
		card = line[++index];
	}
};

void Hand::display() {
	cout << "Hand : ";
	/*for (Card* card : *this) {
		cout << card->getName() << " ";
	}
	*/
	queue<Card*> tempQueue = *this;
	while (!tempQueue.empty()) {
		cout << tempQueue.front()->getName() << " ";
		tempQueue.pop();
	}
	cout << endl;
}

Card* Hand::pickACard(CardFactory * cardFactory) {
	/*string answer;
	bool matched = false;
	Card* result = nullptr;
	int index;

	cout << "Choose a card between: ";
	for (Card* card : *this) {
		cout << card->getName() << " , ";
	}
	cout << " : ";
	cin >> answer;

	do {
		index = 0;
		for (Card* card : *this) {
			index++;
			if (card->getName() == answer) {
				result = cardFactory->getCard(card->getName().at(0));
				remove(index);
				matched = true;
				break;
			}
		}

		if (!matched) {
			cout << "The picked card is not in hand try another card : ";
			cin >> answer;
		}

	} while (!matched);

	return result;
	*/
	string answer;
	bool matched = false;
	Card* result = nullptr;
	queue<Card*> tempQueue = *this;

	cout << "Choose a card between: ";
	while (!tempQueue.empty()) {
		cout << tempQueue.front()->getName() << " , ";
		tempQueue.pop();
	}
	cout << " : ";
	cin >> answer;

	do {
		queue<Card*> tempQueueCopy = *this;
		while (!tempQueueCopy.empty()) {
			if (tempQueueCopy.front()->getName() == answer) {
				result = cardFactory->getCard(tempQueueCopy.front()->getName().at(0));
				tempQueueCopy.pop();
				matched = true;
				break;
			}
			tempQueueCopy.pop();
		}

		if (!matched) {
			cout << "The picked card is not in hand, try another card : ";
			cin >> answer;
		}

	} while (!matched);

	return result;
}

/*
void Hand::remove(int index) {
	auto iterator = this->begin();
	advance(iterator, index-1);
	this->erase(iterator);
}*/
