#include "place.hpp"



place::place(int xnew, int ynew) {
    x=xnew;
    y=ynew;
}
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