#include "card.hpp"

void card::DetermenRank(){
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
    double ranksum=0,ranksum2=0;
    double rankdiff=0;
    double bestRankMatchDiff=10000;
    double rankdiff2=0;
    double bestRankMatchDiff2=10000;
    int cardNumber2=0;
    int cardNumber=0;
    cv::Mat output(height,width,rankImage.type());
    //cv::Mat output2(height,width,rankImage.type());
    for (int k = 0; k < 13; k++)
    {
        ranksum=0;
        ranksum2=0;
         //BinaryAnd(loadedImage, thisCard,temp.data, width, height);
        //std::cout << "came here2\n";
        /*std::cout<<"cols: "<<rankImage.cols<<std::endl;
        std::cout<<"rows: "<<rankImage.rows<<std::endl;
        std::cout<<"cols: "<<ranks[k].cols<<std::endl;
        std::cout<<"rows: "<<ranks[k].rows<<std::endl;*/
        absdiff(rankImage,ranks[k],output);
        //absdiff(rankImage,ranks2[k],output2);
        cv::imshow("compared to", ranks[k]);
        cv::imshow("result", output);
        //v::imshow("result2", output2);
        
        for (size_t i = 0; i < width*height; i++)
        {
            ranksum+=output.data[i];
            //ranksum2+=output2.data[i];
        }
        std::cout<<ranksum<<std::endl;
        //std::cout<<ranksum2<<std::endl;
        rankdiff=ranksum/255;
        //rankdiff2=ranksum2/255;
        if(rankdiff<bestRankMatchDiff){
            bestRankMatchDiff=rankdiff;
            std::cout<<"best card was: "<<cardNumber<<std::endl;
            cardNumber=k;
            std::cout<<"best card is now: "<<cardNumber<<std::endl;
        }
        /*if(rankdiff2<bestRankMatchDiff2){
            bestRankMatchDiff2=rankdiff2;
            std::cout<<"2best card was: "<<cardNumber2<<std::endl;
            cardNumber2=k;
            std::cout<<"2best card is now: "<<cardNumber2<<std::endl;
        }*/
        std::cout << "cardNumber: " << cardNumber+1 << std::endl;
        //std::cout << "2cardNumber: " << cardNumber2+1 << std::endl;
        cv::imshow("compared to", ranks[k]);
        //std::cout << "rank: " << rank << std::endl;
        //cv::waitKey(0);
    }
    /*if(cardNumber==cardNumber2) 
            std::cout << "final cardNumber: " << cardNumber+1 << std::endl;*/
            std::cout << "FINAL cardNumber: " << cardNumber+1 << std::endl;
       // cv::waitKey(0);
        rank = static_cast<Ranks>(cardNumber);
   /* std::cout<<"did i guess correct? y/n\n"<<std::endl;
        char key = cv::waitKey(0);
        std::string name;
        if(key){
            std::cout<<"what was it? (ace,two,three,four,five,six,seven,eight,nine,ten,jack,queen,king)\n"<<std::endl;
            std::cin>>name;
            
        } */



}
std::string card::GetRank(){
    switch (rank)
   {
   case ace:
      return "ace";
      break;
   case two:
      return "two";
      break;
   case three:
      return "three";
      break;
   case four:
      return "four";
      break;
   case five:
      return "five";
      break;
   case six:
      return "six";
      break;
   case seven:
      return "seven";
      break;
   case eight:
      return "eight";
      break;
   case nine:
      return "nine";
      break;
   case ten:
      return "ten";
      break;
   case jack:
      return "jack";
      break;
   case queen:
      return "queen";
      break;
   case king:
      return "king";
      break;

   default:
      break;
   }
   return "nothing";
}
std::string card::GetSuit(){
    switch (suit)
   {
   case h:
      return "heart";
      break;
   case s:
      return "spade";
      break;
   case d:
      return "diamond";
      break;
   case c:
      return "club";
      break;

   default:
      break;
   }
   return "nothing";
}
void card::absdiff(cv::Mat in1, cv::Mat in2, cv::Mat out){
    if(in1.cols!=in2.cols)
    {
        printf("Make sure the input images have the same cols");
        return;
    }
     if(in1.rows!=in2.rows){
         printf("Make sure the input images have the same rows");
        return;
    }
    if(in1.channels()!=in2.channels()){
        std::cout<<": "<<in1.channels()<<std::endl;
        std::cout<<": "<<in2.channels()<<std::endl;
        printf("Make sure the input images have the same channels");
        return;
    }
    for (int i = 0; i < in1.rows; i++)
    {
        for (int j = 0; j < in1.cols; j++)
        {
            for (int k = 0; k < in1.channels(); k++)
            {
                out.at<uchar>(i,j,k)=abs(static_cast<int>(in1.at<uchar>(i,j,k)-in2.at<uchar>(i,j,k)));
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
    double ranksum=0;
    double rankdiff=0;
    double bestRankMatchDiff=10000;
    int cardNumber2=0;
    int cardNumber=0;
    cv::Mat output(height,width,suitImage.type());
    for (int k = 0; k < 4; k++)
    {
        ranksum=0;
        /*std::cout<<"cols: "<<rankImage.cols<<std::endl;
        std::cout<<"rows: "<<rankImage.rows<<std::endl;
        std::cout<<"cols: "<<ranks[k].cols<<std::endl;
        std::cout<<"rows: "<<ranks[k].rows<<std::endl;*/
        absdiff(suitImage,suits[k],output);
        cv::imshow("compared to", suits[k]);
        cv::imshow("result", output);
        
        for (size_t i = 0; i < width*height; i++)
        {
            ranksum+=output.data[i];
        }
        std::cout<<ranksum<<std::endl;
        rankdiff=ranksum/255;
        if(rankdiff<bestRankMatchDiff){
            bestRankMatchDiff=rankdiff;
            std::cout<<"best card was: "<<cardNumber<<std::endl;
            cardNumber=k;
            std::cout<<"best card is now: "<<cardNumber<<std::endl;
        }
        std::cout << "cardNumber: " << cardNumber+1 << std::endl;
        cv::imshow("compared to", suits[k]);
        //cv::waitKey(0);
    }
            std::cout << "FINAL card suit: " << cardNumber+1 << std::endl;
       // cv::waitKey(0);
     suit = static_cast<Suits>(cardNumber);

}

void card::BinaryAnd(std::vector<uchar> mask, std::vector<uchar> targetImage,uchar* out, int width, int height)
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
                out[row * width + col] =targetImage[row * width + col];
                //temp.at<uchar>(row, col,1) = targetImage[row * width + col];
            }
            else
            {
                out[row * width + col] ==255;
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
                if(row!=0 &&col>3)
                    rows = row;
                std::cout << "changed rows to: " << rows << "\n";
            }
            if (thisCard.data[row * width + col] == 0 && col < cols)
            {
                if(col!=0&&row>3)
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
void card::CutRankAndSuit()
{
    std::cout << "CUTTING!\n";
    int rankWidth = 45;
    int rankHeight = 48;
    int suitHeight = 55;

// std::vector<std::vector<cv::Point>> contours;
// std::vector<cv::Vec4i> hierarchy;
// cv::Mat rankSuit = cardImage(cv::Rect(0,0,rankWidth,rankHeight+suitHeight));
    cv::Mat rank = cardImage(cv::Rect(2, 8, rankWidth, rankHeight));
    cv::Mat suit = cardImage(cv::Rect(0, rankHeight+10, rankWidth, suitHeight));
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
    suitImage = allignLeftTop(suitImage, suit.cols, suit.rows);
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

void card::sharpenCard(cv::Mat image){
    //sharpened=original+(original-blurred)*amount
    BlurKernel bkernel = BlurKernel();
    cv::Mat out=image;
    cv::Mat result=image;
    bkernel.blur4(image.data,out.data,image.cols,image.rows);
    result=image+(image-out)*20;
    cv::imshow("enhanced",result);
}
card::card(cv::Mat image, bool savePictures, std::vector<place> corners)
{
    std::cout << "making card\n";
    cardPlace.SetX((corners[0].GetX()+corners[1].GetX()+corners[2].GetX()+corners[3].GetX())/4);
    cardPlace.SetY((corners[0].GetY()+corners[1].GetY()+corners[2].GetY()+corners[3].GetY())/4);
    this->cardImage = image;
    cardHeight = image.rows;
    cardWidth = image.cols;
    std::string rankString[13] = {"ace", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "jack", "queen", "king"};
    std::string rankString2[13] = {"ace2", "two2", "three2", "four2", "five2", "six2", "seven2", "eight2", "nine2", "ten2", "jack2", "queen2", "king2"};
    std::string suitString[4] = {"heart", "club", "spade", "diamond"};
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
            cv::cvtColor(ranks[i],ranks[i], cv::COLOR_BGR2GRAY);
            //ranks2.push_back(cv::imread(imPath + rankString2[i] + ".png"));
            //cv::cvtColor(ranks2[i],ranks2[i], cv::COLOR_BGR2GRAY);
        }
        for (int i = 0; i < 4; i++)
        {
            suits.push_back(cv::imread(imPath + suitString[i] + ".png"));
            cv::cvtColor(suits[i],suits[i], cv::COLOR_BGR2GRAY);
        }
        if (ranks.empty())
            std::cout << "the ranks were not loaded\n";
        if (ranks[0].empty())
            std::cout << "the first picture is empty\n";
    }
    std::cout << "made card\n";
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
