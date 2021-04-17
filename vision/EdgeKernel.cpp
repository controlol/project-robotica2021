#include "EdgeKernel.hpp"

//#define DEBUG false
#ifdef DEBUG
#endif

std::vector<std::vector<uchar>> EdgeKernel::FindEdgeMatrix(std::vector<std::vector<uchar>> picture, int width, int height)
{
  std::vector<std::vector<uchar>> edgeMatrix;
  std::vector<std::vector<uchar>> hor;
  std::vector<std::vector<uchar>> ver;
  std::vector<std::vector<uchar>> resultAngle;
  std::vector<std::vector<uchar>> resultWeight;
  hor = OverlayKernel(picture, width, height);
  std::cout << "gotten horizontal" << std::endl;
  TurnKernel(true);
  ver = OverlayKernel(picture, width, height);
  std::cout << "gotten vertical" << std::endl;
  TurnKernel(false);
  GetWeightedMatrix(hor, ver, width, height);
  GetAngleMatrix(hor, ver, width, height);
  TraceAlongEdges(resultWeight, resultAngle, width, height);
  return edgeMatrix;
}

std::vector<std::vector<uchar>> EdgeKernel::GetWeightedMatrix(std::vector<std::vector<uchar>> hor, std::vector<std::vector<uchar>> ver, int width, int height)
{
  std::vector<std::vector<uchar>> resultWeight;
  for (int i = 0; i < width; i++)
  {
    for (int j = 0; j < height; j++)
    {
      resultWeight[i][j] = sqrt(pow(hor[i][j] + 0.0, 2.0) + pow(ver[i][j] + 0.0, 2.0));
    }
  }
  return resultWeight;
}
std::vector<std::vector<uchar>> EdgeKernel::GetAngleMatrix(std::vector<std::vector<uchar>> hor, std::vector<std::vector<uchar>> ver, int width, int height)
{
  std::vector<std::vector<uchar>> resultAngle;
  double temp;
  int newAngle;
  for (int i = 0; i < width; i++)
  {
    for (int j = 0; j < height; j++)
    {

      temp = atan2(ver[i][j] + 0.0, hor[i][j] + 0.0) * 180 / 3.14159265;

      /* Convert actual edge direction to approximate value */
      if (((temp < 22.5) && (temp > -22.5)) || (temp > 157.5) || (temp < -157.5))
        newAngle = 0;
      if (((temp > 22.5) && (temp < 67.5)) || ((temp < -112.5) && (temp > -157.5)))
        newAngle = 45;
      if (((temp > 67.5) && (temp < 112.5)) || ((temp < -67.5) && (temp > -112.5)))
        newAngle = 90;
      if (((temp > 112.5) && (temp < 157.5)) || ((temp < -22.5) && (temp > -67.5)))
        newAngle = 135;

      resultAngle[i][j] = newAngle;
    }
  }
  return resultAngle;
}

std::vector<std::vector<uchar>> EdgeKernel::TraceAlongEdges(std::vector<std::vector<uchar>> resultWeight, std::vector<std::vector<uchar>> resultAngle, int width, int height)
{
  /*
          N
      W   +   E
          Z
    */
  std::vector<std::vector<uchar>> edgeMatrix;
  for (int i = 0; i < width; i++)
  {
    for (int j = 0; j < height; j++)
    {
      if (resultWeight[i][j] > this->lowerThreshold)
      {
        if (resultAngle[i][j] = 0)
        {
          //compare east and west pixels
          //thats done with j
          if (resultWeight[i][j] > resultWeight[i][j - 1] && resultWeight[i][j] > resultWeight[i][j + 1])
          {
            edgeMatrix[i][j] = 1;
          }
          else
          {
            edgeMatrix[i][j] = 0;
          }
        }
        if (resultAngle[i][j] = 90)
        {
          //compare north and south pixels
          //thats done with i
          if (resultWeight[i][j] > resultWeight[i - 1][j] && resultWeight[i][j] > resultWeight[i + 1][j])
          {
            edgeMatrix[i][j] = 1;
          }
          else
          {
            edgeMatrix[i][j] = 0;
          }
        }
        if (resultAngle[i][j] = 135)
        {
          //compare north-west and south-east pixels
          //i-1 j-1 and i+1 j+1
          if (resultWeight[i][j] > resultWeight[i - 1][j - 1] && resultWeight[i][j] > resultWeight[i + 1][j + 1])
          {
            edgeMatrix[i][j] = 1;
          }
          else
          {
            edgeMatrix[i][j] = 0;
          }
        }
        if (resultAngle[i][j] = 45)
        {
          //compare north-east and south-west pixels
          //i-1 j+1 and i+1 j-1
          if (resultWeight[i][j] > resultWeight[i - 1][j + 1] && resultWeight[i][j] > resultWeight[i + 1][j - 1])
          {
            edgeMatrix[i][j] = 1;
          }
          else
          {
            edgeMatrix[i][j] = 0;
          }
        }
      }
    }
  }
  return edgeMatrix;
}

void EdgeKernel::FindEdgeMatrix2(uchar *picture, uchar *returnMatrix, int width, int height)
{
  int edgeMatrix[width * height];
  int hor[width * height];
  int ver[width * height];
  int resultAngle[width * height];
  int resultWeight[width * height];
  OverlayKernel2(picture, hor, width, height);
#ifdef DEBUG
  std::cout << "gotten horizontal" << std::endl;

  auto horizontal = cv::Mat(height, width, CV_8UC1);
  for (auto x = 0; x < height; x++)
  {
    for (auto y = 0; y < width; y++)
    {
      horizontal.at<uchar>(x, y) = hor[x * width + y] + 128;
    }
  }

  cv::imshow("horizontal", horizontal);
#endif
  TurnKernel(true);
#ifdef DEBUG
  std::cout << "turned kernel" << std::endl;
#endif
  OverlayKernel2(picture, ver, width, height);

#ifdef DEBUG
  std::cout << "gotten vertical" << std::endl;

  auto vertical = cv::Mat(height, width, CV_8UC1);
  for (auto x = 0; x < height; x++)
  {
    for (auto y = 0; y < width; y++)
    {
      vertical.at<uchar>(x, y) = ver[x * width + y] + 128;
    }
  }

  cv::imshow("vertical", vertical);
#endif
  TurnKernel(false);
  GetWeightedMatrix2(hor, ver, resultWeight, width, height);
#ifdef DEBUG
  std::cout << "gotten weighted matrix" << std::endl;

  auto stength = cv::Mat(height, width, CV_8UC1);
  for (auto x = 0; x < height; x++)
  {
    for (auto y = 0; y < width; y++)
    {
      stength.at<uchar>(x, y) = resultWeight[x * width + y];
    }
  }

  cv::imshow("resultWeight", stength);
#endif
  GetAngleMatrix2(hor, ver, resultAngle, width, height);
#ifdef DEBUG
  std::cout << "gotten angle matrix" << std::endl;

  auto angle = cv::Mat(height, width, CV_8UC1);
  for (auto x = 0; x < height; x++)
  {
    for (auto y = 0; y < width; y++)
    {
      angle.at<uchar>(x, y) = resultAngle[x * width + y];
    }
  }

  cv::imshow("angle", angle);
#endif
  TraceAlongEdges2(resultWeight, resultAngle, edgeMatrix, width, height);
#ifdef DEBUG
  std::cout << "gotten edge matrix" << std::endl;
#endif
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      returnMatrix[i * width + j] = edgeMatrix[i * width + j];
    }
  }
#ifdef DEBUG
  std::cout << "returning from finding the edges" << std::endl;
#endif
}

void EdgeKernel::GetWeightedMatrix2(int *hor, int *ver, int *resultWeight, int width, int height)
{
  for (int i = 0; i < width; i++)
  {
    for (int j = 0; j < height; j++)
    {
      resultWeight[i * width + j] = sqrt(pow(static_cast<double>(hor[i * width + j]), 2.0) + pow(static_cast<double>(ver[i * width + j]), 2.0)) / sqrt(2);
    }
  }
}
void EdgeKernel::GetAngleMatrix2(int *hor, int *ver, int *resultAngle, int width, int height)
{
  double angle;
  int newAngle;
  for (int i = 0; i < width; i++)
  {
    for (int j = 0; j < height; j++)
    {

      angle = atan(hor[i * width + j] / (double)ver[i * width + j]) * (180 / 3.14159265);

      if (angle >= 67.5 || angle < -67.5)
      {
        newAngle = 90;
      }
      else if (angle >= 22.5)
      {
        newAngle = 135;
      }
      else if (angle >= -22.5)
      {
        newAngle = 0;
      }
      else if (angle >= -67.5)
      {
        newAngle = 45;
      }

      //std::cout<<"calculated angle"<<std::endl;
      /* Convert actual edge direction to approximate value */

      /*
      if (((temp < 22.5) && (temp > -22.5)) || (temp > 157.5) || (temp < -157.5))
        newAngle = 0;
      if (((temp > 22.5) && (temp < 67.5)) || ((temp < -112.5) && (temp > -157.5)))
        newAngle = 135;
      if (((temp > 67.5) && (temp < 112.5)) || ((temp < -67.5) && (temp > -112.5)))
        newAngle = 90;
      if (((temp > 112.5) && (temp < 157.5)) || ((temp < -22.5) && (temp > -67.5)))
        newAngle = 45;
        */
      //std::cout<<"gotten angle:  "<<newAngle<<std::endl;
      resultAngle[i * width + j] = newAngle;
    }
  }
}

void EdgeKernel::TraceAlongEdges2(int *resultWeight, int *resultAngle, int *edgeMatrix, int width, int height)
{
  /*
          N
      W   +   E
          Z
    */
  //std::vector<std::vector<uchar>> edgeMatrix;
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
#ifdef DEBUG
      std::cout << "pixel: " << i << "   " << j << std::endl;
      std::cout << "width  height:  " << width << "  " << height << std::endl;
#endif
      if (resultWeight[i * width + j] > this->lowerThreshold)
      {
        if (resultAngle[i * width + j] == 0)
        {
          //std::cout << "angle = 0" << std::endl;
          //compare east and west pixels
          //thats done with j
          if (resultWeight[i * width + j] >= resultWeight[i * width + (j - 1)] && resultWeight[i * width + j] >= resultWeight[i * width + (j + 1)])
          {
            //std::cout << "this is the edge " << std::endl;
            edgeMatrix[i * width + j] = 255;
          }
          else
          {
            //std::cout << "this is NOT the edge" << std::endl;
            edgeMatrix[i * width + j] = 0;
          }
        }
        if (resultAngle[i * width + j] == 90)
        {
          //std::cout << "angle = 90" << std::endl;
          //compare north and south pixels
          //thats done with i
          if (resultWeight[i * width + j] >= resultWeight[(i - 1) * width + j] && resultWeight[i * width + j] >= resultWeight[(i + 1) * width + j])
          {
            //std::cout << "this is the edge " << std::endl;
            edgeMatrix[i * width + j] = 255;
          }
          else
          {
            //std::cout << "this is NOT the edge" << std::endl;
            edgeMatrix[i * width + j] = 0;
          }
        }
        if (resultAngle[i * width + j] == 135)
        {
          //std::cout << "angle = 135" << std::endl;
          //compare north-west and south-east pixels
          //i-1 j-1 and i+1 j+1
          if (resultWeight[i * width + j] >= resultWeight[(i - 1) * width + (j - 1)] && resultWeight[i * width + j] >= resultWeight[(i + 1) * width + (j + 1)])
          {
            //std::cout << "this is the edge " << std::endl;
            edgeMatrix[i * width + j] = 255;
          }
          else
          {
            //std::cout << "this is NOT the edge" << std::endl;
            edgeMatrix[i * width + j] = 0;
          }
        }
        if (resultAngle[i * width + j] == 45.0)
        {
          //std::cout << "angle = 45" << std::endl;
          //compare north-east and south-west pixels
          //i-1 j+1 and i+1 j-1
          if (resultWeight[i * width + j] >= resultWeight[(i - 1) * width + (j + 1)] && resultWeight[i * width + j] >= resultWeight[(i + 1) * width + (j - 1)])
          {
            //std::cout << "this is the edge " << std::endl;
            edgeMatrix[i * width + j] = 255;
          }
          else
          {
            //std::cout << "this is NOT the edge" << std::endl;
            edgeMatrix[i * width + j] = 0;
          }
        }
      }
      else
      {
        edgeMatrix[i * width + j] = 0;
      }
    }
  }
}

EdgeKernel::EdgeKernel(/* args */)
{
  //kernel= {1,1,1},
  //      {0,0,0},
  //    {-1,-1,-1};
  this->lowerThreshold = 50;
  signed char temp[3][3] = {1, 2, 1,
                            0, 0, 0,
                            -1, -2, -1};
  kernel.resize(3, std::vector<signed char>(3));
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      kernel[i][j] = temp[i][j];
    }
  }
}

EdgeKernel::~EdgeKernel()
{
}