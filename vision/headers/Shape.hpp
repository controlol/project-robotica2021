#ifndef shapeheader
#define shapeheader
#include"place.hpp"
#include <vector>
#include <opencv2/opencv.hpp>
class Shape
{
private:
    /* data */
    //list of pixels
    std::vector<place> pixels;
    uchar *shapeImage;
    int LowerAreaThreshold = 600;
    int width, height;
    std::vector<place> corners;
public:
    Shape(std::vector<place> listOfPixels);
    Shape(std::vector<cv::Point> listOfPixels);
    Shape(uchar *shapeImage,std::vector<place> listOfPixels);
    Shape();
    ~Shape();

    bool IsShapeSquare();
    bool IsBiggestShape();
    bool IsThisShapeACard(int width, int height);

    std::vector<place> DouglasPeucker(std::vector<place>pointList, double epsilon);
    double PerpendicularDistance(place point, double * formula);
    double *GetLine(place point1, place point2);
    cv::Mat CutOutShape(std::vector<place> points, int width, int height, cv::Mat originalImage);
    double lenght(cv::Point *p1, cv::Point *p2);
     std::vector<place> GetCorners();
};
#endif

