#include "Player.hpp"

Player::Player(place pPlace)
{
}

Player::~Player()
{
}

bool Player::DoesCardBelongToPlayer(place cardPlace)
{
   if (cardPlace.GetX() < playerPlace.GetX() + 50 && cardPlace.GetX() > playerPlace.GetX() - 50)
   {
      if (cardPlace.GetY() < playerPlace.GetY() + 50 && cardPlace.GetY() > playerPlace.GetY() - 50)
      {
         return true;
      }
   }
   return false;
}
void Player::AddCard(card newCard,bool IsThisTheSecondCard)
{
   if(IsThisTheSecondCard)
   {
      cards[1]=newCard;
   }
   else{
      cards[0]=newCard;
   }
}