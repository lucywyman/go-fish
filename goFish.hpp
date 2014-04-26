/******************************
  **Filename: goFish.hpp
  **Author: Lucy Wyman
  **Date: April 25, 2014
  **Description: Interface file for Go fish program
*******************************/

#include<string>
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<vector>
#include<time.h>
#include<stdlib.h>

using namespace std;

struct Card{
	int number;
	string suit;
};

class Deck {
	public:
		Deck();
		~Deck();
		void initializeDeck(Deck *ocean);
		void shuffle(Deck *ocean);
		Card getTopCard(vector<Card>*);
		vector<Card> cards;
		int cards_in_play;
		vector<Card> discard;
};

class Player{
	public:
		Player();
		~Player();
		vector<Card> hand;
		Card goFish();
		Card discard();
		Card getCard(Deck);
		int number;
};

class Game{
	public:
	    Game();
		~Game();	
		vector <Player> p;
		int ask(Player *, Player *, int);
		void playGame(Game *, vector<Player>*, Deck *);
		void deal(vector<Player>*, Deck*);
		char win;
		int getP();
		void setP(int);
	private:
		int players;
};

int errorCheck(int);

int getPlayers();

void printHand(Player);

int check1(int, int, int);

int check2(int);

void checkForSet(Player *, Deck *);

void checkForWin(Player *);

