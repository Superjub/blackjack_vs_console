//headers used

#include <iostream>
#include <algorithm>
#include <ctime>
#include <string>
#include <string.h>
#include <limits>
#include <windows.h>


using namespace std;


//multidimensional array used to hold the string value of the player's first 2 cards; this will later be used to check to see 
//if the player can split as well as to check if they have a blackjack
string playersRanks[7][2];

//variables ending in -2 are associated with the split mechanic.
string playersRanks2[7][2];


//multidimensional arrays for the player's card; theoretically it is possible for the player to draw 1 21 times so this is why
//the maximum number is 21.
string playersCards[7][21];
string playersCardsSplit[7][21];

//2D array for the dealer's cards
string dealersCards[21];

int numberOfGames;

//counters to keep track of how many cards have been drawn.
int cardCounter[7];
int cardCounter2[7];
int cardCounterSplit[7];
int cardCounterDealer;

//used so that the player can answer "y" for yes and "n" for no later.
char yesNo;

//decides who draws their cards first- it is set so Player One will draw their cards first.
bool playersDraw [7] = {true, false, false, false, false, false, false};
bool dealersDraw = false;

//string to store the names of the players that will be inputted later.
string playerName[7];

//turn number integer & number of players
int turnNumb = 0;
int numberOfPlayers;

bool correctValue = false;

//The scores of the player and the dealer; these will increase when cards are drawn.
int playerScore [7];
int playerScore2 [7];

int dealerScore = 0;

//Points are won by winning games. Alternatively they can be lost by losing games.
int playersPoints[7] = {100, 100, 100, 100, 100, 100, 100,};

char playerAction;

//bools to keep track whether each player has splir, surrendered etc.
bool split [7];
bool surrender[7];
bool surrender2[7];
bool doubleDown [7];
bool doubleDown2 [7];
bool bust [8];
bool bust2 [7];
bool blackjack[8];
bool blackjack2[8];

//The value of the second card, used for calculations related to splitting.
int secondCardsValue[7];
//Checks whether the player is on their second hand after splitting.
bool secondHandActive[7] = {false, false, false, false, false, false, false};

bool roundEnd = false;

// names of ranks.
string ranks[] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

// name of suites
string suits[] = {"Spades", "Clubs", "Diamonds", "Hearts"};

//used to keep track of the current ranks/suits/cards.
string currentRank;
string currentSuit;
string currentCard;


//A two-part function that is called from the DealCards() function. This function
//randomly chooses the rank and suit of the cards as well as handles aspects of
//the score and counter.

void print_card(int n)
{
	//calculating the current rank and suit. The modulus operator is used to generate one of the 13 ranks and
	//n is divided by 12 to work out the suit.

	currentRank = ranks[n % 13];
	currentSuit = suits[n / 13];

	//stores the current card.
	currentCard = currentRank + " of " + currentSuit;

	if (playersDraw[0] == true)
	{
		cout << playerName[0] << " drew a(n) " << currentRank << " of " << currentSuit << endl;
		//this is the part of the prgram where it stores the current rank to determine whether the
		//player had blackjack or can split later.
		if (turnNumb == 0)
		{
			if (cardCounter[0] == 0)
			{
				playersRanks[0][0] = currentRank;
			}
			else
			{
				playersRanks[0][1] = currentRank;
			}
		}
		//checks if the player has split and is on their second hand.
		if (secondHandActive[0] == true)
		{
			if (cardCounter2[0] == 0)
			{
				playersRanks2[0][0] = currentRank;
			}
			if (cardCounter2[0] == 1)
			{
				playersRanks2[0][1] = currentRank;
			}
		}
		if (secondHandActive[0] == true)
		{
		playersCardsSplit[0][cardCounter2[0]] = currentCard;
		cardCounter2[0] = cardCounter2[0] + 1;
		}

		else
		//if split is not active 1 is added to the card counter everytime
		//a card is drawn.
		{
		cardCounter[0] = cardCounter[0] + 1;
		playersCards[0][cardCounter[0]] = currentCard;

		}

	}

	//This is done for each of the players.
	else if (playersDraw[1] == true)
	{
		cout << playerName[1] << " drew a(n) " << currentRank << " of " << currentSuit << endl;
		if (turnNumb == 0)
		{
			if (cardCounter[1] == 0)
			{
				playersRanks[1][0] = currentRank;
			}
			else
			{
				playersRanks[1][1] = currentRank;
			}
		}
		if (secondHandActive[1] == true)
		{
			if (cardCounter2[1] == 0)
			{
				playersRanks2[1][0] = currentRank;
			}
			if (cardCounter2[1] == 1)
			{
				playersRanks2[1][1] = currentRank;
			}
		}
		if (secondHandActive[1] == true)
		{
			cardCounter2[1] = cardCounter2[1] + 1;
			playersCardsSplit[1][cardCounter2[1]] = currentCard;
		}

		else
		{
		cardCounter[1] = cardCounter[1] + 1;
		playersCards[1][cardCounter[1]] = currentCard;

		}
	}

	else if (playersDraw[2] == true)
	{
		cout << playerName[2] << " drew a(n) " << currentRank << " of " << currentSuit << endl;
		if (turnNumb == 0)
		{
			if (cardCounter[2] == 0)
			{
				playersRanks[2][0] = currentRank;
			}
			else
			{
				playersRanks[2][1] = currentRank;
			}
		}
		if (secondHandActive[2] == true)
		{
			if (cardCounter2[2] == 0)
			{
				playersRanks2[2][0] = currentRank;
			}
			if (cardCounter2[2] == 1)
			{
				playersRanks2[2][1] = currentRank;
			}
		}
		if (secondHandActive[2] == true)
		{
			cardCounter2[2] = cardCounter2[2] + 1;
			playersCardsSplit[2][cardCounter2[2]] = currentCard;
		}

		else
		{
		cardCounter[2] = cardCounter[2] + 1;
		playersCards[2][cardCounter[2]] = currentCard;

		}
	}

	else if (playersDraw[3] == true)
	{
		cout << playerName[3] << " drew a(n) " << currentRank << " of " << currentSuit << endl;
		if (turnNumb == 0)
		{
			if (cardCounter[3] == 0)
			{
				playersRanks[3][0] = currentRank;
			}
			else
			{
				playersRanks[3][1] = currentRank;
			}
		}
		if (secondHandActive[3] == true)
		{
			if (cardCounter2[3] == 0)
			{
				playersRanks2[3][0] = currentRank;
			}
			if (cardCounter2[3] == 1)
			{
				playersRanks2[3][1] = currentRank;
			}
		}
		if (secondHandActive[3] == true)
		{
			cardCounter2[3] = cardCounter2[3] + 1;
			playersCardsSplit[3][cardCounter2[3]] = currentCard;
		}

		else
		{
		cardCounter[3] = cardCounter[3] + 1;
		playersCards[3][cardCounter[3]] = currentCard;

		}
	}

	else if (playersDraw[4] == true)
	{
		cout << playerName[4] << " drew a(n) " << currentRank << " of " << currentSuit << endl;
		if (turnNumb == 0)
		{
			if (cardCounter[4] == 0)
			{
				playersRanks[4][0] = currentRank;
			}
			else
			{
				playersRanks[4][1] = currentRank;
			}
		}
		if (secondHandActive[4] == true)
		{
			if (cardCounter2[4] == 0)
			{
				playersRanks2[4][0] = currentRank;
			}
			if (cardCounter2[4] == 1)
			{
				playersRanks2[4][1] = currentRank;
			}
		}
		if (secondHandActive[4] == true)
		{
			cardCounter2[4] = cardCounter2[4] + 1;
			playersCardsSplit[4][cardCounter2[4]] = currentCard;
		}

		else
		{
		cardCounter[4] = cardCounter[4] + 1;
		playersCards[4][cardCounter[4]] = currentCard;

		}
	}

	else if (playersDraw[5] == true)
	{
		cout << playerName[5] << " drew a(n) " << currentRank << " of " << currentSuit << endl;
		if (turnNumb == 0)
		{
			if (cardCounter[5] == 0)
			{
				playersRanks[5][0] = currentRank;
			}
			else
			{
				playersRanks[5][1] = currentRank;
			}
		}
		if (secondHandActive[5] == true)
		{
			if (cardCounter2[5] == 0)
			{
				playersRanks2[5][0] = currentRank;
			}
			if (cardCounter2[5] == 1)
			{
				playersRanks2[5][1] = currentRank;
			}
		}
		if (secondHandActive[5] == true)
		{
			cardCounter2[5] = cardCounter2[5] + 1;
			playersCardsSplit[5][cardCounter2[5]] = currentCard;
		}

		else
		{
		cardCounter[5] = cardCounter[5] + 1;
		playersCards[5][cardCounter[5]] = currentCard;

		}
	}

	else if (playersDraw[6] == true)
	{
		cout << playerName[6] << " drew a(n) " << currentRank << " of " << currentSuit << endl;
		if (turnNumb == 0)
		{
			if (cardCounter[6] == 0)
			{
				playersRanks[6][0] = currentRank;
			}
			else
			{
				playersRanks[6][1] = currentRank;
			}
		}
		if (secondHandActive[6] == true)
		{
			if (cardCounter2[6] == 0)
			{
				playersRanks2[6][0] = currentRank;
			}
			if (cardCounter2[6] == 1)
			{
				playersRanks2[6][1] = currentRank;
			}
		}
		if (secondHandActive[6] == true)
		{
			cardCounter2[6] = cardCounter2[6] + 1;
			playersCardsSplit[6][cardCounter2[6]] = currentCard;
		}

		else
		{
		cardCounter[6] = cardCounter[6] + 1;
		playersCards[6][cardCounter[6]] = currentCard;

		}
	}

	else if (dealersDraw == true)
	{
		if (cardCounterDealer == 0)
		{
			cout << "The dealer drew a(n) " << currentRank << " of " << suits[n / 13] << endl;
		    dealersCards[cardCounterDealer] = currentCard;
			cardCounterDealer = cardCounterDealer + 1;
		}
		else
		{
		    cout << "The dealer drew a card..." << endl;
		    dealersCards[cardCounterDealer] = currentCard;
			cardCounterDealer = cardCounterDealer + 1;
		}


	}
	//Checks the string value of the card, and then uses this to give a player/the dealer a score.
	if (currentRank == "Ace")
		{
			if (playersDraw[0] == true)
			{
				if (secondHandActive[0] == true)
				{
					if (playerScore2[0] >= 11)
				    {
					   playerScore2[0] = playerScore2[0] + 1;
				    }
				    else
				    {
					   playerScore2[0] = playerScore2[0] + 11;
				    }
				}

				else if (secondHandActive[0] == false)
				{
					if (playerScore[0] >= 11)
				    {
					   playerScore[0] = playerScore[0] + 1;
				    }
				    else
				    {
					   playerScore[0] = playerScore[0] + 11;
				    }
				}
			}

			else if (playersDraw[1] == true)
			{
				if (secondHandActive[1] == true)
				{
					if (playerScore2[1] >= 11)
				    {
					   playerScore2[1] = playerScore2[0] + 1;
				    }
				    else
				    {
					   playerScore2[1] = playerScore2[0] + 11;
				    }
				}
				else
				{
					if (playerScore[1] >= 11)
				    {
					   playerScore[1] = playerScore[1] + 1;
				    }
				    else
				    {
					   playerScore[1] = playerScore[1] + 1;
				    }
				}
				
			}

			else if (playersDraw[2] == true)
			{
				if (secondHandActive[2] == true)
				{
					if (playerScore2[2] >= 11)
				    {
					   playerScore2[2] = playerScore2[2] + 1;
				    }
				    else
				    {
					   playerScore2[2] = playerScore2[2] + 11;
				    }
				}
				else
				{
					if (playerScore[2] >= 11)
				    {
					   playerScore[2] = playerScore[2] + 1;
				    }
				    else
				    {
					   playerScore[2] = playerScore[2] + 11;
				    }
				}
			}

			else if (playersDraw[3] == true)
			{
				if (secondHandActive[3] == true)
				{
					if (playerScore2[3] >= 11)
				    {
					   playerScore2[3] = playerScore2[3] + 1;
				    }
				    else
				    {
					   playerScore2[3] = playerScore2[3] + 11;
				    }
				}
				else
				{
					if (playerScore[3] >= 11)
				    {
					   playerScore[3] = playerScore[3] + 1;
				    }
				    else
				    {
					   playerScore[3] = playerScore[3] + 11;
				    }
				}
			}

			else if (playersDraw[4] == true)
			{
				if (secondHandActive[4] == true)
				{
					if (playerScore2[4] >= 11)
				    {
					   playerScore2[4] = playerScore2[4] + 1;
				    }
				    else
				    {
					   playerScore2[4] = playerScore2[4] + 11;
				    }
				}
				else
				{
					if (playerScore[4] >= 11)
				    {
					   playerScore[4] = playerScore[4] + 1;
				    }
				    else
				    {
					   playerScore[4] = playerScore[4] + 11;
				    }
				}
			}

			else if (playersDraw[5] == true)
			{
				if (secondHandActive[5] == true)
				{
					if (playerScore2[5] >= 11)
				    {
					   playerScore2[5] = playerScore2[5] + 1;
				    }
				    else
				    {
					   playerScore2[5] = playerScore2[5] + 11;
				    }
				}
				else
				{
					if (playerScore[5] >= 11)
				    {
					   playerScore[5] = playerScore[5] + 1;
				    }
				    else
				    {
					   playerScore[5] = playerScore[5] + 11;
				    }
				}
			}

			else if (playersDraw[6] == true)
			{
				if (secondHandActive[6] == true)
				{
					if (playerScore2[6] >= 11)
				    {
					   playerScore2[6] = playerScore2[6] + 1;
				    }
				    else
				    {
					   playerScore2[6] = playerScore2[6] + 11;
				    }
				}
				else
				{
					if (playerScore[6] >= 11)
				    {
					   playerScore[6] = playerScore[6] + 1;
				    }
				    else
				    {
					   playerScore[6] = playerScore[6] + 11;
				    }
				}
			}

			else if (dealersDraw == true)
			{
				if (dealerScore >= 11)
				{
					dealerScore = dealerScore + 1;
				}
				else
				{
					dealerScore = dealerScore + 11;
				}
			}
		}
		//This is done for each of the ranks.
	if (currentRank == "Two")
	{
		if (playersDraw[0] == true)
		{
			if (secondHandActive[0] == true)
			 {
				playerScore2[0] = playerScore2[0] + 2;
			 }
		    else if (secondHandActive[0] == false)
			 {
				playerScore[0] = playerScore[0] + 2;
			 }
		}
		else if (playersDraw[1] == true)
		{
			if (secondHandActive[1] == true)
			 {
				playerScore2[1] = playerScore2[1] + 2;
			 }
		    else
			 {
				playerScore[1] = playerScore[1] + 2;
			 }
		}
		else if (playersDraw[2] == true)
		{
			if (secondHandActive[2] == true)
			 {
				playerScore2[2] = playerScore2[2] + 2;
			 }
		    else
			 {
				playerScore[2] = playerScore[2] + 2;
			 }
		}
		else if (playersDraw[3] == true)
		{
			if (secondHandActive[3] == true)
			 {
				playerScore2[3] = playerScore2[3] + 2;
			 }
		    else
			 {
				playerScore[3] = playerScore[3] + 2;
			 }
		}
		else if (playersDraw[4] == true)
		{
			if (secondHandActive[4] == true)
			 {
				playerScore2[4] = playerScore2[4] + 2;
			 }
		    else
			 {
				playerScore[4] = playerScore[4] + 2;
			 }
		}
		else if (playersDraw[5] == true)
		{
			if (secondHandActive[5] == true)
			 {
				playerScore2[5] = playerScore2[5] + 2;
			 }
		    else
			 {
				playerScore[5] = playerScore[5] + 2;
			 }
		}
		else if (playersDraw[6] == true)
		{
			if (secondHandActive[6] == true)
			 {
				playerScore2[6] = playerScore2[6] + 2;
			 }
		    else
			 {
				playerScore[6] = playerScore[6] + 2;
			 }
		}
		else if (dealersDraw == true)
		{
			dealerScore = dealerScore + 2;
		}
	}

	if (currentRank == "Three")
	{		
		if (playersDraw[0] == true)
		{
			if (secondHandActive[0] == true)
			 {
				playerScore2[0] = playerScore2[0] + 3;
			 }
		    else if (secondHandActive[0] == false)
			 {
				playerScore[0] = playerScore[0] + 3;
			 }
		}
		else if (playersDraw[1] == true)
		{
			if (secondHandActive[1] == true)
			 {
				playerScore2[1] = playerScore2[1] + 3;
			 }
		    else
			 {
				playerScore[1] = playerScore[1] + 3;
			 }
		}
		else if (playersDraw[2] == true)
		{
			if (secondHandActive[2] == true)
			 {
				playerScore2[2] = playerScore2[2] + 3;
			 }
		    else
			 {
				playerScore[2] = playerScore[2] + 3;
			 }
		}
		else if (playersDraw[3] == true)
		{
			if (secondHandActive[3] == true)
			 {
				playerScore2[3] = playerScore2[3] + 3;
			 }
		    else
			 {
				playerScore[3] = playerScore[3] + 3;
			 }
		}
		else if (playersDraw[4] == true)
		{
			if (secondHandActive[4] == true)
			 {
				playerScore2[4] = playerScore2[4] + 3;
			 }
		    else
			 {
				playerScore[4] = playerScore[4] + 3;
			 }
		}
		else if (playersDraw[5] == true)
		{
			if (secondHandActive[5] == true)
			 {
				playerScore2[5] = playerScore2[5] + 3;
			 }
		    else
			 {
				playerScore[5] = playerScore[5] + 3;
			 }
		}
		else if (playersDraw[6] == true)
		{
			if (secondHandActive[6] == true)
			 {
				playerScore2[6] = playerScore2[6] + 3;
			 }
		    else
			 {
				playerScore[6] = playerScore[6] + 3;
			 }
		}
		else if (dealersDraw == true)
		{
			dealerScore = dealerScore + 3;
		}
	}
	if (currentRank == "Four")
	{
		if (playersDraw[0] == true)
		{
			if (secondHandActive[0] == true)
			 {
				playerScore2[0] = playerScore2[0] + 4;
			 }
		    else if (secondHandActive[0] == false)
			 {
				playerScore[0] = playerScore[0] + 4;
			 }
		}
		else if (playersDraw[1] == true)
		{
			if (secondHandActive[1] == true)
			 {
				playerScore2[1] = playerScore2[1] + 4;
			 }
		    else
			 {
				playerScore[1] = playerScore[1] + 4;
			 }
		}
		else if (playersDraw[2] == true)
		{
			if (secondHandActive[2] == true)
			 {
				playerScore2[2] = playerScore2[2] + 4;
			 }
		    else
			 {
				playerScore[2] = playerScore[2] + 4;
			 }
		}
		else if (playersDraw[3] == true)
		{
			if (secondHandActive[3] == true)
			 {
				playerScore2[3] = playerScore2[3] + 4;
			 }
		    else
			 {
				playerScore[3] = playerScore[3] + 4;
			 }
		}
		else if (playersDraw[4] == true)
		{
			if (secondHandActive[4] == true)
			 {
				playerScore2[4] = playerScore2[4] + 4;
			 }
		    else
			 {
				playerScore[4] = playerScore[4] + 4;
			 }
		}
		else if (playersDraw[5] == true)
		{
			if (secondHandActive[5] == true)
			 {
				playerScore2[5] = playerScore2[5] + 4;
			 }
		    else
			 {
				playerScore[5] = playerScore[5] + 4;
			 }
		}
		else if (playersDraw[6] == true)
		{
			if (secondHandActive[6] == true)
			 {
				playerScore2[6] = playerScore2[6] + 4;
			 }
		    else
			 {
				playerScore[6] = playerScore[6] + 4;
			 }
		}
		else if (dealersDraw == true)
		{
			dealerScore = dealerScore + 4;
		}
	}
	if (currentRank == "Five")
	{
		if (playersDraw[0] == true)
		{
			if (secondHandActive[0] == true)
			 {
				playerScore2[0] = playerScore2[0] + 5;
			 }
		    else if (secondHandActive[0] == false)
			 {
				playerScore[0] = playerScore[0] + 5;
			 }
		}
		else if (playersDraw[1] == true)
		{
			if (secondHandActive[1] == true)
			 {
				playerScore2[1] = playerScore2[1] + 5;
			 }
		    else
			 {
				playerScore[1] = playerScore[1] + 5;
			 }
		}
		else if (playersDraw[2] == true)
		{
			if (secondHandActive[2] == true)
			 {
				playerScore2[2] = playerScore2[2] + 5;
			 }
		    else
			 {
				playerScore[2] = playerScore[2] + 5;
			 }
		}
		else if (playersDraw[3] == true)
		{
			if (secondHandActive[3] == true)
			 {
				playerScore2[3] = playerScore2[3] + 5;
			 }
		    else
			 {
				playerScore[3] = playerScore[3] + 5;
			 }
		}
		else if (playersDraw[4] == true)
		{
			if (secondHandActive[4] == true)
			 {
				playerScore2[4] = playerScore2[4] + 5;
			 }
		    else
			 {
				playerScore[4] = playerScore[4] + 5;
			 }
		}
		else if (playersDraw[5] == true)
		{
			if (secondHandActive[5] == true)
			 {
				playerScore2[5] = playerScore2[5] + 5;
			 }
		    else
			 {
				playerScore[5] = playerScore[5] + 5;
			 }
		}
		else if (playersDraw[6] == true)
		{
			if (secondHandActive[6] == true)
			 {
				playerScore2[6] = playerScore2[6] + 5;
			 }
		    else
			 {
				playerScore[6] = playerScore[6] + 5;
			 }
		}
		else if (dealersDraw == true)
		{
			dealerScore = dealerScore + 5;
		}
	}
	if (currentRank == "Six")
	{
		if (playersDraw[0] == true)
		{
			if (secondHandActive[0] == true)
			 {
				playerScore2[0] = playerScore2[0] + 6;
			 }
		    else if (secondHandActive[0] == false)
			 {
				playerScore[0] = playerScore[0] + 6;
			 }
		}
		else if (playersDraw[1] == true)
		{
			if (secondHandActive[1] == true)
			 {
				playerScore2[1] = playerScore2[1] + 6;
			 }
		    else
			 {
				playerScore[1] = playerScore[1] + 6;
			 }
		}
		else if (playersDraw[2] == true)
		{
			if (secondHandActive[2] == true)
			 {
				playerScore2[2] = playerScore2[2] + 6;
			 }
		    else
			 {
				playerScore[2] = playerScore[2] + 6;
			 }
		}
		else if (playersDraw[3] == true)
		{
			if (secondHandActive[3] == true)
			 {
				playerScore2[3] = playerScore2[3] + 6;
			 }
		    else
			 {
				playerScore[3] = playerScore[3] + 6;
			 }
		}
		else if (playersDraw[4] == true)
		{
			if (secondHandActive[4] == true)
			 {
				playerScore2[4] = playerScore2[4] + 6;
			 }
		    else
			 {
				playerScore[4] = playerScore[4] + 6;
			 }
		}
		else if (playersDraw[5] == true)
		{
			if (secondHandActive[5] == true)
			 {
				playerScore2[5] = playerScore2[5] + 6;
			 }
		    else
			 {
				playerScore[5] = playerScore[5] + 6;
			 }
		}
		else if (playersDraw[6] == true)
		{
			if (secondHandActive[6] == true)
			 {
				playerScore2[6] = playerScore2[6] + 6;
			 }
		    else
			 {
				playerScore[6] = playerScore[6] + 6;
			 }
		}
		else if (dealersDraw == true)
		{
			dealerScore = dealerScore + 6;
		}
	}
	if (currentRank == "Seven")
	{
		if (playersDraw[0] == true)
		{
			if (secondHandActive[0] == true)
			 {
				playerScore2[0] = playerScore2[0] + 7;
			 }
		    else if (secondHandActive[0] == false)
			 {
				playerScore[0] = playerScore[0] + 7;
			 }
		}
		else if (playersDraw[1] == true)
		{
			if (secondHandActive[1] == true)
			 {
				playerScore2[1] = playerScore2[1] + 7;
			 }
		    else
			 {
				playerScore[1] = playerScore[1] + 7;
			 }
		}
		else if (playersDraw[2] == true)
		{
			if (secondHandActive[2] == true)
			 {
				playerScore2[2] = playerScore2[2] + 7;
			 }
		    else
			 {
				playerScore[2] = playerScore[2] + 7;
			 }
		}
		else if (playersDraw[3] == true)
		{
			if (secondHandActive[3] == true)
			 {
				playerScore2[3] = playerScore2[3] + 7;
			 }
		    else
			 {
				playerScore[3] = playerScore[3] + 7;
			 }
		}
		else if (playersDraw[4] == true)
		{
			if (secondHandActive[4] == true)
			 {
				playerScore2[4] = playerScore2[4] + 7;
			 }
		    else
			 {
				playerScore[4] = playerScore[4] + 7;
			 }
		}
		else if (playersDraw[5] == true)
		{
			if (secondHandActive[5] == true)
			 {
				playerScore2[5] = playerScore2[5] + 7;
			 }
		    else
			 {
				playerScore[5] = playerScore[5] + 7;
			 }
		}
		else if (playersDraw[6] == true)
		{
			if (secondHandActive[6] == true)
			 {
				playerScore2[6] = playerScore2[6] + 7;
			 }
		    else
			 {
				playerScore[6] = playerScore[6] + 7;
			 }
		}
		else if (dealersDraw == true)
		{
			dealerScore = dealerScore + 7;
		}
	}
	if (currentRank == "Eight")
	{
		if (playersDraw[0] == true)
		{
			if (secondHandActive[0] == true)
			 {
				playerScore2[0] = playerScore2[0] + 8;
			 }
		    else if (secondHandActive[0] == false)
			 {
				playerScore[0] = playerScore[0] + 8;
			 }
		}
		else if (playersDraw[1] == true)
		{
			if (secondHandActive[1] == true)
			 {
				playerScore2[1] = playerScore2[1] + 8;
			 }
		    else
			 {
				playerScore[1] = playerScore[1] + 8;
			 }
		}
		else if (playersDraw[2] == true)
		{
			if (secondHandActive[2] == true)
			 {
				playerScore2[2] = playerScore2[2] + 8;
			 }
		    else
			 {
				playerScore[2] = playerScore[2] + 8;
			 }
		}
		else if (playersDraw[3] == true)
		{
			if (secondHandActive[3] == true)
			 {
				playerScore2[3] = playerScore2[3] + 8;
			 }
		    else
			 {
				playerScore[3] = playerScore[3] + 8;
			 }
		}
		else if (playersDraw[4] == true)
		{
			if (secondHandActive[4] == true)
			 {
				playerScore2[4] = playerScore2[4] + 8;
			 }
		    else
			 {
				playerScore[4] = playerScore[4] + 8;
			 }
		}
		else if (playersDraw[5] == true)
		{
			if (secondHandActive[5] == true)
			 {
				playerScore2[5] = playerScore2[5] + 8;
			 }
		    else
			 {
				playerScore[5] = playerScore[5] + 8;
			 }
		}
		else if (playersDraw[6] == true)
		{
			if (secondHandActive[6] == true)
			 {
				playerScore2[6] = playerScore2[6] + 8;
			 }
		    else
			 {
				playerScore[6] = playerScore[6] + 8;
			 }
		}
		else if (dealersDraw == true)
		{
			dealerScore = dealerScore + 8;
		}
	}
	if (currentRank == "Nine")
	{
		if (playersDraw[0] == true)
		{
			if (secondHandActive[0] == true)
			 {
				playerScore2[0] = playerScore2[0] + 9;
			 }
		    else if (secondHandActive[0] == false)
			 {
				playerScore[0] = playerScore[0] + 9;
			 }
		}
		else if (playersDraw[1] == true)
		{
			if (secondHandActive[1] == true)
			 {
				playerScore2[1] = playerScore2[1] + 9;
			 }
		    else
			 {
				playerScore[1] = playerScore[1] + 9;
			 }
		}
		else if (playersDraw[2] == true)
		{
			if (secondHandActive[2] == true)
			 {
				playerScore2[2] = playerScore2[2] + 9;
			 }
		    else
			 {
				playerScore[2] = playerScore[2] + 9;
			 }
		}
		else if (playersDraw[3] == true)
		{
			if (secondHandActive[3] == true)
			 {
				playerScore2[3] = playerScore2[3] + 9;
			 }
		    else
			 {
				playerScore[3] = playerScore[3] + 9;
			 }
		}
		else if (playersDraw[4] == true)
		{
			if (secondHandActive[4] == true)
			 {
				playerScore2[4] = playerScore2[4] + 9;
			 }
		    else
			 {
				playerScore[4] = playerScore[4] + 9;
			 }
		}
		else if (playersDraw[5] == true)
		{
			if (secondHandActive[5] == true)
			 {
				playerScore2[5] = playerScore2[5] + 9;
			 }
		    else
			 {
				playerScore[5] = playerScore[5] + 9;
			 }
		}
		else if (playersDraw[6] == true)
		{
			if (secondHandActive[6] == true)
			 {
				playerScore2[6] = playerScore2[6] + 9;
			 }
		    else
			 {
				playerScore[6] = playerScore[6] + 9;
			 }
		}
		else if (dealersDraw == true)
		{
			dealerScore = dealerScore + 9;
		}
	}
	//Ten and the picture cards are all under the same if statement due to awarding the same number of points.
	if (currentRank == "Ten" || currentRank == "Jack" || currentRank == "Queen" || currentRank == "King")
	{
		if (playersDraw[0] == true)
		{
			if (secondHandActive[0] == true)
			 {
				playerScore2[0] = playerScore2[0] + 10;
			 }
		    else if (secondHandActive[0] == false)
			 {
				playerScore[0] = playerScore[0] + 10;
			 }
		}
		else if (playersDraw[1] == true)
		{
			if (secondHandActive[1] == true)
			 {
				playerScore2[1] = playerScore2[1] + 10;
			 }
		    else
			 {
				playerScore[1] = playerScore[1] + 10;
			 }
		}
		else if (playersDraw[2] == true)
		{
			if (secondHandActive[2] == true)
			 {
				playerScore2[2] = playerScore2[2] + 10;
			 }
		    else
			 {
				playerScore[2] = playerScore[2] + 10;
			 }
		}
		else if (playersDraw[3] == true)
		{
			if (secondHandActive[3] == true)
			 {
				playerScore2[3] = playerScore2[3] + 10;
			 }
		    else
			 {
				playerScore[3] = playerScore[3] + 10;
			 }
		}
		else if (playersDraw[4] == true)
		{
			if (secondHandActive[4] == true)
			 {
				playerScore2[4] = playerScore2[4] + 10;
			 }
		    else
			 {
				playerScore[4] = playerScore[4] + 10;
			 }
		}
		else if (playersDraw[5] == true)
		{
			if (secondHandActive[5] == true)
			 {
				playerScore2[5] = playerScore2[5] + 10;
			 }
		    else
			 {
				playerScore[5] = playerScore[5] + 10;
			 }
		}
		else if (playersDraw[6] == true)
		{
			if (secondHandActive[6] == true)
			 {
				playerScore2[6] = playerScore2[6] + 10;
			 }
		    else
			 {
				playerScore[6] = playerScore[6] + 10;
			 }
		}
		else if (dealersDraw == true)
		{
			dealerScore = dealerScore + 10;
		}
	}
	//Checks whether player one can draw a card.
	if (playersDraw [0] == true)
		{
			//Used for when the dealer deals out the cars to all the players.
			if (turnNumb == 0)
			{
				if (cardCounter[0] <= 1)
				{
					return;
				}
				else
				{
					playersDraw[0] = false;

			        if (numberOfPlayers >= 2)
			        {
				         playersDraw[1] = true;
			        }
			        else
			        {
				         dealersDraw = true;
			        }

					return;
			      }     
			}

			else
			{
				return;
			}
		}

		if (playersDraw [1] == true)
		{
			if (turnNumb == 0)
			{
				if (cardCounter[1] <= 1)
				{
					return;
				}
				else
				{
					playersDraw[1] = false;

			        if (numberOfPlayers >= 3)
			        {
				         playersDraw[2] = true;
			        }

			        else
			        {
				         dealersDraw = true;
			        }
					return;
			      }     
			}

			else
			{
				playersDraw[1] = false;

			    if (numberOfPlayers >= 3)
			    {
				   playersDraw[2] = true;
			    }

			     else
			    {
				    dealersDraw = true;
			    }
				return;
			}
		}

		if (playersDraw [2] == true)
		{
			if (turnNumb == 0)
			{
				if (cardCounter[2] <= 1)
				{
					return;
				}
				else
				{
					playersDraw[2] = false;

			        if (numberOfPlayers >= 4)
			        {
				         playersDraw[3] = true;
			        }

			        else
			        {
				         dealersDraw = true;
			        }
					return;
			      }     
			}

			else
			{
				playersDraw[2] = false;

			    if (numberOfPlayers >= 4)
			    {
				   playersDraw[3] = true;
			    }

			     else
			    {
				    dealersDraw = true;
			    }
				return;
			}
		}
		if (playersDraw [3] == true)
		{
			if (turnNumb == 0)
			{
				if (cardCounter[3] <= 1)
				{
					return;
				}
				else
				{
					playersDraw[3] = false;

			        if (numberOfPlayers >= 5)
			        {
				         playersDraw[4] = true;
			        }

			        else
			        {
				         dealersDraw = true;
			        }
					return;
			      }     
			}

			else
			{
				playersDraw[3] = false;

			    if (numberOfPlayers >= 5)
			    {
				   playersDraw[4] = true;
			    }

			     else
			    {
				    dealersDraw = true;
			    }
				return;
			}
		}

		if (playersDraw [4] == true)
		{
			if (turnNumb == 0)
			{
				if (cardCounter[4] <= 1)
				{
					return;
				}
				else
				{
					playersDraw[4] = false;

			        if (numberOfPlayers >= 6)
			        {
				         playersDraw[5] = true;
			        }

			        else
			        {
				         dealersDraw = true;
			        }
					return;
			      }     
			}

			else
			{
				playersDraw[4] = false;

			    if (numberOfPlayers >= 6)
			    {
				   playersDraw[5] = true;
			    }

			     else
			    {
				    dealersDraw = true;
			    }
				return;
			}
		}

		if (playersDraw [5] == true)
		{
			if (turnNumb == 0)
			{
				if (cardCounter[5] <= 1)
				{
					return;
				}
				else
				{
					playersDraw[5] = false;

			        if (numberOfPlayers == 7)
			        {
				         playersDraw[6] = true;
			        }

			        else
			        {
				         dealersDraw = true;
			        }
					return;
			      }     
			}

			else
			{
				playersDraw[5] = false;

			    if (numberOfPlayers == 7)
			    {
				   playersDraw[6] = true;
			    }

			     else
			    {
				    dealersDraw = true;
			    }
				return;
			}
		}

		if (playersDraw [6] == true)
		{
			if (turnNumb == 0)
			{
				if (cardCounter[6] <= 1)
				{
					return;
				}
				else
				{
					playersDraw[6] = false;
                    dealersDraw = true;
			        
			      }
				return;
			}

			else
			{
					playersDraw[6] = false;
                    dealersDraw = true;
			}
			return;
		}

		if (dealersDraw == true)
		{
			if (turnNumb == 0)
			{
				if (cardCounterDealer <= 1)
				{
					return;
				}
				else
				{
                    dealersDraw = false;
					playersDraw[0] = true;   
			      }  
				return;
			}

			else
			{
                    dealersDraw = false;
					playersDraw[0] = true;
			}
			return;
		}
}
//first part of the method for creating the deck.
void dealCards()
{
	//srand is used to randomly generate numbers.
	srand((unsigned int)time(NULL));
	//deck is assigned a int value of 52; the number of cards in a deck.
    int deck[52];

    //While int is less than 52, the cards in the deck are added. They are then shuffled.
    for (int i=0; i<52; deck[i++]=i);
    random_shuffle(deck, deck+52);
    //for_each(deck, deck+52, print_card);
	print_card(deck[0]);
}


void rules()
{
	//the rules of Blackjack
	cout << "~~~~~~~~~~~~~~~~" << endl;
	cout << "Blackjack" << endl;
	cout << "~~~~~~~~~~~~~~~~" << endl;
	cout << endl;
	cout << "  - by Bradley Pick" << endl;
    cout << "-------------------" << endl;
	cout << endl;
	cout << "Would you like to read the rules of blackjack [y/n]?" << endl;
	cin >> yesNo;

	//Checks to see if the character 'y' is typed.
	if (yesNo == 'y')
		{
			//Clears the screen so that other text is not distracting.
			  system("cls");

			  cout << "Rules of Blackjack" << endl;
              cout << "-------------------" << endl;
              cout << "The aim of blackjack is to beat the dealer. To beat the dealer, the player must:" << endl;
              cout << "a) not go over 21 and" << endl;
              cout << "b) outscore the dealer or make him go bust." << endl;
			  cout << endl;
              cout << "-------------------" << endl;
			  cout << "General Rules" << endl;
			  cout << "-------------------" << endl;
			  cout << "Blackjack is played with multiple 52-card decks." << endl;
              cout << "3-7 games can be played." << endl;
              cout << "Aces may be counted as either 1 or 11 points. If the players point total is below 11, they will automatically count as" << endl;
			  cout << "11 points and will adjust according so that if possible they will keep the player at or below 21." << endl;
              cout << "A ‘blackjack’ hand always outranks all other 21- point hands." << endl;
              cout << "At the beginning of the game the dealer will give two cards to each player and then two cards to himself. One of the" << endl;
			  cout << "cards is face up and one face down. The face down card is called the hole card." << endl;
              cout << "If the dealer has an ace showing, insurance is offered. If the dealers other card is any 10-point card, the player gains" << endl;
			  cout << "20 points. If it is not, they lose 20 points." << endl;
              cout << "If the dealer has an ace or a ten showing, they will peek at his hole card to see if they have blackjack. If they do, they" << endl;
			  cout << "will turn it over immediately. If the dealer has blackjack all wagers (but insurance) will lose unless a player also has a" << endl;
			  cout << "blackjack which will result in a push (earning 5 points)." << endl;
              cout << "After each player has had his turn, the dealer will turn over their hole card if not already turned over. If they have 16" << endl;
			  cout << "or less, they will draw another card." << endl;
              cout << "If the dealer goes over 21 points, any player who hasn’t already bust will win." << endl;
              cout << "If no-one busts the player with the highest point wins." << endl;
			  cout << endl;
			  cout << "Win = + 10 points." << endl;
              cout << "Lose = - 10 points" << endl;
              cout << "Blackjack = 15 points" << endl;
              cout << "Draw(Push) = + 5 points" << endl;
			  cout << "(Points earnt/lost are doubled when double down is used." << endl;
			  cout << endl;
              cout << "-------------------" << endl;
			  cout << "Player Actions" << endl;
			  cout << "-------------------" << endl;
              cout << "* Stand: Player stands pat with his cards." << endl;
              cout << "* Hit: Player draws another card (and more if he wishes). If this card causes the player's total points to exceed 21" << endl;
              cout << "(known as 'breaking' or 'busting') then he loses." << endl;
              cout << "* Double down: Player doubles his bet and gets one, and only one, more card." << endl;
              cout << "* Split: If the player has a pair, or any two 10-point cards, then he may double his bet and separate his cards into" << endl;
              cout << "two individual hands. The dealer will automatically give each card a second card. Then, the player may hit, stand, or" << endl;
              cout << "double normally. However, when splitting aces, each ace gets only one card. Sometimes doubling after splitting is not" << endl;
              cout << "allowed. If the player gets a ten and ace after splitting, then it counts as 21 points, not a blackjack. Usually the" << endl; 
              cout << "player may keep re-splitting up to a total of four hands. Sometimes re-splitting aces is not allowed." << endl;
              cout << "* Surrender: The player forfeits half his wager, keeping the other half, and does not play out his hand. This option" << endl;
              cout << "is only available on the initial two cards." << endl;
			  cout << endl;
			  system("pause");
			  system("cls");

		}

		else if (yesNo == 'n')
		{
			system("cls");
			return;
		}

}

void players()
{
	cout << "Setting Up" << endl;
    cout << "-------------------" << endl;
	cout << "Please choose how many HUMAN players will be playing (must be less than or equal to 7)?" << endl;
	choosePlayers:
	cin >> numberOfPlayers;
	
	//Checks to make sure the value entered is an integer and to prevent loops; otherwise entering characters caused looping.
	if ( !cin )
	{
		cin.clear();
		cin.ignore();

		cout << "Please enter an integer between 1-7." << endl;

		goto choosePlayers;
	}

	//Ensures the number of players is greater than 0 and less than or equal to 7.
	if (numberOfPlayers <= 7 && numberOfPlayers > 0)
	{
		confirmPlayers:
		cout << "Are you sure you want to play with " << numberOfPlayers << " players [y/n]?" << endl;
		cin >> yesNo;
		if (yesNo == 'y')
		{
			playerOne:
			if (numberOfPlayers >= 1)
			{
				//name input
				cout << "What is the name of player one?" << endl;
				cin >> playerName[0];
				cout << "Is player one: " << playerName[0] << " ? [y/n]" << endl;
				cin >> yesNo;
				if (yesNo == 'y')
				{
					cout << endl;
				}
				else if (yesNo == 'n')
				{
					goto playerOne;
				}
			}

			playerTwo:
			if (numberOfPlayers >= 2)
			{
				cout << "What is the name of player two?" << endl;
				cin >> playerName[1];
				cout << "Is player two: " << playerName[1] << " ? [y/n]" << endl;
				cin >> yesNo;
				if (yesNo == 'y')
				{
					cout << endl;
				}
				else if (yesNo == 'n')
				{
					goto playerTwo;
				}
			}

			playerThree:
			if (numberOfPlayers >= 3)
			{
				cout << "What is the name of player three?" << endl;
				cin >> playerName[2];
				cout << "Is player three: " << playerName[2] << " ? [y/n]" << endl;
				cin >> yesNo;
				if (yesNo == 'y')
				{
					cout << endl;
				}
				else if (yesNo == 'n')
				{
					goto playerThree;
				}
			}

			playerFour:
			if (numberOfPlayers >= 4)
			{
				cout << "What is the name of player four?" << endl;
				cin >> playerName[3];
				cout << "Is player four: " << playerName[3] << " ? [y/n]" << endl;
				cin >> yesNo;
				if (yesNo == 'y')
				{
					cout << endl;
				}
				else if (yesNo == 'n')
				{
					goto playerFour;
				}
			}

			playerFive:
			if (numberOfPlayers >= 5)
			{
				cout << "What is the name of player five?" << endl;
				cin >> playerName[4];
				cout << "Is player five: " << playerName[4] << " ? [y/n]" << endl;
				cin >> yesNo;
				if (yesNo == 'y')
				{
					cout << endl;
				}
				else if (yesNo == 'n')
				{
					goto playerFive;
				}
			}

			playerSix:
			if (numberOfPlayers >= 6)
			{
				cout << "What is the name of player six?" << endl;
				cin >> playerName[5];
				cout << "Is player six: " << playerName[5] << " ? [y/n]" << endl;
				cin >> yesNo;
				if (yesNo == 'y')
				{
					cout << endl;
				}
				else if (yesNo == 'n')
				{
					goto playerSix;
				}
			}

			playerSeven:
			if (numberOfPlayers >= 7)
			{
				cout << "What is the name of player seven?" << endl;
				cin >> playerName[6];
				cout << "Is player seven: " << playerName[6] << " ? [y/n]" << endl;
				cin >> yesNo;
				if (yesNo == 'y')
				{
					cout << endl;
				}
				else if (yesNo == 'n')
				{
					goto playerSeven;
				}
			}
			//allows the player to choose between 3 and 7 games.
			chooseGames:
			cout << "Choose how many games you want to play [3-7]." << endl;
			cin >> numberOfGames;

			if ( !cin )
	{
		cin.clear();
		cin.ignore();

		cout << "Please enter an integer between 3-7." << endl;

		goto chooseGames;
	}
			//starts the games
			else if (numberOfGames >= 3 && numberOfGames <= 7)
			{
			system("cls");
			return;
			}
		}

		else if (yesNo == 'n')
		{
			goto choosePlayers;
		}

		else
		{
		cout << "This is not a valid response. Either type 'y' for yes or 'n' for no (without the '')." << endl;
		goto confirmPlayers;
		}

	}

	if (numberOfPlayers == 0 || numberOfPlayers > 8)
	{
		cout << "Please enter an integer between 1-7." << endl;
		goto choosePlayers;
	}
}

int main() {
	rules();
	players();	
	beginning: //beginning of the game
	cout << "The game is beginning. Each player gets 2 cards. " << endl;
	cout << endl;
	
	//the dealer dealing out the first two cards. Checks the number of players & how
	//many cards need to be dealt.
	if (numberOfPlayers >= 1)
	{
		dealCards();
		Sleep(1000);
		//sleep is used to create a delay as calling the cards too fast
		//causes them to not have enough time to change rank/suit.
		dealCards();
		Sleep(1000);
		dealCards();
		Sleep(1000);
		dealCards();
		Sleep(1000);
	}

	if (numberOfPlayers >= 2)
	{
		dealCards();
		Sleep(1000);
		dealCards();
		Sleep(1000);
	}

	if (numberOfPlayers >= 3)
	{
		dealCards();
		Sleep(1000);
		dealCards();
		Sleep(1000);
	}

	if (numberOfPlayers >= 4)
	{
		dealCards();
		Sleep(1000);
		dealCards();
		Sleep(1000);
	}

	if (numberOfPlayers >= 5)
	{
		dealCards();
		Sleep(1000);
		dealCards();
		Sleep(1000);
	}

	if (numberOfPlayers >= 6)
	{
		dealCards();
		Sleep(1000);
		dealCards();
		Sleep(1000);
	}

	if (numberOfPlayers == 7)
	{
		dealCards();
		Sleep(1000);
		dealCards();
		Sleep(1000);
	}
	// end of the dealer handing out the first two cards.
	//sets the turn number to 1;
	turnNumb = 1;
	cout << "-----------------" << endl;
	cout << "It's "<< playerName[0] << "'s turn!" << endl;

	//checks to see if the player got blackjack; makes sure they do not have a ten card.
	if (playerScore[0] == 21 && playersRanks[0][0] != "Ten" && playersRanks[0][1] != "Ten") 
	{
		cout << playerName[0] << " got blackjack!" << endl;
		blackjack[0] = true;
		playersDraw[0] = false;
				if (numberOfPlayers >= 2)
				{
					playersDraw[1] = true;
				}
				else
				{
					dealersDraw = true;
				}
	}

	//while loop, allows for the player to draw as many cards until they go over 21.

	while (playersDraw[0] == true && blackjack[0] == false && bust[0] == false && split[0] == false)
	{
		
	        cout << "Current Score: " << playerScore[0] << endl;
	        cout << "What will you do? [Hit(h)/Stand(s)/Double Down(d)/Split(x)/Surrender(q)]" << endl;


	        cin >> playerAction;

			//switch statement to check for key presses
	        switch(playerAction) {

				//the player hitting
            case 'h':
	        cout << playerName[0] << " hits." << endl;
	        dealCards();
			Sleep(1000);
			if (playerScore[0] > 21)
			{
				//the player going bust
				
				cout << "Current Score: " << playerScore[0] << endl;
				cout << "Oh no! " << playerName[0] << " went bust!" << endl;
				playersDraw[0] = false;
				//checks to see if there are 2 or more people; otherwise it is the dealer's turn
				if (numberOfPlayers >= 2)
				{
					bust[0] = true;
					playersDraw[1] = true;
					break;
				}
				else
				{
					bust[0] = true;
					dealersDraw = true;
					break;
				}
			}
			else
			{
			  break;
			}

			//the player sticking
            case 's':
	        cout << playerName[0] << " stands." << endl;
			playersDraw[0] = false;
				if (numberOfPlayers >= 2)
				{
					playersDraw[1] = true;
					break;
				}
				else
				{
					dealersDraw = true;
					break;
				}

			//doubling down
			case 'd':
	        cout << playerName[0] << " doubles down!" << endl;
			doubleDown[0] = true;
	        dealCards();
			if (playerScore[0] > 21)
			{
				cout << "Current Score: " << playerScore[0] << endl;
				cout << "Oh no! " << playerName[0] << " went bust!" << endl;
				playersDraw[0] = false;
				if (numberOfPlayers >= 2)
				{
					bust[0] = true;
					playersDraw[1] = true;
					break;
				}
				else
				{
					bust[0] = true;
					dealersDraw = true;
					break;
				}
			}
			else
			{
			cout << "Current Score: " << playerScore[0] << endl;
			playersDraw[0] = false;
			if (numberOfPlayers >= 2)
				{
					playersDraw[1] = true;
					break;
				}
			else
				{
					dealersDraw = true;
					break;
				}
			}

			//splitting
            case 'x':

			if (playersRanks[0][0] == playersRanks[0][1] && turnNumb == 1)
			{
				cout << playerName[0] << " splits his hand into two." << endl;
				if (playersRanks[0][0] == "Ace")
				{
					playerScore[0] = 11;
					playerScore2[0] = 11;
				}
				else
				{
					secondCardsValue[0] = playerScore[0] / 2;
					playerScore[0] = playerScore[0] /2;
					playerScore2[0] = playerScore[0];
				}
				playersCardsSplit[0][0] = playersCards[0][1];
				playersCards[0][1].clear();
				cardCounter[0] = 1;
				cardCounterSplit[0] = 1;
				split[0] = true;
				break;
				}

			else
			{
				cout << "Only player's who have two cards of the same rank on their first turn can split." << endl;
				break;
			}

			//quitting
	        case 'q':
	        cout << playerName[0] << " surrenders." << endl;
			playersDraw[0] = false;
				if (numberOfPlayers >= 2)
				{
					surrender[0] = true;
					playersDraw[1] = true;
				}
				else
				{
					surrender[0] = true;
					dealersDraw = true;
				}
				break;

            default:
            break;
	     }
		 }
		 //checks if the player has split

				if (playersDraw[0] == true && blackjack[0] == false && bust[0] == false && split[0] == true && secondHandActive[0] == false)
				{
					cout << "Hand 1: " << endl;
					cout << "----------------" << endl;
					dealCards();
	           if (playerScore[0] == 21 && playersRanks[0][0] != "Ten" && playersRanks[0][1] != "Ten") 
	                {
		              cout << playerName[0] << " got blackjack!" << endl;
		              blackjack[0] = true;
					  secondHandActive[0] = true;
	                }

			   				while (playersDraw[0] == true && blackjack[0] == false && bust[0] == false && split[0] == true && secondHandActive[0] == false)
				    {

					cout << "Current Score: " << playerScore[0] << endl;
	                cout << "Dealer's Score: " << dealerScore << endl;
	                cout << "What will you do? [Hit(h)/Stand(s)/Double Down(d)/Surrender(q)]" << endl;
	                cin >> playerAction;
	                switch(playerAction) {
					
					case 'h':
	        cout << playerName[0] << " hits." << endl;
	        dealCards();
			if (playerScore[0] > 21)
			{
				cout << "Current Score: " << playerScore[0] << endl;
				cout << "Oh no! " << playerName[0] << " went bust!" << endl;
				playersDraw[0] = false;
				secondHandActive[0] = true;
				break;
			}
			else
			{
			  break;
			}

					case 's':
					cout << playerName[0] << "stands." << endl;
					secondHandActive[0] = true;
					break;

					case 'd':
	        cout << playerName[0] << " doubles down!" << endl;
			doubleDown[0] = true;
	        dealCards();
			if (playerScore[0] > 21)
			{
				cout << "Current Score: " << playerScore[0] << endl;
				cout << "Oh no! " << playerName[0] << " went bust!" << endl;
				secondHandActive[0] = true;
				break;
			}
			else
			{
				cout << "Current Score: " << playerScore[0] << endl;
				secondHandActive[0] = true;
				break;
			}

	            case 'q':
	            cout << playerName[0] << " surrenders." << endl;
				surrender[0];
				secondHandActive[0] = true;
				break;

               default:
               break;
					}
			}


				}

				if (playersDraw[0] == true && split[0] == true && secondHandActive[0] == true)
				{
					cout << "Hand 2: " << endl;
					cout << "----------------" << endl;
					dealCards();

					if (playerScore2[0] == 21 && playersRanks2[0][0] != "Ten" && playersRanks2[0][1] != "Ten") 
	           {
		              cout << playerName[0] << " got blackjack!" << endl;
		              blackjack2[0] = true;
                playersDraw[0] = false;
				if (numberOfPlayers >= 2)
				 {
					playersDraw[1] = true;
				 }
				else
				 {
					dealersDraw = true;
				 }
				}
								while (playersDraw[0] == true && blackjack2[0] == false && split[0] == true && secondHandActive[0] == true)
				{
					cout << "Current Score: " << playerScore2[0] << endl;
	                cout << "Dealer's Score: " << dealerScore << endl;
	                cout << "What will you do? [Hit(h)/Stand(s)/Double Down(d)/Surrender(q)]" << endl;
	                cin >> playerAction;
	                switch(playerAction) {

					case 'h':
	                cout << playerName[0] << " hits." << endl;
	                dealCards();
			        if (playerScore2[0] > 21)
			        {
				        cout << "Current Score: " << playerScore[0] << endl;
				        cout << "Oh no! " << playerName[0] << " went bust!" << endl;
				        playersDraw[0] = false;
				        if (numberOfPlayers >= 2)
				        {
					        bust2[0] = true;
							playersDraw[1] = true;
							break;
				        }
						else
						{
							bust2[0] = true;
							dealersDraw = true;
							break;
						}
			        }
			        else
			        {
						break;
			        }


					case 's':
					cout << playerName[0] << "stands." << endl;
					playersDraw[0] = false;
					if (numberOfPlayers >= 2)
				        {
							playersDraw[1] = true;
				        }
					else
						{
							dealersDraw = true;
						}
					break;

					case 'd':
	                cout << playerName[0] << " doubles down!" << endl;
			        doubleDown2[0] = true;
			        dealCards();
			        if (playerScore[0] > 21)
			        {
				       cout << "Current Score: " << playerScore[0] << endl;
				       cout << "Oh no! " << playerName[0] << " went bust!" << endl;
					   playersDraw[0] = false;
					   if (numberOfPlayers >= 2)
				        {
							bust2[0] = true;
							playersDraw[1] = true;
				        }
					else
						{
							bust2[0] = true;
							dealersDraw = true;
						}
				       break;
			        }
			        else
			{
			cout << "Current Score: " << playerScore[0] << endl;
			playersDraw[0] = false;
					if (numberOfPlayers >= 2)
				        {
							playersDraw[1] = true;
				        }
					else
						{
							dealersDraw = true;
						}
			        }

                    break;

	            case 'q':
	            cout << playerName[0] << " surrenders." << endl;
			    playersDraw[0] = false;
				surrender2[0];
				playersDraw[0] = false;
				  if (numberOfPlayers >= 2)
				        {
							playersDraw[1] = true;
							break;
				        }
				  else
						{
							dealersDraw = true;
							break;
						}

               default:
               break;
					}
			}
	}

	cout << "-----------------" << endl;
//player 2
	if (numberOfPlayers >= 2)
	{
		cout << "It's "<< playerName[1] << "'s turn!" << endl;
	if (playerScore[1] == 21 && playersRanks[1][0] != "Ten" && playersRanks[1][1] != "Ten") 
	{
		cout << playerName[1] << " got blackjack!" << endl;
		blackjack[1] = true;
		playersDraw[1] = false;
				if (numberOfPlayers >= 3)
				{
					playersDraw[2] = true;
				}
				else
				{
					dealersDraw = true;
				}
	}

while (playersDraw[1] == true && blackjack[1] == false && bust[1] == false && split[1] == false)
	{
		
	        cout << "Current Score: " << playerScore[1] << endl;
	        cout << "What will you do? [Hit(h)/Stand(s)/Double Down(d)/Split(x)/Surrender(q)]" << endl;

	        cin >> playerAction;
	        switch(playerAction) {

            case 'h':
	        cout << playerName[1] << " hits." << endl;
	        dealCards();
			if (playerScore[1] > 21)
			{
				cout << "Current Score: " << playerScore[1] << endl;
				cout << "Oh no! " << playerName[1] << " went bust!" << endl;
				playersDraw[1] = false;
				if (numberOfPlayers >= 3)
				{
					bust[1] = true;
					playersDraw[2] = true;
					break;
				}
				else
				{
					bust[1] = true;
					dealersDraw = true;
					break;
				}
			}
			else
			{
			  break;
			}

            case 's':
	        cout << playerName[1] << " stands." << endl;
			playersDraw[1] = false;
				if (numberOfPlayers >= 3)
				{
					playersDraw[2] = true;
				}
				else
				{
					dealersDraw = true;
				}
            break;


			case 'd':
	        cout << playerName[1] << " doubles down!" << endl;
			doubleDown[1] = true;
	        dealCards();
			if (playerScore[1] > 21)
			{
				cout << "Current Score: " << playerScore[1] << endl;
				cout << "Oh no! " << playerName[1] << " went bust!" << endl;
				playersDraw[1] = false;
				if (numberOfPlayers >= 3)
				{
					bust[1] = true;
					playersDraw[2] = true;
					break;
				}
				else
				{
					bust[1] = true;
					dealersDraw = true;
					break;
				}
			}
			else
			{
			cout << "Current Score: " << playerScore[1] << endl;
			playersDraw[1] = false;
			if (numberOfPlayers >= 3)
				{
					playersDraw[2] = true;
					break;
				}
				else
				{
					dealersDraw = true;
					break;
				}
			}


            case 'x':

			if (playersRanks[1][1] == playersRanks[1][1] && turnNumb == 1)
			{
				cout << playerName[1] << " splits his hand into two." << endl;
				if (playersRanks[1][0] == "Ace")
				{
					playerScore[1] = 11;
					playerScore2[1] = 11;
				}
				else
				{
					secondCardsValue[1] = playerScore[1] / 2;
					playerScore[1] = playerScore[1] /2;
					playerScore2[1] = playerScore[1];
				}
				playersCardsSplit[1][0] = playersCards[1][1];
				playersCards[1][1].clear();
				cardCounter[1] = 1;
				cardCounterSplit[1] = 1;
				split[1] = true;
				break;
				}

			else
			{
				cout << "Only player's who have two cards of the same rank on their first turn can split." << endl;
				break;
			}

	        case 'q':
	        cout << playerName[1] << " surrenders." << endl;
			playersDraw[1] = false;
				if (numberOfPlayers >= 3)
				{
					surrender[1] = true;
					playersDraw[2] = true;
				}
				else
				{
					surrender[1] = true;
					dealersDraw = true;
				}
				break;

            default:
            break;
	     }
		 }

				if (playersDraw[1] == true && blackjack[1] == false && bust[1] == false && split[1] == true && secondHandActive[1] == false)
				{
					cout << "Hand 1: " << endl;
					cout << "----------------" << endl;
					dealCards();
	           if (playerScore[1] == 21 && playersRanks[1][0] != "Ten" && playersRanks[1][1] != "Ten") 
	                {
		              cout << playerName[1] << " got blackjack!" << endl;
		              blackjack[1] = true;
					  secondHandActive[1] = true;
	                }

			   				while (playersDraw[1] == true && blackjack[1] == false && bust[1] == false && split[1] == true && secondHandActive[1] == false)
				    {

					cout << "Current Score: " << playerScore[1] << endl;
	                cout << "Dealer's Score: " << dealerScore << endl;
	                cout << "What will you do? [Hit(h)/Stand(s)/Double Down(d)/Surrender(q)]" << endl;
	                cin >> playerAction;
	                switch(playerAction) {
					
					case 'h':
	        cout << playerName[1] << " hits." << endl;
	        dealCards();
			if (playerScore[1] > 21)
			{
				cout << "Current Score: " << playerScore[1] << endl;
				cout << "Oh no! " << playerName[1] << " went bust!" << endl;
				secondHandActive[1] = true;
				break;
			}
			else
			{
			  break;
			}

					case 's':
					cout << playerName[1] << "stands." << endl;
					secondHandActive[1] = true;
					break;

					case 'd':
	        cout << playerName[1] << " doubles down!" << endl;
			doubleDown[1] = true;
	        dealCards();
			if (playerScore[1] > 21)
			{
				cout << "Current Score: " << playerScore[1] << endl;
				cout << "Oh no! " << playerName[1] << " went bust!" << endl;
				secondHandActive[1] = true;
				break;
			}
			else
			{
				cout << "Current Score: " << playerScore[1] << endl;
				secondHandActive[1] = true;
				break;
			}

	            case 'q':
	            cout << playerName[1] << " surrenders." << endl;
				surrender[1];
				secondHandActive[1] = true;
				break;

               default:
               break;
					}
			}


				}

				if (playersDraw[1] == true && split[1] == true && secondHandActive[1] == true)
				{
					cout << "Hand 2: " << endl;
					cout << "----------------" << endl;
					dealCards();

					if (playerScore2[1] == 21 && playersRanks2[1][0] != "Ten" && playersRanks2[1][1] != "Ten") 
	           {
		              cout << playerName[1] << " got blackjack!" << endl;
		              blackjack2[1] = true;
                playersDraw[1] = false;
				if (numberOfPlayers >= 3)
				 {
					playersDraw[2] = true;
				 }
				else
				 {
					dealersDraw = true;
				 }
				}
								while (playersDraw[1] == true && blackjack2[1] == false && split[1] == true && secondHandActive[1] == true)
				{
					cout << "Current Score: " << playerScore2[1] << endl;
	                cout << "Dealer's Score: " << dealerScore << endl;
	                cout << "What will you do? [Hit(h)/Stand(s)/Double Down(d)/Surrender(q)]" << endl;
	                cin >> playerAction;
	                switch(playerAction) {

					case 'h':
	                cout << playerName[1] << " hits." << endl;
	                dealCards();
			        if (playerScore2[1] > 21)
			        {
				        cout << "Current Score: " << playerScore[1] << endl;
				        cout << "Oh no! " << playerName[1] << " went bust!" << endl;
				        playersDraw[1] = false;
				        if (numberOfPlayers >= 3)
				        {
					        bust2[1] = true;
							playersDraw[2] = true;
							break;
				        }
						else
						{
							bust2[1] = true;
							dealersDraw = true;
							break;
						}
			        }
			        else
			        {
						break;
			        }


					case 's':
					cout << playerName[1] << "stands." << endl;
					playersDraw[1] = false;
					if (numberOfPlayers >= 3)
				        {
							playersDraw[2] = true;
				        }
					else
						{
							dealersDraw = true;
						}
					break;

					case 'd':
	                cout << playerName[1] << " doubles down!" << endl;
			        doubleDown2[1] = true;
			        dealCards();
			        if (playerScore[1] > 21)
			        {
				       cout << "Current Score: " << playerScore[1] << endl;
				       cout << "Oh no! " << playerName[1] << " went bust!" << endl;
					   playersDraw[1] = false;
					   if (numberOfPlayers >= 3)
				        {
							bust2[1] = true;
							playersDraw[2] = true;
				        }
					else
						{
							bust2[1] = true;
							dealersDraw = true;
						}
				       break;
			        }
			        else
			        {
			cout << "Current Score: " << playerScore[1] << endl;
			playersDraw[1] = false;
					if (numberOfPlayers >= 3)
				        {
							playersDraw[2] = true;
				        }
					else
						{
							dealersDraw = true;
						}
			        }

                    break;

	            case 'q':
	            cout << playerName[1] << " surrenders." << endl;
			    playersDraw[1] = false;
				surrender2[1];
				playersDraw[1] = false;
				  if (numberOfPlayers >= 3)
				        {
							playersDraw[2] = true;
							break;
				        }
				  else
						{
							dealersDraw = true;
							break;
						}

               default:
               break;
					}
			}
			}
	}

		cout << "-----------------" << endl;
//player 3
	if (numberOfPlayers >= 3)
	{
		cout << "It's "<< playerName[2] << "'s turn!" << endl;
	if (playerScore[2] == 21 && playersRanks[2][0] != "Ten" && playersRanks[2][1] != "Ten") 
	{
		cout << playerName[2] << " got blackjack!" << endl;
		blackjack[2] = true;
		playersDraw[2] = false;
				if (numberOfPlayers >= 4)
				{
					playersDraw[3] = true;
				}
				else
				{
					dealersDraw = true;
				}
	}

while (playersDraw[2] == true && blackjack[2] == false && bust[2] == false && split[2] == false)
	{
		
	        cout << "Current Score: " << playerScore[2] << endl;
	        cout << "What will you do? [Hit(h)/Stand(s)/Double Down(d)/Split(x)/Surrender(q)]" << endl;

	        cin >> playerAction;
	        switch(playerAction) {

            case 'h':
	        cout << playerName[2] << " hits." << endl;
	        dealCards();
			if (playerScore[2] > 21)
			{
				cout << "Current Score: " << playerScore[2] << endl;
				cout << "Oh no! " << playerName[2] << " went bust!" << endl;
				playersDraw[2] = false;
				if (numberOfPlayers >= 4)
				{
					bust[2] = true;
					playersDraw[3] = true;
					break;
				}
				else
				{
					bust[2] = true;
					dealersDraw = true;
					break;
				}
			}
			else
			{
			  break;
			}

            case 's':
	        cout << playerName[2] << " stands." << endl;
			playersDraw[2] = false;
				if (numberOfPlayers >= 4)
				{
					playersDraw[3] = true;
				}
				else
				{
					dealersDraw = true;
				}
            break;


			case 'd':
	        cout << playerName[2] << " doubles down!" << endl;
			doubleDown[2] = true;
	        dealCards();
			if (playerScore[2] > 21)
			{
				cout << "Current Score: " << playerScore[2] << endl;
				cout << "Oh no! " << playerName[2] << " went bust!" << endl;
				playersDraw[2] = false;
				if (numberOfPlayers >= 4)
				{
					bust[2] = true;
					playersDraw[3] = true;
					break;
				}
				else
				{
					bust[2] = true;
					dealersDraw = true;
					break;
				}
			}
			else
			{
			cout << "Current Score: " << playerScore[2] << endl;
			playersDraw[2] = false;
			if (numberOfPlayers >= 4)
				{
					playersDraw[3] = true;
					break;
				}
				else
				{
					dealersDraw = true;
					break;
				}
			}


            case 'x':

			if (playersRanks[2][1] == playersRanks[2][1] && turnNumb == 1)
			{
				cout << playerName[2] << " splits his hand into two." << endl;
				if (playersRanks[2][0] == "Ace")
				{
					playerScore[2] = 11;
					playerScore2[2] = 11;
				}
				else
				{
					secondCardsValue[2] = playerScore[2] / 2;
					playerScore[2] = playerScore[2] /2;
					playerScore2[2] = playerScore[2];
				}
				playersCardsSplit[2][0] = playersCards[2][1];
				playersCards[2][1].clear();
				cardCounter[2] = 1;
				cardCounterSplit[2] = 1;
				split[2] = true;
				break;
				}

			else
			{
				cout << "Only player's who have two cards of the same rank on their first turn can split." << endl;
				break;
			}

	        case 'q':
	        cout << playerName[2] << " surrenders." << endl;
			playersDraw[2] = false;
				if (numberOfPlayers >= 4)
				{
					surrender[2] = true;
					playersDraw[3] = true;
				}
				else
				{
					surrender[2] = true;
					dealersDraw = true;
				}
				break;

            default:
            break;
	     }
		 }

				if (playersDraw[2] == true && blackjack[2] == false && bust[2] == false && split[2] == true && secondHandActive[2] == false)
				{
					cout << "Hand 1: " << endl;
					cout << "----------------" << endl;
					dealCards();
	           if (playerScore[2] == 21 && playersRanks[2][0] != "Ten" && playersRanks[2][1] != "Ten") 
	                {
		              cout << playerName[2] << " got blackjack!" << endl;
		              blackjack[2] = true;
					  secondHandActive[2] = true;
	                }

			   				while (playersDraw[2] == true && blackjack[2] == false && bust[2] == false && split[2] == true && secondHandActive[2] == false)
				    {

					cout << "Current Score: " << playerScore[2] << endl;
	                cout << "Dealer's Score: " << dealerScore << endl;
	                cout << "What will you do? [Hit(h)/Stand(s)/Double Down(d)/Surrender(q)]" << endl;
	                cin >> playerAction;
	                switch(playerAction) {
					
					case 'h':
	        cout << playerName[2] << " hits." << endl;
	        dealCards();
			if (playerScore[2] > 21)
			{
				cout << "Current Score: " << playerScore[2] << endl;
				cout << "Oh no! " << playerName[2] << " went bust!" << endl;
				secondHandActive[2] = true;
				break;
			}
			else
			{
			  break;
			}

					case 's':
					cout << playerName[2] << "stands." << endl;
					secondHandActive[2] = true;
					break;

					case 'd':
	        cout << playerName[2] << " doubles down!" << endl;
			doubleDown[2] = true;
	        dealCards();
			if (playerScore[2] > 21)
			{
				cout << "Current Score: " << playerScore[2] << endl;
				cout << "Oh no! " << playerName[2] << " went bust!" << endl;
				secondHandActive[2] = true;
				break;
			}
			else
			{
				cout << "Current Score: " << playerScore[2] << endl;
				secondHandActive[2] = true;
				break;
			}

	            case 'q':
	            cout << playerName[2] << " surrenders." << endl;
				surrender[2];
				secondHandActive[2] = true;
				break;

               default:
               break;
					}
			}


				}

				if (playersDraw[2] == true && split[2] == true && secondHandActive[2] == true)
				{
					cout << "Hand 2: " << endl;
					cout << "----------------" << endl;
					dealCards();

					if (playerScore2[2] == 21 && playersRanks2[2][0] != "Ten" && playersRanks2[2][1] != "Ten") 
	           {
		              cout << playerName[2] << " got blackjack!" << endl;
		              blackjack2[2] = true;
                playersDraw[2] = false;
				if (numberOfPlayers >= 4)
				 {
					playersDraw[3] = true;
				 }
				else
				 {
					dealersDraw = true;
				 }
				}
								while (playersDraw[2] == true && blackjack2[2] == false && split[2] == true && secondHandActive[2] == true)
				{
					cout << "Current Score: " << playerScore2[2] << endl;
	                cout << "Dealer's Score: " << dealerScore << endl;
	                cout << "What will you do? [Hit(h)/Stand(s)/Double Down(d)/Surrender(q)]" << endl;
	                cin >> playerAction;
	                switch(playerAction) {

					case 'h':
	                cout << playerName[2] << " hits." << endl;
	                dealCards();
			        if (playerScore2[2] > 21)
			        {
				        cout << "Current Score: " << playerScore[2] << endl;
				        cout << "Oh no! " << playerName[2] << " went bust!" << endl;
				        playersDraw[2] = false;
				        if (numberOfPlayers >= 4)
				        {
					        bust2[2] = true;
							playersDraw[3] = true;
							break;
				        }
						else
						{
							bust2[2] = true;
							dealersDraw = true;
							break;
						}
			        }
			        else
			        {
						break;
			        }


					case 's':
					cout << playerName[2] << "stands." << endl;
					playersDraw[2] = false;
					if (numberOfPlayers >= 4)
				        {
							playersDraw[3] = true;
				        }
					else
						{
							dealersDraw = true;
						}
					break;

					case 'd':
	                cout << playerName[2] << " doubles down!" << endl;
			        doubleDown2[2] = true;
			        dealCards();
			        if (playerScore[2] > 21)
			        {
				       cout << "Current Score: " << playerScore[2] << endl;
				       cout << "Oh no! " << playerName[2] << " went bust!" << endl;
					   playersDraw[2] = false;
					   if (numberOfPlayers >= 4)
				        {
							bust2[2] = true;
							playersDraw[3] = true;
				        }
					else
						{
							bust2[2] = true;
							dealersDraw = true;
						}
				       break;
			        }
			        else
			        {
			cout << "Current Score: " << playerScore[2] << endl;
			playersDraw[2] = false;

					if (numberOfPlayers >= 4)
				        {
							playersDraw[3] = true;
				        }
					else
						{
							dealersDraw = true;
						}
			        }

                    break;

	            case 'q':
	            cout << playerName[2] << " surrenders." << endl;
			    playersDraw[2] = false;
				surrender2[2];
				playersDraw[2] = false;
				  if (numberOfPlayers >= 4)
				        {
							playersDraw[3] = true;
							break;
				        }
				  else
						{
							dealersDraw = true;
							break;
						}

               default:
               break;
					}
			}
			}
	}

			cout << "-----------------" << endl;
//player 4
	if (numberOfPlayers >= 4)
	{
		cout << "It's "<< playerName[3] << "'s turn!" << endl;
	if (playerScore[3] == 21 && playersRanks[3][0] != "Ten" && playersRanks[3][1] != "Ten") 
	{
		cout << playerName[3] << " got blackjack!" << endl;
		blackjack[3] = true;
		playersDraw[3] = false;
				if (numberOfPlayers >= 5)
				{
					playersDraw[4] = true;
				}
				else
				{
					dealersDraw = true;
				}
	}

while (playersDraw[3] == true && blackjack[3] == false && bust[3] == false && split[3] == false)
	{
		
	        cout << "Current Score: " << playerScore[3] << endl;
	        cout << "What will you do? [Hit(h)/Stand(s)/Double Down(d)/Split(x)/Surrender(q)]" << endl;

	        cin >> playerAction;
	        switch(playerAction) {

            case 'h':
	        cout << playerName[3] << " hits." << endl;
	        dealCards();
			if (playerScore[3] > 21)
			{
				cout << "Current Score: " << playerScore[3] << endl;
				cout << "Oh no! " << playerName[3] << " went bust!" << endl;
				playersDraw[3] = false;
				if (numberOfPlayers >= 5)
				{
					bust[3] = true;
					playersDraw[4] = true;
					break;
				}
				else
				{
					bust[3] = true;
					dealersDraw = true;
					break;
				}
			}
			else
			{
			  break;
			}

            case 's':
	        cout << playerName[3] << " stands." << endl;
			playersDraw[3] = false;
				if (numberOfPlayers >= 5)
				{
					playersDraw[4] = true;
				}
				else
				{
					dealersDraw = true;
				}
            break;


			case 'd':
	        cout << playerName[3] << " doubles down!" << endl;
			doubleDown[3] = true;
	        dealCards();
			if (playerScore[3] > 21)
			{
				cout << "Current Score: " << playerScore[3] << endl;
				cout << "Oh no! " << playerName[3] << " went bust!" << endl;
				playersDraw[3] = false;
				if (numberOfPlayers >= 5)
				{
					bust[3] = true;
					playersDraw[4] = true;
					break;
				}
				else
				{
					bust[3] = true;
					dealersDraw = true;
					break;
				}
			}
			else
			{
			cout << "Current Score: " << playerScore[3] << endl;
			playersDraw[3] = false;
			if (numberOfPlayers >= 5)
				{
					playersDraw[4] = true;
					break;
				}
				else
				{
					dealersDraw = true;
					break;
				}
			}


            case 'x':

			if (playersRanks[3][1] == playersRanks[3][1] && turnNumb == 1)
			{
				cout << playerName[3] << " splits his hand into two." << endl;
				if (playersRanks[3][0] == "Ace")
				{
					playerScore[3] = 11;
					playerScore2[3] = 11;
				}
				else
				{
					secondCardsValue[3] = playerScore[3] / 2;
					playerScore[3] = playerScore[3] /2;
					playerScore2[3] = playerScore[3];
				}
				playersCardsSplit[3][0] = playersCards[3][1];
				playersCards[3][1].clear();
				cardCounter[3] = 1;
				cardCounterSplit[3] = 1;
				split[3] = true;
				break;
				}

			else
			{
				cout << "Only player's who have two cards of the same rank on their first turn can split." << endl;
				break;
			}

	        case 'q':
	        cout << playerName[3] << " surrenders." << endl;
			playersDraw[3] = false;
				if (numberOfPlayers >= 5)
				{
					surrender[3] = true;
					playersDraw[4] = true;
				}
				else
				{
					surrender[3] = true;
					dealersDraw = true;
				}
				break;

            default:
            break;
	     }
		 }

				if (playersDraw[3] == true && blackjack[3] == false && bust[3] == false && split[3] == true && secondHandActive[3] == false)
				{
					cout << "Hand 1: " << endl;
					cout << "----------------" << endl;
					dealCards();
	           if (playerScore[3] == 21 && playersRanks[3][0] != "Ten" && playersRanks[3][1] != "Ten") 
	                {
		              cout << playerName[3] << " got blackjack!" << endl;
		              blackjack[3] = true;
					  secondHandActive[3] = true;
	                }

			   				while (playersDraw[3] == true && blackjack[3] == false && bust[3] == false && split[3] == true && secondHandActive[3] == false)
				    {

					cout << "Current Score: " << playerScore[3]  << " points from going over 21!)" << endl;
	                cout << "Dealer's Score: " << dealerScore << endl;
	                cout << "What will you do? [Hit(h)/Stand(s)/Double Down(d)/Surrender(q)]" << endl;
	                cin >> playerAction;
	                switch(playerAction) {
					
					case 'h':
	        cout << playerName[3] << " hits." << endl;
	        dealCards();
			if (playerScore[3] > 21)
			{
				cout << "Current Score: " << playerScore[3] << endl;
				cout << "Oh no! " << playerName[3] << " went bust!" << endl;
				secondHandActive[3] = true;
				break;
			}
			else
			{
			  break;
			}

					case 's':
					cout << playerName[3] << "stands." << endl;
					secondHandActive[3] = true;
					break;

					case 'd':
	        cout << playerName[3] << " doubles down!" << endl;
			doubleDown[3] = true;
	        dealCards();
			if (playerScore[3] > 21)
			{
				cout << "Current Score: " << playerScore[3] << endl;
				cout << "Oh no! " << playerName[3] << " went bust!" << endl;
				secondHandActive[3] = true;
				break;
			}
			else
			{
				cout << "Current Score: " << playerScore[3] << endl;
				secondHandActive[3] = true;
				break;
			}

	            case 'q':
	            cout << playerName[3] << " surrenders." << endl;
				surrender[3];
				secondHandActive[3] = true;
				break;

               default:
               break;
					}
			}


				}

				if (playersDraw[3] == true && split[3] == true && secondHandActive[3] == true)
				{
					cout << "Hand 2: " << endl;
					cout << "----------------" << endl;
					dealCards();

					if (playerScore2[3] == 21 && playersRanks2[3][0] != "Ten" && playersRanks2[3][1] != "Ten") 
	           {
		              cout << playerName[3] << " got blackjack!" << endl;
		              blackjack2[3] = true;
                playersDraw[3] = false;
				if (numberOfPlayers >= 5)
				 {
					playersDraw[4] = true;
				 }
				else
				 {
					dealersDraw = true;
				 }
				}
								while (playersDraw[3] == true && blackjack2[3] == false && split[3] == true && secondHandActive[3] == true)
				{
					cout << "Current Score: " << playerScore2[3]  << endl;
	                cout << "Dealer's Score: " << dealerScore << endl;
	                cout << "What will you do? [Hit(h)/Stand(s)/Double Down(d)/Surrender(q)]" << endl;
	                cin >> playerAction;
	                switch(playerAction) {

					case 'h':
	                cout << playerName[3] << " hits." << endl;
	                dealCards();
			        if (playerScore2[3] > 21)
			        {
				        cout << "Current Score: " << playerScore[3] << endl;
				        cout << "Oh no! " << playerName[3] << " went bust!" << endl;
				        playersDraw[3] = false;
				        if (numberOfPlayers >= 5)
				        {
					        bust2[3] = true;
							playersDraw[4] = true;
							break;
				        }
						else
						{
							bust2[3] = true;
							dealersDraw = true;
							break;
						}
			        }
			        else
			        {
						break;
			        }


					case 's':
					cout << playerName[3] << "stands." << endl;
					playersDraw[3] = false;
					if (numberOfPlayers >= 5)
				        {
							playersDraw[4] = true;
				        }
					else
						{
							dealersDraw = true;
						}
					break;

					case 'd':
	                cout << playerName[3] << " doubles down!" << endl;
			        doubleDown2[3] = true;
			        dealCards();
			        if (playerScore[3] > 21)
			        {
				       cout << "Current Score: " << playerScore[3] << endl;
				       cout << "Oh no! " << playerName[3] << " went bust!" << endl;
					   playersDraw[3] = false;
					   if (numberOfPlayers >= 5)
				        {
							bust2[3] = true;
							playersDraw[4] = true;
				        }
					else
						{
							bust2[3] = true;
							dealersDraw = true;
						}
				       break;
			        }
			        else
			        {
			cout << "Current Score: " << playerScore[3] << endl;
			playersDraw[3] = false;

					if (numberOfPlayers >= 5)
				        {
							playersDraw[4] = true;
				        }
					else
						{
							dealersDraw = true;
						}
			        }

                    break;

	            case 'q':
	            cout << playerName[3] << " surrenders." << endl;
			    playersDraw[3] = false;
				surrender2[3];
				playersDraw[3] = false;
				  if (numberOfPlayers >= 5)
				        {
							playersDraw[4] = true;
							break;
				        }
				  else
						{
							dealersDraw = true;
							break;
						}

               default:
               break;
					}
			}
			}
	}
				cout << "-----------------" << endl;
//player 5
	if (numberOfPlayers >= 5)
	{
		cout << "It's "<< playerName[4] << "'s turn!" << endl;
	if (playerScore[4] == 21 && playersRanks[4][0] != "Ten" && playersRanks[4][1] != "Ten") 
	{
		cout << playerName[4] << " got blackjack!" << endl;
		blackjack[4] = true;
		playersDraw[4] = false;
				if (numberOfPlayers >= 6)
				{
					playersDraw[5] = true;
				}
				else
				{
					dealersDraw = true;
				}
	}

while (playersDraw[4] == true && blackjack[4] == false && bust[4] == false && split[4] == false)
	{
		
	        cout << "Current Score: " << playerScore[4] << endl;
	        cout << "What will you do? [Hit(h)/Stand(s)/Double Down(d)/Split(x)/Surrender(q)]" << endl;

	        cin >> playerAction;
	        switch(playerAction) {

            case 'h':
	        cout << playerName[4] << " hits." << endl;
	        dealCards();
			if (playerScore[4] > 21)
			{
				cout << "Current Score: " << playerScore[4] << endl;
				cout << "Oh no! " << playerName[4] << " went bust!" << endl;
				playersDraw[4] = false;
				if (numberOfPlayers >= 6)
				{
					bust[4] = true;
					playersDraw[5] = true;
					break;
				}
				else
				{
					bust[4] = true;
					dealersDraw = true;
					break;
				}
			}
			else
			{
			  break;
			}

            case 's':
	        cout << playerName[4] << " stands." << endl;
			playersDraw[4] = false;
				if (numberOfPlayers >= 6)
				{
					playersDraw[5] = true;
				}
				else
				{
					dealersDraw = true;
				}
            break;


			case 'd':
	        cout << playerName[4] << " doubles down!" << endl;
			doubleDown[4] = true;
	        dealCards();
			if (playerScore[4] > 21)
			{
				cout << "Current Score: " << playerScore[4] << endl;
				cout << "Oh no! " << playerName[4] << " went bust!" << endl;
				playersDraw[4] = false;
				if (numberOfPlayers >= 6)
				{
					bust[4] = true;
					playersDraw[5] = true;
					break;
				}
				else
				{
					bust[4] = true;
					dealersDraw = true;
					break;
				}
			}
			else
			{
			cout << "Current Score: " << playerScore[4] << endl;
			playersDraw[4] = false;
			if (numberOfPlayers >= 6)
				{
					playersDraw[5] = true;
					break;
				}
				else
				{
					dealersDraw = true;
					break;
				}
			}


            case 'x':

			if (playersRanks[4][1] == playersRanks[4][1] && turnNumb == 1)
			{
				cout << playerName[4] << " splits his hand into two." << endl;
				if (playersRanks[4][0] == "Ace")
				{
					playerScore[4] = 11;
					playerScore2[4] = 11;
				}
				else
				{
					secondCardsValue[4] = playerScore[4] / 2;
					playerScore[4] = playerScore[4] /2;
					playerScore2[4] = playerScore[4];
				}
				playersCardsSplit[4][0] = playersCards[4][1];
				playersCards[4][1].clear();
				cardCounter[4] = 1;
				cardCounterSplit[4] = 1;
				split[4] = true;
				break;
				}

			else
			{
				cout << "Only player's who have two cards of the same rank on their first turn can split." << endl;
				break;
			}

	        case 'q':
	        cout << playerName[4] << " surrenders." << endl;
			playersDraw[4] = false;
				if (numberOfPlayers >= 6)
				{
					surrender[4] = true;
					playersDraw[5] = true;
				}
				else
				{
					surrender[4] = true;
					dealersDraw = true;
				}
				break;

            default:
            break;
	     }
		 }

				if (playersDraw[4] == true && blackjack[4] == false && bust[4] == false && split[4] == true && secondHandActive[4] == false)
				{
					cout << "Hand 1: " << endl;
					cout << "----------------" << endl;
					dealCards();
	           if (playerScore[4] == 21 && playersRanks[4][0] != "Ten" && playersRanks[4][1] != "Ten") 
	                {
		              cout << playerName[4] << " got blackjack!" << endl;
		              blackjack[4] = true;
					  secondHandActive[4] = true;
	                }

			   				while (playersDraw[4] == true && blackjack[4] == false && bust[4] == false && split[4] == true && secondHandActive[4] == false)
				    {

					cout << "Current Score: " << playerScore[4] << endl;
	                cout << "Dealer's Score: " << dealerScore << endl;
	                cout << "What will you do? [Hit(h)/Stand(s)/Double Down(d)/Surrender(q)]" << endl;
	                cin >> playerAction;
	                switch(playerAction) {
					
					case 'h':
	        cout << playerName[4] << " hits." << endl;
	        dealCards();
			if (playerScore[4] > 21)
			{
				cout << "Current Score: " << playerScore[4] << endl;
				cout << "Oh no! " << playerName[4] << " went bust!" << endl;
				secondHandActive[4] = true;
				break;
			}
			else
			{
			  break;
			}

					case 's':
					cout << playerName[4] << "stands." << endl;
					secondHandActive[4] = true;
					break;

					case 'd':
	        cout << playerName[4] << " doubles down!" << endl;
			doubleDown[4] = true;
	        dealCards();
			if (playerScore[4] > 21)
			{
				cout << "Current Score: " << playerScore[4] << endl;
				cout << "Oh no! " << playerName[4] << " went bust!" << endl;
				secondHandActive[4] = true;
				break;
			}
			else
			{
				cout << "Current Score: " << playerScore[4] << endl;
				secondHandActive[4] = true;
				break;
			}

	            case 'q':
	            cout << playerName[4] << " surrenders." << endl;
				surrender[4];
				secondHandActive[4] = true;
				break;

               default:
               break;
					}
			}


				}

				if (playersDraw[4] == true && split[4] == true && secondHandActive[4] == true)
				{
					cout << "Hand 2: " << endl;
					cout << "----------------" << endl;
					dealCards();

					if (playerScore2[4] == 21 && playersRanks2[4][0] != "Ten" && playersRanks2[4][1] != "Ten") 
	           {
		              cout << playerName[4] << " got blackjack!" << endl;
		              blackjack2[4] = true;
                playersDraw[4] = false;
				if (numberOfPlayers >= 6)
				 {
					playersDraw[5] = true;
				 }
				else
				 {
					dealersDraw = true;
				 }
				}
								while (playersDraw[4] == true && blackjack2[4] == false && split[4] == true && secondHandActive[4] == true)
				{
					cout << "Current Score: " << playerScore2[4] << endl;
	                cout << "Dealer's Score: " << dealerScore << endl;
	                cout << "What will you do? [Hit(h)/Stand(s)/Double Down(d)/Surrender(q)]" << endl;
	                cin >> playerAction;
	                switch(playerAction) {

					case 'h':
	                cout << playerName[4] << " hits." << endl;
	                dealCards();
			        if (playerScore2[4] > 21)
			        {
				        cout << "Current Score: " << playerScore[4] << endl;
				        cout << "Oh no! " << playerName[4] << " went bust!" << endl;
				        playersDraw[4] = false;
				        if (numberOfPlayers >= 6)
				        {
					        bust2[4] = true;
							playersDraw[5] = true;
							break;
				        }
						else
						{
							bust2[4] = true;
							dealersDraw = true;
							break;
						}
			        }
			        else
			        {
						break;
			        }


					case 's':
					cout << playerName[4] << "stands." << endl;
					playersDraw[4] = false;
					if (numberOfPlayers >= 6)
				        {
							playersDraw[5] = true;
				        }
					else
						{
							dealersDraw = true;
						}
					break;

					case 'd':
	                cout << playerName[4] << " doubles down!" << endl;
			        doubleDown2[4] = true;
			        dealCards();
			        if (playerScore[4] > 21)
			        {
				       cout << "Current Score: " << playerScore[4] << endl;
				       cout << "Oh no! " << playerName[4] << " went bust!" << endl;
					   playersDraw[4] = false;
					   if (numberOfPlayers >= 6)
				        {
							bust2[4] = true;
							playersDraw[5] = true;
				        }
					else
						{
							bust2[4] = true;
							dealersDraw = true;
						}
				       break;
			        }
			        else
			        {
			cout << "Current Score: " << playerScore[4] << endl;
			playersDraw[4] = false;

					if (numberOfPlayers >= 6)
				        {
							playersDraw[5] = true;
				        }
					else
						{
							dealersDraw = true;
						}
			        }

                    break;

	            case 'q':
	            cout << playerName[4] << " surrenders." << endl;
			    playersDraw[4] = false;
				surrender2[4];
				playersDraw[4] = false;
				  if (numberOfPlayers >= 6)
				        {
							playersDraw[5] = true;
							break;
				        }
				  else
						{
							dealersDraw = true;
							break;
						}

               default:
               break;
					}
			}
			}
	}

					cout << "-----------------" << endl;
//player 6
	if (numberOfPlayers >= 6)
	{
		cout << "It's "<< playerName[5] << "'s turn!" << endl;
	if (playerScore[5] == 21 && playersRanks[5][0] != "Ten" && playersRanks[5][1] != "Ten") 
	{
		cout << playerName[5] << " got blackjack!" << endl;
		blackjack[5] = true;
		playersDraw[5] = false;
				if (numberOfPlayers >= 7)
				{
					playersDraw[6] = true;
				}
				else
				{
					dealersDraw = true;
				}
	}

while (playersDraw[5] == true && blackjack[5] == false && bust[5] == false && split[5] == false)
	{
		
	        cout << "Current Score: " << playerScore[5] << endl;
	        cout << "What will you do? [Hit(h)/Stand(s)/Double Down(d)/Split(x)/Surrender(q)]" << endl;

	        cin >> playerAction;
	        switch(playerAction) {

            case 'h':
	        cout << playerName[5] << " hits." << endl;
	        dealCards();
			if (playerScore[5] > 21)
			{
				cout << "Current Score: " << playerScore[5] << endl;
				cout << "Oh no! " << playerName[5] << " went bust!" << endl;
				playersDraw[5] = false;
				if (numberOfPlayers >= 7)
				{
					bust[5] = true;
					playersDraw[6] = true;
					break;
				}
				else
				{
					bust[5] = true;
					dealersDraw = true;
					break;
				}
			}
			else
			{
			  break;
			}

            case 's':
	        cout << playerName[5] << " stands." << endl;
			playersDraw[5] = false;
				if (numberOfPlayers >= 7)
				{
					playersDraw[6] = true;
				}
				else
				{
					dealersDraw = true;
				}
            break;


			case 'd':
	        cout << playerName[5] << " doubles down!" << endl;
			doubleDown[5] = true;
	        dealCards();
			if (playerScore[5] > 21)
			{
				cout << "Current Score: " << playerScore[5] << endl;
				cout << "Oh no! " << playerName[5] << " went bust!" << endl;
				playersDraw[5] = false;
				if (numberOfPlayers >= 7)
				{
					bust[5] = true;
					playersDraw[6] = true;
					break;
				}
				else
				{
					bust[5] = true;
					dealersDraw = true;
					break;
				}
			}
			else
			{
			cout << "Current Score: " << playerScore[5] << endl;
			playersDraw[5] = false;
			if (numberOfPlayers >= 7)
				{
					playersDraw[6] = true;
					break;
				}
				else
				{
					dealersDraw = true;
					break;
				}
			}


            case 'x':

			if (playersRanks[5][1] == playersRanks[5][1] && turnNumb == 1)
			{
				cout << playerName[5] << " splits his hand into two." << endl;
				if (playersRanks[5][0] == "Ace")
				{
					playerScore[5] = 11;
					playerScore2[5] = 11;
				}
				else
				{
					secondCardsValue[5] = playerScore[5] / 2;
					playerScore[5] = playerScore[5] /2;
					playerScore2[5] = playerScore[5];
				}
				playersCardsSplit[5][0] = playersCards[5][1];
				playersCards[5][1].clear();
				cardCounter[5] = 1;
				cardCounterSplit[5] = 1;
				split[5] = true;
				break;
				}

			else
			{
				cout << "Only player's who have two cards of the same rank on their first turn can split." << endl;
				break;
			}

	        case 'q':
	        cout << playerName[5] << " surrenders." << endl;
			playersDraw[5] = false;
				if (numberOfPlayers >= 7)
				{
					surrender[5] = true;
					playersDraw[6] = true;
				}
				else
				{
					surrender[5] = true;
					dealersDraw = true;
				}
				break;

            default:
            break;
	     }
		 }

				if (playersDraw[5] == true && blackjack[5] == false && bust[5] == false && split[5] == true && secondHandActive[5] == false)
				{
					cout << "Hand 1: " << endl;
					cout << "----------------" << endl;
					dealCards();
	           if (playerScore[5] == 21 && playersRanks[5][0] != "Ten" && playersRanks[5][1] != "Ten") 
	                {
		              cout << playerName[5] << " got blackjack!" << endl;
		              blackjack[5] = true;
					  secondHandActive[5] = true;
	                }

			   				while (playersDraw[5] == true && blackjack[5] == false && bust[5] == false && split[5] == true && secondHandActive[5] == false)
				    {

					cout << "Current Score: " << playerScore[5] << endl;
	                cout << "Dealer's Score: " << dealerScore << endl;
	                cout << "What will you do? [Hit(h)/Stand(s)/Double Down(d)/Surrender(q)]" << endl;
	                cin >> playerAction;
	                switch(playerAction) {
					
					case 'h':
	        cout << playerName[5] << " hits." << endl;
	        dealCards();
			if (playerScore[5] > 21)
			{
				cout << "Current Score: " << playerScore[5] << endl;
				cout << "Oh no! " << playerName[5] << " went bust!" << endl;
				secondHandActive[5] = true;
				break;
			}
			else
			{
			  break;
			}

					case 's':
					cout << playerName[5] << "stands." << endl;
					secondHandActive[5] = true;
					break;

					case 'd':
	        cout << playerName[5] << " doubles down!" << endl;
			doubleDown[5] = true;
	        dealCards();
			if (playerScore[5] > 21)
			{
				cout << "Current Score: " << playerScore[5] << endl;
				cout << "Oh no! " << playerName[5] << " went bust!" << endl;
				secondHandActive[5] = true;
				break;
			}
			else
			{
				cout << "Current Score: " << playerScore[5] << endl;
				secondHandActive[5] = true;
				break;
			}

	            case 'q':
	            cout << playerName[5] << " surrenders." << endl;
				surrender[5];
				secondHandActive[5] = true;
				break;

               default:
               break;
					}
			}


				}

				if (playersDraw[5] == true && split[5] == true && secondHandActive[5] == true)
				{
					cout << "Hand 2: " << endl;
					cout << "----------------" << endl;
					dealCards();

					if (playerScore2[5] == 21 && playersRanks2[5][0] != "Ten" && playersRanks2[5][1] != "Ten") 
	           {
		              cout << playerName[5] << " got blackjack!" << endl;
		              blackjack2[5] = true;
                playersDraw[5] = false;
				if (numberOfPlayers >= 7)
				 {
					playersDraw[6] = true;
				 }
				else
				 {
					dealersDraw = true;
				 }
				}
								while (playersDraw[5] == true && blackjack2[5] == false && split[5] == true && secondHandActive[5] == true)
				{
					cout << "Current Score: " << playerScore2[5] << endl;
	                cout << "Dealer's Score: " << dealerScore << endl;
	                cout << "What will you do? [Hit(h)/Stand(s)/Double Down(d)/Surrender(q)]" << endl;
	                cin >> playerAction;
	                switch(playerAction) {

					case 'h':
	                cout << playerName[5] << " hits." << endl;
	                dealCards();
			        if (playerScore2[5] > 21)
			        {
				        cout << "Current Score: " << playerScore[5] << endl;
				        cout << "Oh no! " << playerName[5] << " went bust!" << endl;
				        playersDraw[5] = false;
				        if (numberOfPlayers >= 7)
				        {
					        bust2[5] = true;
							playersDraw[6] = true;
							break;
				        }
						else
						{
							bust2[5] = true;
							dealersDraw = true;
							break;
						}
			        }
			        else
			        {
						break;
			        }


					case 's':
					cout << playerName[5] << "stands." << endl;
					playersDraw[5] = false;
					if (numberOfPlayers >= 7)
				        {
							playersDraw[6] = true;
				        }
					else
						{
							dealersDraw = true;
						}
					break;

					case 'd':
	                cout << playerName[5] << " doubles down!" << endl;
			        doubleDown2[5] = true;
			        dealCards();
			        if (playerScore[5] > 21)
			        {
				       cout << "Current Score: " << playerScore[5] << endl;
				       cout << "Oh no! " << playerName[5] << " went bust!" << endl;
					   playersDraw[5] = false;
					   if (numberOfPlayers >= 7)
				        {
							bust2[5] = true;
							playersDraw[6] = true;
				        }
					else
						{
							bust2[5] = true;
							dealersDraw = true;
						}
				       break;
			        }
			        else
			        {
			cout << "Current Score: " << playerScore[5] << endl;
			playersDraw[5] = false;

					if (numberOfPlayers >= 7)
				        {
							playersDraw[6] = true;
				        }
					else
						{
							dealersDraw = true;
						}
			        }

                    break;

	            case 'q':
	            cout << playerName[5] << " surrenders." << endl;
			    playersDraw[5] = false;
				surrender2[5];
				playersDraw[5] = false;
				  if (numberOfPlayers >= 7)
				        {
							playersDraw[6] = true;
							break;
				        }
				  else
						{
							dealersDraw = true;
							break;
						}

               default:
               break;
					}
			}
			}
	}

	cout << "-----------------" << endl;
//player 7
	if (numberOfPlayers >= 7)
	{
		cout << "It's "<< playerName[6] << "'s turn!" << endl;
	if (playerScore[6] == 21 && playersRanks[6][0] != "Ten" && playersRanks[6][1] != "Ten") 
	{
		cout << playerName[6] << " got blackjack!" << endl;
		blackjack[6] = true;
		playersDraw[6] = false;
		dealersDraw = true;

	}

while (playersDraw[6] == true && blackjack[6] == false && bust[6] == false && split[6] == false)
	{
		
	        cout << "Current Score: " << playerScore[6] << endl;
	        cout << "What will you do? [Hit(h)/Stand(s)/Double Down(d)/Split(x)/Surrender(q)]" << endl;

	        cin >> playerAction;
	        switch(playerAction) {

            case 'h':
	        cout << playerName[6] << " hits." << endl;
	        dealCards();
			if (playerScore[6] > 21)
			{
				cout << "Current Score: " << playerScore[6] << endl;
				cout << "Oh no! " << playerName[6] << " went bust!" << endl;
				playersDraw[6] = false;
				bust[6] = true;
				dealersDraw = true;
				break;
			}
			else
			{
			  break;
			}

            case 's':
	        cout << playerName[6] << " stands." << endl;
			playersDraw[6] = false;
			dealersDraw = true;
            break;


			case 'd':
	        cout << playerName[6] << " doubles down!" << endl;
			doubleDown[6] = true;
	        dealCards();
			if (playerScore[6] > 21)
			{
				cout << "Current Score: " << playerScore[6] << endl;
				cout << "Oh no! " << playerName[6] << " went bust!" << endl;
				playersDraw[6] = false;

					bust[6] = true;
					dealersDraw = true;
					break;
			}
			else
			{
			cout << "Current Score: " << playerScore[6] << endl;
			playersDraw[6] = false;

					dealersDraw = true;
					break;

			}


            case 'x':

			if (playersRanks[6][1] == playersRanks[6][1] && turnNumb == 1)
			{
				cout << playerName[6] << " splits his hand into two." << endl;
				if (playersRanks[6][0] == "Ace")
				{
					playerScore[6] = 11;
					playerScore2[6] = 11;
				}
				else
				{
					secondCardsValue[6] = playerScore[6] / 2;
					playerScore[6] = playerScore[6] /2;
					playerScore2[6] = playerScore[6];
				}
				playersCardsSplit[6][0] = playersCards[6][1];
				playersCards[6][1].clear();
				cardCounter[6] = 1;
				cardCounterSplit[6] = 1;
				split[6] = true;
				break;
				}

			else
			{
				cout << "Only player's who have two cards of the same rank on their first turn can split." << endl;
				break;
			}

	        case 'q':
	        cout << playerName[6] << " surrenders." << endl;
			playersDraw[6] = false;
					surrender[6] = true;
					dealersDraw = true;
				break;

            default:
            break;
	     }
		 }

				if (playersDraw[6] == true && blackjack[6] == false && bust[6] == false && split[6] == true && secondHandActive[6] == false)
				{
					cout << "Hand 1: " << endl;
					cout << "----------------" << endl;
					dealCards();
	           if (playerScore[6] == 21 && playersRanks[6][0] != "Ten" && playersRanks[6][1] != "Ten") 
	                {
		              cout << playerName[6] << " got blackjack!" << endl;
		              blackjack[6] = true;
					  secondHandActive[6] = true;
	                }

			   				while (playersDraw[6] == true && blackjack[6] == false && bust[6] == false && split[6] == true && secondHandActive[6] == false)
				    {

					cout << "Current Score: " << playerScore[6] << endl;
	                cout << "Dealer's Score: " << dealerScore << endl;
	                cout << "What will you do? [Hit(h)/Stand(s)/Double Down(d)/Surrender(q)]" << endl;
	                cin >> playerAction;
	                switch(playerAction) {
					
					case 'h':
	        cout << playerName[6] << " hits." << endl;
	        dealCards();
			if (playerScore[6] > 21)
			{
				cout << "Current Score: " << playerScore[6] << endl;
				cout << "Oh no! " << playerName[6] << " went bust!" << endl;
				secondHandActive[6] = true;
				break;
			}
			else
			{
			  break;
			}

					case 's':
					cout << playerName[6] << "stands." << endl;
					secondHandActive[6] = true;
					break;

					case 'd':
	        cout << playerName[6] << " doubles down!" << endl;
			doubleDown[6] = true;
	        dealCards();
			if (playerScore[6] > 21)
			{
				cout << "Current Score: " << playerScore[6] << endl;
				cout << "Oh no! " << playerName[6] << " went bust!" << endl;
				secondHandActive[6] = true;
				break;
			}
			else
			{
				cout << "Current Score: " << playerScore[6] << endl;
				secondHandActive[6] = true;
				break;
			}

	            case 'q':
	            cout << playerName[6] << " surrenders." << endl;
				surrender[6];
				secondHandActive[6] = true;
				break;

               default:
               break;
					}
			}


				}

				if (playersDraw[6] == true && split[6] == true && secondHandActive[6] == true)
				{
					cout << "Hand 2: " << endl;
					cout << "----------------" << endl;
					dealCards();

					if (playerScore2[6] == 21 && playersRanks2[6][0] != "Ten" && playersRanks2[6][1] != "Ten") 
	           {
		              cout << playerName[6] << " got blackjack!" << endl;
		              blackjack2[6] = true;
                playersDraw[6] = false;
					dealersDraw = true;
				}
								while (playersDraw[6] == true && blackjack2[6] == false && split[6] == true && secondHandActive[6] == true)
				{
					cout << "Current Score: " << playerScore2[6] << endl;
	                cout << "Dealer's Score: " << dealerScore << endl;
	                cout << "What will you do? [Hit(h)/Stand(s)/Double Down(d)/Surrender(q)]" << endl;
	                cin >> playerAction;
	                switch(playerAction) {

					case 'h':
	                cout << playerName[6] << " hits." << endl;
	                dealCards();
			        if (playerScore2[6] > 21)
			        {
				        cout << "Current Score: " << playerScore[6] << endl;
				        cout << "Oh no! " << playerName[6] << " went bust!" << endl;
				        playersDraw[6] = false;
							bust2[6] = true;
							dealersDraw = true;
							break;
			        }
			        else
			        {
						break;
			        }


					case 's':
					cout << playerName[6] << "stands." << endl;
					playersDraw[6] = false;
					dealersDraw = true;
					break;

					case 'd':
	                cout << playerName[6] << " doubles down!" << endl;
			        doubleDown2[6] = true;
			        dealCards();
			        if (playerScore[6] > 21)
			        {
				       cout << "Current Score: " << playerScore[6] << endl;
				       cout << "Oh no! " << playerName[6] << " went bust!" << endl;
					   playersDraw[6] = false;
							bust2[6] = true;
							dealersDraw = true;
				       break;
			        }
			        else
			        {
			cout << "Current Score: " << playerScore[6] << endl;
			playersDraw[6] = false;
							dealersDraw = true;
			        }

                    break;

	            case 'q':
	            cout << playerName[6] << " surrenders." << endl;
			    playersDraw[6] = false;
				surrender2[6];
				playersDraw[6] = false;
							dealersDraw = true;
							break;

               default:
               break;
					}
			}
			}
	}
	//checks to see if it's the dealer's turn
	if (dealersDraw == true)
	{
		//causes the dealer to deal more cards to himself is he is at or below 16.
		while (dealerScore <=16)
		{
			dealCards();
			Sleep(1000);
		}


		//checks to see if the dealer has a higher score than the player: the check to see if the player score is above 0
		//is so that players who are not playing are discounted.
		if (dealerScore > playerScore[0] && playerScore[0] > 0)
			{
				if (doubleDown[0] = true)
				{
					cout << "The dealer beat " << playerName[0] << "." << endl;
					playersPoints[0] = playersPoints[0] - 20;
				}
				else
				{
					cout << "The dealer beat " << playerName[0] << "." << endl;
					playersPoints[0] = playersPoints[0] - 10;
				}
		    }

		if (dealerScore > playerScore[1] && playerScore[1] > 0)
			{
				if (doubleDown[1] = true)
				{
					cout << "The dealer beat " << playerName[1] << "." << endl;
					playersPoints[1] = playersPoints[1] - 20;
				}
				else
				{
					cout << "The dealer beat " << playerName[1] << "." << endl;
					playersPoints[1] = playersPoints[1] - 10;
				}
		    }

		if (dealerScore > playerScore[2] && playerScore[2] > 0)
			{
				if (doubleDown[2] = true)
				{
					cout << "The dealer beat " << playerName[2] << "." << endl;
					playersPoints[2] = playersPoints[2] - 20;
				}
				else
				{
					cout << "The dealer beat " << playerName[2] << "." << endl;
					playersPoints[2] = playersPoints[2] - 10;
				}
		    }

		
		if (dealerScore > playerScore[3] && playerScore[3] > 0)
			{
				if (doubleDown[3] = true)
				{
					cout << "The dealer beat " << playerName[3] << "." << endl;
					playersPoints[3] = playersPoints[3] - 20;
				}
				else
				{
					cout << "The dealer beat " << playerName[3] << "." << endl;
					playersPoints[3] = playersPoints[3] - 10;
				}
		    }

		if (dealerScore > playerScore[4] && playerScore[4] > 0)
			{
				if (doubleDown[4] = true)
				{
					cout << "The dealer beat " << playerName[4] << "." << endl;
					playersPoints[4] = playersPoints[4] - 20;
				}
				else
				{
					cout << "The dealer beat " << playerName[4] << "." << endl;
					playersPoints[4] = playersPoints[4] - 10;
				}
		    }

		if (dealerScore > playerScore[5] && playerScore[5] > 0)
			{
				if (doubleDown[5] = true)
				{
					cout << "The dealer beat " << playerName[5] << "." << endl;
					playersPoints[5] = playersPoints[5] - 20;
				}
				else
				{
					cout << "The dealer beat " << playerName[5] << "." << endl;
					playersPoints[5] = playersPoints[5] - 10;
				}
		    }

		if (dealerScore > playerScore[6] && playerScore[6] > 0)
			{
				if (doubleDown[6] = true)
				{
					cout << "The dealer beat " << playerName[6] << "." << endl;
					playersPoints[6] = playersPoints[6] - 20;
				}
				else
				{
					cout << "The dealer beat " << playerName[6] << "." << endl;
					playersPoints[6] = playersPoints[6] - 10;
				}
		    }

				if (dealerScore < playerScore[0] && playerScore[0] > 0)
			{
				if (doubleDown[0] = true)
				{
					playersPoints[0] = playersPoints[0] + 20;
				}
				else
				{
					playersPoints[0] = playersPoints[0] + 10;
				}
				cout << playerName[0] <<" beat the dealer." << endl;
		    }

				//checks if the player has beat the dealer.
		if (dealerScore < playerScore[1] && playerScore[1] > 0)
			{
				if (doubleDown[1] = true)
				{
					playersPoints[1] = playersPoints[1] + 20;
				}
				else
				{
					playersPoints[1] = playersPoints[1] + 10;
				}
				cout << playerName[1] <<" beat the dealer." << endl;
		    }

		if (dealerScore < playerScore[2] && playerScore[2] > 0)
			{
				if (doubleDown[2] = true)
				{
					playersPoints[2] = playersPoints[2] + 20;
				}
				else
				{
					playersPoints[2] = playersPoints[2] + 10;
				}
				cout << playerName[2] <<" beat the dealer." << endl;
		    }

		
		if (dealerScore < playerScore[3] && playerScore[3] > 0)
			{
				if (doubleDown[3] = true)
				{
					playersPoints[3] = playersPoints[3] + 20;
				}
				else
				{
					playersPoints[3] = playersPoints[3] + 10;
				}
				cout << playerName[3] <<" beat the dealer." << endl;
		    }

		if (dealerScore < playerScore[4] && playerScore[4] > 0)
			{
				if (doubleDown[4] = true)
				{
					playersPoints[4] = playersPoints[4] + 20;
				}
				else
				{
					playersPoints[4] = playersPoints[4] + 10;
				}
				cout << playerName[4] <<" beat the dealer." << endl;
		    }

		if (dealerScore < playerScore[5] && playerScore[5] > 0)
			{
				if (doubleDown[5] = true)
				{
					playersPoints[5] = playersPoints[5] + 20;
				}
				else
				{
					playersPoints[5] = playersPoints[5] + 10;
				}
				cout << playerName[5] <<" beat the dealer." << endl;
		    }

		if (dealerScore < playerScore[6] && playerScore[6] > 0)
			{
				if (doubleDown[6] = true)
				{
					playersPoints[6] = playersPoints[6] + 20;
				}
				else
				{
					playersPoints[6] = playersPoints[6] + 10;
				}
				cout << playerName[6] <<" beat the dealer." << endl;
		    }

		//checks for a tie/push
		if (dealerScore == playerScore[0] && blackjack[0] == false && blackjack[8] == false)
			{
				playersPoints[0] = playersPoints[0] + 5;
				cout << playerName[0] <<" tied with the dealer." << endl;
		    }

		if (dealerScore == playerScore[1] && blackjack[1] == false && blackjack[8] == false)
			{
				playersPoints[1] = playersPoints[1] + 5;
				cout << playerName[0] <<" tied with the dealer." << endl;
		    }

		if (dealerScore == playerScore[2] && blackjack[2] == false && blackjack[8] == false)
			{
				playersPoints[2] = playersPoints[2] + 5;
				cout << playerName[0] <<" tied with the dealer." << endl;
		    }

		if (dealerScore == playerScore[3] && blackjack[3] == false && blackjack[8] == false)
			{
				playersPoints[3] = playersPoints[3] + 5;
				cout << playerName[0] <<" tied with the dealer." << endl;
		    }

		if (dealerScore == playerScore[4] && blackjack[4] == false && blackjack[8] == false)
			{
				playersPoints[4] = playersPoints[4] + 5;
				cout << playerName[0] <<" tied with the dealer." << endl;
		    }

		if (dealerScore == playerScore[5] && blackjack[5] == false && blackjack[8] == false)
			{
				playersPoints[5] = playersPoints[5] + 5;
				cout << playerName[0] <<" tied with the dealer." << endl;
		    }

		if (dealerScore == playerScore[6] && blackjack[6] == false && blackjack[8] == false)
			{
				playersPoints[6] = playersPoints[6] + 5;
				cout << playerName[0] <<" tied with the dealer." << endl;
		    }
		//calculates the number of games
		numberOfGames = numberOfGames - 1;

		if (numberOfGames == 0)
		{
			cout << "Game Over." << endl;
		}
		if (numberOfGames >= 1)
		{
			fill(playerScore, playerScore+7, 0);
			fill(cardCounter, cardCounter+7, 0);
			cardCounterDealer = 0;

			playersDraw[0] = true;
			playersDraw[1] = false;
			playersDraw[2] = false;
			playersDraw[3] = false;
			playersDraw[4] = false;
			playersDraw[5] = false;
			playersDraw[6] = false;
			dealersDraw = false;

			turnNumb = 0;

			system("pause");
			system("cls");
			goto beginning;
		}

	}

}
