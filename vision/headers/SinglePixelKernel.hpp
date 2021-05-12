#ifndef singlePixelH
#define singlePixelH
#include"Kernel.hpp"
#include<stdio.h>


class SinglePixelKernel : public Kernel
{
private:
    /* data */
public:
    SinglePixelKernel(/* args */);
    ~SinglePixelKernel();
    void RemoveSinglePixels(uchar *picture,  int width, int height);
};


#endif