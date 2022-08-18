#pragma once

#include "Global.h"
#include "Vector2.h"

namespace Just {
    template<typename T>
    struct Matrix2 {
        T data[2][2];

        Matrix2() {
            for (size_t row = 0; row < 2; row++) {
                for (size_t col = 0; col < 2; col++) {
                    data[row][col] = (row == col) ? 1 : 0;
                }
            }
        }

        T* operator[](size_t row) {
            assert(row <= 1 && row >= 0);
            return data[row];
        }

        const T* operator[](size_t row) const {
            assert(row < 2);
            return data[row];
        }

        Vector2<T> Row(size_t row) const {
            assert(row < 2);
            Vector2<T> temp;
            for (size_t col = 0; col < 2; col++) {
                temp[col] = data[row][col];
            }
            return temp;
        }

        T Det() {
            return data[0][0] * data[1][1] - data[0][1] * data[1][0];
        }
    };

    //输出
    template<typename T>
    inline std::ostream& operator<<(std::ostream& os, const Matrix2<T>& mat) {
        for (size_t row = 0; row < 2; row++) {
            os << mat.Row(row) << "\n";
        }
        return os;
    }
}