#ifndef MOOREHEADER
#define MOOREHEADER

#include "place.hpp"
#include <opencv2/opencv.hpp>
#include "Shape.hpp"
#include "enums.hpp"
#include<unordered_set>

class MooreNeighborhood
{
private:
    /* data */
    
public:
    MooreNeighborhood(/* args */);
    ~MooreNeighborhood();/*
    void Trace(uchar *pixture, int width, int height);
    std::unordered_set<place> getBoundary(uchar *image, int width, int height);

    MoveDirection newMoveDir(MoveDirection oldDirection);
    MoveDirection NextMoveDir(MoveDirection oldDirection);
    place GetPixel(MoveDirection moveDir, place currentPixel, int width, int height);
    bool IsPixelLine(MoveDirection moveDir, place currentPixel, uchar *edgeMatrix, int width,int height);

    bool RemovePixelsFromPicture(std::deque<place> pixels, uchar *edges, int height, int width);
    place GetNextPixel(place current, int height, int width);
    bool RemovePixelsFromPicture(place pixel, uchar *edges, int height, int width);*/
    uchar *mooreNeighborTracing(uchar *image, int width, int height);
    uchar * padImage(uchar *image, int width, int height, int paddingColor);
    uchar *anotherTracing(uchar *image,std::vector<place> &pixels, int width, int height);
    uchar *RemovePadding(uchar *targetImage, int width, int height);
    place getPixel(int pos,int height,int width);
};

#endif