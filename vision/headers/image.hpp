#ifndef imageheadervar
#define imageheadervar

#include"card.hpp"
#include"Shape.hpp"
#include<vector>
//#include"enums.hpp"
#include"EdgeKernel.hpp"
#include"BlurKernel.hpp"
#include"place.hpp"
#include <opencv2/opencv.hpp>
#include "Moore.hpp"
#include"SinglePixelKernel.hpp"

class image
{
private:
    /* data */
    EdgeKernel edgeKernel;
    BlurKernel blurKernel;
    SinglePixelKernel singleKernel;
    std::vector<std::vector<uchar>> originalImage;
    card cardList[25];
    std::vector<Shape> shapeList;
    int width;
    int height;
    cv::Mat picture;
    MooreNeighborhood moore;
    //uchar *blurredImage;
    //uchar *edgeMatrix;
public:
    image(BlurKernel, EdgeKernel,SinglePixelKernel, cv::Mat);
    ~image();
std::vector<card> GetCardList();
void  BlurImage(uchar *picture);
void DetectEdges(uchar *picture, uchar *result);
std::vector<Shape> DetectShapes(uchar *edgeMatrix);
std::vector<card>  DetermenCards(std::vector<Shape> Shapes);

int GetWidth();
int GetHeight();
void SetWidth(int);
void SetHeight(int);

MoveDirection newMoveDir(MoveDirection oldDirection);
MoveDirection NextMoveDir(MoveDirection oldDirection);
place GetPixel(MoveDirection moveDir, place currentPixel, int width, int height);
bool IsPixelLine(MoveDirection moveDir, place currentPixel, uchar *edgeMatrix);

std::vector<Shape> DetectShapes2(uchar * edgeMatrix, std::vector<Shape> shapes);
bool RemovePixelsFromPicture(std::vector<place> pixels,  uchar *edges);
place GetNextPixel(place current, int height, int width);
bool RemovePixelsFromPicture(place pixel, uchar *edges);
void RemovePixelsFromPicture(uchar *image, uchar* pixelsToRemove, int width,int height);

bool removeSinglePixels(uchar *image, int width, int height);

void NewMat(cv::Mat);
};
#endif
