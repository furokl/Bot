#pragma once
#include <array>
#include "opencv2/imgproc.hpp"
#include "Constants.h"
#include "Fullscreen.h"

// -----------------------------------------
// 
// Detect grey arrows with OpenCV
// 
// -----------------------------------------
class Detector
{
public: 
    enum mathcTemplTheme
    {
        LIGHT,
        DARK,
        MAX_MATCHTEMPLTHEME
    };

//private:
    int find_x, find_y;

private:
    struct match_templ_struct
    {
        cv::Mat result;
        double minVal, maxVal;
        cv::Point minLoc, maxLoc;
        match_templ_struct()
            : result(cv::Mat()),
              minVal(0), maxVal(0),
              minLoc(cv::Point()),
              maxLoc(cv::Point())
        {

        }
    };

    cv::Mat *find_templ;
    match_templ_struct *find_match;

    std::array<cv::Mat, MAX_MATCHTEMPLTHEME> templ_array;
    std::array<match_templ_struct, MAX_MATCHTEMPLTHEME> mathcTemplTheme;
    std::array<std::thread, MAX_MATCHTEMPLTHEME> t;

public:
    Fullscreen screen;
    Detector()
        : templ_array({cnst::load::templ_light, cnst::load::templ_dark}),
          find_templ(nullptr),
          find_match(nullptr),
          find_x{}, find_y{}
    {
    }
    ~Detector()
    {
    }

    Detector(const Detector &) = delete;
    void operator=(const Detector &) = delete;

    bool detectFromFullscreen();
    int getX() const { return find_x; }
    int getY() const { return find_y; }
    void changeX(int &&dx) { find_x += dx; }
    void changeY(int &&dy) { find_y += dy; }
    
private:
    void findGreyArrows(match_templ_struct &matchTempl, cv::Mat &themeTempl);
};

