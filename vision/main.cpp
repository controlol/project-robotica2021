#include <iostream>
#include <opencv2/opencv.hpp>
#include <sstream>
#include "headers/image.hpp"
#include "Moore.hpp"
#include "card.hpp"
#include "Connection.hpp"

using namespace cv;

Mat src, src_gray;
Mat dst, detected_edges;
int lowThreshold = 20;
const int max_lowThreshold = 100;
const int ratio = 3;
const int kernel_size = 3;
const char *window_name = "Edge Map";

#define PORT 8080

int main(int argc, char **argv)
{
    int count = 0;
    BlurKernel bKernel = BlurKernel();
    EdgeKernel eKernel = EdgeKernel();
    SinglePixelKernel spKernel = SinglePixelKernel();
    cv::VideoCapture camera(0);

    if (!camera.isOpened())
    {
        std::cout << "Error with gettin camera\n";
        return 1;
    }
    //cv::namedWindow("Webcam", WINDOW_AUTOSIZE);
    //cv::namedWindow("done", WINDOW_AUTOSIZE);
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
    int waiter = 0;

    cardPlaces.push_back(cv::Rect(50, 80, 196, 253));    //player 1 card 1
    cardPlaces.push_back(cv::Rect(246, 80, 196, 253));   //p1c2
    cardPlaces.push_back(cv::Rect(443, 80, 196, 253));   //p2c1
    cardPlaces.push_back(cv::Rect(640, 80, 196, 253));   //p2c2
    cardPlaces.push_back(cv::Rect(837, 80, 196, 253));   //p3c1
    cardPlaces.push_back(cv::Rect(1034, 80, 196, 253));  //p3c2
    cardPlaces.push_back(cv::Rect(50, 586, 196, 253));   //p4c1
    cardPlaces.push_back(cv::Rect(246, 586, 196, 253));  //p4c2
    cardPlaces.push_back(cv::Rect(443, 586, 196, 253));  //p5c1
    cardPlaces.push_back(cv::Rect(640, 586, 196, 253));  //p5c2
    cardPlaces.push_back(cv::Rect(837, 586, 196, 253));  //p6c1
    cardPlaces.push_back(cv::Rect(1034, 586, 196, 253)); //p6c2

    cardPlaces.push_back(cv::Rect(148, 333, 196, 253)); //opencard 1
    cardPlaces.push_back(cv::Rect(340, 333, 196, 253)); //oc2
    cardPlaces.push_back(cv::Rect(536, 333, 196, 253)); //oc3
    cardPlaces.push_back(cv::Rect(723, 333, 196, 253)); //oc4
    cardPlaces.push_back(cv::Rect(935, 333, 196, 253)); //oc5
    cv::Mat qualityTest;

    camera.grab();
    camera.retrieve(qualityTest);
    //cv::imshow("testttsss", qualityTest);

    camera.set(CAP_PROP_FRAME_WIDTH, 1280);
    camera.set(CAP_PROP_FRAME_HEIGHT, 960);

    camera.set(CAP_PROP_FRAME_WIDTH, 3840);
    camera.set(CAP_PROP_FRAME_HEIGHT, 2160);

    char stop[256] = {"stop"};
    char check[256] = {"check"};
    Connection connection = Connection(3005);
    std::string buffer1;
    
  /*  while (cv::waitKey(1000) != 32)
    {
        cv::line(frame, cv::Point(246, 0), cv::Point(246, 960), Scalar(255, 0, 0));
        cv::line(frame, cv::Point(443, 0), cv::Point(443, 960), Scalar(255, 0, 0));
        cv::line(frame, cv::Point(640, 0), cv::Point(640, 960), Scalar(255, 0, 0));
        cv::line(frame, cv::Point(837, 0), cv::Point(837, 960), Scalar(255, 0, 0));
        cv::line(frame, cv::Point(1034, 0), cv::Point(1034, 960), Scalar(255, 0, 0));
        cv::line(frame, cv::Point(0, 333), cv::Point(1280, 333), Scalar(255, 0, 0));
        cv::line(frame, cv::Point(0, 586), cv::Point(1280, 586), Scalar(255, 0, 0));
        cv::line(frame, cv::Point(0, 80), cv::Point(1280, 80), Scalar(255, 0, 0));
        cv::line(frame, cv::Point(0, 840), cv::Point(1280, 840), Scalar(255, 0, 0));
        cv::imshow("Webcam", frame);
        camera>>frame;
    }*/

    //main while loop
    while (1)
    {
        //cv::imshow("Webcam", frame);
        camera >> frame;
        std::cout << "Waiting for client\n";
        bool result = connection.WaitForClient();
        if (result)
            std::cout << "client connect" << std::endl;
        std::string data = connection.ReadData();
        std::cout << data << std::endl;
        std::cout<<"this was data"<<data<<"\n";
        std::stringstream string(data);
        int n;
        string>>n;
        std::cout<<n;


        for (size_t i = 0; i < 10; i++)
        {
            camera >> frame;
        }

        std::string allCards[7][6];
        cv::Mat cardt;
        cv::Mat blllurr;
        cv::Mat edddges;
        cv::Mat usablecard;
        std::vector<std::vector<cv::Point>> contours;
        std::vector<Vec4i> hierarchy;
        Shape cardShape;
        int k = 0;
        cv::cvtColor(frame, grey, COLOR_BGR2GRAY);
        size_t j = 0;
        size_t amountOfCards = 0;
        if(n==-1){
            j=0;
            amountOfCards=17;
            std::cout<<"doing all\n";
        }
        else{
            j=n;
            amountOfCards=n+1;
            std::cout<<"doing only: "<<j<<" "<<amountOfCards<<std::endl;;
        }
        for (j; j < amountOfCards; j++)
        {
            cardt = grey(cardPlaces[j]);
            blllurr = cardt.clone();
            edddges = cardt.clone();
            usablecard = cardt;
            //cv::imshow("current card", cardt);
            im2.NewMat(cardt);
            //im2.BlurImage(blllurr.data);
            cv::blur(cardt, blllurr, Size(3, 3));
            //cv::imshow("blur", blllurr);
            //im2.DetectEdges(blllurr.data, edddges.data);

            cv::Canny(blllurr, edddges, 30, 60, 3);
            // cv::imshow("edges", edddges);
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
                    //cv::imshow("current card", cardt);
                    color = Scalar(255, 255, 255);
                    corners = cardShape.GetCorners();
                    temp = cardShape.CutOutShape(corners, cardt.cols, cardt.rows, cardt);
                    testCard = card(temp, false, corners, true);
                    //testCard.DetermenRank();
                    //testCard.DetermenSuit();
                    testCard.GetCompleteCard();
                    std::cout << "RANK AND SUIT: " << testCard.GetRank() << "  " << testCard.GetSuit() << std::endl;
                    //allCards.push_back(std::vector<std::string> "p"+i/2+"-"+testCard.GetRank()+"-"+testcard.GetSuit());
                    if (j > 11)
                    {

                        std::string message = testCard.GetRank() + "" + testCard.GetSuit();
                        //if(j-11!=k)
                            allCards[6][j-12] = message;
                        //if (i == contours.size() - 1&&j-11==k)
                           // allCards[6][k] = message;
                           // k++;
                    }
                    else
                    {
                        std::string message;
                        message = testCard.GetRank() + "" + testCard.GetSuit();
                        allCards[(j / 2)][j % 2] = message;
                    }
                }
                else
                    color = Scalar(255, 255, 0);
                cv::drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
            }
            //cv::imshow("contours", drawing);
            //cv::waitKey(0);
        }
        //}
        //}
        std::string message = "";
        for (size_t i = 0; i < 7; i++)
        {
            for (size_t j = 0; j < 5; j++)
            {
                if (allCards[i][j].empty())
                {
                    if (i < 6 && j < 2)
                    {
                        std::cout << "player " << i + 1 << " is missching card " << j + 1 << std::endl;
                        allCards[i][j] = "p" + std::to_string(i) + "xxx";
                    }
                    else if (i == 6)
                    {
                        std::cout << "open card " << j + 1 << " is missching " << std::endl;
                        allCards[i][j] = "0" + std::to_string(i) + "xxx";
                    }
                }
                else
                {
                    std::cout << allCards[i][j] << std::endl;
                }
                if (i == 6 || j < 2)
                    message += allCards[i][j] + "\n";
            }
        }
        connection.SendData(message); /*
                n = write(newsockfd, message.c_str(), message.size());
                if (n < 0)
                    std::cout << ("ERROR writing to socket");
                std::cout<<allCards[0];
 */
    }
    //else
    //{

    //}

    //printf("Here is the message: %s\n", buffer);
    //}
    // close(sockfd);
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