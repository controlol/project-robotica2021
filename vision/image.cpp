
#include "image.hpp"

image::image(BlurKernel blur, EdgeKernel edge, cv::Mat image)
{
    picture = image;
    blurKernel = blur;
    edgeKernel = edge;
    std::vector<uchar> temp;
    /*if (image.isContinuous())
    {
        temp.assign(image.data, image.data + image.total() * image.channels());
    }
    else
    {
        for (int i = 0; i < image.rows; ++i)
        {
            temp.insert(temp.end(), image.ptr<uchar>(i), image.ptr<uchar>(i) + image.cols * image.channels());
        }
    }
    this->width = image.rows;
    this->height = image.cols;
    originalImage.resize(image.rows,std::vector<uchar>(image.cols));
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            originalImage[i][j]=temp[image.rows*i+j];             
        }
        
    }*/
    
}
image::~image()
{
    
}
std::vector<card> image::GetCardList()
{
    std::vector<card> returnCards;
    std::vector<Shape> shapes;
    uchar blurredImage[width*height];
    uchar edgeMatrix[width*height];
    BlurImage(blurredImage);
    DetectEdges(blurredImage, edgeMatrix);
    shapes = DetectShapes(edgeMatrix);
    for (int i = 0; i < shapes.size(); i++)
    {
        //remember shapes that are square
        if (shapes[i].IsShapeSquare() == false)
        {
            shapes.erase(shapes.begin() + i);
        }
    }

    returnCards = DetermenCards(shapes);
    return returnCards;
}

void image::DetectEdges(uchar *picture, uchar *edgeMatrix)
{
    //std::vector<std::vector<uchar>> edgeMatrix;
    //edgeMatrix.resize(width,std::vector<uchar>(height));
    edgeKernel.FindEdgeMatrix2(picture, edgeMatrix, GetWidth(), GetHeight());
    //return edgeMatrix;
}

std::vector<Shape> image::DetectShapes(uchar * edgeMatrix)
{
    std::vector<Shape> shapes;
    MoveDirection moveDir = E;
    std::vector<place> shapeList;
    place currentPixel;
    int timesFoundStart = 2;
    int width = GetWidth();
    int height = GetHeight();
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < GetHeight(); j++)
        {
            if (edgeMatrix[i*width+j] == 1)
            {
                shapeList.push_back(place());
                currentPixel = place();
                break;
            }
        }
    }
    moveDir = newMoveDir(moveDir);
    while (!shapeList.empty() || timesFoundStart != 0)
    {
        if (IsPixelLine(moveDir, currentPixel, edgeMatrix))
        {
            currentPixel = GetPixel(moveDir, currentPixel);
            moveDir = newMoveDir(moveDir);
            if (shapeList.end() == shapeList.begin() && shapeList.size() > 2)
            {
                Shape shape = Shape();
                shapes.push_back(shape);
                break;
            }
            else if (shapeList.end() == shapeList.begin() && shapeList.size() == 2)
            {
                timesFoundStart--;
            }
        }
        else
        {
            moveDir = NextMoveDir(moveDir);
        }
    }
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            for (int k = 0; k < shapeList.size(); k++)
            {
                if (shapeList[k].GetX() == i && shapeList[k].GetY() == j)
                {
                    edgeMatrix[i*width+j] = 0;
                }
            }
        }
    }
    if (shapeList.size() > 15)
    {
        shapes = DetectShapes(edgeMatrix);
    }

    return shapes;
}

std::vector<card> image::DetermenCards(std::vector<Shape> shapes)
{
     std::vector<card> cards;
    for (int i = 0; i < shapes.size(); i++)
    {
        cards.push_back(card());
        cards[i].DetermenRank();
        cards[i].DetermenSuit();
    }
    return cards;
}
void image::BlurImage(uchar *returnMatrix)
{
    //std::vector<std::vector<uchar>> returnMatrix;
    //returnMatrix.resize(this->width,std::vector<uchar>(this->height));
    std::cout << "came before the gaussian blur"<<std::endl;
    blurKernel.blur4(picture.data, returnMatrix, GetWidth(), GetHeight());

    //cv::Mat blurMatrix;
    //blurKernel.guassian_blur2D(picture.data, blurMatrix.data, picture.rows, picture.cols);
    //cv::namedWindow("blurred", cv::WINDOW_AUTOSIZE);
    //cv::imshow("blurred", blurMatrix);

    //return returnMatrix;
}

int image::GetWidth()
{
    return this->width;
}
int image::GetHeight()
{
    return this->height;
}


MoveDirection image::newMoveDir(MoveDirection oldDirection)
{
    MoveDirection newMoveDir;
    //get move direction 2 counter clock wise from old direction
    //return direction
    return newMoveDir;
}

MoveDirection image::NextMoveDir(MoveDirection oldDirection)
{
    MoveDirection newMoveDir;
    //get move direction 1 clock wise from old direction
    //return direction
    return newMoveDir;
}

place image::GetPixel(MoveDirection moveDir, place currentPixel)
{
    place pixel = place();
    switch (moveDir)
    {
    case N:
        pixel.SetX(currentPixel.GetX() - 1);
        pixel.SetY(currentPixel.GetY());
        break;
    case NE:

        pixel.SetX(currentPixel.GetX() - 1);
        pixel.SetY(currentPixel.GetY() + 1);
        break;
    case E:

        pixel.SetX(currentPixel.GetX());
        pixel.SetY(currentPixel.GetY() + 1);
        break;
    case ES:

        pixel.SetX(currentPixel.GetX() + 1);
        pixel.SetY(currentPixel.GetY() + 1);
        break;
    case S:

        pixel.SetX(currentPixel.GetX() + 1);
        pixel.SetY(currentPixel.GetY());
        break;
    case SW:

        pixel.SetX(currentPixel.GetX() + 1);
        pixel.SetY(currentPixel.GetY() - 1);
        break;
    case W:

        pixel.SetX(currentPixel.GetX());
        pixel.SetY(currentPixel.GetY() - 1);
        break;
    case NW:

        pixel.SetX(currentPixel.GetX() - 1);
        pixel.SetY(currentPixel.GetY() - 1);
        break;

    default:
        pixel.SetX(currentPixel.GetX());
        pixel.SetY(currentPixel.GetY());
        break;
    }
    return pixel;
}

bool image::IsPixelLine(MoveDirection moveDir, place currentPixel, uchar *edgeMatrix)
{
    bool isPixelLine = false;

    switch (moveDir)
    {
    case N:
        if (edgeMatrix[(currentPixel.GetX() - 1)*GetWidth() + currentPixel.GetY()] == 1)
        {
            isPixelLine = true;
        }

        break;
    case NE:
        if (edgeMatrix[(currentPixel.GetX() - 1)*GetWidth() + (currentPixel.GetY() + 1)] == 1)
        {
            isPixelLine = true;
        }

        break;
    case E:
        if (edgeMatrix[currentPixel.GetX()*GetWidth() + (currentPixel.GetY() + 1)] == 1)
        {
            isPixelLine = true;
        }

        break;
    case ES:
        if (edgeMatrix[(currentPixel.GetX() + 1)*GetWidth() + (currentPixel.GetY() + 1)] == 1)
        {
            isPixelLine = true;
        }

        break;
    case S:
        if (edgeMatrix[(currentPixel.GetX() + 1)*GetWidth() + currentPixel.GetY()] == 1)
        {
            isPixelLine = true;
        }

        break;
    case SW:
        if (edgeMatrix[(currentPixel.GetX() + 1)*GetWidth() + (currentPixel.GetY() - 1)] == 1)
        {
            isPixelLine = true;
        }

        break;
    case W:
        if (edgeMatrix[currentPixel.GetX()*GetWidth() + (currentPixel.GetY() - 1)] == 1)
        {
            isPixelLine = true;
        }

        break;
    case NW:
        if (edgeMatrix[(currentPixel.GetX() - 1)*GetWidth() + (currentPixel.GetY() - 1)] == 1)
        {
            isPixelLine = true;
        }

        break;

    default:
        break;
    }
    return isPixelLine;
}
