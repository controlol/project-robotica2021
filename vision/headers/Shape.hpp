#ifndef shapeheader
#define shapeheader
#include"place.hpp"
#include <vector>
class Shape
{
private:
    /* data */
    //list of pixels
    std::vector<place> pixels;
public:
    Shape(std::vector<place> listOfPixels);
    ~Shape();

    bool IsShapeSquare();
    bool IsBiggestShape();
};
#endif

