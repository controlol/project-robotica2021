#ifndef tableheader
#define tableheader
#include"image.hpp"
#include"Player.hpp"

class Table
{
private:
    /* data */
    std::vector<card> openCards;
    std::vector<Player> players;
public:
    Table(/* args */);
    ~Table();

    image TakePicture();
    void InformBrain();
    void DistributeCards(std::vector<card> cards);
};


#endif