#include "Card.hxx"
#include "Hand.hxx"
#include "PokerUtils.hxx"
#include <boost/variant.hpp>

int main()
{

   spc_type
        h_5(new Card(Rank(5), Suit(1)))
      , d_5(new Card(Rank(5), Suit(2)))
      , s_5(new Card(Rank(5), Suit(3)))
      , c_5(new Card(Rank(5), Suit(4)))
      , h_6(new Card(Rank(6), Suit(1)))
      , d_6(new Card(Rank(6), Suit(2)))
      , s_6(new Card(Rank(6), Suit(3)))
      , c_6(new Card(Rank(6), Suit(4)))
      , h_7(new Card(Rank(7), Suit(1)))
      , d_7(new Card(Rank(7), Suit(2)))
      , s_7(new Card(Rank(7), Suit(3)))
      , c_7(new Card(Rank(7), Suit(4)))
      , h_8(new Card(Rank(8), Suit(1)))
      , d_8(new Card(Rank(8), Suit(2)))
      , s_8(new Card(Rank(8), Suit(3)))
      , c_8(new Card(Rank(8), Suit(4)))
      , h_9(new Card(Rank(9), Suit(1)))
      , d_9(new Card(Rank(9), Suit(2)))
      , s_9(new Card(Rank(9), Suit(3)))
      , c_9(new Card(Rank(9), Suit(4)))
      ;

   std::array<spc_type, 5> h1 = {h_5, d_5, c_5, h_7, c_9};

   Ranked_Hand rh1 = rankHand(h1);

   std::cout << rh1 << std::endl;

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
