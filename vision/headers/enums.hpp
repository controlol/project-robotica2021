#ifndef enumsheader
#define enumsheader
#include <iostream>
enum Suits
{
   h,
   c,
   s,
   d
};

enum Ranks
{
   ace,
   two,
   three,
   four,
   five,
   six,
   seven,
   eight,
   nine,
   ten,
   jack,
   queen,
   king
};

enum class MoveDirection
{
   N = 0,
   NE = 1,
   E = 2,
   ES = 3,
   S = 4,
   SW = 5,
   W = 6,
   NW = 7
};
inline std::ostream &operator<<(std::ostream &os, const MoveDirection &obj)
{
   os << static_cast<std::underlying_type<MoveDirection>::type>(obj);
   return os;
}
inline std::ostream &operator<<(std::ostream &os, const Ranks &obj)
{
   switch (obj)
   {
   case ace:
      os << "ace";
      break;
   case two:
      os << "two";
      break;
   case three:
      os << "three";
      break;
   case four:
      os << "four";
      break;
   case five:
      os << "five";
      break;
   case six:
      os << "six";
      break;
   case seven:
      os << "seven";
      break;
   case eight:
      os << "eight";
      break;
   case nine:
      os << "nine";
      break;
   case ten:
      os << "ten";
      break;
   case jack:
      os << "jack";
      break;
   case queen:
      os << "queen";
      break;
   case king:
      os << "king";
      break;

   default:
      break;
   }
   return os;
}
#endif