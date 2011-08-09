#ifndef __MRR_HAND_HXX__
#define __MRR_HAND_HXX__

//===========================================================================
// Hand class for representing and ranking poker hands.
// Author: Matt Renaud - mrenaud92@gmail.com
// Assistance from Paul Preney and Bryan St. Amour
//---------------------------------------------------------------------------

#include "Card.hxx"
#include <vector>
#include <memory>
#include <boost/variant.hpp>
#include <boost/optional.hpp>

//===========================================================================

template <typename T, typename Traits>
class Hand_Impl
{
public:
  typedef Traits traits_type;

  static const unsigned HAND_SIZE = 5;

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

  // Default constructor.
  explicit Hand_Impl()
  {
  }

  // Hand vector constructor.
  explicit Hand_Impl(std::vector<spc_type> const& h)
    : hand_(h), high_card_(h.front()->rank_)
  {
  }

  std::vector<spc_type> hand_;
  Rank high_card_;
};


//===========================================================================
// Traits class for Hands
//---------------------------------------------------------------------------
template <unsigned ID>
struct Hand_Traits
{
  typedef char ORDER[ID];
};


//===========================================================================
// Basic hand class
//---------------------------------------------------------------------------
class Hand
  : public Hand_Impl<Hand,Hand_Traits<1> >
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
  : public Hand_Impl<Pair_Hand,Hand_Traits<2> >
{
public:
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

  Rank pair_rank_;
  spc_type pair_card_1_;
  spc_type pair_card_2_;
  Rank high_card_;
  Rank second_high_card_;
  Rank third_high_card_;

  Pair_Hand(spc_type pc1, spc_type pc2, spc_type hc
	    , spc_type shc, spc_type thc)
    : pair_rank_(pc1->rank_), pair_card_1_(pc1), pair_card_2_(pc2)
    , high_card_(hc->rank_), second_high_card_(shc->rank_)
    , third_high_card_(thc->rank_)
  {
  }
};



//===========================================================================
// Two Pair Hand Class
//---------------------------------------------------------------------------
class Two_Pair_Hand
  : public Hand_Impl<Two_Pair_Hand,Hand_Traits<3> >
{

public:

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


  Rank high_pair_rank_;
  Rank low_pair_rank_;
  spc_type high_pair_card_1_;
  spc_type high_pair_card_2_;
  spc_type low_pair_card_1_;
  spc_type low_pair_card_2_;
  Rank high_card_;

  Two_Pair_Hand(spc_type hp1, spc_type hp2
		, spc_type lp1, spc_type lp2
		, spc_type hc)
    : high_pair_rank_(hp1->rank_), low_pair_rank_(lp1->rank_)
    , high_pair_card_1_(hp1), high_pair_card_2_(hp2)
    , low_pair_card_1_(lp1), low_pair_card_2_(lp2)
    , high_card_(hc->rank_)
  {
  }

};



//===========================================================================
// Three of a Kind Hand Class
//---------------------------------------------------------------------------
class Three_Of_A_Kind_Hand
  : public Hand_Impl<Three_Of_A_Kind_Hand,Hand_Traits<4> >
{
  Rank triple_rank_;
  spc_type triple_card_1_;
  spc_type triple_card_2_;
  spc_type triple_card_3_;
  Rank high_card_;
  Rank second_high_card_;

public:
  Three_Of_A_Kind_Hand(spc_type tc1, spc_type tc2, spc_type tc3
		       , spc_type hc, spc_type shc)
    : triple_rank_(tc1->rank_), triple_card_1_(tc1)
    , triple_card_2_(tc2), triple_card_3_(tc3)
    , high_card_(hc->rank_), second_high_card_(shc->rank_)
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
    else if(triple_rank_ > rhs.triple_rank_)
      return false;
    else if(high_card_ < rhs.high_card_)
      return true;
    else if(high_card_ > rhs.high_card_)
      return false;
    else if(second_high_card_ < rhs.second_high_card_)
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
  : public Hand_Impl<Straight_Hand,Hand_Traits<5> >
{
    Rank high_card_in_straight_;

public:
  // Constructor for passing in the rank of high card in straight.
  Straight_Hand(Rank r)
    : high_card_in_straight_(r)
  {
  }

  // Constructor for passing in pointer to the high card.
  Straight_Hand(spc_type hc)
    : high_card_in_straight_(hc->rank_)
  {
  }

  Straight_Hand(std::vector<spc_type> const& h)
    : high_card_in_straight_(h.back()->rank_)
  {
    Hand_Impl<Straight_Hand, Hand_Traits<5> >::hand_ = h;
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
  : public Hand_Impl<Flush_Hand,Hand_Traits<6> >
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
  : public Hand_Impl<Full_House_Hand,Hand_Traits<7> >
{
  Rank triple_rank_;
  Rank pair_rank_;

public:
  // Constructor for passing in two ranks.
  Full_House_Hand(Rank tr, Rank pr)
    : triple_rank_(tr), pair_rank_(pr)
  {
  }

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
class Four_Of_A_Kind_Hand : public Hand_Impl<Four_Of_A_Kind_Hand,Hand_Traits<8> >
{
  Rank quad_rank_;

public:
  Four_Of_A_Kind_Hand(Rank r, spc_type qc1, spc_type qc2
		      , spc_type qc3, spc_type qc4, spc_type hc)
    : quad_rank_(r), quad_card_1_(qc1), quad_card_2_(qc2)
    , quad_card_3_(qc3), quad_card_4_(qc4)
    , high_card_(hc->rank_)
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
    return false;
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
  : public Hand_Impl<Straight_Flush_Hand,Hand_Traits<9> >
{

public:
  explicit Straight_Flush_Hand(spc_type const& c)
  {
    Hand_Impl<Straight_Flush_Hand, Hand_Traits<9> >::high_card_ = c->rank_;
  }

  explicit Straight_Flush_Hand(std::vector<spc_type> const& h) // PAUL
  {
    Hand_Impl<Straight_Flush_Hand,Hand_Traits<9> >::hand_ = h;
    Hand_Impl<Straight_Flush_Hand,Hand_Traits<9> >::high_card_ = h.back()->rank_;
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


struct Ranked_Hand_Less_Than
  : public boost::static_visitor<bool>
{
  template <typename T>
  bool operator () (T& t1, T& t2) const
  {
    return t1 < t2;
  }

  template <typename T, typename U>
  bool operator () (T& t, U& u) const
  {
    return (sizeof(typename T::traits_type::ORDER) < sizeof(typename U::traits_type::ORDER));
  }
};

//===========================================================================
// Visitor struct for Ranked_Hand boost::variant class
// Compares equality of 2 ranked hands.
//---------------------------------------------------------------------------
struct Ranked_Hand_Equal_To
  : public boost::static_visitor<bool>
{
  template <typename T>
  bool operator () (T& t1, T& t2) const
  {
    return t1 == t2;
  }

  template <typename T, typename U>
  bool operator () (T& t, U& u) const
  {
    return false;
  }
};

//===========================================================================
// Visitor - Easy output of ranked hands.
//---------------------------------------------------------------------------

struct Ranked_Hand_Ostream_Out
  : public boost::static_visitor<std::ostream&>
{
  Ranked_Hand_Ostream_Out(std::ostream& os)
    : os_(os) { }

  template <typename T>
  std::ostream& operator () (T const& h) const
  {
    os_ << h;
    return os_;
  }

private:
  std::ostream& os_;
};

//===========================================================================
// Operator for comparing and outputing ranked hands.
//---------------------------------------------------------------------------
/*
inline bool operator < (Ranked_Hand const& lhs, Ranked_Hand const& rhs)
{
  return boost::apply_visitor(Ranked_Hand_Less_Than(), lhs, rhs);
}
*/

/*
inline bool operator == (Ranked_Hand const& lhs, Ranked_Hand const& rhs)
{
  return boost::apply_visitor(Ranked_Hand_Equal_To(), lhs, rhs);
}
*/
 /*
std::ostream& operator << (std::ostream& os, Ranked_Hand const& h)
{
  return boost::apply_visitor(Ranked_Hand_Ostream_Out(os), h);
}
 */


//===========================================================================
// This works but I want to find out why it doesn't work with boost::variant.
// Help from Bryan St. Amour.
//---------------------------------------------------------------------------
/*
  inline bool compare(std::shared_ptr<Hand> lhs, std::shared_ptr<Hand> rhs)
  {
  if(sizeof(typename T::traits_type::ORDER) < sizeof(U::traits_type::ORDER))
  return true;
  else if(sizeof(typename T::traits_type::ORDER) == sizeof(U::traits_type::ORDER))
  return lhs < rhs;
  else
  return false;
  }
*/
#endif
