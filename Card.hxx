#ifndef __CARD_HXX__
#define __CARD_HXX__

#include <iostream>
#include <map>
#include <string>
#include <memory>


enum Suit { SPADES = 0, HEARTS, DIAMONDS, CLUBS, JOKER };
enum Rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE
	    , TEN, JACK, QUEEN, KING };

class Card
{
private:

  std::map<Suit, std::string> suit2string;
  std::map<Rank, std::string> rank2string;

public:
  Rank rank_;
  Suit suit_;
  Card() { }
  Card(Rank r, Suit s) : rank_(r), suit_(s)
  {
    suit2string =
    {
      {SPADES, "spades"},
      {HEARTS, "hearts"},
      {DIAMONDS, "diamonds"},
      {CLUBS, "clubs"}
    };
    rank2string =
    {
      {ACE, "ace"},
      {TWO, "two"},
      {THREE, "three"},
      {FOUR, "four"},
      {FIVE, "five"},
      {SIX, "six"},
      {SEVEN, "seven"},
      {EIGHT, "eight"},
      {NINE,  "nine"},
      {TEN, "ten"},
      {JACK, "jack"},
      {QUEEN, "queen"},
      {KING, "king"}
    };
  }

  void showCard()
  {
    auto r = rank2string.find(rank_);
    if (r == rank2string.end())
      return;

    auto s = suit2string.find(suit_);
    if (s == suit2string.end())
      return;

    std::cout
    << r->second
    << " of "
    << s->second
    ;
  }
};

typedef std::shared_ptr<Card> spc_type;

bool operator < (spc_type const& lhs, spc_type const& rhs)
{
  return (lhs->rank_ < rhs->rank_);
}

bool operator == (spc_type const& lhs, spc_type const& rhs)
{
  return (lhs->rank_ == rhs->rank_);
}
#endif
