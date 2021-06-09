#ifndef cardheader
#define cardheader
#include "enums.hpp"
#include "place.hpp"
#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include "BlurKernel.hpp"

class card
{
private:
    /* data */
    Ranks rank;
    Suits suit;
    cv::Mat rankImage;
    cv::Mat suitImage;
    place cardPlace;
    int cardWidth;
    int cardHeight;
    //matrix
    cv::Mat cardImage;
    place thing;
    std::vector<cv::Mat> ranks;
    std::vector<cv::Mat> ranks2;
    std::vector<cv::Mat> suits;

public:
    card(cv::Mat image, bool, std::vector<place> corner);
    ~card();
    card();
    void DetermenRank();
    void DetermenSuit();
    place GetCardPlace();
    void CutRankAndSuit();

    cv::Mat allignLeftTop(cv::Mat thisCard, int width, int height);
    void BinaryAnd(std::vector<uchar> mask, std::vector<uchar> targetImage, uchar *out, int width, int height);
    void absdiff(cv::Mat in1, cv::Mat in2, cv::Mat out);
    void sharpenCard(cv::Mat image);
    std::string GetRank();
};
#endif