#include "Table.hpp"

void Table::DistributeCards(std::vector<card> cards)
{
    place cardPlace;
    //place playerPlace;
    bool addedCard1=false;
    for (int i = 0; i < (sizeof(players) / sizeof(players[0])); i++)
    {
        addedCard1=false;
        for (int j = 0; j < (sizeof(cards) / sizeof(cards[0])); j++)
        {
            cardPlace = cards[j].GetCardPlace();

            if (players[i].DoesCardBelongToPlayer(cardPlace))
            {
                players[i].AddCard(cards[j],addedCard1);
                addedCard1=true;
            }
        }
    }
}

Table::Table(int amountOfPlayers)
{
    int x=50,y=50;
    for (size_t i = 0; i < amountOfPlayers; i++)
    {
        players.push_back(Player(place(x,y)));
        x+=100; 
        if(x>680){
            x=50;
            y+=200;
        }
    }
    
}

Table::~Table()
{
}