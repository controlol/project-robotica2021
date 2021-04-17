#include "Player.hpp"

Player::Player(/* args */)
{
}

Player::~Player()
{
}

place::place(/* args */) {}
place::~place() {}

int place::GetX()
{
    return this->x;
}
int place::GetY()
{
    return this->y;
}
void place::SetX(int newX)
{
    this->x = newX;
}
void place::SetY(int newY)
{
    this->y = newY;
}