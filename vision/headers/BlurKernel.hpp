#ifndef blurheader
#define blurheader
#include<math.h>
#include"Kernel.hpp"

class BlurKernel : public Kernel
{
private:
    /* data */
public:
    BlurKernel(/* args */);
    ~BlurKernel();
    std::vector<std::vector<uchar>> GuassianBlur(std::vector<std::vector<uchar>> picture, int width, int height);

    std::vector<std::vector<uchar>> gaussBlur_1 (std::vector<std::vector<uchar>>scl, int w, int h, int r);
    std::vector<std::vector<uchar>> GuassianBlur3(std::vector<std::vector<uchar>> picture, int width, int height);

    int accessPixel(unsigned char * arr, int col, int row, int k, int width, int height) ;
    void guassian_blur2D(unsigned char * arr, unsigned char * result, int width, int height);

    void blur4(uchar *array, uchar *result, int width, int height);
};
#endif

