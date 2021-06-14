#include <iostream>
#include <opencv2/opencv.hpp>
#include "headers/image.hpp"
#include "Moore.hpp"
#include "card.hpp"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

using namespace cv;

Mat src, src_gray;
Mat dst, detected_edges;
int lowThreshold = 20;
const int max_lowThreshold = 100;
const int ratio = 3;
const int kernel_size = 3;
const char *window_name = "Edge Map";
static void CannyThreshold(int, void *)
{
    blur(src_gray, detected_edges, Size(3, 3));
    Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * ratio, kernel_size);
    dst = Scalar::all(0);
    src.copyTo(dst, detected_edges);
    imshow(window_name, dst);
}

static void opencvEdgestuff(int argc, char **argv)
{
    cv::VideoCapture camera(0);
    if (!camera.isOpened())
    {
        std::cout << "Error with gettin camera\n";
        //return 1;
    }
    cv::namedWindow("Webcam", WINDOW_AUTOSIZE);
    cv::Mat frame;
    camera >> frame;
    while (1)
    {
        cv::imshow("Webcam", frame);
        if (cv::waitKey(10) >= 0)
            break;
        cv::Mat grey;
        src = frame;

        std::cout << "is frame continues? " << grey.isContinuous() << std::endl;
        if (src.empty())
        {
            std::cout << "Could not open or find the image!\n"
                      << std::endl;
            std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
            //return -1;
        }

        std::cout << "ImageChannels: " << grey.channels() << "  Image type: " << grey.type() << std::endl;
        std::cout << std::flush;
        dst.create(src.size(), src.type());
        cvtColor(src, src_gray, COLOR_BGR2GRAY);
        namedWindow(window_name, WINDOW_AUTOSIZE);
        createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);
        CannyThreshold(0, 0);
        camera >> frame;
    }

    //CommandLineParser parser( argc, argv, "{@input | lake.jpg | input image}" );
    // src = imread( samples::findFile( parser.get<String>( "@input" ) ), IMREAD_COLOR ); // Load an image
    /* if (src.empty())
    {
        std::cout << "Could not open or find the image!\n"
                  << std::endl;
        std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
        return -1;
    }
    dst.create(src.size(), src.type());
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    namedWindow(window_name, WINDOW_AUTOSIZE);
    createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);
    CannyThreshold(0, 0);
    waitKey(0);*/
}

static void stuff(cv::VideoCapture camera, cv::Mat frame, BlurKernel bKernel, EdgeKernel eKernel, SinglePixelKernel spKernel)
{
    std::cout << "imma resizing" << std::endl;
    std::cout << "imma resizing" << std::endl;
    std::cout << "imma resizing" << std::endl;
    cv::resize(frame, frame, cv::Size(frame.cols / 2, frame.rows / 2));
    cv::Mat grey;
    std::cout << "gmaking it grey" << std::endl;
    cv::cvtColor(frame, grey, COLOR_BGR2GRAY);
    /*std::vector<std::vector<uchar>>originalImage;
std::vector<uchar> temp;
    if (grey.isContinuous())
    {
        temp.assign(grey.data, grey.data + grey.total() * grey.channels());
    }
    else
    {
        for (int i = 0; i < grey.rows; ++i)
        {
            temp.insert(temp.end(), grey.ptr<uchar>(i), grey.ptr<uchar>(i) + grey.cols * grey.channels());
        }
    }
    originalImage.resize(grey.rows,std::vector<uchar>(grey.cols));
    for (int i = 0; i < grey.rows; i++)
    {
        for (int j = 0; j < grey.cols; j++)
        {
            originalImage[i][j]=temp[grey.cols*i+j];             
        }
        
    }*/

    //image im1 = image(bKernel, eKernel, grey);
    //std::vector<std::vector<uchar>> blurredImage;
    std::cout << "saving grey in 2 mat" << std::endl;
    cv::Mat test = grey.clone();
    cv::Mat grey2 = grey.clone();
    // cv::Mat test(grey.rows,grey.cols,CV_8UC1);
    //cv::Mat edges(grey.rows,grey.cols,CV_8UC1);
    //int uhhh[test.total() * test.elemSize()];
    //bKernel.guassian_blur2D(frame.data, frame.data, frame.cols, frame.rows);
    //blurredImage = im1.BlurImage();
    //blurredImage = bKernel.gaussBlur_1(originalImage,grey.rows,grey.cols,5);
    //blurredImage = bKernel.GuassianBlur3(originalImage,grey.rows,grey.cols);
    //bKernel.blur4(grey.data, test.data, grey.cols, grey.rows);

    //std::cout<<"yeah done with the blur\n";
    // std::memcpy(test.data,uhhh, test.total() * test.elemSize());
    //std::vector<std::vector<double>> angles;
    /* cv::Mat matAngles(blurredImage.size(), blurredImage[0].size(), CV_8UC1) ;
        for(int i=0; i<matAngles.rows; ++i)
            for(int j=0; j<matAngles.cols; ++j)
                matAngles.at<uchar>(i, j) = blurredImage.at(i).at(j);*/

    //namedWindow("Blurred image", WINDOW_AUTOSIZE);
    //imshow("Blurred image",test);
    // eKernel.FindEdgeMatrix2(test.data,edges.data,grey.cols,grey.rows);
    //namedWindow("edges", WINDOW_AUTOSIZE);
    //imshow("edges",edges);
    std::cout << "the image cl<ss" << std::endl;
    image im1 = image(bKernel, eKernel, spKernel, grey);
    // im1.GetCardList();
    std::cout << "doing moore on the test picture" << std::endl;
    MooreNeighborhood moore = MooreNeighborhood();

    im1.BlurImage(grey.data);
    cv::imshow("blur", grey);
    im1.DetectEdges(grey.data, grey.data);
    cv::imshow("grey", grey);
    std::vector<place> tedt;
    test.data = moore.anotherTracing(grey.data, tedt, grey.cols, grey.rows);
    Shape testHape = Shape(test.data, tedt);
    if (testHape.IsShapeSquare())
    {
        std::vector<place> corners = testHape.GetCorners();
        cv::Mat temp = testHape.CutOutShape(corners, grey.cols, grey.rows, grey2);
        std::cout << "yaasss" << std::endl;
        // card testCard= card(temp,true);
        // temp.deallocate();
    }

    //std::cout<<"pixels.lenght: " <<tedt.size()<<std::endl;
    // std::cout<<"this is a card 1: " << moore.IsThisShapeACard(test.data, grey.cols,grey.rows)<<std::endl;
    cv::imshow("Webcam", frame);
    cv::imshow("new", test);
    std::cout << "shown frames" << std::endl;
    // im1.RemovePixelsFromPicture(grey.data, test.data, grey.cols,grey.rows);
    // im1.removeSinglePixels(grey.data,grey.cols,grey.rows);
    //cv::imshow("neeew", grey);
    // test.data= moore.anotherTracing(grey.data,tedt, grey.cols,grey.rows);
    //std::cout<<"this is a card 2: " << moore.IsThisShapeACard(test.data, grey.cols,grey.rows)<<std::endl;
    //testHape=Shape(test.data,tedt);
    /* if(testHape.IsShapeSquare()){
            std::vector<place> corners= testHape.GetCorners();
            testHape.CutOutShape(corners,grey.cols,grey.rows, grey2);
        }*/
    //cv::imshow("neew", test);

    //namedWindow("grey", WINDOW_AUTOSIZE);
    //imshow("grey",grey);
    if (!camera.isOpened())
    {
        std::cout << "Error with gettin camera\n";
    }
    camera >> frame;
    std::cout << "gotten new frame" << std::endl;
}

int main(int argc, char **argv)
{ /*
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         std::cout<<"ERROR, no port provided\n";
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        std::cout<<("ERROR opening socket\n");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              std::cout<<("ERROR on binding\n");
     listen(sockfd,5);

     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
     bzero(buffer,256);
     n = read(newsockfd,buffer,255);
     if (n < 0) error("ERROR reading from socket");
     printf("Here is the message: %s\n",buffer);
     n = write(newsockfd,"I got your message",18);
     if (n < 0) error("ERROR writing to socket");

*/

    int count = 0;
    BlurKernel bKernel = BlurKernel();
    EdgeKernel eKernel = EdgeKernel();
    SinglePixelKernel spKernel = SinglePixelKernel();
    cv::VideoCapture camera(0);
    // camera.release();
    std::cout << camera.get(CAP_PROP_BRIGHTNESS) << std::endl;
    std::cout << camera.get(CAP_PROP_CONTRAST) << std::endl;
    std::cout << camera.get(CAP_PROP_SATURATION) << std::endl;
    std::cout << camera.get(CAP_PROP_AUTO_WB) << std::endl;
    std::cout << camera.get(CAP_PROP_HUE) << std::endl;
    //camera.set(CAP_PROP_BRIGHTNESS,120);
    //camera.set(CAP_PROP_CONTRAST, 32);
    //camera.set(CAP_PROP_SATURATION,100);
    //1280 720
    camera.set(CAP_PROP_FRAME_WIDTH,1280);
    camera.set(CAP_PROP_FRAME_HEIGHT,960);
    camera.set(CAP_PROP_AUTO_WB, 1);
    if (!camera.isOpened())
    {
        std::cout << "Error with gettin camera\n";
        return 1;
    }
    cv::namedWindow("Webcam", WINDOW_AUTOSIZE);
    cv::namedWindow("done", WINDOW_AUTOSIZE);
    cv::Mat frame;
    camera >> frame;

    cv::Mat test;
    cv::Mat grey;
    cv::Mat grey2;
    cv::Mat temp;
    cv::Mat something;
    cv::Mat temp2;

    image im1 = image(bKernel, eKernel, spKernel, grey);
    image im2 = image(bKernel, eKernel, spKernel, grey);
    MooreNeighborhood moore = MooreNeighborhood();

    card testCard;

    std::vector<place> tedt;
    std::vector<place> tedt2;
    std::vector<place> corners;
    std::vector<card> cards;
    std::vector<cv::Rect> cardPlaces;

    cardPlaces.push_back(cv::Rect(50, 80, 196, 253));     //player 1 card 1
    cardPlaces.push_back(cv::Rect(246, 80, 196, 253));   //p1c2
    cardPlaces.push_back(cv::Rect(443, 80, 196, 253));   //p2c1
    cardPlaces.push_back(cv::Rect(640, 80, 196, 253));   //p2c2
    cardPlaces.push_back(cv::Rect(837, 80, 196, 253));   //p3c1
    cardPlaces.push_back(cv::Rect(1034, 80, 196, 253));   //p3c2
    cardPlaces.push_back(cv::Rect(50, 586, 196, 253));   //p4c1
    cardPlaces.push_back(cv::Rect(246, 586, 196, 253)); //p4c2
    cardPlaces.push_back(cv::Rect(443, 586, 196, 253)); //p5c1
    cardPlaces.push_back(cv::Rect(640, 586, 196, 253)); //p5c2
    cardPlaces.push_back(cv::Rect(837, 586, 196, 253)); //p6c1
    cardPlaces.push_back(cv::Rect(1034, 586, 196, 253)); //p6c2

    cardPlaces.push_back(cv::Rect(148, 333, 196, 253));   //opencard 1
    cardPlaces.push_back(cv::Rect(340, 333, 196, 253)); //oc2
    cardPlaces.push_back(cv::Rect(536, 333, 196, 253)); //oc3
    cardPlaces.push_back(cv::Rect(723, 333, 196, 253)); //oc4
    cardPlaces.push_back(cv::Rect(935, 333, 196, 253)); //oc5
    cv::Mat qualityTest;


        camera.grab();
        camera.retrieve(qualityTest);
        //cv::imshow("testttsss", qualityTest);

camera.set(CAP_PROP_FRAME_WIDTH,3840);
    camera.set(CAP_PROP_FRAME_HEIGHT,2160);

    //while (cv::waitKey(1000) < 0)
   // {
       // camera >> frame;
        /*cv::line(frame, cv::Point(246, 0), cv::Point(246, 960), Scalar(255, 0, 0));
        cv::line(frame, cv::Point(443, 0), cv::Point(443, 960), Scalar(255, 0, 0));
            cv::line(frame, cv::Point(640, 0), cv::Point(640, 960), Scalar(255, 0, 0));
        cv::line(frame, cv::Point(837, 0), cv::Point(837, 960), Scalar(255, 0, 0));
        cv::line(frame, cv::Point(1034, 0), cv::Point(1034, 960), Scalar(255, 0, 0));

        cv::line(frame, cv::Point(0, 333), cv::Point(1280, 333), Scalar(255, 0, 0));
        cv::line(frame, cv::Point(0, 586), cv::Point(1280, 586), Scalar(255, 0, 0));

        cv::line(frame, cv::Point(0, 80), cv::Point(1280, 80), Scalar(255, 0, 0));
        cv::line(frame, cv::Point(0, 840), cv::Point(1280, 840), Scalar(255, 0, 0));*/

       // cv::imshow("Webcam", frame);
        
        //td::cout<<frame.rows<<" "<<frame.cols<<std::endl;
        //std::cout<<qualityTest.rows<<" "<<qualityTest.cols<<std::endl;
   // }

   while(1){

cv::imshow("Webcam", frame);
    camera >> frame;
        char keycode=   cv::waitKey(1000);
        if(keycode==27)
            break;
       if(keycode==32){

    std::string allCards[7][6];
    cv::Mat cardt;
    cv::Mat blllurr;
    cv::Mat edddges;
    cv::Mat usablecard;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<Vec4i> hierarchy;
    Shape cardShape;
    int k = 0;
    //for (int k = 9; k > 0; k--)
    //{
        //camera >> frame;
        cv::cvtColor(frame, grey, COLOR_BGR2GRAY);
        //if (9 % k == 0)
        //{
            for (size_t j = 0; j < cardPlaces.size(); j++)
            {
                cardt = grey(cardPlaces[j]);
                blllurr = cardt.clone();
                edddges = cardt.clone();
                usablecard = cardt;
                cv::imshow("current card", cardt);
                im2.NewMat(cardt);
                //im2.BlurImage(blllurr.data);
                cv::blur(cardt, blllurr, Size(3, 3));
                cv::imshow("blur", blllurr);
                //im2.DetectEdges(blllurr.data, edddges.data);

                cv::Canny(blllurr, edddges, 30, 60, 3);
                cv::imshow("edges", edddges);
                //eKernel.FindEdgeMatrix2(blllurr.data,edddges.data,cardt.cols,cardt.rows);

                findContours(edddges, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
                Mat drawing = Mat::zeros(cardt.size(), CV_8UC3);
                sort(contours.begin(), contours.end(), [](const std::vector<cv::Point> &c1, const std::vector<cv::Point> &c2)
                     { return cv::contourArea(c1, false) < cv::contourArea(c2, false); });

                for (size_t i = 0; i < contours.size(); i++)
                {
                    Scalar color;
                    cardShape = Shape(contours[i]);
                    if (cardShape.IsShapeSquare())
                    {
                        cv::imshow("current card", cardt);
                        color = Scalar(255, 255, 255);
                        corners = cardShape.GetCorners();
                        temp = cardShape.CutOutShape(corners, cardt.cols, cardt.rows, cardt);
                        testCard = card(temp, false, corners, true);
                        //testCard.DetermenRank();
                        //testCard.DetermenSuit();
                        testCard.GetCompleteCard();
                        std::cout << "RANK AND SUIT: " << testCard.GetRank() << "  " << testCard.GetSuit() << std::endl;
                        //allCards.push_back(std::vector<std::string> "p"+i/2+"-"+testCard.GetRank()+"-"+testcard.GetSuit());
                        if(j>11){
                            
                            std::string message = "o"+std::to_string(k)+" "+testCard.GetRank()+" "+testCard.GetSuit();
                            allCards[6][k]=message;
                            if(i==contours.size()-1)
                                k++;
                        }
                        else{
                            std::string message;
                            message="P"+std::to_string(j/2)+" "+testCard.GetRank()+" "+testCard.GetSuit();
                            allCards[(j/2)][j%2]=message;
                        }
                    }
                    else
                        color = Scalar(255, 255, 0);
                    drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
                }
                cv::imshow("contours", drawing);
                //cv::waitKey(0);
            }
        //}
    //}

      for (size_t i = 0; i < 7; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            if(allCards[i][j].empty()){
                if(i<6 && j<2)
                    std::cout<<"player " <<i+1<<" is missching card "<<j+1<<std::endl;
                else if(i==6 )
                    std::cout<<"open card " <<j+1<<" is missching "<<std::endl;
            }
            else{
                std::cout<<allCards[i][j]<<std::endl;
            }
        }
        
    }
    //std::cout<<allCards[0];
    
       }}
    //cv::waitKey(0);

    // while (1)
    // {
    //     cv::resize(frame, frame, cv::Size(frame.cols, frame.rows));

    //     cv::cvtColor(frame, grey, COLOR_BGR2GRAY);
    //     test = grey.clone();
    //     grey2 = grey.clone();
    //     cv::Rect fuck(0, 0, 100, 150);
    //     cv::Mat loser = grey(fuck);
    //     imshow("horrible person", loser);
    //     im1.NewMat(grey);
    //     im2.NewMat(loser);
    //     something = loser;

    //     // cards.clear();
    //     // cards = im1.GetCardList();
    //     // std::cout<<"gotten list"<<std::endl;
    //     // for (size_t i = 0; i < cards.size(); i++)
    //     // {
    //     //     std::cout<<"card "<<i<<"has rank"<<cards[i].GetRank()<<std::endl;
    //     //     /*place cplace=cards[i].GetCardPlace();
    //     //     std::string string ="card rank: ";
    //     //     string+= cards[i].GetRank();
    //     //     cv::putText(frame,string,Point(cplace.GetX(),cplace.GetY()),FONT_HERSHEY_COMPLEX,0.8,Scalar(200,200,0));*/
    //     // }

    //     // cv::waitKey(0);
    //     /*if (cards.size() > 0)
    //     {
    //         std::cout <<"The rank is::::: "<< cards[0].GetRank() << std::endl;
    //     }*/

    //     im1.BlurImage(grey.data);
    //     im2.BlurImage(loser.data);
    //     cv::imshow("blur", grey);

    //     im1.DetectEdges(grey.data, grey.data);
    //     im2.DetectEdges(loser.data, loser.data);
    //     cv::imshow("grey", grey);
    //     cv::imshow("edggggg", loser);

    //     std::vector<std::vector<cv::Point>> contours;
    //     std::vector<Vec4i> hierarchy;
    //     findContours(loser, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
    //     Shape testshape2;
    //     Mat drawing = Mat::zeros(loser.size(), CV_8UC3);
    //     for (size_t i = 0; i < contours.size(); i++)
    //     {
    //         Scalar color;
    //         testshape2 = Shape(contours[i]);
    //         if (testshape2.IsShapeSquare())
    //         {
    //             color = Scalar(255, 255, 255);
    //             corners = testshape2.GetCorners();
    //             temp = testshape2.CutOutShape(corners, grey.cols, grey.rows, grey2);
    //             testCard = card(temp, false, corners);
    //             testCard.DetermenRank();
    //         }
    //         else
    //             color = Scalar(255, 255, 0);
    //         drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
    //     }
    //     imshow("contours", drawing);

    //     tedt.clear();
    //     tedt2.clear();
    //     // test.data = moore.anotherTracing(grey.data, tedt, grey.cols, grey.rows);
    //     something.data = moore.anotherTracing(loser.data, tedt2, loser.cols, loser.rows);
    //     std::cout << something.empty();
    //     //tedt2 = moore.anotherTracing2(grey.data, grey.cols, grey.rows);
    //     std::cout << "length of tedt: " << tedt.size() << std::endl;
    //     std::cout << "length of tedt2: " << tedt2.size() << std::endl;
    //     // cv::imshow("moore1", test);
    //     //cv::imshow("done",something);
    //     //cv::imshow("moore2",tedt2);
    //     //Shape testHape = Shape(test.data, tedt);
    //     //sharpenCard(grey2);

    //     /*if (testHape.IsShapeSquare())
    //     {
    //         std::cout << "Shape is square" << std::endl;
    //         corners = testHape.GetCorners();
    //         temp = testHape.CutOutShape(corners, grey.cols, grey.rows, grey2);
    //         testCard = card(temp, false,corners);
    //         testCard.DetermenRank();
    //     }
    //     else
    //     {
    //         std::cout << "Shape is NOT square" << std::endl;
    //     }*/
    //     //testHape.~Shape();

    //     // int rankWidth = 45;
    //     // int rankHeight = 48;
    //     // int suitHeight = 55;

    //     // cv::Mat rank = cardImage(cv::Rect(0, 0, rankWidth, rankHeight));
    //     // cv::Mat suit = cardImage(cv::Rect(0, rankHeight, rankWidth, suitHeight));
    //     // std::cout << "rank widht,height" << rank.cols << "  " << rank.rows << std::endl;
    //     // cv::threshold(rank, rankImage, 170, 255, cv::THRESH_BINARY);
    //     // cv::threshold(suit, suitImage, 170, 255, cv::THRESH_BINARY);

    //     // std::vector<std::vector<Point> > r_cnts;
    //     // std::vector<std::vector<Point> > s_cnts;

    //     // Rect r_boundbox;
    //     // Rect s_boundbox;

    //     // Mat r_copy = r.clone();
    //     // Mat s_copy = s.clone();

    //     // findContours(r_copy, r_cnts, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    //     // sort(r_cnts.begin(), r_cnts.end(), [](const std::vector<Point>& c1, const std::vector<Point>& c2) {
    //     // 	return contourArea(c1, false) < contourArea(c2, false);
    //     // });
    //     // r_boundbox = boundingRect(r_cnts[r_cnts.size() - 1]);

    //     // findContours(s_copy, s_cnts, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    //     // sort(s_cnts.begin(), s_cnts.end(), [](const std::vector<Point>& c1, const std::vector<Point>& c2) {
    //     // 	return contourArea(c1, false) < contourArea(c2, false);
    //     // });
    //     // s_boundbox = boundingRect(s_cnts[s_cnts.size() - 1]);

    //     // Mat rr, ss;

    //     // rr = r(r_boundbox);
    //     // ss = s(s_boundbox);

    //     // resize(rr, rr, Size(70, 125));
    //     // resize(ss, ss, Size(70, 100));

    //     // imshow("RANKROI", rr);
    //     // imshow("SUITROI", ss);

    //     imshow("Webcam", frame);
    //     camera >> frame;
    //     if (cv::waitKey(1000) >= 0)
    //         break;
    // }
    //while(cv::waitKey(1000) < 0)
    //continue;
    return 0;
}