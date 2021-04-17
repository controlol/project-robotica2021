#ifndef kernelheadervar
#define kernelheadervar
#include<vector>
#include <opencv2/opencv.hpp>

class Kernel
{
protected:
    /* data */
    std::vector<std::vector<signed char>> kernel;
public:
    Kernel(/* args */);
    ~Kernel();
    std::vector<std::vector<uchar>> OverlayKernel(std::vector<std::vector<uchar>> picture, int width, int height);
    int applyFilter(int row, int col, std::vector<std::vector<uchar>> picture);
    void TurnKernel(bool turnCounterClockwise);

    void OverlayKernel2(uchar *picture,int *result, int width, int height);
    int applyFilter2(int row, int col,int height, int width, uchar *picture);
    
};
#endif
