#include "Shape.hpp"

const uchar WHITE = 255;
const uchar BLACK = 0;

bool Shape::IsShapeSquare()
{
    bool answer = false; 
    if(pixels.empty())  
        return false;
    GetCorners();
    std::vector<int> tempIndexes;
    for (int i = 0; i < corners.size(); i++)
    {
        place prevPoint = corners[(i - 1) >= 0 ? i - 1 : corners.size() - 1];
        place currentPoint = corners[i];
        place nextPoint = corners[(i + 1) < corners.size() ? i + 1 : 0];
        // double *Line1 =GetLine(prevPoint,currentPoint);
        //double *Line2 =GetLine(nextPoint,currentPoint);
        double ab = GetDistance(prevPoint, currentPoint);
        double bc = GetDistance(nextPoint, currentPoint);
        double ac = GetDistance(prevPoint, nextPoint);
        double cosb = pow(ac, 2) - pow(ab, 2) - pow(bc, 2);
        cosb = cosb / (2 * ab * bc);
        double angle = 180 - acos(cosb) * 180 / M_PI;
        if (angle > 120)
            tempIndexes.push_back(i);
        std::cout << "angle between the points is: " << angle;
        //if(prevPoint.GetX())
    }
    for (int i = 0; i < tempIndexes.size(); i++)
    {
        std::cout << "point " << i << " will be removed\n";
        corners.erase(corners.begin() + tempIndexes[i]);
    }
    std::cout << "corner size: " << corners.size() << std::endl;
    if (corners.size() == 4)
    {
        // IsPointWrong(corners);
        answer = true;
    }
    return answer;
}

/*void IsPointWrong(std::vector<place> corners)
{
    int margex=0;
    int margey=0;

    double upper = GetDistance(corners[0],corners[3]);
    double lower = GetDistance(corners[1],corners[2]);
    double left = GetDistance(corners[0],corners[1]);
    double right = GetDistance(corners[3],corners[2]);
    if(upper<margex-5){
        double deltax = corners[3].GetX() - corners[0].GetX();
        double deltay = corners[3].GetY() - corners[0].GetY();
        double a = deltay / deltax;
        double dx = margex/sqrt(1+pow(a,2));
        double dy = margex-dx;
        if(lower>margex-5&&lower<margex+5){
            if(corners[0].GetX())
        }
    }
    else if(upper > margex+5 && right < margey-5){
        double deltax = corners[3].GetX() - corners[0].GetX();
        double deltay = corners[3].GetY() - corners[0].GetY();
        double a = deltay / deltax;
        double dx = margex/sqrt(1+pow(a,2));
        double dy = margex-dx;
    }

        
}
*/
double Shape::GetDistance(place p1, place p2)
{
    return sqrt(pow(p2.GetX() - p1.GetX(), 2) + pow(p2.GetY() - p1.GetY(), 2));
}

std::vector<place> Shape::GetCorners()
{
    std::cout << "corners?\n";
    //std::vector<cv::Point> out;
    //cv::approxPolyDP(cvPixels, out, 12, true);
    //if (out.size() == 4)
        //std::cout << "Opencv calls it a square\n";
    if (corners.empty())
        corners = DouglasPeucker(pixels, 10);
    std::cout << "amount of corners:  " << corners.size() << std::endl;
    for (int i = 0; i < corners.size(); i++)
    {
        std::cout << "corner " << corners[i] << std::endl;
    }
    return corners;
}

bool Shape::IsThisShapeACard(int width, int height)
{
    place mostLeft = place(0, width);
    place mostRight = place(0, 0);
    place top = place(0, height);
    place bottom = place(0, 0);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            //get the most top pixel
            if (y < top.GetY() && shapeImage[y * width + x] == BLACK)
            {
                top.ChangeXY(x, y);
            }
            //get the bottom most pixel
            if (y > bottom.GetY() && shapeImage[y * width + x] == BLACK)
            {
                bottom.ChangeXY(x, y);
            }
            //get the most left pixel
            if (x < mostLeft.GetX() && shapeImage[y * width + x] == BLACK)
            {
                mostLeft.ChangeXY(x, y);
            }
            //get the right most pixel
            if (x > mostRight.GetX() && shapeImage[y * width + x] == BLACK)
            {
                mostRight.ChangeXY(x, y);
            }
        }
    }
    //place topRight = place(mostRight.GetX(),top.GetY());
    //place topLeft = place(mostLeft.GetX(),top.GetY());
    //place bottomRight = place(mostRight.GetX(),bottom.GetY());
    //place bottomLeft = place(mostLeft.GetX(),bottom.GetY());
    int width2 = mostLeft.GetX() - mostRight.GetX();
    int height2 = top.GetY() - bottom.GetY();
    std::cout << "the area is: " << width2 * height2 << std::endl;
    if (width2 * height2 >= LowerAreaThreshold)
    {

        return true;
    }

    return false;
}

std::vector<place> Shape::DouglasPeucker(std::vector<place> pointList, double epsilon)
{
    //std::cout<<"Recursive algorithm"<<std::endl;
    if (pointList.empty())
    {
        std::cout << "YO SOMETHING IS WRONG IN Shape.cpp DouglasPeucker()" << std::endl;
    }
    double dMax = 0;
    int index = 0;
    int end = pointList.size() - 1;
    double distance = 0;
    for (int i = 0; i < end - 1; i++)
    {
        distance = PerpendicularDistance(pointList[i], GetLine(pointList[0], pointList[end]));
        if (distance > dMax)
        {
            //std::cout<<"distance > dmax"<<std::endl;
            index = i;
            dMax = distance;
        }
    }
    std::vector<place> resultList, recursive1, recursive2;

    if (dMax > epsilon)
    {
        std::vector<place> first(pointList.begin(), pointList.begin() + index + 1);
        std::vector<place> second(pointList.begin() + index, pointList.end());

        recursive1 = DouglasPeucker(first, epsilon);
        recursive2 = DouglasPeucker(second, epsilon);

        //resultList.reserve( recursive1.size() + recursive2.size() ); // preallocate memory
        resultList.assign(recursive1.begin(), recursive1.end() - 1);
        resultList.insert(resultList.end(), recursive2.begin(), recursive2.end());
    }
    else
    {
        resultList.push_back(pointList[0]);
        resultList.push_back(pointList[end]);
        //resultList=pointList;
    }
    //std::cout<<"result: "<<resultList.size()<<std::endl;
    return resultList;
}

double Shape::PerpendicularDistance(place point, double *formula)
{
    //the formula contains 3 numbers. A B C for the formula Ax + By + C = 0
    return fabs((formula[0] * point.GetX() + formula[1] * point.GetY() + formula[2])) / (sqrt(formula[0] * formula[0] + formula[1] * formula[1]));
}
double *Shape::GetLine(place point1, place point2)
{
    static double formula[3];
    double deltax = point2.GetX() - point1.GetX();
    double deltay = point2.GetY() - point1.GetY();
    double a = deltay / deltax;
    double b = static_cast<double>(point1.GetY()) - a * static_cast<double>(point1.GetX());
    formula[0] = -a;
    formula[1] = 1;
    formula[2] = -b;
    return formula;
}

cv::Mat Shape::CutOutShape(std::vector<place> points, int width, int height, cv::Mat originalImage)
{
    std::cout << "starting the cutout" << std::endl;
    if (points.size() < 4)
        return originalImage;
    // int x = points[0].GetX();
    //int y = points[0].GetY();
    cv::Point corners[1][4];
    /*corners[0][0].x = height;   //top left
    corners[0][0].y = width;
    std::cout<<"dddd"<<std::endl;
    corners[0][1].x = 0;        //top right
    corners[0][1].y = width;
    std::cout<<"aaa"<<std::endl;
    corners[0][2].x = height;   //bottem left
    corners[0][2].y = 0;
    std::cout<<"bbb"<<std::endl;
    corners[0][3].x = 0;        //bottem right
    corners[0][3].y = 0;*/
    //cv::Point topRight = place(0,width);
    //cv::Point topLeft = place(height,width);
    //cv::Point bottomRight =place(0,0);
    //cv::Point bottomLeft =place(height,0);
    //int min, max;
    int topleft = height + width;
    int topRight = 0;
    int bottomleft = topleft;
    int bottemright = topRight;
    std::cout << "going to search the corners" << std::endl;
    /* for (int i = 0; i < points.size() - 1; i++)
    {
        if (corners[0][0].x > points[i].GetX() && corners[0][0].y > points[i].GetY())
        {
            corners[0][0].x = points[i].GetX();
            corners[0][0].y = points[i].GetY();
        }
        else if (corners[0][1].x < points[i].GetX() && corners[0][1].y > points[i].GetY())
        {
            corners[0][1].x = points[i].GetX();
            corners[0][1].y = points[i].GetY();
        }
        else if (corners[0][2].x > points[i].GetX() && corners[0][2].y < points[i].GetY())
        {
            corners[0][2].x = points[i].GetX();
            corners[0][2].y = points[i].GetY();
        }
        else if (corners[0][3].x < points[i].GetX() && corners[0][3].y < points[i].GetY())
        {
            corners[0][3].x = points[i].GetX();
            corners[0][3].y = points[i].GetY();
        }
    }*/
    for (int i = 0; i < points.size(); i++)
    {
        if (points[i].GetX() == 0 || points[i].GetY() == 0)
        {
            std::cout << "one of the coordinates is 0" << std::endl;
            continue;
        }
        if ((points[i].GetX() + points[i].GetY()) < topleft)
        {
            topleft = (points[i].GetX() + points[i].GetY());
            corners[0][0].x = points[i].GetX();
            corners[0][0].y = points[i].GetY();
            std::cout << "found topleft" << std::endl;
        }
        if ((points[i].GetX() - points[i].GetY()) > topRight)
        {
            topRight = (points[i].GetX() - points[i].GetY());
            corners[0][1].x = points[i].GetX();
            corners[0][1].y = points[i].GetY();
            std::cout << "found topright" << std::endl;
        }
        if ((points[i].GetX() + points[i].GetY()) > bottemright)
        {
            bottemright = (points[i].GetX() + points[i].GetY());
            corners[0][2].x = points[i].GetX();
            corners[0][2].y = points[i].GetY();
            std::cout << "found bottomright" << std::endl;
        }
        if ((points[i].GetX() - points[i].GetY()) < bottomleft)
        {
            bottomleft = (points[i].GetX() - points[i].GetY());
            corners[0][3].x = points[i].GetX();
            corners[0][3].y = points[i].GetY();
            std::cout << "found bottomleft " << std::endl;
        }
    }

    std::cout << "calculating the length" << std::endl;
    double cardwidth = lenght(corners[0], corners[1]);
    double cardlength = lenght(corners[0], corners[3]);
    /*if (cardwidth > cardlength)
    {
        std::cout<<"rotating angles"<<std::endl;
        cv::Point temp = corners[0][0];
        corners[0][0] = corners[0][3];
        corners[0][3] = corners[0][2];
        corners[0][2] = corners[0][1];
        corners[0][1] = temp;
    }*/
    std::cout << "cutout shape" << std::endl;
    /* const cv::Point *corner_list[1] = {corners[0]};
    int num_points = 4;
    int num_polygons = 1;
    int line_type = 8;
    cv::Mat mask(height,width, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::fillPoly(mask, corner_list, &num_points, num_polygons, cv::Scalar(255, 255, 255), line_type);
std::cout<<"actual cut out"<<std::endl;
    cv::Mat result;
    cv::bitwise_and(originalImage, mask, result);
    cv::imshow("ujyhtgrfde",result);*/
    std::vector<cv::Point2f> source, dest;
    std::cout << "corners from left to right" << points[0] << "] [" << points[1] << "] [" << points[2] << "] [" << points[3] << "] [" << points[4] << std::endl;
    std::cout << "corners from left to right" << corners[0][0] << " " << corners[0][1] << " " << corners[0][2] << " " << corners[0][3] << std::endl;
    source.push_back(corners[0][0]);
    source.push_back(corners[0][1]);
    source.push_back(corners[0][3]);
    source.push_back(corners[0][2]);
    int outputWidth = 250;
    int outputHeight = 325;
    cv::Mat outputImage(outputWidth, outputHeight, originalImage.type());
    dest.push_back(cv::Point2f(0, 0));
    dest.push_back(cv::Point2f(outputWidth, 0));
    dest.push_back(cv::Point2f(0, outputHeight));
    dest.push_back(cv::Point2f(outputWidth, outputHeight));
    std::cout << "get perspective stuff" << std::endl;
    cv::Mat warpMatrix = cv::getPerspectiveTransform(source, dest);
    if (warpMatrix.empty())
        std::cout << "The warp perspevtive gettinh wnt wrong" << std::endl;
    std::cout << "warp shape" << std::endl;
    try
    {
        cv::warpPerspective(originalImage, outputImage, warpMatrix, cv::Size(outputWidth, outputHeight));
    }
    catch (const cv::Exception &ex)
    {
        std::cout << "Exeption warping image: " << ex.what() << std::endl;
    }
    cv::imshow("sdhlfhsod", outputImage);
    std::cout << "whoooohoooo" << std::endl;

    //cv::cvtColor(outputImage, outputImage, cv::COLOR_BGR2GRAY)   ;
    //cv::threshold(outputImage,outputImage,30,255,1);
    //cv::Mat dst;
    //cv::threshold(outputImage, dst, 150, 200, cv::THRESH_BINARY);
    //cv::imshow("dfdfdfdfdf",dst);
    return outputImage;
}

double Shape::lenght(cv::Point *p1, cv::Point *p2)
{
    double x = p2->x - p1->x;
    double y = p2->y - p1->y;
    return sqrt(pow(x, 2) + pow(y, 2));
}

Shape::Shape(uchar *shapeImage, std::vector<place> listOfPixels)
{
    //std::cout<<"new shape"<<std::endl;
    this->shapeImage = shapeImage;
    this->pixels = listOfPixels;
}
/*outdated do not use! UNLESS you don't plan on using the check for card function*/
Shape::Shape(std::vector<place> listOfPixels)
{
    this->pixels = listOfPixels;
}

Shape::Shape(std::vector<cv::Point> listOfPixels)
{
    //cvpixels=listOfPixels;
    //polylines(pixelsCV, listOfPixels, true, cv::Scalar(255));
    std::vector<place> newList;
    for (size_t i = 0; i < listOfPixels.size(); i++)
    {
        newList.push_back(place(listOfPixels[i].x, listOfPixels[i].y));
    }
    std::cout<<listOfPixels.size();
    std::vector<cv::Point> out=listOfPixels;
    cv::approxPolyDP(listOfPixels,out,12,true);
    std::cout<<out.size();
    for (size_t i = 0; i < out.size(); i++)
    {
        this->corners.push_back(place(out[i].x,out[i].y));
    }
    this->pixels = newList;
}

Shape::~Shape()
{
    //delete shapeImage;
}
Shape::Shape()
{
}