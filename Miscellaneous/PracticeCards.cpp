#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

struct Card
{
	std::string suit;
	std::string key;
};

class Deck
{
public:
	Deck();
	Deck( int );
	~Deck();
	// Card drawCard( int );
	Card drawCard();
	Card drawRandomCard();
	void shuffleDeck();
	void printDeck();
	void buildDeck();
	void drawDeck();
	int deckSize;
private:
	std::vector< Card > deck;
	std::vector< Card > discardPile;

};

// Build a data structure that can store the contents of a playing card, enough to fill a deck; print in order: hearts, diamonds, spades, clubs

Deck::Deck()
{
	deckSize = 52;
}

Deck::Deck( int size )
{
	deckSize = size;
}

Deck::~Deck()
{

}

Card fixKey( Card newCard )
{
	if ( newCard.key == "1")
	{
		newCard.key = "A";
		return newCard;
	}

	else if ( newCard.key == "11" )
	{
		newCard.key = "J";
		return newCard;
	}

	else if ( newCard.key == "12" )
	{
		newCard.key = "Q";
		return newCard;
	}

	else if ( newCard.key == "0" )
	{
		newCard.key = "K";
		return newCard;
	}

	else
	{
		return newCard;
	}
}

void Deck::buildDeck( )
{
	std::string suit = "Hearts";
	for ( int i = 1; i < deckSize + 1; ++i )
	{
		Card newCard;
		newCard.key = std::to_string(i % 13);
		if ( i > 13 )
		{
			suit = "Diamonds";
		}
		if ( i > 26 )
		{
			suit = "Spades";
		}
		if ( i > 39 )
		{
			suit = "Clubs";
		}
		newCard.suit = suit;
		newCard = fixKey( newCard );
		deck.push_back( newCard );
	}
}

void Deck::printDeck( )
{
	if ( deckSize == 0 )
	{
		std::cout << "The deck is empty" << std::endl;
	}

	for ( int i = 0; i < deckSize; ++i )
	{
		std::string cardName = deck[ i ].key + " of " + deck[ i ].suit;
		std::cout << "Current card: " << deck[ i ].key << " of " << deck[ i ].suit << std::endl;
	}
	std::cout << std::endl;
}

std::string printCard( Card newCard )
{
	std::string cardDescription = newCard.key + " of " + newCard.suit;
	return cardDescription;
}

Card Deck::drawCard()
{
	Card tmpCard = deck.front();
	std::cout << "Drawing Card: " << printCard( tmpCard ) << std::endl;
	discardPile.push_back( tmpCard );
	deck.erase( deck.begin() );
	return tmpCard;
}

// Card Deck::drawCard( int position )
// {
// 	if ( position >= deckSize )
// 	{
// 		std::cout << "Request is out-of-bounds" << std::endl;
// 		return drawCard();
// 	}
	
// 	Card tmpCard = deck[ position ];
// 	discardPile.push_back( tmpCard );
// 	deck.erase( deck.begin() + position );
// 	return tmpCard;
// }

void Deck::drawDeck()
{
	for (int i = 0; i < this->deckSize; ++i)
	{
		this->drawCard();
		// std::cout << drawCount++ << std::endl;
	}
}

Card Deck::drawRandomCard( )
{
	Card tmpCard = deck[ rand() % deckSize ];
	deckSize--;

	return tmpCard;
}

void Deck::shuffleDeck()
{
	std::cout << "======SHUFFLED DECK======" << std::endl;
	std::vector< Card > newDeck;
	while( !deck.empty() )
	{
		Card newCard = deck[ rand() % deckSize ];
		deckSize--;
		newDeck.push_back( newCard );
		this->deck.erase( deck.begin() );
	}

	deckSize = 52;

	this->deck = newDeck;
}

int main()
{
	srand( time( NULL ) );
	Deck myDeck;
	myDeck.buildDeck();
	myDeck.printDeck();
	// myDeck.drawDeck();
	myDeck.shuffleDeck();
	myDeck.printDeck();

	return 0;
}