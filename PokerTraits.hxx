#ifndef __MRR_POKER_TRAITS_HXX__
#define __MRR_POKER_TRAITS_HXX__

template <typename Card>
struct HandTraits
{
  typedef Card card_type;
  typedef std::vector<card_type> hand_type;
  static const bool blah = true;
};


#endif

