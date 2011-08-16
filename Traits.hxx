#ifndef __MRR_TRAITS_HXX__
#define __MRR_TRAITS_HXX__

#include <array>
#include <vector>
#include <memory>
#include <iterator>
#include <boost/variant.hpp>


// Forward class declarations.
class Card;
class Hand;
class Pair_Hand;
class Two_Pair_Hand;
class Three_Of_A_Kind_Hand;
class Straight_Hand;
class Flush_Hand;
class Full_House_Hand;
class Four_Of_A_Kind_Hand;
class Straight_Flush_Hand;

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

enum TRAIT_VALS { CARDS_IN_DECK = 52, SUITS_IN_DECK = 4, CARDS_IN_SUIT = 13 };

typedef std::shared_ptr<Card> card_type;
typedef std::vector<card_type> hand_type;
typedef hand_type::iterator hand_iter_type;
typedef std::vector<Ranked_Hand> ranked_hand_type;
typedef std::vector<hand_type> hand_collection_type;
typedef std::array<card_type, CARDS_IN_DECK> deck_type;


#endif // #ifndef __MRR_CARD_TRAITS_HXX__
