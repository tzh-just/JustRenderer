#pragma once

#include <vector>

namespace Just {
//Ref: Nori
//离散概率密度函数 前缀和
class DiscretePdf {
private:
    //前缀和 累积分布函数
    std::vector<float> cdf;
public:
    //三角形面积之和
    float sum;
    //归一化系数
    float normalization;
    bool isNormalized;

    explicit DiscretePdf(size_t size) {
        //初始化扩展数组，并填入0
        Reverse(size);
        Clear();
    }

    //获取概率密度，累积分布函数的前缀和数组的第i元素前后之差
    float operator[](size_t i) const {
        return cdf[i + 1] - cdf[i];
    }

    void Clear() {
        cdf.clear();
        cdf.push_back(0);
        isNormalized = false;
    }

    //累积分布函数，在前面所有元素之和之上再加上当前元素
    void Append(float value) {
        cdf.push_back(cdf.back() + value);
    }

    void Reverse(size_t size) {
        cdf.reserve(size + 1);
    }

    //实际元素个数应为前缀和数组的元素个数减一
    size_t Size() const {
        return cdf.size() - 1;
    }

    float Normalize() {
        sum = cdf.back();
        if (sum > 0) {
            //pdf为面积的倒数
            normalization = 1.0f / sum;
            //将累积分布函数归一化到[0,1]
            for (size_t i = 1; i < cdf.size(); ++i) {
                cdf[i] *= normalization;
            }
            //确保累积分布部函数最后值为 1
            cdf.back() = 1.0f;
            isNormalized = true;
        } else {
            sum = 0.0f;
        }
        return sum;
    }

    //由均匀分布的随机数获取在累积分布函数中采样三角形的索引
    size_t Sample(float sample) const {
        //在累积分布函数中查找第一个大于sample的元素
        auto it = std::lower_bound(cdf.begin(), cdf.end(), sample);
        //pdf索引比累积分布函数索引小一
        size_t index = std::max(ptrdiff_t(0), it - cdf.begin() - 1);
        //pdf索引注意
        return std::min(index, Size() - 1);
    }
};
}
