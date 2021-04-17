#ifndef edgeheader
#define edgeheader
#include"Kernel.hpp"
#include<stdio.h>


class EdgeKernel : public Kernel
{
private:
    /* data */
    double lowerThreshold;
public:
    EdgeKernel(/* args */);
    ~EdgeKernel();

    std::vector<std::vector<uchar>> FindEdgeMatrix(std::vector<std::vector<uchar>> picture,  int width, int height);
    std::vector<std::vector<uchar>> TraceAlongEdges(std::vector<std::vector<uchar>> resultWeight, std::vector<std::vector<uchar>> resultAngle,  int width, int height);
std::vector<std::vector<uchar>> GetWeightedMatrix(std::vector<std::vector<uchar>> hor, std::vector<std::vector<uchar>> ver, int width, int height);
std::vector<std::vector<uchar>> GetAngleMatrix(std::vector<std::vector<uchar>> hor, std::vector<std::vector<uchar>> ver, int width, int height);

    void TraceAlongEdges2(int *resultWeight, int *resultAngle, int *edgeMatrix, int width, int height);
    void GetAngleMatrix2(int *hor, int *ver, int *resultAngle, int width, int height);
    void GetWeightedMatrix2(int *hor, int *ver, int *resultWeight,  int width, int height);
    void FindEdgeMatrix2(uchar *picture, uchar *returnMatrix, int width, int height);
    
};


#endif