#include <iostream>
#include <algorithm>
#include <tr1/random>
#include <ctime>
#include "Card.hxx"
#include <array>


class Deck
{
protected:
   // Some card deck constants.
   static const int CARDS_IN_DECK = 52;
   static const int SUITS_IN_DECK = 4;
   static const int CARDS_IN_SUIT = 13;

   unsigned positionInDeck;
   std::array<spc_type,CARDS_IN_DECK> deck;

public:
   Deck() : positionInDeck(0)  // Deck constructor.
   {
      int c = 0;
      for(int s = 0; s < 4; ++s)
	 for(int r = 1; r <= 13; ++r)
	 {
	    deck[c++] = spc_type (new Card(Rank(r), Suit(s)));
	    //deck[c].reset();
	 }
   }

   void swap(int i, int j)
   {
      deck[i].swap(deck[j]);
   }

   void showDeck()
   {
      // for_each using lambda function.
      /*
      for_each(
	 deck, deck+CARDS_IN_DECK,
	 [](spc_type& c) { if (c) c->showCard(); cout << endl; }
//	 [](auto c) { if (c) c->showCard(); cout << endl; }
      );
      */

      // Range based for loop.
      for(auto &c: deck)
      {
	 c->showCard();
	 std::cout << std::endl;
      }
   }

   void shuffle()
   {
      std::tr1::mt19937 gen(std::time(0));
      std::tr1::uniform_real<> dist(1,51);
      std::tr1::variate_generator< mt19937&, uniform_real<> > rnd(gen, dist);

      int pos;
      for(int i = 0; i < CARDS_IN_DECK; ++i)
      {
	 pos = rnd();
	 spc_type c = deck[pos];
	 deck[pos] = deck[i];
	 deck[i] = c;
      }
   }

   spc_type dealTopCard()
   {
      if(positionInDeck < CARDS_IN_DECK)
	 return deck[positionInDeck++];
      else
	 return deck[0];
   }

}; // Deck class


