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
    unsigned c = 0;
    for(unsigned s = 0; s < 4; ++s)
      for(unsigned r = 2; r <= 14; ++r)
      {
	deck[c++] = spc_type (new Card(Rank(r), Suit(s)));
	//deck[c].reset();
      }
  }

  void swap(unsigned i, unsigned j)
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
    for(spc_type &c: deck)
    {
      std::cout << c;
      std::cout << std::endl;
    }
  }

  void shuffle()
  {
    using std::tr1::mt19937;
    using std::tr1::uniform_int;
    using std::tr1::variate_generator;

    mt19937 gen(std::time(0));
    uniform_int<> dist(1,51);
    variate_generator<mt19937&, uniform_int<> > rnd(gen, dist);

    int pos;
    for(unsigned i = 0; i < CARDS_IN_DECK; ++i)
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

  template <unsigned N>
  std::vector<spc_type> dealHand ()
  {
    std::vector<spc_type> hand;
    for(unsigned i = 0; i < N; ++i)
    {
      hand.push_back(dealTopCard());
    }

    return hand;
  }


}; // Deck class


