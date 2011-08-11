#include "Card.hxx"
#include "Hand.hxx"
#include "PokerUtils.hxx"
#include <boost/variant.hpp>
#include <vector>

int main()
{

  spc_type
  s_5(new Card(Rank(5), Suit(0))),
  h_5(new Card(Rank(5), Suit(1))),
  d_5(new Card(Rank(5), Suit(2))),
  c_5(new Card(Rank(5), Suit(3))),
  s_6(new Card(Rank(6), Suit(0))),
  h_6(new Card(Rank(6), Suit(1))),
  d_6(new Card(Rank(6), Suit(2))),
  c_6(new Card(Rank(6), Suit(3))),
  s_7(new Card(Rank(7), Suit(0))),
  h_7(new Card(Rank(7), Suit(1))),
  d_7(new Card(Rank(7), Suit(2))),
  c_7(new Card(Rank(7), Suit(3))),
  s_8(new Card(Rank(8), Suit(0))),
  h_8(new Card(Rank(8), Suit(1))),
  d_8(new Card(Rank(8), Suit(2))),
  c_8(new Card(Rank(8), Suit(3))),
  s_9(new Card(Rank(9), Suit(0))),
  h_9(new Card(Rank(9), Suit(1))),
  d_9(new Card(Rank(9), Suit(2))),
  c_9(new Card(Rank(9), Suit(3))),
  s_10(new Card(Rank(10), Suit(0))),
  h_10(new Card(Rank(10), Suit(1))),
  d_10(new Card(Rank(10), Suit(2))),
  c_10(new Card(Rank(10), Suit(3)))
  ;

#if 0
  std::vector<spc_type> h1{h_7,h_5,h_6,h_9,h_8};
  std::vector<spc_type> h2{s_7,h_5,h_6,h_9,h_8};
  for_each(h1.begin(), h1.end(), [](spc_type c) { std::cout << c << std::endl; } );
  std::cout << "==================================================" << std::endl;
  std::sort(h1.begin(), h1.end());
  for_each(h1.begin(), h1.end(), [](spc_type c) { std::cout << c << std::endl; } );

  Ranked_Hand rh1 = rankHand(h1);
  Ranked_Hand rh2 = rankHand(h2);
  std::cout << rh1 << std::endl;
  std::cout << rh2 << std::endl;

  std::cout << (rh1 == rh1) << std::endl;
  std::cout << (rh1 == rh2) << std::endl;
  std::cout << (rh1 < rh1) << std::endl;
  std::cout << (rh2 < rh1) << std::endl;
  std::cout << (rh1 < rh2) << std::endl;

  std::vector<spc_type> h3{h_7, s_7, h_5, d_5, d_9};

  std::sort(h3.begin(), h3.end(), sort_suit_ordinal());
  std::sort(h3.begin(), h3.end(), sort_ordinal_suit());
  for_each(h3.begin(), h3.end(), [](spc_type c) { std::cout << c << std::endl; } );
#endif

  std::vector<spc_type> h4{s_10, s_7, s_5, s_6, s_8};
  Ranked_Hand rh4 = rankHand(h4);
  std::cout << rh4 << std::endl;

  std::vector<spc_type> h5{h_9, h_7, h_5, h_6, h_10};
  Ranked_Hand rh5 = rankHand(h5);
  std::cout << rh5 << std::endl;

  std::cout << "==================================================" << std::endl;
  std::cout << (rh4 < rh5) << std::endl;


/*
  std::shared_ptr<Pair_Hand> p1(new Pair_Hand(h_5, d_5, c_9, c_8, c_6));
  std::shared_ptr<Two_Pair_Hand> t1(new Two_Pair_Hand(h_5, d_5, h_6, d_6, s_8));



  std::cout << (ph1 < ph2)  << std::endl;
  std::cout << (ph1 == ph1) << std::endl;
  std::cout << (ph2 < ph1)  << std::endl;

  std::cout << "================" << std::endl;

  std::cout << compare(t1, p1) << std::endl;
  std::cout << compare(p1, p1) << std::endl;


  std::cout << boost::apply_visitor(Ranked_Hand_Less_Than(), *p1, *t1) << std::endl;
*/



}
