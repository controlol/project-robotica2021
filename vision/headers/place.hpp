#ifndef placeheader
#define placeheader
#include <iostream>
class place
{
private:
    /* data */
    int x;
    int y;

public:
    place(int x=0, int y=0);
    ~place();

    int GetX();
    int GetY();
    void SetX(int);
    void SetY(int);
    void ChangeXY(int x, int y);

    bool operator==(place p1)
    {
        if (p1.GetX() == x && p1.GetY() == y)
        {
            return (true);
        }
        return (false);
    }
      bool operator!=(place p1)
    {
        if (p1.GetX() != x || p1.GetY() != y)
        {
            return (true);
        }
        return (false);
    }
    friend std::ostream& operator<<(std::ostream& os,place c1)
    {
        os<<c1.GetX()<<"  "<<c1.GetY();
        return os;
    }
    place operator+(place p1)
    {
        place temp;
        temp.SetX(p1.GetX()+x);
        temp.SetY(p1.GetY()+y);
        return (temp);
    }
    place operator-(place p1)
    {
        place temp;
        temp.SetX(x-p1.GetX());
        temp.SetY(y-p1.GetY());
        return (temp);
    }
};



#endif