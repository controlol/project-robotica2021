#include "Table.hpp"

void Table::DistributeCards(std::vector<card> cards)
{
    place cardPlace;
    //place playerPlace;
    for (int i = 0; i < (sizeof(cards) / sizeof(cards[0])); i++)
    {
        cardPlace = cards[i].GetCardPlace();
        for (int i = 0; i < (sizeof(players) / sizeof(players[0])); i++)
        {
            if (players[i].DoesCardBelongToPlayer(cardPlace))
            {
                players[i].AddCard(cards[i]);
            }
        }
    }
}

Table::Table(/* args */)
{
}

Table::~Table()
{
}