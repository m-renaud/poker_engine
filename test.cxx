#include "Card.hxx"
#include "Hand.hxx"
#include "PokerUtils.hxx"
#include <boost/variant.hpp>
#include <vector>

int main()
{

   spc_type
        s_5(new Card(Rank(5), Suit(0)))
      , h_5(new Card(Rank(5), Suit(1)))
      , d_5(new Card(Rank(5), Suit(2)))
      , c_5(new Card(Rank(5), Suit(3)))
      , s_6(new Card(Rank(6), Suit(0)))
      , h_6(new Card(Rank(6), Suit(1)))
      , d_6(new Card(Rank(6), Suit(2)))
      , c_6(new Card(Rank(6), Suit(3)))
      , s_7(new Card(Rank(7), Suit(0)))
      , h_7(new Card(Rank(7), Suit(1)))
      , d_7(new Card(Rank(7), Suit(2)))
      , c_7(new Card(Rank(7), Suit(3)))
      , s_8(new Card(Rank(8), Suit(0)))
      , h_8(new Card(Rank(8), Suit(1)))
      , d_8(new Card(Rank(8), Suit(2)))
      , c_8(new Card(Rank(8), Suit(3)))
      , s_9(new Card(Rank(9), Suit(0)))
      , h_9(new Card(Rank(9), Suit(1)))
      , d_9(new Card(Rank(9), Suit(2)))
      , c_9(new Card(Rank(9), Suit(3)))
      ;

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
   std::cout << (rh2 < rh1) << std::endl;
   std::cout << (rh1 < rh2) << std::endl;

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
