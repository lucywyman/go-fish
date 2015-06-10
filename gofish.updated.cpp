/*
GoFish

To Do:
-> Integrate Stack into Code
-> Add good commenting
-> Continue debugging

References:
http://en.wikipedia.org/wiki/Go_Fish
Lucy W. - Oregon State University Open Source Lab (Git fork)
http://boardgames.about.com/od/cardgames/a/go_fish.htm
http://rosettacode.org/wiki/Go_Fish/C
http://www.cplusplus.com/forum/beginner/98524/
*/

#include<string>
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<vector>
#include<time.h>
#include<stdlib.h>

using namespace std;

//***************************************
// struct Card
// Structure for each card
//***************************************
struct Card
{
	int number;
	string suit;
};

//***************************************
// class Deck
// Class for the deck of cards
// Contains constructor, destructor, deck
// initialization and shuffle functions, 
// as well as cards in play and discarded.
//***************************************
class Deck 
{
public:
	Deck()	// Constructor
		{ /* This is the Deck Constructor*/ }
	~Deck()	// Destructor
		{ /* This is the Deck Destructor */ }

	void initializeDeck(Deck *pool);
	void shuffle(Deck *pool);
	Card getTopCard(vector<Card>*);
	vector<Card> cards;
	int cards_in_play;
	vector<Card> discard;
};


//***************************************
// class Player
// Class for the deck of cards
// Contains constructor, destructor, deck
// initialization and shuffle functions, 
// as well as cards in play and discarded.
//***************************************
class Player
{
public:
	Player()	// Constructor
		{ /* This is the Player constructor*/ }
	~Player()	// Destructor
		{ /* This si the Player destructor*/ }
	vector<Card> hand;
	Card goFish();
	Card discard();
	Card getCard(Deck);
	int number;
};

class Game
{
public:
	Game()	// Constructor
		{ /* This is the Game constructor */ }
	~Game()	// Destructor
		{ /* This sis the Game destructor */ }
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

// Function prototypes
int errorCheck(int);
int getPlayers();
void printHand(Player);
int check1(int, int, int);
int check2(int);
void checkForSet(Player *, Deck *);
void checkForWin(Player *);

// Main Program
int main()
{
	// Menu Start
	cout << "\n        GO FISH!        \n\n";
	Game goFish = Game();
	Deck pool = Deck();
	pool.cards.resize(52);
	pool.initializeDeck(&pool);
	pool.shuffle(&pool);
	int a = getPlayers();
	goFish.p.resize(a);
	for (int i = 0; i<a; i++)
		goFish.p.at(i).number = i + 1;
	int players = goFish.getP();
	goFish.setP(a);
	goFish.deal(&goFish.p, &pool);
	goFish.playGame(&goFish, &goFish.p, &pool);
	return 0;
}

int errorCheck(int a)
{
	int valid = 1;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		valid = 0;
	}
	return valid;
}

// ***********************
// printHand
// Print the hand of given player
// @ Player passed with p
// **********************
void printHand(Player p)
{
	system("cls");		// Clear the screen so the next player doesn't see the previous players cards
	cout << "\nPlayer " << p.number << "'s turn to take the console. ";
	system("pause");	// For next players go ahead
	cout << endl;
	cout << "** Player " << p.number << "'s Hand **" << endl;
	for (int i = 0 ; i < p.hand.size() ; i++)
		cout << " * " << p.hand.at(i).number << " of " << p.hand.at(i).suit << " " << endl;
	cout << endl;
}

int getPlayers()
{
	int players, valid = 0;
	cout << "How many players will play Go Fish? ";
	while (valid == 0)
	{
		cin >> players;
		valid = errorCheck(players);
		if (valid == 0 || players < 2 || players>6)
		{
			cout << "ERROR: Invalid number.  Enter a number between 2 and 6. ";
			valid = 0;
		}
	}
	return players;
}

int Game::getP()
{
	return this->players;
}

void Game::setP(int players)
{
	this->players = players;
}

void Deck::initializeDeck(Deck *pool)
{
	pool->cards_in_play = 52;
	string suitstring;
	int i = 0;
	for (int suit = 1; suit <= 4; suit++)
	{
		if (suit == 1)
			suitstring = "hearts";
		else if (suit == 2)
			suitstring = "spades";
		else if (suit == 3)
			suitstring = "diamonds";
		else
			suitstring = "clubs";
		for (int card = 1; card <= 13; card++)
		{
			pool->cards.at(i).suit = suitstring;
			pool->cards.at(i).number = card;
			i++;
		}
	}
}

void Deck::shuffle(Deck *pool)
{
	int i, j, a;
	Card temp;
	srand(time(NULL));
	a = pool->cards_in_play;
	for (int b = 0 ; b < 4 ; b++)
	{
		for (i = 0; i < a ; i++)
		{
			j = rand() % a;
			temp = pool->cards.at(i);
			pool->cards.at(i) = pool->cards.at(j);
			pool->cards.at(j) = temp;
		}
	}
}

Card Deck::getTopCard(vector<Card> *cards)
{
	Card a = cards->at(0);
	cards->erase(cards->begin());
	if (cards->size() == 0)
	{
		cout << "You're out of cards!  Game over!" << endl;
		exit(1);
	}
	return a;
}

void Game::deal(vector<Player> *p, Deck *pool)
{
	Card a;
	for (int i = 0 ; i < p->size() ; i++)
	{
		for (int j = 0 ; j < 7 ; j++)
		{
			a = pool->getTopCard(&pool->cards);
			p->at(i).hand.push_back(a);
		}
	}
}

int check1(int valid, int i, int players)
{
	int pBeingAsked;
	while (valid == 0)
	{
		cin >> pBeingAsked;
		valid = errorCheck(pBeingAsked);
		if (pBeingAsked <= 0 || pBeingAsked > players || pBeingAsked == i + 1)
		{
			valid = 0;
			cout << "ERROR: Invalid player! \nEnter another player number, 1 - total # players, not including yourself. " << endl;
		}
	}
	return pBeingAsked;
}

int check2(int valid)
{
	int cardAskedFor;
	while (valid == 0)
	{
		cin >> cardAskedFor;
		valid = errorCheck(cardAskedFor);
		if (cardAskedFor < 1 || cardAskedFor > 13)
		{
			valid = 0;
			cout << "ERROR: Ivalied card number!  Enter a number between 1 and 13. " << endl;
		}
	}
	return cardAskedFor;
}

void Game::playGame(Game *goFish, vector<Player> *p, Deck *pool)
{
	int pBeingAsked, cardAskedFor, cardsBack;
	while (1)
	{
		int i = 0;
		for (i = 0 ; i < goFish->players ; i++)
		{
			printHand(p->at(i));
			cout << "Player " << i + 1 << ", which player do you want to ask for cards?  ";
			pBeingAsked = check1(0, i, goFish->players);
			cout << "Player " << i + 1 << ", what number do you want to ask for?  ";
			cardAskedFor = check2(0);
			cardsBack = ask(&p->at(i), &p->at(pBeingAsked - 1), cardAskedFor);
			if (cardsBack == 0)
			{
				cout << " * Gone Fishing! A card is drawn from the pool to your hand \n";
				p->at(i).hand.push_back(pool->getTopCard(&pool->cards));
			}
			checkForSet(&p->at(i), pool);
			checkForWin(&p->at(i));
			cout << endl;
			system("pause");
		}
	}
}

void checkForSet(Player *p, Deck *pool)
{
	int count = 0;
	for (int j = 0 ; j <= 13 ; j++)
	{
		count = 0;
		for (int i = 0 ; i < p->hand.size() ; i++)
		{
			if (p->hand.at(i).number == j)
			{
				count++;
			}
			if (count == 4)
			{
				for (int k = 0 ; k < p->hand.size() ; k++)
				{
					if (p->hand.at(k).number == j)
					{
						pool->discard.push_back(p->hand.at(k));
						p->hand.erase(p->hand.begin() + k);
						k--;
						i--;
					}
				}
				cout << "You got a set!  Nice!" << endl;
			}
		}
	}
}

int Game::ask(Player *asking, Player *beingAsked, int cardAskedFor)
{
	int num = 0;
	for (int i = 0 ; i < beingAsked->hand.size() ; i++)
	{
		if (beingAsked->hand.at(i).number == cardAskedFor)
		{
			asking->hand.push_back(beingAsked->hand.at(i));
			beingAsked->hand.erase(beingAsked->hand.begin() + i);
			i--;
			num++;
		}
	}
	cout << "\n** Results **";
	cout << "\n * Player " << beingAsked->number << " had " << num << " " << cardAskedFor << "'s." << endl;
	return num;
}

void checkForWin(Player *p)
{
	if (p->hand.size() == 0)
	{
		cout << "Player " << p->number << " wins!" << endl;
		exit(1);
	}
}
