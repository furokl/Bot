#include "Detector.h"

// -----------------------------------------
// Detect grey arrows
// -----------------------------------------
bool Detector::detectFromFullscreen() {
    screen.refresh();
    for (int theme{}; theme < MAX_MATCHTEMPLTHEME; ++theme) {
        t[theme] = std::thread(&Detector::findGreyArrows, this, std::ref(mathcTemplTheme[theme]), std::ref(templ_array[theme]));
        t[theme].join();
    }
    if (find_templ == nullptr || find_match == nullptr) return false;

    find_y = find_match->maxLoc.y + (find_templ->rows / 2);
    find_x = find_match->maxLoc.x + (find_templ->cols / 2);
    return true;
}

// -----------------------------------------
// Similarity calculation : max_val ~ 1 (TM_CCORR_NORMED)
// @see: cnst::cv_k::grey_arrows
// -----------------------------------------
void Detector::findGreyArrows(match_templ_struct& matchTempl, cv::Mat& themeTempl) {
    matchTemplate(screen.getScreen(), themeTempl, matchTempl.result, cv::TM_CCORR_NORMED);
    minMaxLoc(matchTempl.result,
              &matchTempl.minVal,
              &matchTempl.maxVal,
              &matchTempl.minLoc,
              &matchTempl.maxLoc);
    if (matchTempl.maxVal < cnst::cv_k::grey_arrows) return;

    find_templ = &themeTempl;
    find_match = &matchTempl;
}