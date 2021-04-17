#include "BlurKernel.hpp"
#define PI 3.141592

//#define DEBUG false
#ifdef DEBUG
#endif

std::vector<std::vector<uchar>> BlurKernel::GuassianBlur(std::vector<std::vector<uchar>> picture, int width, int height)
{
    std::cout << "going to gaussianBlur" << std::endl;
    std::vector<std::vector<uchar>> blurredPicture;
    blurredPicture.resize(width, std::vector<uchar>(height));
    blurredPicture = OverlayKernel(picture, width, height);
    int kernelSum = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            kernelSum += this->kernel[i][j];
        }
    }
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            blurredPicture[row][col] = round(blurredPicture[row][col] / kernelSum);
        }
    }
    std::cout << "done with gaussianBlur" << std::endl;
    return blurredPicture;
}

BlurKernel::BlurKernel(/* args */)
{
    int temp[3][3] = {1, 2, 1,
                      2, 4, 2,
                      1, 2, 1};
    kernel.resize(3, std::vector<signed char>(3));
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            kernel[i][j] = temp[i][j];
        }
    }
}

BlurKernel::~BlurKernel()
{
}

std::vector<std::vector<uchar>> BlurKernel::GuassianBlur3(std::vector<std::vector<uchar>> picture, int width, int height)
{
    std::cout << "going to gaussianBlur3" << std::endl;
    std::vector<std::vector<uchar>> blurredPicture = picture;
    blurredPicture = OverlayKernel(picture, width, height);
    int kernelSum = 0;

    /*std::cout << "going to sum kernel" << std::endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            
            kernelSum += this->kernel[i][j];
        }
    }*/
    std::cout << "going to do stuff with the kernel sum" << std::endl;
    std::cout << "width height: " << width << "  " << height << std::endl;
    std::vector<std::vector<uchar>>::iterator row;
    std::vector<uchar>::iterator col;
    int i = 0;
    int j = 0;
    for (row = picture.begin(); row < picture.end(); row = row + 1)
    {
        for (col = row->begin(); col < row->end(); col = col + 1)
        {

            blurredPicture[i][j] = round(blurredPicture[i][j] / 45);
            j = std::distance(row->begin(), col);
        }
        i = std::distance(picture.begin(), row);
    }
    std::cout << "done with gaussianBlur" << std::endl;
    return blurredPicture;
}

// source channel, target channel, width, height, radius
std::vector<std::vector<uchar>> BlurKernel::gaussBlur_1(std::vector<std::vector<uchar>> scl, int w, int h, int r)
{
    std::cout << "gaussian fast\n";
    std::vector<std::vector<uchar>> tcl;
    tcl.resize(w, std::vector<uchar>(h));
    int significantRadius = ceil(r * 2.57); // significant radius
    std::cout << "for the loops\n";
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            double val = 0, wsum = 0;
            for (int iy = i - significantRadius; iy < i + significantRadius + 1; iy++)
            {
                for (int ix = j - significantRadius; ix < j + significantRadius + 1; ix++)
                {
                    std::cout << "in last loop\n";
                    int x = fmin(w - 1, fmax(0, ix));
                    int y = fmin(h - 1, fmax(0, iy));
                    std::cout << "in last loop min\n";
                    int dsq = (ix - j) * (ix - j) + (iy - i) * (iy - i);
                    std::cout << "in last loop dsq\n";
                    uchar wght = exp(-dsq / (2 * r * r)) / (PI * 2 * r * r);
                    std::cout << "in last loop wght\n";
                    val += scl[x][y] * wght;
                    std::cout << "in last loop val\n";
                    wsum += wght;
                    std::cout << "in last loop wsum\n";
                }
            }
            std::cout << "val/wsum" << (double)val << (double)wsum;
            std::cout << "itteration: " << j << std::endl;

            tcl[j][i] = round(val / wsum);
            std::cout << "round(VAl/wsum) \n";
        }
    }
    std::cout << "returning\n";
    return tcl;
}
void BlurKernel::blur4(uchar *array, uchar *result, int width, int height)
{
    int test[width * height];

    OverlayKernel2(array, test, width, height);

    for (int row = 0; row < height; row = row + 1)
    {
        for (int col = 0; col < width; col = col + 1)
        {
#ifdef DEBUG
            std::cout << "Before final pixel value: " << (unsigned int)test[row * width + col] << std::endl;
#endif
            result[row * width + col] = round(test[row * width + col] / 16);
#ifdef DEBUG
            std::cout << "Final pixel value: " << (unsigned int)result[row * width + col] << std::endl;
#endif
            //return;
        }
    }
}
void BlurKernel::guassian_blur2D(unsigned char *arr, unsigned char *result, int width, int height)
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            for (int k = 0; k < 3; k++)
            {
                result[3 * row * width + 3 * col + k] = accessPixel(arr, col, row, k, width, height);
            }
        }
    }
}

int BlurKernel::accessPixel(unsigned char *arr, int col, int row, int k, int width, int height)
{
    int sum = 0;
    int sumKernel = 0;
    int kernel2[3][3] = {1, 2, 1,
                         2, 4, 2,
                         1, 2, 1};

#ifdef DEBUG
    std::cout << "initialized intiables" << std::endl;
#endif
    for (int j = -1; j <= 1; j++)
    {
        for (int i = -1; i <= 1; i++)
        {
            if ((row + j) >= 0 && (row + j) < height && (col + i) >= 0 && (col + i) < width)
            {
                int color = arr[(row + j) * 3 * width + (col + i) * 3 + k];
#ifdef DEBUG
                std::cout << "color: " << color << std::endl;
#endif
                sum += color * kernel[i + 1][j + 1];
                sumKernel += kernel[i + 1][j + 1];
            }
        }
    }
#ifdef DEBUG
    std::cout << "Sums: " << sum << "  " << sumKernel << std::endl;
#endif
    return sum / sumKernel;
}
