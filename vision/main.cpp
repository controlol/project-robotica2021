#include <iostream>
#include <opencv2/opencv.hpp>
#include "headers/image.hpp"
#include"Moore.hpp"
#include"card.hpp"

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
    cv::namedWindow("Webcam", WINDOW_AUTOSIZE);
    cv::Mat frame;
    camera >> frame;
    while (1)
    {
        cv::resize(frame,frame,cv::Size(frame.cols/2,frame.rows/2));
        cv::Mat grey;
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

        image im1 = image(bKernel,eKernel,spKernel,grey);
       // im1.GetCardList();
       std::cout<<"doing moore on the test picture"<<std::endl;
        MooreNeighborhood moore = MooreNeighborhood();
        int data[25]={0,0,0,0,0,
                      0,255,255,255,0,
                      0,255,0,255,0,
                      0,255,255,255,0,
                      0,0,0,0,0};
        //cv::Mat test = cv::Mat(5,5,CV_8UC1, data);
        cv::Mat test2 = cv::Mat(5,5,CV_8UC1);
        //moore.Trace(test.data, 5,5);
        im1.BlurImage(grey.data);
        cv::imshow("blur", grey);
        im1.DetectEdges(grey.data,grey.data);
        cv::imshow("grey", grey);
        std::vector<place>tedt;
        test.data= moore.anotherTracing(grey.data,tedt, grey.cols,grey.rows);
        Shape testHape=Shape(test.data,tedt);
        if(testHape.IsShapeSquare()){
            std::vector<place> corners= testHape.GetCorners();
            cv::Mat temp =testHape.CutOutShape(corners,grey.cols,grey.rows, grey2);
           // card testCard= card(temp,true);
           // temp.deallocate();
        }
         
        
        //std::cout<<"pixels.lenght: " <<tedt.size()<<std::endl;
       // std::cout<<"this is a card 1: " << moore.IsThisShapeACard(test.data, grey.cols,grey.rows)<<std::endl;
        cv::imshow("Webcam", frame);
        cv::imshow("new", test);
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
        if (cv::waitKey(1000) >= 0)
            break;
        //namedWindow("grey", WINDOW_AUTOSIZE);
        //imshow("grey",grey);
        camera >> frame;
        //count--;
        if(count < 0)
            break;
    }
    //while(cv::waitKey(1000) < 0)
        //continue;
    return 0;
}