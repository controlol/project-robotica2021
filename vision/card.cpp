#include "card.hpp"

void card::DetermenRank()
{
    double same=0;
    int rows;
    int cols;
    int width = rankImage.cols;
    int height = rankImage.rows;
    double SAD;
    double minSAD=256.0;
    int searchImage;
    int compareImage;
    double bestSad;
    double cardSad=0.0;
    int cardNumber=0;

    std::vector<uchar> loadedImage;
    std::vector<uchar> thisCard;
    thisCard.assign(rankImage.data, rankImage.data + rankImage.total() * rankImage.channels());
    std::vector<uchar> thisCardtmp;
    for (int k = 0; k < 13; k++)
    {
        loadedImage.assign(ranks[k].data, ranks[k].data + ranks[k].total() * ranks[k].channels());
        thisCardtmp = BinaryAnd(loadedImage, thisCard, width, height);
        //std::cout << "came here2\n";
        if (loadedImage.empty())
            std::cout << "loaded image is empty\n";
        if (thisCard.empty())
            std::cout << "this card is empty\n";
        cv::imshow("compared to", ranks[k]);
        //cv::waitKey(0);
        SAD=0.0;
        same=0.0;
        for (size_t x = 0; x < width; x++)
        {
            for (size_t y = 0; y < height; y++)
            {
                if(loadedImage[y*width+x]==thisCardtmp[y*width+x]){
                    same++;
                }



                

                /*for (size_t j = 0; j < width; j++)
                {
                    for (size_t i = 0; i < height; i++)
                    {
                        
                        searchImage=thisCard[(x+y)*width+(y+i)];
                        compareImage=loadedImage[j*width+i];

                        SAD=abs(searchImage-compareImage);
                    }
                    
                }
                if(minSAD>SAD){
                    minSAD=SAD;
                    rows=x;
                    cols=y;
                    bestSad=SAD;
                }*/
            }
            
        }/*
        std::cout<<"best sad: "<<bestSad<<std::endl;
        if(bestSad<cardSad){
            cardSad=bestSad;
            std::cout<<"card sad: "<<cardSad<<std::endl;
            std::cout<<"best card was: "<<cardNumber<<std::endl;
            cardNumber=k;
            std::cout<<"best card is now: "<<cardNumber<<std::endl;
        }*/
        SAD=(same/thisCardtmp.size())*100.0;
       if(SAD>cardSad){
            cardSad=SAD;
            std::cout<<"card sad: "<<cardSad<<std::endl;
            std::cout<<"best card was: "<<cardNumber<<std::endl;
            cardNumber=k;
            std::cout<<"best card is now: "<<cardNumber<<std::endl;
        }
    }
    rank = static_cast<Ranks>(cardNumber);
    cv::imshow("compared to", ranks[cardNumber]);
    std::cout << "rank: " << rank << std::endl;
    std::cout << "cardNumber: " << cardNumber << std::endl;
    //std::cout << "compare: " << comaprisonNumber << std::endl;
}
void card::DetermenSuit()
{
}

std::vector<uchar> card::BinaryAnd(std::vector<uchar> mask, std::vector<uchar> targetImage, int width, int height){
    std::vector<uchar> thisCardtmp;
    for (int col = 0; col < width; col++)
    {
        for (int row = 0; row < height; row++)
        {
            if(mask[row*width+col]==0){
                thisCardtmp.push_back(targetImage[row*width+col]);
            }
            else{
                thisCardtmp.push_back(255);
            }
        }
    }
    return thisCardtmp;
}

cv::Mat card::allignLeftTop(cv::Mat thisCard, int width, int height)
{
    int rows = height;
    int cols = width;
    for (int col = 0; col < width; col++)
    {
        //std::cout << "came here1\n";
        for (int row = 0; row < height; row++)
        {
            //std::cout << "came here\n";

            /* if (thisCard[row * width + col] == 0 && loadedImage[row * width + col]==255){
                    thisCardtmp[row * width + col] =255;
                }*/
            //comaprisonNumber++;
            //if(loadedImage[row * width + col]==0)
            //loadedIm++;
            //if(thisCardtmp[row * width + col] == 0)
            //cardImg++;

            //std::cout<<cardImg<<"  "<<loadedIm<<std::endl;

            if (thisCard.data[row * width + col] == 0 && row < rows)
            {
                
                rows = row;
                std::cout<<"changed rows to: "<<rows<<"\n";
            }
            if (thisCard.data[row * width + col] == 0 && col < cols)
            {
                
                cols = col;
                std::cout<<"changed cols to: "<<cols<<"\n";
            }
        }
    }
    
        std::cout<<"rows: cols: "<<rows<<" "<<cols<<"\n";
    //thisCard.data[rows * width + cols] = 50;
    cv::imshow("out2", thisCard);
    // move rank to the top left corner and diff the images
    cv::Mat out(thisCard.rows,thisCard.cols,CV_8UC1);
    out=255;
    for (int col = cols; col < width; col++)
    {
        //std::cout << "came here1\n";
        for (int row = rows; row < height; row++)
        {
            out.data[(row-rows)*width+(col-cols)]=thisCard.data[(row) * width + col];
        }
    }
    std::cout<<"Made it here\n";
    //cv::imshow("out", thisCard);
    //rankImage(cv::Rect(cols, rows, width - cols, height - rows)).copyTo(out(cv::Rect(0, 0, width , height )));
    return out;
}
void card::CutRankAndSuit()
{
    std::cout << "CUTTING!\n";
    int rankWidth = 45;
    int rankHeight = 48;
    int suitHeight = 55;

    cv::Mat rank = cardImage(cv::Rect(0, 0, rankWidth, rankHeight));
    cv::Mat suit = cardImage(cv::Rect(0, rankHeight, rankWidth, suitHeight));

    std::cout << "rank widht,height" << rank.cols << "  " << rank.rows << std::endl;
    cv::threshold(rank, rankImage, 170, 255, cv::THRESH_BINARY);
    cv::threshold(suit, suitImage, 170, 255, cv::THRESH_BINARY);
    cv::imshow("rank1", rankImage);
    cv::imshow("suit1", suitImage);
    //cv::waitKey(0);
    /*std::vector<uchar> thisRank;
    thisRank.assign(rankImage.data, rankImage.data + rankImage.total() * rankImage.channels());
    std::vector<uchar> thisSuit;
    thisSuit.assign(suitImage.data, suitImage.data + suitImage.total() * suitImage.channels());
    std::cout << "going to allign!\n";*/
    rankImage= allignLeftTop(rankImage, rank.cols, rank.rows);
    suitImage= allignLeftTop(suitImage, suit.cols, suit.rows);
    cv::imshow("rank", rankImage);
    cv::imshow("suit", suitImage);
    std::cout << "allign!\n";
    //cv::waitKey(0);
    std::cout << "DONE!\n";
}
place GetCardPlace()
{
    return place(0, 0);
}

card::card(cv::Mat image, bool savePictures)
{
    std::cout << "making card\n";
    this->cardImage = image;
    cardHeight = image.rows;
    cardWidth = image.cols;
    std::string rankString[13] = {"ace", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "jack", "queen", "king"};
    std::string suitString[4] = {"heart", "club", "diamond", "spade"};
    std::string imPath = "/home/pi/Desktop/git/project-robotica2021/vision/images/";
    CutRankAndSuit();
    if (savePictures)
    {
        std::cout << "waiting until key press to save current picture\n";

        int keyCode = cv::waitKey(0);
        if (keyCode == 32)
        {
            try
            {
                if (suitImage.empty())
                    std::cout << "Spicture empty\n";
                if (rankImage.empty())
                    std::cout << "Rpicture empty\n";
                cv::imwrite(imPath + "RENAMESUIT.png", suitImage);
                std::cout << "done thisn";
                cv::imwrite(imPath + "RENAMERANK.png", rankImage);
            }
            catch (const cv::Exception &ex)
            {
                fprintf(stderr, "Exeption converting image to png: %s\n", ex.what());
            }
            std::cout << "rename pictures with hand please\n";
        }
    }
    else
    {
        std::cout << "cameHere???\n";
        for (int i = 0; i < 13; i++)
        {
            ranks.push_back(cv::imread(imPath + rankString[i] + ".png"));
        }
        for (int i = 0; i < 4; i++)
        {
            suits.push_back(cv::imread(imPath + suitString[i] + ".png"));
        }
        if (ranks.empty())
            std::cout << "the ranks were not loaded\n";
        if (ranks[0].empty())
            std::cout << "the first picture is empty\n";
    }
    std::cout << "made card\n";
}
card::card()
{
}

card::~card()
{
}
