/*
 * @Author: George Zhao
 * @Date: 2020-03-18 11:51:14
 * @LastEditors: George Zhao
 * @LastEditTime: 2020-03-19 16:06:15
 * @Description: 
 * @Email: 2018221138@email.szu.edu.cn
 * @Company: SZU
 * @Version: 1.0
 */
#ifndef SDK_Core_hpp
#define SDK_Core_hpp
#include <iostream>
namespace SDK_Core {

std::string ltos(const unsigned long long l);
std::string dtos(const double l);

struct SIZE2D {
    double W;
    double H;
};

struct POINT2D {
    double X;
    double Y;
};

struct RGB {
    double R;
    double G;
    double B;
    operator std::string() const;
};

struct ARGB : RGB {
    double A;
    operator std::string() const;
};

namespace NormalColor {
    static const RGB RED = RGB({ 255.0 / 255.0, 0, 0 });
    static const RGB BLUE = RGB({ 0, 0, 255 / 255.0 });
    static const RGB GREEN = RGB({ 0, 255.0 / 255.0, 0 });
    static const RGB BLACK = RGB({ 0, 0, 0 });
    static const RGB WHITE = RGB({ 255.0 / 255.0, 255.0 / 255.0, 255.0 / 255.0 });
    static const RGB PURPLE = RGB({ 159.0 / 255.0, 95.0 / 255.0, 159.0 / 255.0 });
    static const RGB BROWN = RGB({ 166.0 / 255.0, 125.0 / 255.0, 61.0 / 255.0 });
    static const RGB SKYBLUE = RGB({ 64.0 / 255.0, 141.0 / 255.0, 223.0 / 255.0 });
    static const RGB PINK = RGB({ 255.0 / 255.0, 105.0 / 255.0, 180.0 / 255.0 });
    static const RGB GRy = RGB({ 66.0 / 255.0, 66.0 / 255.0, 66.0 / 255.0 });
};

}

#endif