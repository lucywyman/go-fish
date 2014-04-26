/*****************************
  **Filename: main.cpp
  **Author: Lucy Wyman
  **Date: April 25, 2014
  **Description: Main function for go Fish game
  ****************************/

#include "goFish.hpp"

using namespace std;

int main(){
	Game goFish = Game();
	Deck ocean = Deck();
	ocean.cards.resize(52);
	ocean.initializeDeck(&ocean);
	ocean.shuffle(&ocean);
	int a = getPlayers();   
	goFish.p.resize(a);
	for (int i = 0; i<a; i++)
		goFish.p.at(i).number = i+1;
	int players = goFish.getP();
	goFish.setP(a);
	goFish.deal(&goFish.p, &ocean);
	goFish.playGame(&goFish, &goFish.p, &ocean);
	return 0;
}

