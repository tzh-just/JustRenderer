
//================================================

#pragma once

#include "Global.h"
#include "Vector3.h"
#include "Homogeneous.h"

namespace Just {
    template<typename T>
    struct Matrix2 {
        T data[2][2];

        constexpr Matrix2() {
            for (int row = 0; row < 2; row++) {
                for (int col = 0; col < 2; col++) {
                    data[row][col] = (row == col) ? 1 : 0;
                }
            }
        }

        constexpr float Det() {
            return data[0][0] * data[1][1] - data[0][1] * data[1][0];
        }
    };
}