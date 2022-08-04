//================================================
// 计时器
//================================================

#pragma once

#include <chrono>
#include <iostream>

namespace Just
{

    struct Timer
    {
        using namespace std::chrono;

        time_point<steady_clock> start;
        time_point<steady_clock> end;
        float time;

        Timer() : time(0) {}

        void Begin()
        {
            start = high_resolution_clock::now();
        }

        void End()
        {
            end = high_resolution_clock::now();
            duration<float> duration = end - start;
            time = duration.count() * 1000.0f;
        }
    };

}
