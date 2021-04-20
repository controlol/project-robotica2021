
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
    uchar blurredImage[width * height];
    uchar edgeMatrix[width * height];
    BlurImage(blurredImage);
    DetectEdges(blurredImage, edgeMatrix);
    //shapes = DetectShapes(edgeMatrix);
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
/*
std::vector<Shape> image::DetectShapes(uchar * edgeMatrix)
{
    std::vector<Shape> shapes;
    MoveDirection moveDir = E;
    std::vector<place> shapeList;
    place currentPixel = place(0,0);
    int timesFoundStart = 2;
    int width = GetWidth();
    int height = GetHeight();
    //for every pixel that is white, put it in a list as a place
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (edgeMatrix[i*width+j] == 255)
            {
                shapeList.push_back(place(i,j));
                
                break;
            }
        }
    }
    moveDir = newMoveDir(moveDir);
    currentPixel.ChangeXY(shapeList[0].GetX(),shapeList[0].GetY());
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
*/
std::vector<Shape> image::DetectShapes2(uchar *edgeMatrix, std::vector<Shape> shapes)
{

    MoveDirection moveDir = MoveDirection::E;
    std::vector<place> shapeList;
    place currentPixel = place(0, 0);
    int timesFoundStart = 2;
    int width = GetWidth();
    int height = GetHeight();
    bool pictureIsEmpty = false;

    while (pictureIsEmpty)
    {
        if (IsPixelLine(moveDir, currentPixel, edgeMatrix))
        {
            currentPixel = GetPixel(moveDir, currentPixel);
            moveDir = MoveDirection::N;
            if (!shapeList.empty() && shapeList.back() == shapeList.front() && shapeList.size() > 2)
            {
                if (shapeList.size() > 15)
                {
                    Shape shape = Shape(shapeList);
                    shapes.push_back(shape);
                    pictureIsEmpty = RemovePixelsFromPicture(shapeList);
                    shapeList.clear();
                }
                else
                {
                    pictureIsEmpty = RemovePixelsFromPicture(shapeList);
                    shapeList.clear();
                }
            }
            else if (shapeList.end() == shapeList.begin() && moveDir != MoveDirection::N)
            {
                timesFoundStart--;
            }
            if (timesFoundStart <= 0)
            {
                pictureIsEmpty = RemovePixelsFromPicture(shapeList);
                shapeList.clear();
            }
        }
        else
        {
            moveDir = NextMoveDir(moveDir);
            if (moveDir == MoveDirection::N)
            {
                currentPixel = GetNextPixel(currentPixel, width, height);
            }
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
                    edgeMatrix[i * width + j] = 0;
                }
            }
        }
    }

    return shapes;
}
place image::GetNextPixel(place current, int height, int width){

}

bool image::RemovePixelsFromPicture(std::vector<place> pixels){

    return false;
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
    std::cout << "came before the gaussian blur" << std::endl;
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
    switch (oldDirection)
    {
    case MoveDirection::N:
        newMoveDir = MoveDirection::NE;
        break;
    case MoveDirection::NE:
        newMoveDir = MoveDirection::E;
        break;
    case MoveDirection::E:
        newMoveDir = MoveDirection::ES;
        break;
    case MoveDirection::ES:
        newMoveDir = MoveDirection::S;
        break;
    case MoveDirection::S:
        newMoveDir = MoveDirection::SW;
        break;
    case MoveDirection::SW:
        newMoveDir = MoveDirection::W;
        break;
    case MoveDirection::W:
        newMoveDir = MoveDirection::NW;
        break;
    case MoveDirection::NW:
        newMoveDir = MoveDirection::N;
        break;
    default:
        newMoveDir = oldDirection;
        break;
    }

    return newMoveDir;
}

place image::GetPixel(MoveDirection moveDir, place currentPixel)
{
    place pixel = currentPixel;
    switch (moveDir)
    {
    case MoveDirection::N:
        pixel.SetX(currentPixel.GetX() - 1);
        pixel.SetY(currentPixel.GetY());
        break;
    case MoveDirection::NE:
        pixel.SetX(currentPixel.GetX() - 1);
        pixel.SetY(currentPixel.GetY() + 1);
        break;
    case MoveDirection::E:
        pixel.SetX(currentPixel.GetX());
        pixel.SetY(currentPixel.GetY() + 1);
        break;
    case MoveDirection::ES:
        pixel.SetX(currentPixel.GetX() + 1);
        pixel.SetY(currentPixel.GetY() + 1);
        break;
    case MoveDirection::S:
        pixel.SetX(currentPixel.GetX() + 1);
        pixel.SetY(currentPixel.GetY());
        break;
    case MoveDirection::SW:
        pixel.SetX(currentPixel.GetX() + 1);
        pixel.SetY(currentPixel.GetY() - 1);
        break;
    case MoveDirection::W:
        pixel.SetX(currentPixel.GetX());
        pixel.SetY(currentPixel.GetY() - 1);
        break;
    case MoveDirection::NW:
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
    case MoveDirection::N:
        if (edgeMatrix[(currentPixel.GetX() - 1) * GetWidth() + currentPixel.GetY()] == 1)
        {
            isPixelLine = true;
        }

        break;
    case MoveDirection::NE:
        if (edgeMatrix[(currentPixel.GetX() - 1) * GetWidth() + (currentPixel.GetY() + 1)] == 1)
        {
            isPixelLine = true;
        }

        break;
    case MoveDirection::E:
        if (edgeMatrix[currentPixel.GetX() * GetWidth() + (currentPixel.GetY() + 1)] == 1)
        {
            isPixelLine = true;
        }

        break;
    case MoveDirection::ES:
        if (edgeMatrix[(currentPixel.GetX() + 1) * GetWidth() + (currentPixel.GetY() + 1)] == 1)
        {
            isPixelLine = true;
        }

        break;
    case MoveDirection::S:
        if (edgeMatrix[(currentPixel.GetX() + 1) * GetWidth() + currentPixel.GetY()] == 1)
        {
            isPixelLine = true;
        }

        break;
    case MoveDirection::SW:
        if (edgeMatrix[(currentPixel.GetX() + 1) * GetWidth() + (currentPixel.GetY() - 1)] == 1)
        {
            isPixelLine = true;
        }

        break;
    case MoveDirection::W:
        if (edgeMatrix[currentPixel.GetX() * GetWidth() + (currentPixel.GetY() - 1)] == 1)
        {
            isPixelLine = true;
        }

        break;
    case MoveDirection::NW:
        if (edgeMatrix[(currentPixel.GetX() - 1) * GetWidth() + (currentPixel.GetY() - 1)] == 1)
        {
            isPixelLine = true;
        }

        break;

    default:
        break;
    }
    return isPixelLine;
}
