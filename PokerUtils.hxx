#include <array>

#include "Card.hxx"
#include "Hand.hxx"


Ranked_Hand rankHand(std::array<spc_type, 5> hand)
{
  return Straight_Hand(TEN);
}
