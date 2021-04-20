#ifndef playerheader
#define playerheader
#include"card.hpp"
#include"place.hpp"

class Player
{
private:
    /* data */
   // card cards[2];
    //place playerPlace;
    bool firstCardToBePlaced;
public:
    Player();
    ~Player();
    bool DoesCardBelongToPlayer(place);
    void AddCard(card);
};
#endif

