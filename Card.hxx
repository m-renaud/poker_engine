#ifndef __MRR_CARD_HXX__
#define __MRR_CARD_HXX__

//===========================================================================
// Card implementation for use in poker engine.
// Author: Matt Renaud - mrenaud92@gmail.com
//===========================================================================

#include <iostream>
#include <map>
#include <string>

#include "Traits.hxx"

enum Suit { SPADES = 0, HEARTS, DIAMONDS, CLUBS, JOKER };
enum Rank { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
	    TEN, JACK, QUEEN, KING, ACE };

class Card
{
private:

  std::map<Suit, std::string> suit2string;
  std::map<Rank, std::string> rank2string;

public:
  Rank rank_;
  Suit suit_;
  Card() : rank_(KING), suit_(JOKER){ }
  Card(Card const& c) : rank_(c.rank_), suit_(c.suit_) { }
  Card(Rank r, Suit s) : rank_(r), suit_(s)
  {
    suit2string =
    {
      {SPADES,   "spades"  },
      {HEARTS,   "hearts"  },
      {DIAMONDS, "diamonds"},
      {CLUBS,    "clubs"   }
    };
    rank2string =
    {
      {ACE,   "ace"  },
      {TWO,   "two"  },
      {THREE, "three"},
      {FOUR,  "four" },
      {FIVE,  "five" },
      {SIX,   "six"  },
      {SEVEN, "seven"},
      {EIGHT, "eight"},
      {NINE,  "nine" },
      {TEN,   "ten"  },
      {JACK,  "jack" },
      {QUEEN, "queen"},
      {KING,  "king" }
    };
  }

  Card& operator = (Card const& c)
  {
    rank_ = c.rank_;
    suit_ = c.suit_;
    return *this;
  }

  std::ostream& showCard(std::ostream& os) const
  {
    auto r = rank2string.find(rank_);
    if (r == rank2string.end())
      return os;

    auto s = suit2string.find(suit_);
    if (s == suit2string.end())
      return os;

    os
    << r->second
    << " of "
    << s->second
    ;

    return os;
  }
};

bool operator < (card_type const& lhs, card_type const& rhs)
{
  return (lhs->rank_ < rhs->rank_);
}

bool operator == (card_type const& lhs, card_type const& rhs)
{
  return (lhs->rank_ == rhs->rank_);
}

std::ostream& operator << (std::ostream& os, card_type const& c)
{
  c->showCard(os);
  return os;
}

//===========================================================================
struct sort_ordinal_suit
{
  bool operator ()(card_type const& c1, card_type const& c2) const
  {
    if(c1->rank_ < c2->rank_)
      return true;
    else if(c1->rank_ == c2->rank_)
      return c1->suit_ < c2->suit_;
    else
      return false;
  }
};

struct sort_suit_ordinal
{
  bool operator ()(card_type const& c1, card_type const& c2) const
  {
    if(c1->suit_ < c2->suit_)
      return true;
    else if(c1->suit_ == c2->suit_)
      return c1->rank_ < c2->rank_;
    else
      return false;
  }
};

#endif // __MRR_CARD_HXX__
