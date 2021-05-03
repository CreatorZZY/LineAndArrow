/*
 * @Author: George Zhao
 * @Date: 2020-03-17 18:37:35
 * @LastEditors: George Zhao
 * @LastEditTime: 2021-05-03 23:03:57
 * @Description: 
 * @Email: 2018221138@email.szu.edu.cn
 * @Company: SZU
 * @Version: 1.0
 */
#ifndef SDK_hpp_
#define SDK_hpp_

#include "../Core/SDK_Core.hpp"
#include <functional>
#include <iostream>
#include <string>
namespace cr {
#include <cairo/cairo-pdf.h>
#include <cairo/cairo-svg.h>
#include <cairo/cairo.h>
}

namespace SDK_Draw {

// Gobal:
const double PageW = 1920;
const double PageH = 1080;
const double W_line = 3;
const double W = 5;
const double gap = 10;

// Arrow
const double arrow_line_gap = 20;
// Anontate
const double annotate_line_w = 5;
const double annotate_line_H = 10;
extern double annotate_font_size;
const double annotate_font_line_gap = 2;
const SDK_Core::RGB annotate_line_color = SDK_Core::RGB({ 50, 50, 50 });
const SDK_Core::RGB annotate_text_color = SDK_Core::NormalColor::GRy;

extern std::function<bool(const double, const double)> UpandDown;
void annotate(cr::cairo_surface_t* surface, const double& Present, const SDK_Core::SIZE2D& pagesize, const char* context, const double linewidth, const bool upAndDpwn);

void arrow(cr::cairo_surface_t* surface, const double& startPresent, const double& endPresent, const SDK_Core::RGB& rgb, const SDK_Core::SIZE2D& pagesize, const double& ArrowWirth);
SDK_Core::RGB changeCharToRGB(const char* text);

void make_line(cr::cairo_surface_t* surface, const SDK_Core::RGB& line_color);
}

#endif