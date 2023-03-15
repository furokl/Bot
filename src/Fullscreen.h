#pragma once
#include <Windows.h>
#include <WinUser.h>
#include "opencv2/highgui.hpp"

// -----------------------------------------
// 
// Read from the screen
// 
// -----------------------------------------
class Fullscreen
{
private:
    HWND hwndDesktop;
    HDC hwindowDC, hwindowCompatibleDC;
    HBITMAP hbwindow;
    BITMAPINFOHEADER bi;
    RECT windowsize;
    int height, width, srcheight, srcwidth;
    cv::Mat src;

public:
    Fullscreen()
    {
        init();
    }
    ~Fullscreen()
    {
    }
    Fullscreen(const Fullscreen &) = delete;
    void operator=(const Fullscreen &) = delete;
    
    const HWND& getHwnd() const { return hwndDesktop; }
    const cv::Mat& getScreen() const { return src; }
    const int getWidth() const { return width; }
    const int getHeight() const { return height; }
    void refresh();

private:
    void init();
};