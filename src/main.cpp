#include <Windows.h>
#include <WinUser.h>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <array>
#include "Constants.h"

using namespace cv;
using namespace std;

static HDC hwindowDC, hwindowCompatibleDC;
static int height, width, srcheight, srcwidth;
static HBITMAP hbwindow;
static Mat src;
static BITMAPINFOHEADER  bi;
static RECT windowsize;

static Mat hwnd2mat(HWND hwnd)
{
    hwindowDC = GetDC(hwnd);
    hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
    SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);

    GetClientRect(hwnd, &windowsize);

    srcheight = windowsize.bottom;
    srcwidth = windowsize.right;
    height = windowsize.bottom / 1;
    width = windowsize.right / 1;

    src.create(height, width, CV_8UC4);

    hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = width;
    bi.biHeight = -height;
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    SelectObject(hwindowCompatibleDC, hbwindow);
    StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, 0, 0, srcwidth, srcheight, SRCCOPY); //change SRCCOPY to NOTSRCCOPY for wacky colors !
    GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, src.data, (BITMAPINFO *)&bi, DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow

    DeleteObject(hbwindow);
    DeleteDC(hwindowCompatibleDC);
    ReleaseDC(hwnd, hwindowDC);

    return src;
}

enum MyKey
{
    LEFT,
    UP,
    RIGHT,
    DOWN,
    MAX_MYKEY
};

static INPUT &fillingInputKey(const int& macros) {
    INPUT in;
    in.type = INPUT_KEYBOARD;
    in.ki.wVk = macros;
    in.ki.wScan = MapVirtualKey(macros, MAPVK_VK_TO_VSC);
    return in;
};

static INPUT move_left = fillingInputKey(0x41);
static INPUT move_right = fillingInputKey(0x44);
static std::array<INPUT, MAX_MYKEY> inputKey
{
    fillingInputKey(VK_LEFT),
    fillingInputKey(VK_UP),
    fillingInputKey(VK_RIGHT),
    fillingInputKey(VK_DOWN)
};

static cv::Mat templ_light = imread("..\\src\\resources\\GreyArrowLight.png", IMREAD_UNCHANGED);
static cv::Mat templ_dark = imread("..\\src\\resources\\GreyArrowDark.png", IMREAD_UNCHANGED);

static void lclick(INPUT &in) {
    in.mi.dwFlags = MOUSEEVENTF_MOVE;
    SendInput(1, &in, sizeof INPUT);
    Sleep(50);
    in.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &in, sizeof INPUT);
    Sleep(50);
    in.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &in, sizeof INPUT);
};

static void rclick(INPUT &in) {
    in.mi.dwFlags = MOUSEEVENTF_MOVE;
    SendInput(1, &in, sizeof INPUT);
    Sleep(50);
    in.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    SendInput(1, &in, sizeof INPUT);
    Sleep(50);
    in.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    SendInput(1, &in, sizeof INPUT);
};

static void pressKey(INPUT &in, bool &&isArrow = true) {
    if (isArrow) 
    {
        in.ki.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_SCANCODE;
        SendInput(1, &in, sizeof INPUT);
        in.ki.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
        SendInput(1, &in, sizeof INPUT);
        Sleep(200);
    }
    else
    {
        in.ki.dwFlags = KEYEVENTF_SCANCODE;
        SendInput(1, &in, sizeof INPUT);
        Sleep(100);
        in.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
        SendInput(1, &in, sizeof INPUT);
        Sleep(100);
    }
}

int main()
{
    HWND hwndDesktop = GetDesktopWindow();
    cv::Mat result, src, templ;
    double minVal{ }, maxVal{ };
    Point minLoc, maxLoc;
    while(true)
    {
        src = hwnd2mat(hwndDesktop);
        matchTemplate(src, templ_light, result, TM_CCORR_NORMED);
        minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
        if (maxVal > cnst::cv_k::grey_arrows) {
            templ = std::move(templ_light);
            break;
        }
        matchTemplate(src, templ_dark, result, TM_CCORR_NORMED);
        minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
        if (maxVal > cnst::cv_k::grey_arrows) {
            templ = std::move(templ_dark);
            break;
        }
    }

    const int findY{ maxLoc.y + (templ.rows / 2) };
    const int findX{ maxLoc.x + (templ.cols / 2) };
    std::array<const int, MAX_MYKEY> arrow_x
    {
        maxLoc.x + (templ.cols / 2) + cnst::left_dx,
        maxLoc.x + (templ.cols / 2) + cnst::up_dx,
        maxLoc.x + (templ.cols / 2) + cnst::right_dx,
        maxLoc.x + (templ.cols / 2) + cnst::down_dx
    };
    std::array<COLORREF, MAX_MYKEY> color;
    INPUT mouse;
    mouse.type = INPUT_MOUSE;
    SetCursorPos(findX, findY);
    mouse.mi.dx = 0;
    mouse.mi.dy = 0;
    mouse.mi.mouseData = 0;
    mouse.mi.time = 0;

    do
    {
        int count{};
        while (count < 40)
        {
            src = hwnd2mat(hwndDesktop);
            for (size_t i{}; i < MAX_MYKEY; ++i)
            {
                HDC dc = GetWindowDC(NULL);
                color[i] = GetPixel(dc, arrow_x[i], findY);
                if (color[i] != cnst::arrow::grey &&
                    color[i] != 0)
                {
                    pressKey(inputKey[i]); ++count; break;
                }
            }
        }
        Sleep(7000);
        pressKey(move_left, false);
        pressKey(move_right, false);
        rclick(mouse);
        Sleep(9000);
    }
    while (GetAsyncKeyState(VK_ESCAPE) == 0);
}