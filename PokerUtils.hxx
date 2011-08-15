#ifndef __MRR_POKER_UTILS_HXX__
#define __MRR_POKER_UTILS_HXX__

#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <set>

#include "Card.hxx"
#include "Hand.hxx"

Ranked_Hand rankHand(std::vector<spc_type> hand);
bool isStraight(std::vector<spc_type> hand);

typedef std::map<Rank, unsigned> RANK_HIST;
typedef std::map<RANK_HIST::mapped_type, std::set<RANK_HIST::key_type> > REV_RANK_HIST;

typedef std::map<Suit, unsigned> SUIT_HIST;
typedef std::map<SUIT_HIST::mapped_type, std::set<SUIT_HIST::key_type> > REV_SUIT_HIST;


//===========================================================================
Ranked_Hand rankHand(std::vector<spc_type> hand)
{
  std::sort(hand.begin(), hand.end());

  // Create a rank and suit histogram.
  RANK_HIST rank_hist;
  SUIT_HIST suit_hist;
  {
    std::vector<spc_type>::iterator i = hand.begin();
    std::vector<spc_type>::iterator iEnd = hand.end();
    for(; i != iEnd; ++i)
    {
      ++rank_hist[(*i)->rank_];
      ++suit_hist[(*i)->suit_];
    }
  }


  // Reverse the suit and rank histograms.
  REV_RANK_HIST rev_rank_hist;
  for_each(rank_hist.begin(), rank_hist.end(),
	   [&rev_rank_hist](RANK_HIST::value_type const& i)
	   {
	     rev_rank_hist.insert(make_pair(i.second, REV_RANK_HIST::mapped_type())).first->second.insert(i.first);
	   });

  REV_SUIT_HIST rev_suit_hist;
  for_each(suit_hist.begin(), suit_hist.end(),
	   [&rev_suit_hist](SUIT_HIST::value_type const& i)
	   {
	     rev_suit_hist.insert(make_pair(i.second, REV_SUIT_HIST::mapped_type())).first->second.insert(i.first);
	   });

  auto rsh_end = rev_suit_hist.end();
  auto rrh_end = rev_rank_hist.end();

  // Check whether the hand is a straight or flush.
  bool is_flush = rev_suit_hist.find(5) != rsh_end;
  bool is_straight = isStraight(hand);

  if(is_straight && is_flush)
    return Straight_Flush_Hand(hand);

  if(is_straight)
    return Straight_Hand(hand);

  if(is_flush)
    return Flush_Hand(hand);

  auto foak_iter = rev_rank_hist.find(4);
  auto toak_iter = rev_rank_hist.find(3);
  auto pair_iter = rev_rank_hist.find(2);

#if 0 // Good practice for finding in a histogram.
  auto toak_iter = pair_iter != rrh_end ? ++REV_RANK_HIST::iterator(pair_iter) : rrh_end;
  auto foak_iter = toak_iter != rrh_end ? ++REV_RANK_HIST::iterator(toak_iter) : rrh_end;

  // look for a 3 or 4 or set to end if not...
  if (toak_iter != rrh_end && toak_iter->first == 4)
  {
    foak_iter = toak_iter;
    toak_iter = rrh_end;
  } else if (toak_iter != rrh_end && toak_iter != 3)
    toak_iter = foak_iter = rrh_end;
  else if (foak_iter != rrh_end && foak_iter != 4)
    foak_iter = rrh_end;
#endif


  if(foak_iter != rrh_end)
    return Four_Of_A_Kind_Hand(*(foak_iter->second.begin()), hand);

  if(toak_iter != rrh_end && pair_iter != rrh_end)
    return Full_House_Hand(*(toak_iter->second.begin()),
			   *(pair_iter->second.begin()),
			   hand);

  if(pair_iter != rrh_end)
    if(pair_iter->second.size() == 2)
      return Two_Pair_Hand(*(pair_iter->second.begin()),
			   *(++pair_iter->second.begin()),
			   *(rev_rank_hist[1].begin()),
			   hand);

  if(toak_iter != rrh_end)
    return Three_Of_A_Kind_Hand(*(toak_iter->second.begin()), hand);

  if(pair_iter != rrh_end)
    return Pair_Hand(*(pair_iter->second.begin()),
		     *(rev_rank_hist[1].begin()),
		     *(++rev_rank_hist[1].begin()),
		     *(++ ++rev_rank_hist[1].begin()),
		     hand);

  return Hand(hand);
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
