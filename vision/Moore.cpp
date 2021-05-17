
#include "Moore.hpp"

const uchar WHITE = 255;
const uchar BLACK = 0;

std::vector<place> MooreNeighborhood::anotherTracing2(uchar *image, int width, int height){

    //std::cout<<"inside function"<<std::endl;
    //bool inside = false;
    int pos = 0;
    std::vector<place> pixels;

    // Need to start by padding the image by 1 pixel
    uchar *paddedImage = padImage(image, width, height, BLACK);
    
   // uchar *targetImage = (uchar *)malloc(sizeof(uchar) * (height) * (width));
    //targetImage = padImage(targetImage, width, height, WHITE);

    /*for (int y = 0; y < (height + 2); y++)
    {
        for (int x = 0; x < (width + 2); x++)
        {
            targetImage[x + y * (width + 2)] = WHITE;
        }
    }*/

for (int y = 0; y < (height + 2); y++)
    {
        for (int x = 0; x < (width + 2); x++)
        {
            pos = x + y * (width + 2);

            // Scan for BLACK pixel
           /* if (targetImage[pos] == BLACK && !inside) // Entering an already discovered border
            {
               //std::cout<<"Entering an already discovered border: "<<pos<<" "<<x<<" "<<y<<std::endl;
                inside = true;
            }
            else *//*if (paddedImage[pos] == WHITE && inside) // Already discovered border point
            {
               // std::cout<<"Already discovered border point: "<<pos<<" "<<x<<" "<<y<<std::endl;
                continue;
            }
            else if (paddedImage[pos] == BLACK && inside) // Leaving a border
            {
              // std::cout<<"Leaving a border: "<<pos<<" "<<x<<" "<<y<<std::endl;
                inside = false;
            }
            else */
            
            if (paddedImage[pos] == WHITE /*&& !inside*/) // Undiscovered border point
            {
                //std::cout<<"Undiscovered border point: "<<pos<<" "<<x<<" "<<y<<std::endl;
                //targetImage[pos] = BLACK; // Mark the start pixel
                int checkLocationNr = 1;  // The neighbor number of the location we want to check for a new border point
                int checkPosition;        // The corresponding absolute array address of checkLocationNr
                int newCheckLocationNr;   // Variable that holds the neighborhood position we want to check if we find a new border at checkLocationNr
                int startPos = pos;       // Set start position
                int counter = 0;          // Counter is used for the jacobi stop criterion
                int counter2 = 0;         // Counter2 is used to determine if the point we have discovered is one single point

                // Defines the neighborhood offset position from current position and the neighborhood
                // position we want to check next if we find a new border at checkLocationNr
                int neighborhood[8][2] = {
                    {-1, 7},            //w         //
                    {-3 - width, 7},    //nw
                    {-width - 2, 1},    //n
                    {-1 - width, 1},    //ne
                    {1, 3},             //e
                    {3 + width, 3},     //se
                    {width + 2, 5},     //s
                    {1 + width, 5}};    //sw
                // Trace around the neighborhood
              //  std::cout<<"Trace around the neighborhood"<<std::endl;
                while (true)
                {
                    checkPosition = pos + neighborhood[checkLocationNr - 1][0]; //get the posistion of the pixel to be checked
                    newCheckLocationNr = neighborhood[checkLocationNr - 1][1];  //if that pixel is part of the line, follow the moore rule and go back in direction

                    if (paddedImage[checkPosition] == WHITE) // Next border point found
                    {
                    //    std::cout<<"Next border point found: "<<checkPosition<<std::endl;
                        if (checkPosition == startPos)
                        {
                    //        std::cout<<"next pos == start pos  "<<checkPosition<<" == "<<startPos<<std::endl;
                            counter++;

                            // Stopping criterion (jacob)
                            if (newCheckLocationNr == 1 || counter >= 3)
                            {
                                // Close loop
                       //         std::cout<<"Close loop"<<std::endl;
                       //         std::cout<<"Since we are starting the search at were we first started we must set inside to true"<<std::endl;
                                //inside = true; // Since we are starting the search at were we first started we must set inside to true
                                break;
                            }
                        }

                        checkLocationNr = newCheckLocationNr; // Update which neighborhood position we should check next
                        pos = checkPosition;                  //the current posistion becomes the pixel we just found
                        counter2 = 0;                       // Reset the counter that keeps track of how many neighbors we have visited
                        //targetImage[checkPosition] = BLACK; // Set the border pixel
                        pixels.push_back(getPixel(pos,height+2,width+2));
                        //std::cout<<"pixels.lenght: " <<pixels.size()<<std::endl;
                    }
                    else
                    {
                        //std::cout<<"Rotate clockwise in the neighborhood"<<std::endl;
                        // Rotate clockwise in the neighborhood
                        checkLocationNr = 1 + (checkLocationNr % 8);
                        if (counter2 > 8)
                        {
                            //std::cout<<"the border is a single black pixel"<<std::endl;
                            // If counter2 is above 8 we have traced around the neighborhood and
                            // therefor the border is a single black pixel and we can exit
                            counter2 = 0;
                            break;
                        }
                        else
                        {
                            counter2++;
                        }
                    }
                }
                //std::cout<<"DONE Trace around the neighborhood"<<std::endl;
                //return RemovePadding(targetImage,width,height);
                return pixels;

            }
        }
    }
    //return targetImage;
    return pixels;
    

}


uchar *MooreNeighborhood::anotherTracing(uchar *image,std::vector<place> &pixels, int width, int height){

    //std::cout<<"inside function"<<std::endl;
    bool inside = false;
    int pos = 0;

    // Need to start by padding the image by 1 pixel
    uchar *paddedImage = padImage(image, width, height, BLACK);
    
    uchar *targetImage = (uchar *)malloc(sizeof(uchar) * (height) * (width));
    targetImage = padImage(targetImage, width, height, WHITE);

    for (int y = 0; y < (height + 2); y++)
    {
        for (int x = 0; x < (width + 2); x++)
        {
            targetImage[x + y * (width + 2)] = WHITE;
        }
    }

for (int y = 0; y < (height + 2); y++)
    {
        for (int x = 0; x < (width + 2); x++)
        {
            pos = x + y * (width + 2);

            // Scan for BLACK pixel
            if (targetImage[pos] == BLACK && !inside) // Entering an already discovered border
            {
               //std::cout<<"Entering an already discovered border: "<<pos<<" "<<x<<" "<<y<<std::endl;
                inside = true;
            }
            else if (paddedImage[pos] == WHITE && inside) // Already discovered border point
            {
               // std::cout<<"Already discovered border point: "<<pos<<" "<<x<<" "<<y<<std::endl;
                continue;
            }
            else if (paddedImage[pos] == BLACK && inside) // Leaving a border
            {
              // std::cout<<"Leaving a border: "<<pos<<" "<<x<<" "<<y<<std::endl;
                inside = false;
            }
            else if (paddedImage[pos] == WHITE && !inside) // Undiscovered border point
            {
                //std::cout<<"Undiscovered border point: "<<pos<<" "<<x<<" "<<y<<std::endl;
                targetImage[pos] = BLACK; // Mark the start pixel
                int checkLocationNr = 1;  // The neighbor number of the location we want to check for a new border point
                int checkPosition;        // The corresponding absolute array address of checkLocationNr
                int newCheckLocationNr;   // Variable that holds the neighborhood position we want to check if we find a new border at checkLocationNr
                int startPos = pos;       // Set start position
                int counter = 0;          // Counter is used for the jacobi stop criterion
                int counter2 = 0;         // Counter2 is used to determine if the point we have discovered is one single point

                // Defines the neighborhood offset position from current position and the neighborhood
                // position we want to check next if we find a new border at checkLocationNr
                int neighborhood[8][2] = {
                    {-1, 7},            //w         //
                    {-3 - width, 7},    //nw
                    {-width - 2, 1},    //n
                    {-1 - width, 1},    //ne
                    {1, 3},             //e
                    {3 + width, 3},     //se
                    {width + 2, 5},     //s
                    {1 + width, 5}};    //sw
                // Trace around the neighborhood
              //  std::cout<<"Trace around the neighborhood"<<std::endl;
                while (true)
                {
                    checkPosition = pos + neighborhood[checkLocationNr - 1][0]; //get the posistion of the pixel to be checked
                    newCheckLocationNr = neighborhood[checkLocationNr - 1][1];  //if that pixel is part of the line, follow the moore rule and go back in direction

                    if (paddedImage[checkPosition] == WHITE) // Next border point found
                    {
                    //    std::cout<<"Next border point found: "<<checkPosition<<std::endl;
                        if (checkPosition == startPos)
                        {
                    //        std::cout<<"next pos == start pos  "<<checkPosition<<" == "<<startPos<<std::endl;
                            counter++;

                            // Stopping criterion (jacob)
                            if (newCheckLocationNr == 1 || counter >= 3)
                            {
                                // Close loop
                       //         std::cout<<"Close loop"<<std::endl;
                       //         std::cout<<"Since we are starting the search at were we first started we must set inside to true"<<std::endl;
                                inside = true; // Since we are starting the search at were we first started we must set inside to true
                                break;
                            }
                        }

                        checkLocationNr = newCheckLocationNr; // Update which neighborhood position we should check next
                        pos = checkPosition;                  //the current posistion becomes the pixel we just found
                        counter2 = 0;                       // Reset the counter that keeps track of how many neighbors we have visited
                        targetImage[checkPosition] = BLACK; // Set the border pixel
                        pixels.push_back(getPixel(pos,height+2,width+2));
                        //std::cout<<"pixels.lenght: " <<pixels.size()<<std::endl;
                    }
                    else
                    {
                        //std::cout<<"Rotate clockwise in the neighborhood"<<std::endl;
                        // Rotate clockwise in the neighborhood
                        checkLocationNr = 1 + (checkLocationNr % 8);
                        if (counter2 > 8)
                        {
                            //std::cout<<"the border is a single black pixel"<<std::endl;
                            // If counter2 is above 8 we have traced around the neighborhood and
                            // therefor the border is a single black pixel and we can exit
                            counter2 = 0;
                            break;
                        }
                        else
                        {
                            counter2++;
                        }
                    }
                }
                //std::cout<<"DONE Trace around the neighborhood"<<std::endl;
                return RemovePadding(targetImage,width,height);
            }
        }
    }
    return targetImage;
    

}
uchar *MooreNeighborhood::RemovePadding(uchar *targetImage, int width, int height){
uchar *clippedBorderImage = (uchar *)malloc(sizeof(uchar) * (height) * (width));
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            clippedBorderImage[x + y * width] = targetImage[x + 1 + (y + 1) * (width + 2)];
        }
    }
    return clippedBorderImage;
}

place MooreNeighborhood::getPixel(int pos,int height,int width){
    for (int y = 0; y < (height ); y++)
    {
        for (int x = 0; x < (width ); x++)
        {
            if((x + y * width )==pos)
            return place(x,y);
        }
    }
    return place(0,0);
}

uchar *MooreNeighborhood::mooreNeighborTracing(uchar *image, int width, int height)
{
    std::cout<<"inside function"<<std::endl;
    bool inside = false;
    int pos = 0;

    // Need to start by padding the image by 1 pixel
    uchar *paddedImage = padImage(image, width, height, WHITE);

    // Allocate new image as a 1D array
    uchar *borderImage = (uchar *)malloc(sizeof(uchar) * (height + 2) * (width + 2));

    // Set entire image to WHITE
    for (int y = 0; y < (height + 2); y++)
    {
        for (int x = 0; x < (width + 2); x++)
        {
            borderImage[x + y * (width + 2)] = WHITE;
        }
    }

    for (int y = 0; y < (height + 2); y++)
    {
        for (int x = 0; x < (width + 2); x++)
        {
            pos = x + y * (width + 2);

            // Scan for BLACK pixel
            if (borderImage[pos] == BLACK && !inside) // Entering an already discovered border
            {
                std::cout<<"Entering an already discovered border: "<<pos<<" "<<x<<" "<<y<<std::endl;
                inside = true;
            }
            else if (paddedImage[pos] == BLACK && inside) // Already discovered border point
            {
                std::cout<<"Already discovered border point: "<<pos<<" "<<x<<" "<<y<<std::endl;
                continue;
            }
            else if (paddedImage[pos] == WHITE && inside) // Leaving a border
            {
                std::cout<<"Leaving a border: "<<pos<<" "<<x<<" "<<y<<std::endl;
                inside = false;
            }
            else if (paddedImage[pos] == BLACK && !inside) // Undiscovered border point
            {
                std::cout<<"Undiscovered border point: "<<pos<<" "<<x<<" "<<y<<std::endl;
                borderImage[pos] = BLACK; // Mark the start pixel
                int checkLocationNr = 1;  // The neighbor number of the location we want to check for a new border point
                int checkPosition;        // The corresponding absolute array address of checkLocationNr
                int newCheckLocationNr;   // Variable that holds the neighborhood position we want to check if we find a new border at checkLocationNr
                int startPos = pos;       // Set start position
                int counter = 0;          // Counter is used for the jacobi stop criterion
                int counter2 = 0;         // Counter2 is used to determine if the point we have discovered is one single point

                // Defines the neighborhood offset position from current position and the neighborhood
                // position we want to check next if we find a new border at checkLocationNr
                int neighborhood[8][2] = {
                    {-1, 7},
                    {-3 - width, 7},
                    {-width - 2, 1},
                    {-1 - width, 1},
                    {1, 3},
                    {3 + width, 3},
                    {width + 2, 5},
                    {1 + width, 5}};
                // Trace around the neighborhood
                std::cout<<"Trace around the neighborhood"<<std::endl;
                while (true)
                {
                    checkPosition = pos + neighborhood[checkLocationNr - 1][0];
                    newCheckLocationNr = neighborhood[checkLocationNr - 1][1];

                    if (paddedImage[checkPosition] == BLACK) // Next border point found
                    {
                        std::cout<<"Next border point found: "<<checkPosition<<std::endl;
                        if (checkPosition == startPos)
                        {
                            std::cout<<"next pos == start pos  "<<checkPosition<<" == "<<startPos<<std::endl;
                            counter++;

                            // Stopping criterion (jacob)
                            if (newCheckLocationNr == 1 || counter >= 3)
                            {
                                // Close loop
                                std::cout<<"Close loop"<<std::endl;
                                std::cout<<"Since we are starting the search at were we first started we must set inside to true"<<std::endl;
                                inside = true; // Since we are starting the search at were we first started we must set inside to true
                                break;
                            }
                        }

                        checkLocationNr = newCheckLocationNr; // Update which neighborhood position we should check next
                        pos = checkPosition;
                        counter2 = 0;                       // Reset the counter that keeps track of how many neighbors we have visited
                        borderImage[checkPosition] = BLACK; // Set the border pixel
                    }
                    else
                    {
                        std::cout<<"Rotate clockwise in the neighborhood"<<std::endl;
                        // Rotate clockwise in the neighborhood
                        checkLocationNr = 1 + (checkLocationNr % 8);
                        if (counter2 > 8)
                        {
                            std::cout<<"the border is a single black pixel"<<std::endl;
                            // If counter2 is above 8 we have traced around the neighborhood and
                            // therefor the border is a single black pixel and we can exit
                            counter2 = 0;
                            break;
                        }
                        else
                        {
                            counter2++;
                        }
                    }
                }
                std::cout<<"DONE Trace around the neighborhood"<<std::endl;
            }
        }
    }

    // Remove white padding and return it
    uchar *clippedBorderImage = (uchar *)malloc(sizeof(uchar) * (height) * (width));
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            clippedBorderImage[x + y * width] = borderImage[x + 1 + (y + 1) * (width + 2)];
        }
    }
    return clippedBorderImage;
}

uchar * MooreNeighborhood::padImage(uchar *image, int width, int height, int paddingColor)
{
    uchar *paddedImage = (uchar *)malloc(sizeof(uchar) * (height + 2) * (width + 2));
    for (int x = 0; x < width + 2; x++)
    {
        for (int y = 0; y < height + 2; y++)
        {
            if (x == 0 || y == 0 || x == width + 1 || y == height + 1)
            {
                paddedImage[x + y * (width + 2)] = paddingColor;
            }
            else
            {
                paddedImage[x + y * (width + 2)] = image[x - 1 + (y - 1) * width];
            }
        }
    }
    return paddedImage;
}
/*
std::unordered_set<place> MooreNeighborhood::getBoundary(uchar *image, int width, int height)
{
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            if (image[j * width + i] == 255)
            {
                return squareTrace(place(i, j), image, width);
                break;
            }
        }
    }
}

std::unordered_set<place> squareTrace(place start, uchar *image, int width)
{
    std::unordered_set<place> boundariyPoints;
    boundariyPoints.insert(start);

    place nextStep = GoLeft(place(1, 0));
    place next = start + nextStep;
    while (next != start)
    {
        if (image[next.GetY() * width + next.GetX()] == 0)
        {
            next = next - nextStep;
            nextStep = GoRight(nextStep);
            next = next + nextStep;
        }
        else
        {
            boundariyPoints.insert(next);
            nextStep = GoLeft(nextStep);
            next = next + nextStep;
        }
    }
    return boundariyPoints;
}
place GoRight(place p)
{
    p.SetX(p.GetX() - 1);
    return p;
}
place GoLeft(place p)
{
    p.SetY(p.GetY() - 1);
    return p;
}

void MooreNeighborhood::Trace(uchar *edgeMatrix, int width, int height)
{
    auto show = cv::Mat(height, width, CV_8UC1);
    int teller = 20;
    std::vector<Shape> shapes;
    //start ia left top corner
    MoveDirection moveDir = MoveDirection::E;
    //s list for the pixels of the shape
    std::deque<place> shapePixels;
    // std::vector<place> shapeList;
    //the movedir that tells us if we went full circle
    MoveDirection startMoveDir = moveDir;

    //shapeList.resize(1);
    place currentPixel = place(0, 0);
    place newPixel;
    place last = currentPixel;
    bool pictureIsEmpty = false;

    //the picture contails a pixel !0
    while (!pictureIsEmpty)
    {
        //if the next pixel in the neighborhood is not 0,
        if (IsPixelLine(moveDir, currentPixel, edgeMatrix, width, height))
        {
            //then it can be counted as a line
            std::cout << "yeah it is a line" << std::endl;
            std::cout << "moveDirection  " << moveDir << std::endl;

            //get the pixel
            newPixel = GetPixel(moveDir, currentPixel, width, height);
            //put it in a list where all the pixels are thar are part of this shape
            shapePixels.push_back(newPixel);
            std::cout << "Last pixel " << last << " current pixel " << currentPixel << " new pixel " << newPixel << std::endl;
            //if the new pixel is the same as the last one, then it is a dead end
            if (newPixel == last)
            {
                std::cout << " current pixel is a dead end so let's remove it" << std::endl;
                pictureIsEmpty = RemovePixelsFromPicture(currentPixel, edgeMatrix, height, width);
                std::cout << "was it removed?  " << (unsigned int)edgeMatrix[currentPixel.GetX() * width + currentPixel.GetY()] << std::endl;
                //get a better list or something
                shapePixels.pop_back();
                //shapePixels.erase(shapePixels.end()-1);
                last = shapePixels.at(shapePixels.size() - 2);
                std::cout << "shapelist size: " << shapePixels.size() << std::endl;
                std::cout << "new Last pixel " << last << std::endl;
            }
            else
            {
                //if it is still a line, just continue as normal
                last = currentPixel;
            }

            currentPixel = newPixel;
            moveDir = newMoveDir(moveDir);
            startMoveDir = moveDir;
            std::cout << "movedir and stuff has been changed" << std::endl;
            std::cout << "shapelist size: " << shapePixels.size() << std::endl;
            std::cout << "start of shape: " << shapePixels.front() << std::endl;
            std::cout << "end of shape: " << shapePixels.back() << std::endl;
            //the list may not be empty. If the value of the first and last are the same and the list is bigger than 2
            if (!shapePixels.empty() && shapePixels.back() == shapePixels.front() && shapePixels.size() > 2)
            {
                std::cout << "yeah it is a shape  i think\n";
                //if the shape is bigger than 15, it is a usefull shape
                if (shapePixels.size() > 15)
                {

                    std::cout << "yeah it is a shape!\n";
                    //give the list to a shape object and store that object
                    //Shape shape = Shape(shapePixels);
                    //shapes.push_back(shape);
                    //remove the pixels from the image, so new shapes can be detected
                    pictureIsEmpty = RemovePixelsFromPicture(shapePixels, edgeMatrix, height, width);
                    //clear the list
                    shapePixels.clear();
                }
                else
                {
                    //not a usefull shape, so remove everything from that shape
                    pictureIsEmpty = RemovePixelsFromPicture(shapePixels, edgeMatrix, height, width);
                    shapePixels.clear();
                }
            }
            teller--;
            if (teller < 0)
                pictureIsEmpty = true;
        }
        else
        {
            //the pixel is not a line, so it is an empty pixel.
            //get the nex movedirection in a clockwise motion
            moveDir = NextMoveDir(moveDir);
            //have we gone full circle without a pixel that is !0?
            if (moveDir == startMoveDir)
            {
                //and is the current pixel also !0
                if (edgeMatrix[(currentPixel.GetX()) * width + currentPixel.GetY()] != 0)
                {
                    //then remove this pixel from the picture and remove it from the list
                    std::cout << "so this pixel is on it's own" << std::endl;
                    pictureIsEmpty = RemovePixelsFromPicture(currentPixel, edgeMatrix, height, width);
                    shapePixels.clear();
                }
                //go to the next pixel in the picture. this is the pixel of the right from the current pixel
                currentPixel = GetNextPixel(currentPixel, width, height);
            }
        }
    }
}

place MooreNeighborhood::GetNextPixel(place current, int height, int width)
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

bool MooreNeighborhood::RemovePixelsFromPicture(std::deque<place> pixels, uchar *edges, int height, int width)
{
    std::cout << "remove list of pixels" << std::endl;
    bool isEmpty = true;
    for (int i; i < pixels.size(); i++)
    {
        isEmpty = RemovePixelsFromPicture(pixels[i], edges, height, width);
    }

    return isEmpty;
}
bool MooreNeighborhood::RemovePixelsFromPicture(place pixel, uchar *edges, int height, int width)
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

MoveDirection MooreNeighborhood::newMoveDir(MoveDirection oldDirection)
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

MoveDirection MooreNeighborhood::NextMoveDir(MoveDirection oldDirection)
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

place MooreNeighborhood::GetPixel(MoveDirection moveDir, place currentPixel, int width, int height)
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

bool MooreNeighborhood::IsPixelLine(MoveDirection moveDir, place currentPixel, uchar *edgeMatrix, int width, int height)
{
    bool isPixelLine = false;

    switch (moveDir)
    {
    case MoveDirection::N:
        if (edgeMatrix[(currentPixel.GetX() - 1) * width + currentPixel.GetY()] != 0 && currentPixel.GetX() - 1 > 0)
        {
            isPixelLine = true;
        }

        break;
    case MoveDirection::NE:
        if (edgeMatrix[(currentPixel.GetX() - 1) * width + (currentPixel.GetY() + 1)] != 0 && currentPixel.GetX() - 1 > 0 && currentPixel.GetY() + 1 < height)
        {
            isPixelLine = true;
        }

        break;
    case MoveDirection::E:
        if (edgeMatrix[currentPixel.GetX() * width + (currentPixel.GetY() + 1)] != 0 && currentPixel.GetY() + 1 < height)
        {
            isPixelLine = true;
        }

        break;
    case MoveDirection::ES:
        if (edgeMatrix[(currentPixel.GetX() + 1) * width + (currentPixel.GetY() + 1)] != 0 && currentPixel.GetY() + 1 < height && currentPixel.GetX() + 1 < width)
        {
            isPixelLine = true;
        }

        break;
    case MoveDirection::S:
        if (edgeMatrix[(currentPixel.GetX() + 1) * width + currentPixel.GetY()] != 0 && currentPixel.GetX() + 1 < width)
        {
            isPixelLine = true;
        }

        break;
    case MoveDirection::SW:
        if (edgeMatrix[(currentPixel.GetX() + 1) * width + (currentPixel.GetY() - 1)] != 0 && currentPixel.GetX() + 1 < width && currentPixel.GetY() - 1 > 0)
        {
            isPixelLine = true;
        }

        break;
    case MoveDirection::W:
        if (edgeMatrix[currentPixel.GetX() * width + (currentPixel.GetY() - 1)] != 0 && currentPixel.GetY() - 1 > 0)
        {
            isPixelLine = true;
        }

        break;
    case MoveDirection::NW:
        if (edgeMatrix[(currentPixel.GetX() - 1) * width + (currentPixel.GetY() - 1)] != 0 && currentPixel.GetY() - 1 > 0 && currentPixel.GetX() - 1 > 0)
        {
            isPixelLine = true;
        }

        break;

    default:
        break;
    }
    return isPixelLine;
}
*/
MooreNeighborhood::MooreNeighborhood(/* args */)
{
}

MooreNeighborhood::~MooreNeighborhood()
{
}