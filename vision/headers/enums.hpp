#ifndef enumsheader
#define enumsheader
#include <iostream>
enum Suits{h,c,s,d};

enum Ranks{one,two,three,four,five,six,seven,eight,nine,ten,jack,queen,king,ace};

enum class MoveDirection{N=0,NE=1,E=2,ES=3,S=4,SW=5,W=6,NW=7};
inline std::ostream& operator << (std::ostream& os, const MoveDirection& obj)
{
   os << static_cast<std::underlying_type<MoveDirection>::type>(obj);
   return os;
}

#endif