#ifndef __HAND_HXX__
#define __HAND_HXX__

// Written by Matt Renaud
// Assistance from Paul Preney

#include "Card.hxx"
#include <array>
#include <memory>
#include <boost/variant.hpp>

//===========================================================================

template <typename T, typename Traits>
class Hand_Impl
{
public:
  typedef Traits traits_type;

  static const unsigned HAND_SIZE = 5;

  Hand_Impl()
  {
    int r = 0;
    int s = 1;

    for(int c = 0; c < HAND_SIZE; ++c)
    {
      hand_[c] = spc_type (new Card(Rank(r++), Suit(s)));
    }
  }

protected:
  std::array<spc_type, 5> hand_;
};

// Default < definition...
template <typename T, typename Traits>
bool operator <(Hand_Impl<T,Traits> const& lhs, Hand_Impl<T,Traits> const& rhs)
{
  return false;
}

// Default == definition...
template <typename T, typename Traits>
bool operator ==(Hand_Impl<T,Traits> const& lhs, Hand_Impl<T,Traits> const& rhs)
{
  return false;
}

//===========================================================================

template <unsigned ID>
struct Hand_Traits
{
  typedef char ORDER[ID];
};

class Hand : public Hand_Impl<Hand,Hand_Traits<1> >
{
};

//===========================================================================

/* **************************************************
   Pair Hand Class
   * **************************************************/
class Pair_Hand : public Hand_Impl<Pair_Hand,Hand_Traits<2> >
{
  friend bool operator <(Pair_Hand const& lhs, Pair_Hand const& rhs);
  friend bool operator ==(Pair_Hand const& lhs, Pair_Hand const& rhs);

  Rank pair_rank_;
  spc_type pair_card_1_;
  spc_type pair_card_2_;
  Rank high_card_;
  Rank second_high_card_;
  Rank third_high_card_;

public:
  Pair_Hand(spc_type pc1, spc_type pc2, spc_type hc
	    , spc_type shc, spc_type thc)
    : pair_rank_(pc1->rank_), pair_card_1_(pc1), pair_card_2_(pc2)
    , high_card_(hc->rank_), second_high_card_(shc->rank_)
    , third_high_card_(thc->rank_)
  {
  }
};

// Put in .cxx file later...
bool operator <(Pair_Hand const& lhs, Pair_Hand const& rhs)
{
  if(lhs.pair_rank_ < rhs.pair_rank_)
    return true;
  else if(lhs.pair_rank_ > rhs.pair_rank_)
    return false;
  else if(lhs.high_card_ < rhs.high_card_)
    return true;
  else if(lhs.high_card_ > rhs.high_card_)
    return false;
  else if(lhs.second_high_card_ < rhs.second_high_card_)
    return true;
  else if(lhs.second_high_card_ > rhs.second_high_card_)
    return true;
  else if(lhs.third_high_card_ < rhs.third_high_card_)
    return true;
  else
    return false;
}

// Put in .cxx file later...
bool operator ==(Pair_Hand const& lhs, Pair_Hand const& rhs)
{
  return (
    (lhs.pair_rank_ == rhs.pair_rank_) &&
    (lhs.high_card_ == rhs.high_card_) &&
    (lhs.second_high_card_ == rhs.second_high_card_) &&
    (lhs.third_high_card_ == rhs.third_high_card_ )
  );
}

std::ostream& operator << (std::ostream& os, Pair_Hand const& h)
{
  os << "Pair Hand";
  return os;
}

//===========================================================================
/* **************************************************
   Two Pair Hand Class
   * **************************************************/
class Two_Pair_Hand : public Hand_Impl<Two_Pair_Hand,Hand_Traits<3> >
{
  friend bool operator <(Two_Pair_Hand const& lhs, Two_Pair_Hand const& rhs);
  friend bool operator ==(Two_Pair_Hand const& lhs, Two_Pair_Hand const& rhs);

  Rank high_pair_rank_;
  Rank low_pair_rank_;
  spc_type high_pair_card_1_;
  spc_type high_pair_card_2_;
  spc_type low_pair_card_1_;
  spc_type low_pair_card_2_;
  Rank high_card_;

  public:
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

// Put in .cxx file later...
bool operator <(Two_Pair_Hand const& lhs, Two_Pair_Hand const& rhs)
{
  if(lhs.high_pair_rank_ < rhs.high_pair_rank_)
    return true;
  else if (lhs.high_pair_rank_ > rhs.high_pair_rank_)
    return false;
  else if(lhs.low_pair_rank_ < rhs.low_pair_rank_)
    return true;
  else
    return false;
}

// Put in .cxx file later...
bool operator ==(Two_Pair_Hand const& lhs, Two_Pair_Hand const& rhs)
{
  return (
    (lhs.high_pair_rank_ == rhs.high_pair_rank_) &&
    (lhs.low_pair_rank_ == rhs.low_pair_rank_) &&
    (lhs.high_card_ == rhs.high_card_)
  );
}

std::ostream& operator << (std::ostream& os, Two_Pair_Hand const& h)
{
  os << "Two Pair Hand";
  return os;
}

//===========================================================================
/* **************************************************
   Three of a Kind Hand Class
   * **************************************************/
class Three_Of_A_Kind_Hand
  : public Hand_Impl<Three_Of_A_Kind_Hand,Hand_Traits<4> >
{
  friend bool operator < (Three_Of_A_Kind_Hand const& lhs, Three_Of_A_Kind_Hand const& rhs);
  friend bool operator == (Three_Of_A_Kind_Hand const& lhs, Three_Of_A_Kind_Hand const& rhs);

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
};

// Put in .cxx file later...
bool operator < (Three_Of_A_Kind_Hand const& lhs, Three_Of_A_Kind_Hand const& rhs)
{
  if(lhs.triple_rank_ < rhs.triple_rank_)
    return true;
  else if(lhs.triple_rank_ > rhs.triple_rank_)
    return false;
  else if(lhs.high_card_ < rhs.high_card_)
    return true;
  else if(lhs.high_card_ > rhs.high_card_)
    return false;
  else if(lhs.second_high_card_ < rhs.second_high_card_)
    return true;
  else
    return false;
}

// Put in .cxx file later...
bool operator == (Three_Of_A_Kind_Hand const& lhs, Three_Of_A_Kind_Hand const& rhs)
{
  return false;
}

std::ostream& operator << (std::ostream& os, Three_Of_A_Kind_Hand const& h)
{
  os << "Three of a kind";
  return os;
}

//===========================================================================
/* **************************************************
   Straight Hand Class
   * **************************************************/
class Straight_Hand : public Hand_Impl<Straight_Hand,Hand_Traits<5> >
{
  friend bool operator < (Straight_Hand const& lhs, Straight_Hand const& rhs);
  friend bool operator == (Straight_Hand const& lhs, Straight_Hand const& rhs);

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

};

std::ostream& operator << (std::ostream& os, Straight_Hand const& h)
{
  os << "Straight";
  return os;
}

bool operator < (Straight_Hand const& lhs, Straight_Hand const& rhs)
{
  return lhs.high_card_in_straight_ < rhs.high_card_in_straight_;
}

bool operator == (Straight_Hand const& lhs, Straight_Hand const& rhs)
{
  return lhs.high_card_in_straight_ == rhs.high_card_in_straight_;
}



//===========================================================================
/* **************************************************
   Flush Hand Class
   * **************************************************/
class Flush_Hand : public Hand_Impl<Flush_Hand,Hand_Traits<6> >
{
  public:
};

//===========================================================================
/* **************************************************
   Full House Hand Class
   * **************************************************/
class Full_House_Hand : public Hand_Impl<Full_House_Hand,Hand_Traits<7> >
{
  friend bool operator < (Full_House_Hand const& lhs, Full_House_Hand const& rhs);
  friend bool operator == (Full_House_Hand const& lhs, Full_House_Hand const& rhs);

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
};

bool operator < (Full_House_Hand const& lhs, Full_House_Hand const& rhs)
{
  if(lhs.triple_rank_ < rhs.triple_rank_)
    return true;
  else if(lhs.triple_rank_ > rhs.triple_rank_)
    return false;
  else if(lhs.pair_rank_ < rhs.pair_rank_)
    return true;
  else
    return false;
}

bool operator == (Full_House_Hand const& lhs, Full_House_Hand const& rhs)
{
  return false;
}

//===========================================================================
/* **************************************************
   Four of a Kind Hand Class
   * **************************************************/
class Four_Of_A_Kind_Hand : public Hand_Impl<Four_Of_A_Kind_Hand,Hand_Traits<8> >
{
  friend bool operator < (Four_Of_A_Kind_Hand const& lhs, Four_Of_A_Kind_Hand const& rhs);
  friend bool operator == (Four_Of_A_Kind_Hand const& lhs, Four_Of_A_Kind_Hand const& rhs);

  Rank quad_rank_;
  spc_type quad_card_1_;
  spc_type quad_card_2_;
  spc_type quad_card_3_;
  spc_type quad_card_4_;
  Rank high_card_;

  public:
  Four_Of_A_Kind_Hand(Rank r, spc_type qc1, spc_type qc2
		      , spc_type qc3, spc_type qc4, spc_type hc)
  : quad_rank_(r), quad_card_1_(qc1), quad_card_2_(qc2)
  , quad_card_3_(qc3), quad_card_4_(qc4)
  , high_card_(hc->rank_)
  {
  }

};

bool operator < (Four_Of_A_Kind_Hand const& lhs, Four_Of_A_Kind_Hand const& rhs)
{
  return lhs.quad_rank_ < rhs.quad_rank_;
}

bool operator == (Four_Of_A_Kind_Hand const&, Four_Of_A_Kind_Hand const&)
{
  return false;
}

//===========================================================================
/* **************************************************
   Straight Flush Hand Class
   * **************************************************/
class Straight_Flush_Hand
  : public Hand_Impl<Straight_Flush_Hand,Hand_Traits<9> >
{
};

// Use default < and ==.


//===========================================================================
/* **************************************************
   Ranked Hand using boost::variant
   * **************************************************/
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
    //return (sizeof(t.order()) < sizeof(u.order()));
    return (sizeof(typename T::traits_type::ORDER) < sizeof(typename U::traits_type::ORDER));
  }
};

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

struct Ranked_Hand_Ostream_Out
  : public boost::static_visitor<std::ostream&>
{
  template <typename T>
  std::ostream& operator () (std::ostream& os, T const& h)
  {
    os << h;
    return os;
  }
};

inline bool operator < (Ranked_Hand const& lhs, Ranked_Hand const& rhs)
{
  return boost::apply_visitor(Ranked_Hand_Less_Than(), lhs, rhs);
}


inline bool operator == (Ranked_Hand const& lhs, Ranked_Hand const& rhs)
{
  return boost::apply_visitor(Ranked_Hand_Equal_To(), lhs, rhs);
}

std::ostream& operator << (std::ostream& os, Ranked_Hand const& h)
{
  return boost::apply_visitor(Ranked_Hand_Ostream_Out(),os, h);
}

// This works but I want to find out why it doesn't work with boost::variant.
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
