#ifndef playerheader
#define playerheader
#include"card.hpp"
#include"place.hpp"

class Player
{
private:
    /* data */
    std::vector<card> cards;
    place playerPlace;
    bool firstCardToBePlaced;
public:
    Player(place);
    ~Player();
    bool DoesCardBelongToPlayer(place);
    void AddCard(card,bool);
};
#endif

