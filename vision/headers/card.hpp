#ifndef cardheader
#define cardheader
#include "enums.hpp"
#include "place.hpp"
#include <opencv2/opencv.hpp>

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
    std::vector<cv::Mat> suits;
public:
    card(cv::Mat image,bool);
    ~card();
    card();
    void DetermenRank();
    void DetermenSuit();
    place GetCardPlace();
    void CutRankAndSuit();
};
#endif