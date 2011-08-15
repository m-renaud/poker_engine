#include "Poker.hxx"

int main()
{
  Poker<4> p;

  p.deal<5>();
  p.showHands();
  p.sortHands(RANK);
  std::cout << std::endl
	    << "Sorted by rank:" << std::endl;;
  p.showHands();

  std::cout << std::endl
	    << "Sorted by suit:" << std::endl;;
  p.sortHands(SUIT);
  p.showHands();

}
