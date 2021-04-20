#ifndef placeheader
#define placeheader

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
};

#endif