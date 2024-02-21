//WAFFO TONY ADAMS
//300310088

// Game.cpp : Contain the main file for executing the game

using namespace std;


#include <iostream>
#include "Card.h"
#include "Chain.h"
#include "Coins.h"
#include "Deck.h"
#include "DiscardPile.h"
#include "Hand.h"
#include "Player.h"
#include "Table.h"
#include "TradeArea.h"
#include "Black.h"
#include "Blue.h"
#include "Chili.h"
#include "Garden.h"
#include "Green.h"
#include "Red.h"
#include "Soy.h"
#include "Stink.h"
#include "CardFactoryAndDeck.h"


Table *table;
char answer;
CardFactory* cardFactory;


int player = false;
Card* topCard;
Card* pickedCard;
vector<Card*> pickedCards;
 

void freshStart();
void saveProgress();
void continueGame();
void accomplishMove();
void  playGame();

int main()
{
    cardFactory = new CardFactory();

    // ask user if wants to resume a game or start a new one

    cout << "Start a new game (n) or continue a paused game (c) : ";
    cin >> answer;
    while (answer != 'n' && answer != 'c') {
        cout << "Invalid answer, please try again : new game (n), continue game (c) : ";
        cin >> answer;
    }

    if (answer == 'c') {
        cout << "---------- Resuming paused game ----------" << endl;
        continueGame();
    }
    else {
        cout << "---------- Starting a new game ----------" << endl;
        freshStart();
    }


};

void freshStart() {

    string name1, name2;
    cout << "Player1 one can enter his name ";
    cin >> name1;
    cout << "Player2 one can enter his name ";
    cin >> name2;
    table = new Table(name1, name2);
    
    playGame();

}

void continueGame() {
    ifstream input("data.txt");
    if (input.is_open()) {
        table = new Table(input, cardFactory);
        input.close();
    }
    else {
        cout << "Error while resuming the game. it new session will begin instead" << endl;
        freshStart();
    }

    playGame();
}

void saveProgress() {
    ofstream output("data.txt");
    if (output.is_open()) {
        output << *table;
        output.close();
    }
}


//IMPLEMENTS PSEUDO CODE
void accomplishMove() {
    cout << "Pause game (p) or continue (c) : ";
    cin >> answer;
    while (answer != 'p' && answer != 'c') {
        cout << "Invalid, Pause game (p) or continue (c) ";
        cin >> answer;
    }

    if (answer == 'p') { // save the game and exit
        saveProgress();
        exit(0);
    }

    table->display(); // display the whole table

    cout << "************" << table->players[player]->name << " can play now ************" << endl;


    topCard = table->deck->draw(); //player draws top card from Deck
    cout << "The picked card is " << topCard->getName() << endl;;

    if (!table->tradeArea->cards.empty()) { // If tradeArea is not empty

        cout << "Add cards to chains (c) or discard them (d) : ";
        cin >> answer;

        while (answer != 'c' && answer != 'd') {
            cout << "Invalid!! Add cards to chains (c) or discard them (d) : ";
            cin >> answer;
        }

        if (answer == 'c') {
            //Add bean cards from the TradeArea to chains
            cout << "Placing tradearea cards in " << table->players[player]->getName() << "'s chains ..." << endl;
            for (Card* card : table->tradeArea->cards) {
                // place into discard pile if there is no match found in the chain
                if (!table->players[player]->addCard(card)) { 

                    //due to error while using the += operator, i added it in the brute way
                    table->discardPile->cards.push_back(card);
                }

            }
            cout << "------------------------------------------------------" << endl;
            table->players[player]->display();
            cout << "------------------------------------------------------" << endl;
        }
        else { // place trade area cards into discard pile if it the option (d) was choosen
            cout << "Placing trade area cards into discard cards" << endl;
            for (Card* card : table->tradeArea->cards) {
                table->discardPile->cards.push_back(card);
            }
        }
    }

    cout << table->players[player]->name << " plays topmost card from hand" << endl;
    // Play topmost card from Hand
    //If chain is ended, cards for chain are removed and player receives coin(s).
    table->players[player]->play();  

    cout << "Show " << table->players[player]->name << " full hand ? yes (y) or no (n) : ";
    cin >> answer;

    while (answer != 'y' && answer != 'n') {
        cout << "Invalid answer, please try again : yes (y) or no (n) ";
        cin >> answer;
    }


    /*
    Players's decison to show the player's full hand and to selects an arbitrary card
    he can also Discard the arbitrary card from the player's hand and place it on the discard pile.*/
    if (answer == 'y') { 
        cout << table->players[player]->name << " ";
        table->players[player]->printHand(cout, true); ////Show the player's full hand 
        pickedCard = table->players[player]->hand->pickACard(cardFactory); //player selects an arbitrary card
        /*int num;
        cout << "Enter a number between 1 and "<< table->players[player]->hand->size()<<" ";
        cin >> answer;
        pickedCard = table->players[player]->hand[num-1];*/
        table->discardPile->cards.push_back(pickedCard); // place it on the discard pile.
    }

    //Draw three cards from the deck and place cards in the trade area
    cout << "Drawing 3 cards from the deck and add matching cards..." << endl;
    for (int i = 0; i < 3; i++) { 
        table->tradeArea->cards.push_back(table->deck->draw());
    }

    //while top card of discard pile matches an existing card in the trade area
    while (table->tradeArea->legal(table->discardPile->top())) { 
        pickedCard = table->discardPile->pickUp();
        table->tradeArea->cards.push_back(pickedCard);
    }

    cout << "Trade Area : ";
    table->tradeArea->display();
    for (Card* card : table->tradeArea->cards) {
        cout << "Do you want to remove " << card->getName() << ": yes (y) or anything else for no : ";
        cin >> answer;
        if (answer == 'y') {
            if (table->players[player]->addCard(card)) {
                pickedCards.push_back(card);
            }
            else {
                cout << "Cannot add " << card->getName() << " to " << table->players[player]->name << " chains " << endl;
            }
        }
    }

    for (Card* card : pickedCards) { // remove all the cards chosen on the previous step from the trade area
        table->tradeArea->remove(card);
    }

    cout << "Buy a 3th chain? yes (y) or anything else for no : " << endl;
    cin >> answer;

    if (answer == 'y') {
        try {
            table->players[player]->buyThirdChain();
        }
        catch (exception& ex) {
            cout << "Not Engouh coins" << endl;
        }
    }

}



void playGame() { // IMPLEMENTATION DU PSEUDO CODE
    
    for (int i = 0; i < 5; i++) {
        table->players[0]->hand->push(table->deck->pick());
        table->players[1]->hand->push(table->deck->pick());
    }

    while (!table->deck->empty()) { // While there are still cards on the Deck

        if (table->players[player]->getNumOfCards() > 0) {
            accomplishMove();
        }

        cout << "Drawing 2 cards from the deck to " << table->players[player]->name << " cards" << endl;
        table->players[player]->hand->push(table->deck->pick());
        table->players[player]->hand->push(table->deck->pick());

        player = !player; //switch player



    }

}

