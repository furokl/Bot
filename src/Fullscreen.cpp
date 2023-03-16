#include "Fullscreen.h"

// -----------------------------------------
// 
// -----------------------------------------
void Fullscreen::init() {
    hwndDesktop = GetDesktopWindow();
    hwindowDC = GetDC(hwndDesktop);
    hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);

    SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);
    GetClientRect(hwndDesktop, &windowsize);

    srcheight = windowsize.bottom;
    srcwidth = windowsize.right;
    height = windowsize.bottom / 1;
    width = windowsize.right / 1;

    src.create(height, width, CV_8UC3);

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
    StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, 0, 0, srcwidth, srcheight, SRCCOPY);
    GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, src.data, (BITMAPINFO *)&bi, DIB_RGB_COLORS);

    DeleteObject(hbwindow);
    DeleteDC(hwindowCompatibleDC);
    ReleaseDC(hwndDesktop, hwindowDC);
}

// -----------------------------------------
// 
// -----------------------------------------
void Fullscreen::refresh() {
    hwindowDC = GetDC(hwndDesktop);
    hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
    SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);
    GetClientRect(hwndDesktop, &windowsize);

    src.create(height, width, CV_8UC4);
    hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);

    SelectObject(hwindowCompatibleDC, hbwindow);
    StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, 0, 0, srcwidth, srcheight, SRCCOPY);
    GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, src.data, (BITMAPINFO *)&bi, DIB_RGB_COLORS);

    DeleteObject(hbwindow);
    DeleteDC(hwindowCompatibleDC);
    ReleaseDC(hwndDesktop, hwindowDC);
}