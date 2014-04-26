/**************************
  **Filename: goFish.cpp
  **Author: Lucy Wyman
  **Date: April 25, 2014
  **Description: Function definitions for go Fish
  *************************/

#include "goFish.hpp"

using namespace std;

/*******************
 **Function: Game constructor
 **Description: Initialize instance of Game
 ******************/
Game::Game(){}

/*******************
 **Function: Game destructor
 **Description: Destructor for game
 ******************/
Game::~Game(){}

Deck::Deck(){
}

Deck::~Deck(){
}

Player::Player(){}

Player::~Player(){}

int errorCheck(int a){
	int valid = 1;
	if(cin.fail()){
		cin.clear();
		cin.ignore(1000, '\n');
		valid = 0;
	}
	return valid;
}
/***********************
 **Function: printHand
 **Description: Print the hand of given player
 **Parameters: Player
 **********************/ 
void printHand(Player p){
	cout<<endl;
	cout<<"\033[1;34mPlayer "<<p.number<<", here's your hand:\33[0m"<<endl;
	for(int i = 0; i<p.hand.size(); i++)
		cout<<"\033[1;35m"<<p.hand.at(i).number<<" of "<<p.hand.at(i).suit<<"\033[0m"<<endl;
	cout<<endl;
}

int getPlayers(){
	int players, valid = 0;
	cout<<"How many people will be playing this round of Go Fish? ";
	while (valid == 0){
		cin>>players;
		valid = errorCheck(players);
		if (valid == 0 || players<2 || players>6){
			cout<<"Sorry! You did not enter a number between 2 and 6.  Please try again. ";
			valid = 0;
		}
	}
	return players;
}

int Game::getP(){
	return this->players;
}

void Game::setP(int players){
	this->players = players;
}

void Deck::initializeDeck (Deck *ocean){
	ocean->cards_in_play = 52;
	string suitstring;
	int i = 0;
	for (int suit = 1; suit<=4; suit++){
		if (suit == 1)
			suitstring = "hearts";
		else if (suit == 2)
			suitstring = "spades";
		else if (suit == 3)
			suitstring = "diamonds";
		else 
			suitstring = "clubs";
		for (int card = 1; card<=13; card++){
			ocean->cards.at(i).suit = suitstring;
			ocean->cards.at(i).number = card;
			i++;
		}
	}
}

void Deck::shuffle(Deck *ocean){
	int i, j, a;
	Card temp;
	srand(time(NULL));
	a = ocean->cards_in_play;
	for (int b = 0; b<4; b++){
		for (i = 0; i<a; i++){
			j = rand()% a;
			temp = ocean->cards.at(i);
			ocean->cards.at(i) = ocean->cards.at(j);
			ocean->cards.at(j) = temp;
		}
	}
}

Card Deck::getTopCard(vector<Card> *cards){
	Card a = cards->at(0);
	cards->erase(cards->begin());
	if (cards->size() == 0){
		cout<<"You're out of cards!  Game over!"<<endl;
		exit(1);
	}
	return a;
}

void Game::deal(vector<Player> *p, Deck *ocean){
	Card a;
	for(int i = 0; i<p->size(); i++){
		for(int j = 0; j<7; j++){
			a = ocean->getTopCard(&ocean->cards);
			p->at(i).hand.push_back(a);
		}
	}
}

int check1(int valid, int i, int players){
	int pBeingAsked;
	while(valid == 0){
		cin>>pBeingAsked;
		valid = errorCheck(pBeingAsked);
		if (pBeingAsked<=0 || pBeingAsked>players || pBeingAsked == i+1){
			valid = 0;
			cout<<"\033[1;31mYou didn't enter a valid player!  Please enter a number between 1 and the number of players playing. \033[0m"<<endl;
		}
	}
	return pBeingAsked;
}

int check2(int valid){
	int cardAskedFor;
	while(valid == 0){
		cin>>cardAskedFor;
		valid = errorCheck(cardAskedFor);
		if (cardAskedFor<1 || cardAskedFor>13){
			valid = 0;
			cout<<"You didn't enter a valid card number!  Please enter a number between 1 and 13. "<<endl;
		}
	}
	return cardAskedFor;
}

void Game::playGame(Game *goFish, vector<Player> *p, Deck *ocean){
	int pBeingAsked, cardAskedFor, cardsBack;
	while (1){
		int i = 0;	   
		for(i = 0; i<goFish->players; i++){
			printHand(p->at(i));
			cout<<"Player "<<i+1<<", which player would you like to ask for their cards?  ";
			pBeingAsked = check1(0, i, goFish->players);
			cout<<"Player "<<i+1<<", what number do you want to ask for?  ";
			cardAskedFor = check2(0);
			cardsBack = ask(&p->at(i), &p->at(pBeingAsked-1), cardAskedFor);
			if(cardsBack == 0)
				p->at(i).hand.push_back(ocean->getTopCard(&ocean->cards));
			checkForSet(&p->at(i), ocean);
			checkForWin(&p->at(i));
		}
	}	
}

void checkForSet(Player *p, Deck *ocean){
	int count = 0;
	for (int j = 0; j<=13; j++){
		count = 0;
		for(int i = 0; i<p->hand.size(); i++){
			if (p->hand.at(i).number == j){
				cout<<"1";
				count++;
			}
			if (count == 4){
				for (int k = 0; k<p->hand.size(); k++){
					cout<<"K"<<k;
					if (p->hand.at(k).number == j){
						cout<<"2";
						ocean->discard.push_back(p->hand.at(k));
						cout<<"3";
						p->hand.erase(p->hand.begin()+k);
						cout<<"4";
						k--;
						i--;
					}
				}
				cout<<"You got a set!  Congratulations!"<<endl;
			}
		}
	}
}

int Game::ask(Player *asking, Player *beingAsked, int cardAskedFor){
	int num = 0;
	//cout<<"Beginning of funct ";
	//printHand(*beingAsked);
	//cout<<endl;;
	for (int i = 0; i<beingAsked->hand.size(); i++){
		cout<<"I"<<i;
		if (beingAsked->hand.at(i).number == cardAskedFor){
			cout<<"2";
			asking->hand.push_back(beingAsked->hand.at(i));
			cout<<"3";
			beingAsked->hand.erase(beingAsked->hand.begin()+i);
			i--;
			num ++;
		}
	}	
	//cout<<"End of funct";
	//printHand(*beingAsked);
	//cout<<endl;
	cout<<"Player "<<beingAsked->number<<" had "<<num<<" "<<cardAskedFor<<"'s."<<endl<<endl;
	return num;
}

void checkForWin(Player *p){
	if (p->hand.size() == 0){
		cout<<"Player "<<p->number<<" wins!!  Congratulations!"<<endl;
		exit(1);
	}
}

