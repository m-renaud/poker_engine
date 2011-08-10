#ifndef __MRR_HAND_HXX__
#define __MRR_HAND_HXX__

//===========================================================================
// Hand class for representing and ranking poker hands.
// Author: Matt Renaud - mrenaud92@gmail.com
// Assistance from Paul Preney and Bryan St. Amour
//---------------------------------------------------------------------------

#include "Card.hxx"
#include <vector>
#include <boost/variant.hpp>
#include <boost/optional.hpp>

//===========================================================================
template <typename T>
class Hand_Impl
{
public:
  std::vector<spc_type> hand_;
  Rank high_card_;

  explicit Hand_Impl()
  {
  }

  explicit Hand_Impl(std::vector<spc_type> const& h)
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
  std::ostream& write_impl(std::ostream& os) const
  {
    os << "Hand";
    return os;
  }

  bool less_than_impl(Hand const& rhs) const
  {
    return false;
  }

  bool equal_impl(Hand const& rhs) const
  {
    return false;
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

  Pair_Hand(spc_type const& p, spc_type const& hc,
	    spc_type const& shc, spc_type const& thc)
    : pair_rank_(p->rank_), second_high_card_(shc->rank_), third_high_card_(thc->rank_)
  {
    Hand_Impl<Pair_Hand>::high_card_ = hc->rank_;
  }
  // Barton-Nackmann
  std::ostream& write_impl(std::ostream& os) const
  {
    os << "Pair Hand";
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
  Rank high_card_;

public:
  Two_Pair_Hand(spc_type const& hp, spc_type const& lp, spc_type const& hc)
    : high_pair_rank_(hp->rank_), low_pair_rank_(lp->rank_)
  {
    Hand_Impl<Two_Pair_Hand>::high_card_ = hc->rank_;
  }

  // Barton-Nackmann
  std::ostream& write_impl(std::ostream& os) const
  {
    os << "Two Pair Hand";
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
  Three_Of_A_Kind_Hand(spc_type const& tc)
    : triple_rank_(tc->rank_)
  {
  }

  // Barton-Nackmann
  std::ostream& write_impl(std::ostream& os) const
  {
    os << "Three of a Kind Hand";
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
  Straight_Hand(spc_type hc)
    : high_card_in_straight_(hc->rank_)
  {
  }

  // Barton-Nackmann
  std::ostream& write_impl(std::ostream& os) const
  {
    os << "Straight Hand";
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
  Flush_Hand(std::vector<spc_type> const& h) { }

  // Barton-Nackmann
  std::ostream& write_impl(std::ostream& os) const
  {
    os << "Flush Hand";
    return os;
  }

  bool less_than_impl(Flush_Hand const& rhs) const
  {
    return false;
  }

  bool equal_impl(Flush_Hand const& rhs) const
  {
    return false;
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
  Full_House_Hand(spc_type tc, spc_type pc)
    : triple_rank_(tc->rank_), pair_rank_(pc->rank_)
  {
  }

  // Barton-Nackmann
  std::ostream& write_impl(std::ostream& os) const
  {
    os << "Full House Hand";
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
  Four_Of_A_Kind_Hand(spc_type const& q)
    : quad_rank_(q->rank_)
  {
  }

  // Barton-Nackmann
  std::ostream& write_impl(std::ostream& os) const
  {
    os << "Four of a Kind Hand";
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
  explicit Straight_Flush_Hand(spc_type const& c)
  {
    Hand_Impl<Straight_Flush_Hand>::high_card_ = c->rank_;
  }

  explicit Straight_Flush_Hand(std::vector<spc_type> const& h)
  {
    Hand_Impl<Straight_Flush_Hand>::hand_ = h;
    Hand_Impl<Straight_Flush_Hand>::high_card_ = h.back()->rank_;
  }

  // Barton-Nackmann
  std::ostream& write_impl(std::ostream& os) const
  {
    os << "Straight Flush Hand";
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
