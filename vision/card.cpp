#include "card.hpp"

void card::DetermenRank()
{
    int comaprisonNumber = 0;
    int old = 0;
    int cardNumber;
    uchar *loadedImage;
    uchar *thisCard = rankImage.data;
    int width = rankImage.cols;
    int height = rankImage.rows;

    for (int i = 0; i < 13; i++)
    {
        for (int col = 0; col < width; col++)
        {
            for (int row = 0; row < height; row++)
            {
                if (thisCard[row * width + col] != 0 && thisCard[row * width + col] == loadedImage[row * width + col])
                    comaprisonNumber++;
            }
        }
        if (comaprisonNumber > old)
        {
            cardNumber = i;
            old = comaprisonNumber;
        }
    }
    rank = static_cast<Ranks>(cardNumber);
}
void card::DetermenSuit()
{
}
void card::CutRankAndSuit()
{
    std::cout << "CUTTING!\n";
    int rankWidth = cardWidth * 0.27;
    int rankHeight = cardHeight * 0.18;
    int suitHeight = cardHeight * 0.3;

    cv::Mat rank = cardImage(cv::Rect(0, 0, rankWidth, rankHeight));
    cv::Mat suit = cardImage(cv::Rect(0, rankHeight, rankWidth, suitHeight));

    cv::threshold(rank, rankImage, 170, 255, cv::THRESH_BINARY);
    cv::threshold(suit, suitImage, 170, 255, cv::THRESH_BINARY);
    cv::imshow("rank",rankImage);
    cv::imshow("suit",suitImage);
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
    std::string rankString[13] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "jack", "queen", "king"};
    std::string suitString[4] = {"heart", "club", "diamond", "spade"};
    std::string imPath = "~/Desktop/git/project-robotica2021/vision/";
    /*if (savePictures)
    {
        std::cout << "waiting until key press to save current picture\n";
        CutRankAndSuit();
        
        cv::waitKey(0);
        try{
            if(suitImage.empty())
            std::cout << "Spicture empty\n";
            if(rankImage.empty())
            std::cout << "Rpicture empty\n";
        cv::imwrite(imPath + "RENAMESUIT.png", suitImage);
        std::cout << "done thisn";
        cv::imwrite(imPath + "RENAMERANK.png", rankImage);
        }
        catch(const cv::Exception& ex){
            fprintf(stderr,"Exeption converting image to png: %s\n",ex.what());
        }
        std::cout << "rename pictures with hand please\n";
    }
    else
    {
        std::cout << "cameHere???\n";
        for (int i = 0; i < 13; i++)
        {
            ranks.push_back(cv::imread(imPath + rankString[i] + ".jpg", 0));
        }
        for (int i = 0; i < 4; i++)
        {
            suits.push_back(cv::imread(imPath + suitString[i] + ".jpg", 0));
        }
    }*/
    std::cout << "made card\n";
}
card::card()
{
}

card::~card()
{
}
