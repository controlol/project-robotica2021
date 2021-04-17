#ifndef placeheader
#define placeheader
class place
{
private:
    /* data */
    int x;
    int y;
public:
    place(/* args */);
    ~place();

    int GetX();
    int GetY();
    void SetX(int);
    void SetY(int);
};

#endif