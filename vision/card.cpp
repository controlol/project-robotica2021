#include "card.hpp"

void card::DetermenRank()
{
    int comaprisonNumber = 0;
    int old = 0;
    int cardNumber=0;
    int width = rankImage.cols;
    int height = rankImage.rows;
    std::vector<uchar> loadedImage;
    std::vector<uchar> thisCard;
    thisCard.assign(rankImage.data,rankImage.data+rankImage.total()*rankImage.channels());
    

    for (int i = 0; i < 13; i++)
    {
        loadedImage.assign(ranks[i].data,ranks[i].data+ranks[i].total()*ranks[i].channels());
        std::cout<<"came here2\n";
        for (int col = 0; col < width; col++)
        {
            std::cout<<"came here1\n";
            for (int row = 0; row < height; row++)
            {
                    std::cout<<"came here\n";
            
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
    std::cout<<"cardNumber: "<<cardNumber<<std::endl;
    std::cout<<"compare: "<<comaprisonNumber<<std::endl;
}
void card::DetermenSuit()
{
}
void card::CutRankAndSuit()
{
    std::cout << "CUTTING!\n";
    int rankWidth = 45;
    int rankHeight = 48;
    int suitHeight = 55;

    cv::Mat rank = cardImage(cv::Rect(0, 0, rankWidth, rankHeight));
    cv::Mat suit = cardImage(cv::Rect(0, rankHeight, rankWidth, suitHeight));

    std::cout<<"rank widht,height"<<rank.cols<<"  "<<rank.rows<<std::endl;
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
    std::string imPath = "/home/pi/Desktop/git/project-robotica2021/vision/images/";
    CutRankAndSuit();
    if (savePictures)
    {
        std::cout << "waiting until key press to save current picture\n";
        
        
        int keyCode = cv::waitKey(0);
        if(keyCode==32){
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
    else{}
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
    }
    std::cout << "made card\n";
}
card::card()
{
}

card::~card()
{
}
