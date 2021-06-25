#include "card.hpp"

//#define DEBUG

void card::DetermenRank()
{
    /* const char *path="/home/pi/Desktop/git/project-robotica2021/vision/images/rank.png";
    //cv::imwrite(path, rankImage);
    char* outText;
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    if(api->Init(NULL,"eng")){
        fprintf(stderr,"could not initialize tesseract.\n");
        return;
    }
    Pix *image = pixRead(path);
    api->SetImage(image);
    outText=api->GetUTF8Text();
    std::cout<<"tekst is: "<<outText<<std::endl;
    api->End();
    delete api;
    delete [] outText;
    pixDestroy(&image);*/

    int width = rankImage.cols;
    int height = rankImage.rows;
    double ranksum = 0, ranksum2 = 0;
    double rankdiff = 0;
    double bestRankMatchDiff = 10000;
    double rankdiff2 = 0;
    double bestRankMatchDiff2 = 10000;
    int cardNumber2 = 0;
    int cardNumber = 0;
    cv::Mat output(height, width, rankImage.type());
    //cv::Mat output2(height,width,rankImage.type());
    for (int k = 0; k < 13; k++)
    {
        ranksum = 0;
        ranksum2 = 0;
        //BinaryAnd(loadedImage, thisCard,temp.data, width, height);
        //std::cout << "came here2\n";
        /*std::cout<<"cols: "<<rankImage.cols<<std::endl;
        std::cout<<"rows: "<<rankImage.rows<<std::endl;
        std::cout<<"cols: "<<ranks[k].cols<<std::endl;
        std::cout<<"rows: "<<ranks[k].rows<<std::endl;*/
        absdiff(rankImage, ranks[k], output);
//absdiff(rankImage,ranks2[k],output2);
#ifdef DEBUG
        cv::imshow("compared to", ranks[k]);
        cv::imshow("result", output);
#endif
        //v::imshow("result2", output2);

        for (size_t i = 0; i < width * height; i++)
        {
            ranksum += output.data[i];
            //ranksum2+=output2.data[i];
        }
        //std::cout << ranksum << std::endl;
        //std::cout<<ranksum2<<std::endl;
        rankdiff = ranksum / 255;
        //rankdiff2=ranksum2/255;
        if (rankdiff < bestRankMatchDiff)
        {
            bestRankMatchDiff = rankdiff;
#ifdef DEBUG
            std::cout << "best card was: " << cardNumber << std::endl;
#endif
            cardNumber = k;
#ifdef DEBUG
            std::cout << "best card is now: " << cardNumber << std::endl;
#endif
        }
/*if(rankdiff2<bestRankMatchDiff2){
            bestRankMatchDiff2=rankdiff2;
            std::cout<<"2best card was: "<<cardNumber2<<std::endl;
            cardNumber2=k;
            std::cout<<"2best card is now: "<<cardNumber2<<std::endl;
        }*/
#ifdef DEBUG
        std::cout << "cardNumber: " << cardNumber + 1 << std::endl;
        //std::cout << "2cardNumber: " << cardNumber2+1 << std::endl;
        cv::imshow("compared to", ranks[k]);
//std::cout << "rank: " << rank << std::endl;
//cv::waitKey(0);
#endif
    }
    /*if(cardNumber==cardNumber2) 
            std::cout << "final cardNumber: " << cardNumber+1 << std::endl;*/
#ifdef DEBUG
    std::cout << "FINAL cardNumber: " << cardNumber + 1 << std::endl;
#endif
    // cv::waitKey(0);
    rank = static_cast<Ranks>(cardNumber);
}
std::string card::GetRank()
{
    switch (rank)
    {
    case ace:
        return "a";
        break;
    case two:
        return "2";
        break;
    case three:
        return "3";
        break;
    case four:
        return "4";
        break;
    case five:
        return "5";
        break;
    case six:
        return "6";
        break;
    case seven:
        return "7";
        break;
    case eight:
        return "8";
        break;
    case nine:
        return "9";
        break;
    case ten:
        return "10";
        break;
    case jack:
        return "j";
        break;
    case queen:
        return "q";
        break;
    case king:
        return "k";
        break;

    default:
        break;
    }
    return "nothing";
}
std::string card::GetSuit()
{
    switch (suit)
    {
    case h:
        return "h";
        break;
    case s:
        return "s";
        break;
    case d:
        return "d";
        break;
    case c:
        return "c";
        break;

    default:
        break;
    }
    return "nothing";
}
void card::absdiff(cv::Mat in1, cv::Mat in2, cv::Mat out)
{
    if (in1.cols != in2.cols)
    {
        std::cout << ": " << in1.cols << std::endl;
        std::cout << ": " << in2.cols << std::endl;
        printf("Make sure the input images have the same cols");
        return;
    }
    if (in1.rows != in2.rows)
    {
        std::cout << ": " << in1.rows << std::endl;
        std::cout << ": " << in2.rows << std::endl;
        printf("Make sure the input images have the same rows");
        return;
    }
    if (in1.channels() != in2.channels())
    {
        std::cout << ": " << in1.channels() << std::endl;
        std::cout << ": " << in2.channels() << std::endl;
        printf("Make sure the input images have the same channels");
        return;
    }
    for (int i = 0; i < in1.rows; i++)
    {
        for (int j = 0; j < in1.cols; j++)
        {
            for (int k = 0; k < in1.channels(); k++)
            {
                out.at<uchar>(i, j, k) = abs(static_cast<int>(in1.at<uchar>(i, j, k) - in2.at<uchar>(i, j, k)));
                //std::cout<<(int)out.at<uchar>(i,j,k)<<std::endl;
            }
        }
    }
}

// void card::DetermenRank()
// {
//     double same = 0.0;
//     int rows;
//     int cols;
//     int width = rankImage.cols;
//     int height = rankImage.rows;
//     double SAD;
//     double minSAD = 256.0;
//     int searchImage;
//     int compareImage;
//     double bestSad;
//     double cardSad = 0.0;
//     int cardNumber = 0;

//     std::vector<uchar> loadedImage;
//     std::vector<uchar> thisCard;
//    // cv::Mat temp(height, width, CV_8UC1);
//    // temp=255;
//     thisCard.assign(rankImage.data, rankImage.data + rankImage.total() * rankImage.channels());
//     std::vector<uchar> thisCardtmp;
//     for (int k = 0; k < 13; k++)
//     {
//         loadedImage.assign(ranks[k].data, ranks[k].data + ranks[k].total() * ranks[k].channels());
//          //BinaryAnd(loadedImage, thisCard,temp.data, width, height);
//         //std::cout << "came here2\n";
//         if (loadedImage.empty())
//             std::cout << "loaded image is empty\n";
//         if (thisCard.empty())
//             std::cout << "this card is empty\n";
//         cv::imshow("compared to", ranks[k]);
//         //cv::imshow("result", temp);

//         SAD = 0.0;
//         same = 0.0;
//         for (size_t x = 0; x < width; x++)
//         {
//             for (size_t y = 0; y < height; y++)
//             {
//                 if (loadedImage[y * width + x] == thisCardtmp[y * width + x])
//                 {
//                     same++;
//                 }

//                 /*for (size_t j = 0; j < width; j++)
//                 {
//                     for (size_t i = 0; i < height; i++)
//                     {

//                         searchImage=thisCard[(x+y)*width+(y+i)];
//                         compareImage=loadedImage[j*width+i];

//                         SAD=abs(searchImage-compareImage);
//                     }

//                 }
//                 if(minSAD>SAD){
//                     minSAD=SAD;
//                     rows=x;
//                     cols=y;
//                     bestSad=SAD;
//                 }*/
//             }

//         } /*
//         std::cout<<"best sad: "<<bestSad<<std::endl;
//         if(bestSad<cardSad){
//             cardSad=bestSad;
//             std::cout<<"card sad: "<<cardSad<<std::endl;
//             std::cout<<"best card was: "<<cardNumber<<std::endl;
//             cardNumber=k;
//             std::cout<<"best card is now: "<<cardNumber<<std::endl;
//         }*/
//         SAD = (same / thisCardtmp.size()) * 100.0;
//         std::cout << "card sad: " << SAD << std::endl;
//         std::cout << "same pixels:: " << same << std::endl;
//         if (SAD > cardSad)
//         {
//             cardSad = SAD;

//             std::cout << "best card was: " << cardNumber << std::endl;
//             cardNumber = k;
//             std::cout << "best card is now: " << cardNumber << std::endl;
//         }
//     }
//     rank = static_cast<Ranks>(cardNumber);
//     cv::imshow("compared to", ranks[cardNumber]);
//     std::cout << "rank: " << rank << std::endl;
//     std::cout << "cardNumber: " << cardNumber << std::endl;
//     cv::waitKey(0);
//     //std::cout << "compare: " << comaprisonNumber << std::endl;
// }
void card::DetermenSuit()
{
    int width = suitImage.cols;
    int height = suitImage.rows;
    double ranksum = 0;
    double rankdiff = 0;
    double bestRankMatchDiff = 10000;
    int cardNumber2 = 0;
    int cardNumber = 0;
    cv::Mat output(height, width, suitImage.type());
    for (int k = 0; k < 4; k++)
    {
        ranksum = 0;
        /*std::cout<<"cols: "<<rankImage.cols<<std::endl;
        std::cout<<"rows: "<<rankImage.rows<<std::endl;
        std::cout<<"cols: "<<ranks[k].cols<<std::endl;
        std::cout<<"rows: "<<ranks[k].rows<<std::endl;*/
        absdiff(suitImage, suits[k], output);
#ifdef DEBUG
        cv::imshow("compared to", suits[k]);
        cv::imshow("result", output);
#endif

        for (size_t i = 0; i < width * height; i++)
        {
            ranksum += output.data[i];
        }
        //std::cout << ranksum << std::endl;
        rankdiff = ranksum / 255;
        if (rankdiff < bestRankMatchDiff)
        {
            bestRankMatchDiff = rankdiff;
#ifdef DEBUG
            std::cout << "best card was: " << cardNumber << std::endl;
#endif
            cardNumber = k;
#ifdef DEBUG
            std::cout << "best card is now: " << cardNumber << std::endl;
#endif
        }

        std::cout << "cardNumber: " << cardNumber + 1 << std::endl;
        cv::imshow("compared to", suits[k]);
        //cv::waitKey(0);
    }
#ifdef DEBUG
            std::cout
        << "FINAL card suit: " << cardNumber + 1 << std::endl;
#endif
    // cv::waitKey(0);
    suit = static_cast<Suits>(cardNumber);
}

void card::BinaryAnd(std::vector<uchar> mask, std::vector<uchar> targetImage, uchar *out, int width, int height)
{
    //uchar thisCardtmp[width*height];
    //cv::Mat temp(width, height, CV_8UC1);
    //temp=255;
    //thisCardtmp.assign(temp.data, temp.data + temp.total() * temp.channels());
    for (int col = 0; col < width; col++)
    {
        for (int row = 0; row < height; row++)
        {
            if (mask[row * width + col] == 0)
            {
                out[row * width + col] = targetImage[row * width + col];
                //temp.at<uchar>(row, col,1) = targetImage[row * width + col];
            }
            else
            {
                out[row * width + col] == 255;
                //==temp.data[row * width + col] = 255;
            }
        }
    }
    //cv::imshow("result", temp);
    // return thisCardtmp;
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
                if (row != 0 && col > 3)
                    rows = row;
                std::cout << "changed rows to: " << rows << "\n";
            }
            if (thisCard.data[row * width + col] == 0 && col < cols)
            {
                if (col != 0 && row > 3)
                    cols = col;
                std::cout << "changed cols to: " << cols << "\n";
            }
        }
    }

    std::cout << "rows: cols: " << rows << " " << cols << "\n";
    //thisCard.data[rows * width + cols] = 50;
    cv::imshow("out2", thisCard);
    // move rank to the top left corner and diff the images
    cv::Mat out(thisCard.rows, thisCard.cols, CV_8UC1);
    out = 255;
    for (int col = cols; col < width; col++)
    {
        //std::cout << "came here1\n";
        for (int row = rows; row < height; row++)
        {
            out.data[(row - rows) * width + (col - cols)] = thisCard.data[(row)*width + col];
        }
    }
    std::cout << "Made it here\n";
    //cv::imshow("out", thisCard);
    //rankImage(cv::Rect(cols, rows, width - cols, height - rows)).copyTo(out(cv::Rect(0, 0, width , height )));
    return out;
}

cv::Mat card::allignLeftBottom(cv::Mat thisCard, int width, int height)
{
    int rows = height;
    int cols = width;
    for (int col = width; col > 0; col--)
    {
        //std::cout << "came here1\n";
        for (int row = height; row > 0; row--)
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
                //if(row!=0 &&col>3)
                rows = row;
                std::cout << "changed rows to: " << rows << "\n";
            }
            if (thisCard.data[row * width + col] == 0 && col < cols)
            {
                //if(col!=0&&row>3)
                cols = col;
                std::cout << "changed cols to: " << cols << "\n";
            }
        }
    }

    std::cout << "rows: cols: " << rows << " " << cols << "\n";
    //thisCard.data[rows * width + cols] = 50;
    cv::imshow("out2", thisCard);
    // move rank to the top left corner and diff the images
    cv::Mat out(thisCard.rows, thisCard.cols, CV_8UC1);
    out = 255;

    for (int col = width; col > 0; col--)
    {
        for (int row = height; row > 0; row--)
        {
            out.data[(row - rows) * width + (col - cols)] = thisCard.data[(row)*width + col];
        }
    }

    /*for (int col = cols; col < width; col++)
    {
        //std::cout << "came here1\n";
        for (int row = rows; row < height; row++)
        {
            out.data[(height-row ) * width + (col - cols)] = thisCard.data[(row)*width + col];
        }
    }*/
    std::cout << "Made it here\n";
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
    int suitWidth = 40;

    // std::vector<std::vector<cv::Point>> contours;
    // std::vector<cv::Vec4i> hierarchy;
    // cv::Mat rankSuit = cardImage(cv::Rect(0,0,rankWidth,rankHeight+suitHeight));
    cv::Mat rank = cardImage(cv::Rect(2, 8, rankWidth, rankHeight));
    cv::Mat suit = cardImage(cv::Rect(0, rankHeight + 10, suitWidth, suitHeight));
    cv::imshow("rank2", rank);
    cv::imshow("suit2", suit);
    std::cout << "rank widht,height" << rank.cols << "  " << rank.rows << std::endl;
    // cv::Canny(rankSuit,rankSuit,30,60,3);
    // findContours(rankSuit, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    cv::threshold(rank, rankImage, 130, 255, cv::THRESH_BINARY);
    cv::threshold(suit, suitImage, 130, 255, cv::THRESH_BINARY);
    cv::imshow("rank1", rankImage);
    cv::imshow("suit1", suitImage);
    //cv::waitKey(0);
    /*std::vector<uchar> thisRank;
    thisRank.assign(rankImage.data, rankImage.data + rankImage.total() * rankImage.channels());
    std::vector<uchar> thisSuit;
    thisSuit.assign(suitImage.data, suitImage.data + suitImage.total() * suitImage.channels());
    std::cout << "going to allign!\n";*/
    rankImage = allignLeftTop(rankImage, rank.cols, rank.rows);
    suitImage = allignLeftBottom(suitImage, suit.cols, suit.rows);
    cv::imshow("rank", rankImage);
    cv::imshow("suit", suitImage);
    std::cout << "allign!\n";
    //cv::waitKey(0);
    std::cout << "DONE!\n";
}
place card::GetCardPlace()
{
    return cardPlace;
}

void card::sharpenCard(cv::Mat image)
{
    //sharpened=original+(original-blurred)*amount
    BlurKernel bkernel = BlurKernel();
    cv::Mat out = image;
    cv::Mat result = image;
    bkernel.blur4(image.data, out.data, image.cols, image.rows);
    result = image + (image - out) * 20;
    cv::imshow("enhanced", result);
}
void card::CompleteCard()
{
    cv::threshold(cardImage, cardImage, 130, 255, cv::THRESH_BINARY);
    cv::imshow("THE card", cardImage);
}
void card::GetCompleteCard()
{
    int width = cardImage.cols;
    int height = cardImage.rows;
    double ranksum = 0;
    double rankdiff = 0;
    double bestRankMatchDiff = 10000;
    int rankNumber = 0;
    int suitNumber = 0;
    cv::Mat output(height, width, cardImage.type());
    for (int s = 0; s < 4; s++)
    {
        for (int r = 0; r < 13; r++)
        {
            ranksum = 0;
            /*std::cout<<"cols: "<<rankImage.cols<<std::endl;
        std::cout<<"rows: "<<rankImage.rows<<std::endl;
        std::cout<<"cols: "<<ranks[k].cols<<std::endl;
        std::cout<<"rows: "<<ranks[k].rows<<std::endl;*/
            absdiff(cardImage, allCards[s * 13 + r], output);
            #ifdef DEBUG
            cv::imshow("compared to", allCards[s * 13 + r]);
            cv::imshow("result", output);
            #endif

            for (size_t i = 0; i < width * height; i++)
            {
                if (output.data[i] > 50)
                    ranksum += output.data[i];
            }
            //std::cout << ranksum << std::endl;
            rankdiff = ranksum / 255;
            if (rankdiff < bestRankMatchDiff)
            {
                bestRankMatchDiff = rankdiff;
                #ifdef DEBUG
                std::cout << "best card was: " << rankNumber + 1 << std::endl;
                #endif
                rankNumber = r;
                suitNumber = s;
                #ifdef DEBUG
                std::cout << "best card is now: " << rankNumber + 1 << " " << suitNumber << std::endl;
                #endif
            }
            #ifdef DEBUG
            std::cout << "cardNumber: " << rankNumber + 1 << std::endl;
            #endif
            //cv::imshow("compared to", allCards[s*13+r]);
            //cv::waitKey(0);
        }
    }
    #ifdef DEBUG
    std::cout << "FINAL card suit: " << rankNumber + 1 << " " << suitNumber << std::endl;
    #endif
    // cv::waitKey(0);
    rank = static_cast<Ranks>(rankNumber);
    suit = static_cast<Suits>(suitNumber);
}
card::card(cv::Mat image, bool savePictures, std::vector<place> corners, bool doCompleteCard)
{
    //std::cout << "making card\n";
    cardPlace.SetX((corners[0].GetX() + corners[1].GetX() + corners[2].GetX() + corners[3].GetX()) / 4);
    cardPlace.SetY((corners[0].GetY() + corners[1].GetY() + corners[2].GetY() + corners[3].GetY()) / 4);
    this->cardImage = image;
    cardHeight = image.rows;
    cardWidth = image.cols;
    std::string rankString[13] = {"ace", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "jack", "queen", "king"};
    std::string rankString2[13] = {"ace2", "two2", "three2", "four2", "five2", "six2", "seven2", "eight2", "nine2", "ten2", "jack2", "queen2", "king2"};
    std::string suitString[4] = {"heart", "club", "spade", "diamond"};
    std::string imPath = "/home/pi/Desktop/git/project-robotica2021/vision/images/";
    if (doCompleteCard)
    {
        //CompleteCard();
        if (savePictures)
        {
            std::cout << "waiting until space press to save current picture\n";

            int keyCode = cv::waitKey(0);
            if (keyCode == 32)
            {
                try
                {
                    cv::imwrite(imPath + "RENAMECARD.png", cardImage);
                    //std::cout << "done thisn";
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
            //std::cout << "cameHere???\n";
            for (int j = 0; j < 4; j++)
            {

                for (int i = 0; i < 13; i++)
                {
                    allCards.push_back(cv::imread(imPath + rankString[i] + suitString[j] + ".png", cv::IMREAD_GRAYSCALE));
                    if (allCards[j * 13 + i].channels() != 1)
                    {
                       // std::cout << "CONVER TO GREY!!!!!";
                        cv::cvtColor(allCards[i], allCards[i], cv::COLOR_BGR2GRAY);
                    }
                    //ranks2.push_back(cv::imread(imPath + rankString2[i] + ".png"));
                    //cv::cvtColor(ranks2[i],ranks2[i], cv::COLOR_BGR2GRAY);
                }
            }
            if (allCards.size() < 52)
                std::cout << "SOMETHING WENT WRONG\n";
        }
    }
    else
    {

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
            //std::cout << "cameHere???\n";
            for (int i = 0; i < 13; i++)
            {
                ranks.push_back(cv::imread(imPath + rankString[i] + ".png"));
                cv::cvtColor(ranks[i], ranks[i], cv::COLOR_BGR2GRAY);
                //ranks2.push_back(cv::imread(imPath + rankString2[i] + ".png"));
                //cv::cvtColor(ranks2[i],ranks2[i], cv::COLOR_BGR2GRAY);
            }
            for (int i = 0; i < 4; i++)
            {
                suits.push_back(cv::imread(imPath + suitString[i] + ".png"));
                cv::cvtColor(suits[i], suits[i], cv::COLOR_BGR2GRAY);
            }
            if (ranks.empty())
                std::cout << "the ranks were not loaded\n";
            if (ranks[0].empty())
                std::cout << "the first picture is empty\n";
        }
    }
   // std::cout << "made card\n";
    //sharpenCard(cardImage);
    //cv::Mat out;
    //cv::cvtColor(image,image,cv::COLOR_GRAY2BGR);
    //cv::detailEnhance(image, out);
    //cv::detailEnhance(out, out);
    //cv::imshow("detail enhance",out);
    //cardImage=out;
}
card::card()
{
}

card::~card()
{
}
