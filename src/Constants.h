#pragma once

namespace cnst
{
    const int
        right_dx = 200,
        up_dx = 70,
        left_dx = -200,
        down_dx = -70;

    namespace cv_k
    {
        const double grey_arrows = 0.97;
    } 

    namespace arrow
    {
        const int grey = 11708060;
    }

    namespace fishing
    {
        const int
            durability = 12,
            slots = 3,
            max_arrow = 40;
    }

    namespace key
    {
        const int
            A = 0x41,
            D = 0x44,
            space = 0x20,
            k1 = 0x31,
            k2 = 0x32,
            k3 = 0x33,
            k4 = 0x34,
            k5 = 0x35,
            k6 = 0x36,
            k7 = 0x37,
            k8 = 0x38;
    }
}