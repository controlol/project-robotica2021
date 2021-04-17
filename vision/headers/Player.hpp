#ifndef playerheader
#define playerheader
#include"card.hpp"

class Player
{
private:
    /* data */
    card cards[2];
    place playerPlace;
    bool firstCardToBePlaced;
public:
    Player(/* args */);
    ~Player();
    bool DoesCardBelongToPlayer(place);
    void AddCard(card);
};
#endif

