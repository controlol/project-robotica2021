#ifndef cardheader
#define cardheader
#include "enums.hpp"
#include "place.hpp"

class card
{
private:
    /* data */
    Ranks rank;
    Suits suit;
    place cardPlace;
    //matrix

    place thing;
public:
    card(/* args */);
    ~card();
    void DetermenRank();
    void DetermenSuit();
    place GetCardPlace();
};
#endif