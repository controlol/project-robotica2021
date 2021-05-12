
#include "image.hpp"

image::image(BlurKernel blur, EdgeKernel edge, SinglePixelKernel single, cv::Mat image)
{
    std::cout << "making image\n";
    picture = image;
    blurKernel = blur;
    edgeKernel = edge;
    singleKernel = single;
    std::vector<uchar> temp;
    this->width = image.cols;
    this->height = image.rows;
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
    
    originalImage.resize(image.rows,std::vector<uchar>(image.cols));
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            originalImage[i][j]=temp[image.rows*i+j];             
        }
        
    }*/
    std::cout << "made image\n";
}
image::~image()
{
}
std::vector<card> image::GetCardList()
{
    std::cout << width << "  " << height << std::endl;
    std::cout << "retrieving cards\n";
    std::vector<card> returnCards;
    std::vector<Shape> shapes;

    uchar edgeMatrix[width * height];
    uchar blurredImage[width * height];
    std::cout << "initialized variables\n";
    auto show = cv::Mat(height, width, CV_8UC1);
    std::cout << "initialized all variables\n";
    BlurImage(blurredImage);
    std::cout << "blurred image\n";
    show.data = blurredImage;
    cv::imshow("Blurred", show);
    DetectEdges(blurredImage, edgeMatrix);
    std::cout << "edged image\n";
    show.data = edgeMatrix;
    cv::imshow("edges", show);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            edgeMatrix[i * width + j] = 0;
        }
    }
    /*
-----
 |
*/
    edgeMatrix[1] = 255;         //0 1
    edgeMatrix[2] = 255;         //0 2
    edgeMatrix[3] = 255;         //0 3
    edgeMatrix[4] = 255;         //0 4
    edgeMatrix[5] = 255;         //0 5
    edgeMatrix[width + 2] = 255; //1 2      122
    //edgeMatrix[2*width+2]=255;
    //edgeMatrix[2*width+2]=255;

    show.data = edgeMatrix;
    cv::imshow("edges1", show);
    if (cv::waitKey(1000) >= 0)
        std::cout << std::endl;

    //shapes = DetectShapes(edgeMatrix);
    std::cout << "gonna do shapes\n";
    shapes = DetectShapes2(edgeMatrix, shapes);
    std::cout << "done with shapes\n";
    for (int i = 0; i < shapes.size(); i++)
    {
        //remember shapes that are square
        if (shapes[i].IsShapeSquare() == false)
        {
            shapes.erase(shapes.begin() + i);
        }
    }

    //returnCards = DetermenCards(shapes);
    return returnCards;
}

void image::DetectEdges(uchar *picture, uchar *edgeMatrix)
{
    //std::vector<std::vector<uchar>> edgeMatrix;
    //edgeMatrix.resize(width,std::vector<uchar>(height));
    edgeKernel.FindEdgeMatrix2(picture, edgeMatrix, GetWidth(), GetHeight());
    //return edgeMatrix;
}

std::vector<Shape> image::DetectShapes(uchar *edgeMatrix)
{
    std::vector<Shape> shapes;
    std::vector<place>shapePixels;
    bool isNotEmpty;
    while (isNotEmpty)
    {
        uchar *targetImage = moore.anotherTracing(edgeMatrix,shapePixels, width, height);
        isNotEmpty = removeSinglePixels(edgeMatrix, width, height);
        shapes.push_back(Shape(targetImage,shapePixels));
        for (int i = 0; i < shapes.size(); i++)
        {
            if (!shapes[i].IsThisShapeACard(width, height))
            {
                shapes.erase(shapes.begin() + i);
            }
        }
    }
    return shapes;
}

std::vector<Shape> image::DetectShapes2(uchar *edgeMatrix, std::vector<Shape> shapes)
{
    auto show = cv::Mat(height, width, CV_8UC1);
    int teller = 20;
    MoveDirection moveDir = MoveDirection::E;
    std::vector<place> shapeList;
    MoveDirection startMoveDir = moveDir;

    //shapeList.resize(1);
    place currentPixel = place(0, 0);
    place newPixel;
    place last = currentPixel;
    int timesFoundStart = 2;
    int width = GetWidth();
    int height = GetHeight();
    bool pictureIsEmpty = false;

    while (!pictureIsEmpty)
    {
        ///show.data = edgeMatrix;
        //cv::imshow("edges", show);
        if (IsPixelLine(moveDir, currentPixel, edgeMatrix))
        {
            std::cout << "yeah it is a line" << std::endl;
            std::cout << "moveDirection  " << moveDir << std::endl;

            newPixel = GetPixel(moveDir, currentPixel, width, height);
            shapeList.push_back(newPixel);
            std::cout << "Last pixel " << last << " current pixel " << currentPixel << " new pixel " << newPixel << std::endl;
            if (newPixel == last)
            {
                std::cout << " current pixel is a dead end so let's remove it" << std::endl;
                pictureIsEmpty = RemovePixelsFromPicture(currentPixel, edgeMatrix);
                std::cout << "was it removed?  " << (unsigned int)edgeMatrix[currentPixel.GetX() * width + currentPixel.GetY()] << std::endl;
                shapeList.pop_back();
                shapeList.erase(shapeList.end() - 1);
                last = shapeList[shapeList.size() - 2];
                std::cout << "shapelist size: " << shapeList.size() << std::endl;
                std::cout << "new Last pixel " << last << std::endl;
            }
            else
            {
                last = currentPixel;
            }

            currentPixel = newPixel;
            moveDir = newMoveDir(moveDir);
            startMoveDir = moveDir;
            std::cout << "movedir and stuff has been changed" << std::endl;
            std::cout << "shapelist size: " << shapeList.size() << std::endl;
            std::cout << "start of shape: " << shapeList.front() << std::endl;
            std::cout << "end of shape: " << shapeList.back() << std::endl;
            if (!shapeList.empty() && shapeList.back() == shapeList.front() && shapeList.size() > 2)
            {
                std::cout << "yeah it is a shape  i think\n";
                if (shapeList.size() > 15)
                {

                    std::cout << "yeah it is a shape!\n";
                    Shape shape = Shape(shapeList);
                    shapes.push_back(shape);
                    pictureIsEmpty = RemovePixelsFromPicture(shapeList, edgeMatrix);
                    shapeList.clear();
                }
                else
                {
                    pictureIsEmpty = RemovePixelsFromPicture(shapeList, edgeMatrix);
                    shapeList.clear();
                }
            } /*
            else if (!shapeList.empty() && shapeList.back() == shapeList.front())
            {
                std::cout<<"I found start";
                timesFoundStart--;
            }
            if (timesFoundStart <= 0)
            {
                std::cout<<"it is no shape :(";
                pictureIsEmpty = RemovePixelsFromPicture(shapeList, edgeMatrix);
                shapeList.clear(); 
                timesFoundStart = 2;
            }*/
            //std::cout<<"is it the resize?\n";
            //shapeList.resize(shapeList.size()+1);
            //std::cout<<"no\n";
            teller--;
            if (teller < 0)
                pictureIsEmpty = true;
        }
        else
        {

            //std::cout<<"empty "<<currentPixel<<std::endl;
            moveDir = NextMoveDir(moveDir);
            // std::cout<<"moveDirection  "<<moveDir<<std::endl;
            if (moveDir == startMoveDir)
            {
                if (edgeMatrix[(currentPixel.GetX()) * GetWidth() + currentPixel.GetY()] != 0)
                {
                    std::cout << "so this pixel is on it's own" << std::endl;
                    pictureIsEmpty = RemovePixelsFromPicture(currentPixel, edgeMatrix);
                    shapeList.pop_back();
                }
                currentPixel = GetNextPixel(currentPixel, width, height);
            }
        }
    }
    /*for (int i = 0; i < width; i++)
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
    }*/

    return shapes;
}
place image::GetNextPixel(place current, int height, int width)
{
    std::cout << "the current pixel is: " << current << std::endl;
    place newPixel = current;
    newPixel.SetY(current.GetY() + 1);
    if (newPixel.GetY() >= width)
    {
        newPixel.SetX(current.GetX() + 1);
        newPixel.SetY(0);

        if (newPixel.GetX() >= height)
        {
            newPixel.SetX(0);
        }
    }
    std::cout << "the new pixel is: " << newPixel << std::endl;
    return newPixel;
}

bool image::RemovePixelsFromPicture(std::vector<place> pixels, uchar *edges)
{
    std::cout << "remove list of pixels" << std::endl;
    bool isEmpty = true;
    for (int i; i < pixels.size(); i++)
    {
        isEmpty = RemovePixelsFromPicture(pixels[i], edges);
    }
    /* for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            for (int i = 0; i < pixels.size(); i++)
            {
                if (pixels[i].GetX() == row && pixels[i].GetY() == col)
                {
                    std::cout<<"pixel "<<pixels[i]<<" Is on coordinate "<<row<<"  "<<col<<std::endl;
                    edges[row*width+col] = 0;
                }
            }
            if (edges[row*width+col] > 0)
            
                isEmpty=false;
        }
        
    }
    if (isEmpty == false)
    {
       std::cout<<"still a pixel not 0\n";
    }*/

    return isEmpty;
}
bool image::RemovePixelsFromPicture(place pixel, uchar *edges)
{
    std::cout << "remove 1 pixel" << std::endl;
    bool isEmpty = true;
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            if (pixel.GetX() == row && pixel.GetY() == col)
            {
                std::cout << "pixel " << pixel << " Is on coordinate " << row << "  " << col << std::endl;
                edges[row * width + col] = 0;
                std::cout << "did it work? " << (unsigned int)edges[row * width + col] << std::endl;
            }
            if (edges[row * width + col] > 0)

                isEmpty = false;
        }
    }
    if (isEmpty == false)
    {
        std::cout << "still a pixel not 0\n";
    }

    return isEmpty;
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
    switch (oldDirection)
    {
    case MoveDirection::N:
        newMoveDir = MoveDirection::NW;
        break;
    case MoveDirection::NE:
        newMoveDir = MoveDirection::NW;
        break;
    case MoveDirection::E:
        newMoveDir = MoveDirection::NE;
        break;
    case MoveDirection::ES:
        newMoveDir = MoveDirection::NE;
        break;
    case MoveDirection::S:
        newMoveDir = MoveDirection::ES;
        break;
    case MoveDirection::SW:
        newMoveDir = MoveDirection::ES;
        break;
    case MoveDirection::W:
        newMoveDir = MoveDirection::SW;
        break;
    case MoveDirection::NW:
        newMoveDir = MoveDirection::SW;
        break;
    default:
        newMoveDir = oldDirection;
        break;
    }

    return newMoveDir;
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

place image::GetPixel(MoveDirection moveDir, place currentPixel, int width, int height)
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
    if (pixel.GetX() >= width)
        pixel.SetX(width - 1);
    if (pixel.GetY() >= height)
        pixel.SetY(height - 1);
    if (pixel.GetX() < 0)
        pixel.SetX(0);
    if (pixel.GetY() < 0)
        pixel.SetY(0);
    return pixel;
}

bool image::IsPixelLine(MoveDirection moveDir, place currentPixel, uchar *edgeMatrix)
{
    bool isPixelLine = false;

    switch (moveDir)
    {
    case MoveDirection::N:
        if (edgeMatrix[(currentPixel.GetX() - 1) * GetWidth() + currentPixel.GetY()] != 0 && currentPixel.GetX() - 1 > 0)
        {
            isPixelLine = true;
        }

        break;
    case MoveDirection::NE:
        if (edgeMatrix[(currentPixel.GetX() - 1) * GetWidth() + (currentPixel.GetY() + 1)] != 0 && currentPixel.GetX() - 1 > 0 && currentPixel.GetY() + 1 < height)
        {
            isPixelLine = true;
        }

        break;
    case MoveDirection::E:
        if (edgeMatrix[currentPixel.GetX() * GetWidth() + (currentPixel.GetY() + 1)] != 0 && currentPixel.GetY() + 1 < height)
        {
            isPixelLine = true;
        }

        break;
    case MoveDirection::ES:
        if (edgeMatrix[(currentPixel.GetX() + 1) * GetWidth() + (currentPixel.GetY() + 1)] != 0 && currentPixel.GetY() + 1 < height && currentPixel.GetX() + 1 < width)
        {
            isPixelLine = true;
        }

        break;
    case MoveDirection::S:
        if (edgeMatrix[(currentPixel.GetX() + 1) * GetWidth() + currentPixel.GetY()] != 0 && currentPixel.GetX() + 1 < width)
        {
            isPixelLine = true;
        }

        break;
    case MoveDirection::SW:
        if (edgeMatrix[(currentPixel.GetX() + 1) * GetWidth() + (currentPixel.GetY() - 1)] != 0 && currentPixel.GetX() + 1 < width && currentPixel.GetY() - 1 > 0)
        {
            isPixelLine = true;
        }

        break;
    case MoveDirection::W:
        if (edgeMatrix[currentPixel.GetX() * GetWidth() + (currentPixel.GetY() - 1)] != 0 && currentPixel.GetY() - 1 > 0)
        {
            isPixelLine = true;
        }

        break;
    case MoveDirection::NW:
        if (edgeMatrix[(currentPixel.GetX() - 1) * GetWidth() + (currentPixel.GetY() - 1)] != 0 && currentPixel.GetY() - 1 > 0 && currentPixel.GetX() - 1 > 0)
        {
            isPixelLine = true;
        }

        break;

    default:
        break;
    }
    return isPixelLine;
}

void image::RemovePixelsFromPicture(uchar *image, uchar *pixelsToRemove, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (pixelsToRemove[i * width + j] == 0)
            {
                image[i * width + j] = 0;
            }
        }
    }
}
bool image::removeSinglePixels(uchar *image, int width, int height)
{

    singleKernel.RemoveSinglePixels(image, width, height);
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            for (int k = 0; k < shapeList.size(); k++)
            {
                if (image[i * width + j] == 0)
                    return true;
            }
        }
    }
    return false;
}