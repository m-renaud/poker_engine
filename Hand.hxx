#ifndef __MRR_HAND_HXX__
#define __MRR_HAND_HXX__

//===========================================================================
// Hand class for representing and ranking poker hands.
// Author: Matt Renaud - mrenaud92@gmail.com
// Assistance from Paul Preney and Bryan St. Amour
//---------------------------------------------------------------------------

#include <vector>
#include <boost/variant.hpp>
#include <boost/optional.hpp>

#include "Card.hxx"
#include "PokerTraits.hxx"

//===========================================================================
template <typename T>
class Hand_Impl
{
public:

  hand_type hand_;
  Rank high_card_;

  explicit Hand_Impl()
  {
  }

  explicit Hand_Impl(hand_type const& h)
    : hand_(h), high_card_(h.front()->rank_)
  {
  }

  // Barton-Nackmann trick for output and comparison.
  friend std::ostream& operator << (std::ostream& os, T const& t)
  {
    return t.write_impl(os);
  }

  friend bool operator < (T const& lhs, T const& rhs)
  {
    return lhs.less_than_impl(rhs);
  }

  friend bool operator == (T const& lhs, T const& rhs)
  {
    return lhs.equal_impl(rhs);
  }
};

//===========================================================================
// Basic hand class
//---------------------------------------------------------------------------
class Hand
  : public Hand_Impl<Hand>
{
public:
  Hand(hand_type const& h)
  {
    Hand_Impl<Hand>::hand_ = h;
  }
  std::ostream& write_impl(std::ostream& os) const
  {
    os << "Hand";
    return os;
  }

  bool less_than_impl(Hand const& rhs) const
  {
    auto i = hand_.rbegin();
    auto iEnd = hand_.rend();
    auto rhsi = rhs.hand_.rbegin();
    for(; i != iEnd; ++i, ++rhsi)
    {
      if((*i)->rank_ < (*rhsi)->rank_)
	return true;
    }
    return false;
  }

  bool equal_impl(Hand const& rhs) const
  {
    auto i = hand_.rbegin();
    auto iEnd = hand_.rend();
    auto rhsi = rhs.hand_.rbegin();
    for(; i != iEnd; ++i, ++rhsi)
    {
      if((*i)->rank_ != (*rhsi)->rank_)
	return false;
    }
    return true;
  }
};


//===========================================================================
// Pair Hand Class
//---------------------------------------------------------------------------
class Pair_Hand
  : public Hand_Impl<Pair_Hand>
{
public:
  Rank pair_rank_;
  Rank second_high_card_;
  Rank third_high_card_;

  Pair_Hand(Rank const& pr, Rank const& thc, Rank const& shc, Rank const& hc,
	    hand_type const& h)

    : pair_rank_(pr), second_high_card_(shc), third_high_card_(thc)
  {
    Hand_Impl<Pair_Hand>::hand_ = h;
    Hand_Impl<Pair_Hand>::high_card_ = hc;
  }
  // Barton-Nackmann
  std::ostream& write_impl(std::ostream& os) const
  {
    os << "Pair Hand:" << std::endl
       << "  Pair Rank: " << pair_rank_ << std::endl
       << "  High Card: " << high_card_ << std::endl
       << "  Second High Card : " << second_high_card_ << std::endl
       << "  Third High Card: " << third_high_card_;

    return os;
  }

  bool less_than_impl(Pair_Hand const& rhs) const
  {
    if(pair_rank_ < rhs.pair_rank_)
      return true;
    else if(pair_rank_ > rhs.pair_rank_)
      return false;
    else if(high_card_ < rhs.high_card_)
      return true;
    else if(high_card_ > rhs.high_card_)
      return false;
    else if(second_high_card_ < rhs.second_high_card_)
      return true;
    else if(second_high_card_ > rhs.second_high_card_)
      return true;
    else if(third_high_card_ < rhs.third_high_card_)
      return true;
    else
      return false;

  }

  bool equal_impl(Pair_Hand const& rhs) const
  {
    return (
      (pair_rank_ == rhs.pair_rank_) &&
      (high_card_ == rhs.high_card_) &&
      (second_high_card_ == rhs.second_high_card_) &&
      (third_high_card_ == rhs.third_high_card_ )
    );
  }
};



//===========================================================================
// Two Pair Hand Class
//---------------------------------------------------------------------------
class Two_Pair_Hand
  : public Hand_Impl<Two_Pair_Hand>
{
  Rank high_pair_rank_;
  Rank low_pair_rank_;

public:
  Two_Pair_Hand(Rank const& lpr, Rank const& hpr, Rank const& hc,
		hand_type const& h)
    : low_pair_rank_(lpr), high_pair_rank_(hpr)
  {
    Hand_Impl<Two_Pair_Hand>::high_card_ = hc;
    Hand_Impl<Two_Pair_Hand>::hand_ = h;
  }

  // Barton-Nackmann
  std::ostream& write_impl(std::ostream& os) const
  {
    os << "Two Pair Hand:" << std::endl
       << "  High Pair Rank: " << high_pair_rank_ << std::endl
       << "  Low Pair Rank: " << low_pair_rank_ << std::endl
       << "  High Card: " << high_card_;
    return os;
  }

  bool less_than_impl(Two_Pair_Hand const& rhs) const
  {
    if(high_pair_rank_ < rhs.high_pair_rank_)
      return true;
    else if (high_pair_rank_ > rhs.high_pair_rank_)
      return false;
    else if(low_pair_rank_ < rhs.low_pair_rank_)
      return true;
    else
      return false;
  }

  bool equal_impl(Two_Pair_Hand const& rhs) const
  {
    return (
      (high_pair_rank_ == rhs.high_pair_rank_) &&
      (low_pair_rank_ == rhs.low_pair_rank_) &&
      (high_card_ == rhs.high_card_)
    );
  }
};



//===========================================================================
// Three of a Kind Hand Class
//---------------------------------------------------------------------------
class Three_Of_A_Kind_Hand
  : public Hand_Impl<Three_Of_A_Kind_Hand>
{
  Rank triple_rank_;

public:
  Three_Of_A_Kind_Hand(Rank tr, hand_type const& h)
    : triple_rank_(tr)
  {
    Hand_Impl<Three_Of_A_Kind_Hand>::hand_ = h;
  }

  // Barton-Nackmann
  std::ostream& write_impl(std::ostream& os) const
  {
    os << "Three of a Kind Hand:" << std::endl
       << "  Triple Rank: " << triple_rank_;
    return os;
  }

  bool less_than_impl(Three_Of_A_Kind_Hand const& rhs) const
  {
    if(triple_rank_ < rhs.triple_rank_)
      return true;
    else
      return false;
  }

  bool equal_impl(Three_Of_A_Kind_Hand const& rhs) const
  {
    return false;
  }
};


//===========================================================================
// Straight Hand Class
//---------------------------------------------------------------------------
class Straight_Hand
  : public Hand_Impl<Straight_Hand>
{
    Rank high_card_in_straight_;

public:
  // Constructor for passing in pointer to the high card.
  Straight_Hand(hand_type const& h)
  {
    Hand_Impl<Straight_Hand>::high_card_ = h.back()->rank_;
    Hand_Impl<Straight_Hand>::hand_ = h;
  }

  // Barton-Nackmann
  std::ostream& write_impl(std::ostream& os) const
  {
    os << "Straight Hand:" << std::endl
       << "  High Card in Straight: " << high_card_in_straight_;
    return os;
  }

  bool less_than_impl(Straight_Hand const& rhs) const
  {
    return high_card_ < rhs.high_card_;
  }

  bool equal_impl(Straight_Hand const& rhs) const
  {
    return high_card_ == rhs.high_card_;
  }
};


//===========================================================================
// Flush Hand Class
//---------------------------------------------------------------------------
class Flush_Hand
  : public Hand_Impl<Flush_Hand>
{

public:
  Flush_Hand(hand_type const& h)
  {
    Hand_Impl<Flush_Hand>::hand_ = h;
  }

  // Barton-Nackmann
  std::ostream& write_impl(std::ostream& os) const
  {
    os << "Flush Hand:" << std::endl
       << "  Ranks: ";
    for_each(hand_.begin(), hand_.end(),
	     [&os](card_type const& c)
	     {
	       os << c->rank_ << " ";
	     });
    return os;
  }

  bool less_than_impl(Flush_Hand const& rhs) const
  {
    auto i = hand_.rbegin();
    auto iEnd = hand_.rend();
    auto rhsi = rhs.hand_.rbegin();
    for(; i != iEnd; ++i, ++rhsi)
    {
      if((*i)->rank_ < (*rhsi)->rank_)
	return true;
    }
    return false;
  }

  bool equal_impl(Flush_Hand const& rhs) const
  {
    auto i = hand_.rbegin();
    auto iEnd = hand_.rend();
    auto rhsi = rhs.hand_.rbegin();
    for(; i != iEnd; ++i, ++rhsi)
    {
      if((*i)->rank_ != (*rhsi)->rank_)
	return false;
    }
    return true;
  }
};

//===========================================================================
// Full House Hand Class
class Full_House_Hand
  : public Hand_Impl<Full_House_Hand>
{
  Rank triple_rank_;
  Rank pair_rank_;

public:
  // Constructor for passing in two shared pointers to cards.
  Full_House_Hand(Rank const& tr, Rank const& pr, hand_type const& h)
    : triple_rank_(tr), pair_rank_(pr)
  {
    Hand_Impl<Full_House_Hand>::hand_ = h;
  }

  // Barton-Nackmann
  std::ostream& write_impl(std::ostream& os) const
  {
    os << "Full House Hand" << std::endl
       << "  Triple Rank: " << triple_rank_ << std::endl
       << "  Pair Rank: " << pair_rank_;
    return os;
  }

  bool less_than_impl(Full_House_Hand const& rhs) const
  {
    return false;
  }

  bool equal_impl(Full_House_Hand const& rhs) const
  {
    return false;
  }
};


//===========================================================================
// Four of a Kind Hand Class
//---------------------------------------------------------------------------
class Four_Of_A_Kind_Hand
  : public Hand_Impl<Four_Of_A_Kind_Hand>
{
  Rank quad_rank_;

public:
  Four_Of_A_Kind_Hand(Rank const& r, hand_type const& h)
    : quad_rank_(r)
  {
    Hand_Impl<Four_Of_A_Kind_Hand>::hand_ = h;
  }

  // Barton-Nackmann
  std::ostream& write_impl(std::ostream& os) const
  {
    os << "Four of a Kind Hand" << std::endl
       << "  Quad Rank: " << quad_rank_;
    return os;
  }

  bool less_than_impl(Four_Of_A_Kind_Hand const& rhs) const
  {
    quad_rank_ < rhs.quad_rank_;
  }

  bool equal_impl(Four_Of_A_Kind_Hand const& rhs) const
  {
    return false;
  }
};


//===========================================================================
// Straight Flush Hand Class
//---------------------------------------------------------------------------
class Straight_Flush_Hand
  : public Hand_Impl<Straight_Flush_Hand>
{

public:
  explicit Straight_Flush_Hand(hand_type const& h)
  {
    Hand_Impl<Straight_Flush_Hand>::hand_ = h;
    Hand_Impl<Straight_Flush_Hand>::high_card_ = h.back()->rank_;
  }

  // Barton-Nackmann
  std::ostream& write_impl(std::ostream& os) const
  {
    os << "Straight Flush Hand" << std::endl
       << "  High card in straight: " << high_card_;
    return os;
  }

  bool less_than_impl(Straight_Flush_Hand const& rhs) const
  {
    return high_card_ < rhs.high_card_;
  }

  bool equal_impl(Straight_Flush_Hand const& rhs) const
  {
    return high_card_ == rhs.high_card_;
  }
};


//===========================================================================
// Ranked Hand using boost::variant
//---------------------------------------------------------------------------
typedef boost::variant<
  Hand,
  Pair_Hand,
  Two_Pair_Hand,
  Three_Of_A_Kind_Hand,
  Straight_Hand,
  Flush_Hand,
  Full_House_Hand,
  Four_Of_A_Kind_Hand,
  Straight_Flush_Hand
  > Ranked_Hand;

#endif
