#ifndef __MRR_POKER_HXX__
#define __MRR_POKER_HXX__

#include "Card.hxx"
#include "Hand.hxx"
#include "Deck.hxx"
#include "PokerUtils.hxx"

typedef std::vector<spc_type> HAND;

enum SORT_CRITERIA {SUIT = 0, RANK = 1};

std::ostream& operator << (std::ostream& os, HAND const& h)
{
  for(auto &c: h)
    os << c << " - ";

  return os;
}


template <unsigned Players>
class Poker
{
  Deck *deck;
  std::vector<HAND> hand;
  std::vector<Ranked_Hand> rankedHand;

public:
  Poker()
  {
    deck = new Deck();
    deck->shuffle();
  }

  template <unsigned Cards>
  void deal()
  {
    std::cout << "In Poker::deal()" << std::endl;
    for(unsigned i = 0; i < Players; ++i)
    {
      hand.push_back(deck->dealHand<Cards>());
    }
  }


  void showHands()
  {
    std::cout << "In Poker::showHands()" << std::endl;
    for(auto &h: hand)
      std::cout << h << std::endl;
  }

  void sortHands(SORT_CRITERIA criteria)
  {
    if(criteria == SUIT)
    {
      for(auto &h: hand)
	std::sort(h.begin(), h.end(), sort_suit_ordinal());
    }
    else
    {
      for(auto &h: hand)
	std::sort(h.begin(), h.end(), sort_ordinal_suit());
    }
  }


};


#endif // #ifndef __MRR_POKER_HXX__
