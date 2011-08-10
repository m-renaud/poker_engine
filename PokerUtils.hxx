#ifndef __MRR_POKER_UTILS_HXX__
#define __MRR_POKER_UTILS_HXX__

#include <vector>
#include <algorithm>

#include "Card.hxx"
#include "Hand.hxx"

Ranked_Hand rankHand(std::vector<spc_type> hand);

bool isFlush(std::vector<spc_type> hand);
bool isStraight(std::vector<spc_type> hand);


//===========================================================================
Ranked_Hand rankHand(std::vector<spc_type> hand)
{
  std::sort(hand.begin(), hand.end());

  bool is_flush = isFlush(hand);
  bool is_straight = isStraight(hand);

  if(is_straight && is_flush)
  {
    return Straight_Flush_Hand(hand.back());
  }

  if(is_straight)
    return Straight_Hand(hand.back());

  if(is_flush)
    return Flush_Hand(hand);

  return Straight_Hand(hand.back());
}

//===========================================================================
bool isFlush(std::vector<spc_type> hand)
{
  Suit s = hand.front()->suit_;
  for(unsigned i = 1; i < hand.size(); ++i)
    if(hand[i]->suit_ != s)
      return false;

  return true;
}

//===========================================================================
bool isStraight(std::vector<spc_type> hand)
{
  int r = static_cast<int>(hand.front()->rank_);
  for(int i = 1; i < hand.size(); ++i)
  {
    if(hand[i]->rank_ != (r + 1))
      return false;
    ++r;
  }
  return true;
}

#endif // __MRR_POKER_UTILS_HXX__
