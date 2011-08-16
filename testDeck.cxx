#include <iostream>

#include "Card.hxx"
#include "Hand.hxx"
#include "Deck.hxx"
#include "PokerUtils.hxx"
#include "Traits.hxx"

int main()
{
  Deck d;
  std::vector<hand> h;
  std::vector<Ranked_Hand> rh;

  d.shuffle();

  for(unsigned i = 0; i < 4; ++i)
  {
    h.push_back(d.dealHand<5>());
    for(auto &c: h[i])
      std::cout << c << ", ";

    std::cout << std::endl;

    rh.push_back(rankHand(h[i]));
    std::cout << rh[i] << std::endl << std::endl;
  }

  std::cout << "==================================================" << std::endl
	    << "Sorted"                                             << std::endl
	    << "==================================================" << std::endl;

  std::sort(rh.begin(), rh.end());

  for(auto &h: rh)
    std::cout << h << std::endl;



}

