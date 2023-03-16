#pragma once
#include <Windows.h>
#include <WinUser.h>
#include <array>
#include "Constants.h"

// -----------------------------------------
//              *KEYBOARD*
// 
//  1 2 3   
//  
//  A   D                        Up
//               SPACE       Le  Do  Ri
// 
// -----------------------------------------

// -----------------------------------------
// private method for filling any key
// -----------------------------------------
static INPUT fillingInputKey(const int& macros) {
    INPUT in;
    in.type = INPUT_KEYBOARD;
    in.ki.wVk = macros;
    in.ki.wScan = MapVirtualKey(macros, MAPVK_VK_TO_VSC);
    in.ki.dwFlags = 0;
    in.ki.dwExtraInfo = 0;
    in.ki.time = 0;
    return in;
}

class Keyboard
{
public:
    enum ArrowKey
    {
        LEFT,
        UP,
        RIGHT,
        DOWN,
        MAX_ARROWKEY
    };

    enum Slots
    {
        SLOT1,
        SLOT2,
        SLOT3,
        MAX_SLOTS
    };

private:
    std::array<INPUT, MAX_ARROWKEY> in_arrows;
    std::array<INPUT, MAX_SLOTS> in_slots;
    INPUT in_left,
          in_right,
          in_space,
          in_mouse;

public:
    Keyboard()
        : in_left(fillingInputKey       (cnst::key::A)),
          in_right(fillingInputKey      (cnst::key::D)),
          in_space(fillingInputKey      (cnst::key::space)),
          in_arrows({fillingInputKey    (VK_LEFT),
              fillingInputKey           (VK_UP),
              fillingInputKey           (VK_RIGHT),
              fillingInputKey           (VK_DOWN)}),
          in_slots({fillingInputKey     (cnst::key::k1),
              fillingInputKey           (cnst::key::k2),
              fillingInputKey           (cnst::key::k3)}),
          in_mouse({                    in_mouse.type = INPUT_MOUSE,
                                        in_mouse.mi.dx = 0,
                                        in_mouse.mi.dy = 0,
                                        in_mouse.mi.mouseData = 0,
                                        in_mouse.mi.time = 0})
    {
    }

    ~Keyboard()
    {
    }

    Keyboard(const Keyboard &) = delete;
    void operator=(const Keyboard &) = delete;

    Keyboard    &lclick(),
                &rclick(),
                &move_left(bool &&isArrow = false, int &&delay = 1000),
                &move_right(bool &&isArrow = false, int &&delay = 1000),
                &jump(bool &&isArrow = false, int &&delay = 200),
                &ar(const int &arrow),
                &ar(const int &&arrow),
                &ar_left(),
                &ar_up(),
                &ar_right(),
                &ar_down(),
                &num_left(bool &&isArrow = false),
                &num_up(bool &&isArrow = false),
                &num_right(bool &&isArrow = false),
                &num_down(bool &&isArrow = false),
                &change_slot(int &slot, bool &&isArrow = false);

private:
    void pressKey(INPUT &in, bool &&isArrow = true, int &&delay = 200);
    //INPUT &fillingInputKey(const int &macros);
};

