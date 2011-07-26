#include "CardDeck.hxx"



class PlayPoker : public Deck
{
private:
   static const int NUMBER_OF_HANDS = 4;
   static const int CARDS_IN_HAND = 2;
   static const int MAX_CARDS_ON_TABLE = 5;
   unsigned cardsOnTable;
   spc_type hand[NUMBER_OF_HANDS][CARDS_IN_HAND];
   spc_type table_card[MAX_CARDS_ON_TABLE];

public:
   PlayPoker() : Deck() { }

   void dealHands()
   {
      positionInDeck = 0;
      cardsOnTable = 0;
      shuffle();

      for(int cc = 0; cc < CARDS_IN_HAND; ++cc)
      {
	 for(int hc = 0; hc < NUMBER_OF_HANDS; ++hc)
	 {
	    hand[hc][cc] = deck[positionInDeck++];
	 }
      }

      for(; cardsOnTable < 3; ++cardsOnTable)
      {
	 table_card[cardsOnTable] = deck[positionInDeck++];
      }

   }

   void showHand(unsigned handNumber)
   {
      /*
      for_each(
	 hand[handNumber], hand[handNumber]+CARDS_IN_HAND,
	 [](spc_type& c) { if (c) c->showCard(); cout << endl; }
	 );
      */

      // Range based for loop.
      for(auto &c: hand[handNumber])
      {
	 c->showCard();
	 cout << endl;
      }
   }

   void showHands()
   {
      for(unsigned hand = 0; hand < NUMBER_OF_HANDS; ++hand)
      {
	 cout << "Hand " << (hand + 1) << ":" << endl;
	 showHand(hand);
	 cout << endl;
      }
   }

   void showTableCards()
   {
      cout << "Cards on Table:" << endl;
      for_each(
	 table_card, table_card+cardsOnTable,
	 [](spc_type& c) { if (c) c->showCard(); cout << endl; }
	 );
      cout << endl;
   }

   void dealNextTableCard()
   {
      table_card[cardsOnTable++] = dealTopCard();
   }


};
