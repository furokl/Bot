#include "Detector.h"
#include "Keyboard.h"

int WinMain(_In_ HINSTANCE hInstance,
            _In_opt_ HINSTANCE hPrevInstance,
            _In_ LPSTR lpCmdLine,
            _In_ int nShowCmd)
{
    Keyboard keyboard;
    Detector openCV;
    std::array<std::thread, Keyboard::MAX_ARROWKEY> th_arrows;
    std::array<COLORREF, Keyboard::MAX_ARROWKEY> pixel_arrows;
    std::array<int, Keyboard::MAX_ARROWKEY> arrow_x;
    std::array<HDC, Keyboard::MAX_ARROWKEY> hdc_arrows { 
        GetWindowDC(NULL), 
        GetWindowDC(NULL), 
        GetWindowDC(NULL), 
        GetWindowDC(NULL) 
    };

    // Close programm on 'ESC' key
    std::thread close_programm([&openCV]() {
        do
        {
            ;
        }
        while (GetAsyncKeyState(VK_ESCAPE) == 0);
        exit(EXIT_SUCCESS);
    });
    close_programm.detach();

    // -----------------------------------------
    // Dlya Pigmeya
    // 
    // openCV.find_x = 959;
    // openCV.find_y = 264;
    // Sleep(9000);
    // // while(!openCV.detectFromFullscreen());
    // 
    // -----------------------------------------

    // Detect grey arrows
    while(!openCV.detectFromFullscreen());
    arrow_x = {
        openCV.getX() + cnst::left_dx,
        openCV.getX() + cnst::up_dx,
        openCV.getX() + cnst::right_dx,
        openCV.getX() + cnst::down_dx
    };
 
    // Bot work
    while (true) 
    {
        int slot{};
        for (int fishing{}; fishing < cnst::fishing::durability; ++fishing)
        {
            SetCursorPos(openCV.getX(), openCV.getY());
            if (fishing != 0) Sleep(9000);
            std::atomic<int> count{};

            // Run thread refresh screen
            std::thread thScr([&openCV, &count]() {
                while (count.load() < cnst::fishing::max_arrow) {
                    openCV.screen.getScreen();
                }});
            thScr.detach();

            // Run threads check pixels on grey arrows
            for (int i{}; i < Keyboard::MAX_ARROWKEY; ++i) 
            {
                th_arrows[i] = std::thread([i, &keyboard, &hdc_arrows, &pixel_arrows, &arrow_x, &openCV, &count]() {
                    while (count.load() < cnst::fishing::max_arrow) {
                        pixel_arrows[i] = GetPixel(hdc_arrows[i], arrow_x[i], openCV.getY());
                        if (pixel_arrows[i] != cnst::arrow::grey &&
                            pixel_arrows[i] != 0)
                        {
                            keyboard.ar(i); ++count;
                        }
                    }
                });
            }
            // End threads
            for (auto &th : th_arrows) th.join();

            Sleep(7000);
            keyboard.rclick();
        }

        // Moving when fishing rod is broken
        Sleep(2000);
        keyboard
            .rclick()
            .move_left()
            .jump()
            .move_right()
            .jump()
            .move_right()
            .move_left()
            .jump();

        // Change slot
        if (slot >= keyboard.MAX_SLOTS) break;
        ++slot;
        keyboard.change_slot(slot);
    }
}