#include "Keyboard.h"

// -----------------------------------------
// private method for filling any key
// -----------------------------------------
//INPUT &Keyboard::fillingInputKey(const int& macros) {
//    INPUT in;
//    in.type = INPUT_KEYBOARD;
//    in.ki.wVk = macros;
//    in.ki.wScan = MapVirtualKey(macros, MAPVK_VK_TO_VSC);
//    in.ki.dwFlags = 0;
//    in.ki.dwExtraInfo = 0;
//    in.ki.time = 0;
//    return in;
//}

// -----------------------------------------
// private method press any key
// -----------------------------------------
void Keyboard::pressKey(INPUT &in, bool &&isArrow, int &&delay) {
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
        Sleep(delay);
        in.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
        SendInput(1, &in, sizeof INPUT);
        Sleep(100);
    }
}

// Left Click Mouse
Keyboard& Keyboard::lclick() {
    in_mouse.mi.dwFlags = MOUSEEVENTF_MOVE;
    SendInput(1, &in_mouse, sizeof INPUT);
    Sleep(50);
    in_mouse.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &in_mouse, sizeof INPUT);
    Sleep(50);
    in_mouse.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &in_mouse, sizeof INPUT);
    return *this;
}

// Right Click Mouse 
Keyboard& Keyboard::rclick() {
    in_mouse.mi.dwFlags = MOUSEEVENTF_MOVE;
    SendInput(1, &in_mouse, sizeof INPUT);
    Sleep(50);
    in_mouse.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    SendInput(1, &in_mouse, sizeof INPUT);
    Sleep(50);
    in_mouse.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    SendInput(1, &in_mouse, sizeof INPUT);
    return *this;
}

// SPACEBAR
Keyboard& Keyboard::jump(bool &&isArrow, int &&delay) {
    pressKey(in_space, std::move(isArrow), std::move(delay));
    return *this;
}

// ← ↑ → ↓ MAX_ARROWKEY : public ArrowKey
Keyboard& Keyboard::ar(const int &arrow) {
    pressKey(in_arrows[arrow]);
    return *this;
}
Keyboard &Keyboard::ar(const int &&arrow) {
    return ar(arrow);
}

// ←
Keyboard& Keyboard::ar_left() {
    pressKey(in_arrows[LEFT]);
    return *this;
}

// ↑
Keyboard& Keyboard::ar_up() {
    pressKey(in_arrows[UP]);
    return *this;
}

// →
Keyboard& Keyboard::ar_right() {
    pressKey(in_arrows[RIGHT]);
    return *this;
}

// ↓
Keyboard& Keyboard::ar_down() {
    pressKey(in_arrows[DOWN]);
    return *this;
}

// num ←
Keyboard& Keyboard::num_left(bool &&isArrow) {
    pressKey(in_arrows[LEFT], std::move(isArrow));
    return *this;
}

// num ↑
Keyboard& Keyboard::num_up(bool &&isArrow) {
    pressKey(in_arrows[UP], std::move(isArrow));
    return *this;
}

// num →
Keyboard& Keyboard::num_right(bool &&isArrow) {
    pressKey(in_arrows[RIGHT], std::move(isArrow));
    return *this;
}

// num ↓
Keyboard& Keyboard::num_down(bool &&isArrow) {
    pressKey(in_arrows[DOWN], std::move(isArrow));
    return *this;
}

// A
Keyboard& Keyboard::move_left(bool &&isArrow, int &&delay) {
    pressKey(in_left, std::move(isArrow), std::move(delay));
    return *this;
}

// D
Keyboard& Keyboard::move_right(bool &&isArrow, int &&delay) {
    pressKey(in_right, std::move(isArrow), std::move(delay));
    return *this;
}

// 1 2 3 MAX_SLOTS : public Slots) 
Keyboard& Keyboard::change_slot(int &slot, bool &&isArrow) {
    pressKey(in_slots[slot], std::move(isArrow));
    return *this;
}