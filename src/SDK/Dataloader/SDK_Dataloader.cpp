/*
 * @Author: George Zhao
 * @Date: 2020-03-18 11:37:51
 * @LastEditors: George Zhao
 * @LastEditTime: 2020-03-20 17:25:57
 * @Description: 
 * @Email: 2018221138@email.szu.edu.cn
 * @Company: SZU
 * @Version: 1.0
 */
#include "../Dataloader/SDK_Dataloader.hpp"
#include "../Core/SDK_Core.hpp"
#include <fstream>
#include <iostream>
#include <regex>
namespace SDK_Dataloader {

fdata::operator std::string()
{
    return this->name + ", " + SDK_Core::ltos(this->startpoint) + ", " + SDK_Core::ltos(this->endpoint) + ", " + std::string(" (") + std::string(this->color) + std::string(") ");
}

pdata::operator std::string()
{
    return this->name + ", " + SDK_Core::dtos(this->startpoint) + ", " + SDK_Core::dtos(this->endpoint) + ", " + std::string(" (") + std::string(this->color) + std::string(") ");
}

std::vector<fdata> readdata(const std::string& pathway)
{
    std::fstream database;
    database.open(pathway);
    if (database.is_open() == false)
        std::cout << "\033[1;32m" << pathway << " Not Open. \033[0m" << std::endl;
    std::vector<fdata> data;
    while (database.eof() != true) {
        std::string line;
        std::getline(database, line);
        if (line.empty())
            continue;
        data.push_back(Reline(line));
    }
    return data;
}

std::vector<pdata> normalize_data(const std::vector<fdata>& thefdata)
{
    unsigned long long max_p = thefdata[0].startpoint;
    unsigned long long min_p = thefdata[0].startpoint;
    for (const auto& element : thefdata) {
        if (element.startpoint > element.endpoint) {
            if (element.startpoint > max_p)
                max_p = element.startpoint;
            if (element.endpoint < min_p)
                min_p = element.endpoint;
        } else {
            if (element.endpoint > max_p)
                max_p = element.endpoint;
            if (element.startpoint < min_p)
                min_p = element.startpoint;
        }
    }
    double legth = max_p - min_p;
    std::vector<pdata> thepdata;
    for (auto& element : thefdata) {
        thepdata.push_back(pdata(element.name, (double)(element.startpoint - min_p) / legth, (double)(element.endpoint - min_p) / legth, element.color));
    }
    return thepdata;
}

// ^([A-Za-z0-9]+)\s+([A-Za-z]*)\(*\s*(\d+)..(\d+)\s*\)*\s+(\w*)$
const SDK_Core::RGB& defaultArrowcolor = SDK_Core::NormalColor::GREEN;
const std::regex regex("([A-Za-z0-9]+)\\s+([A-Za-z]*)\\(*\\s*(\\d+)..(\\d+)\\s*\\)*\\s+([#A-Za-z0-9]*)\\r*");
SDK_Core::RGB changeCharToRGB(const char* text)
{
    if (text[0] != '#')
        throw std::invalid_argument(text);
    // return RGB({ 0, 0, 0 });
    SDK_Core::RGB rgb = SDK_Core::RGB({ 0, 0, 0 });
    double* ptr_rgb = &rgb.R;
    for (int i = 1; i <= 6; i++) {
        double c = 16;
        if (i % 2 == 0)
            c = 1;
        if (text[i] >= 65 && text[i] <= 70) {
            // ABCDEF
            *ptr_rgb += (text[i] - 55) * c;
        } else if (text[i] >= 97 && text[i] <= 102) {
            // abcdef
            *ptr_rgb += (text[i] - 87) * c;
        } else if (text[i] >= 48 && text[i] <= 57) {
            // 123456789
            *ptr_rgb += (text[i] - 48) * c;
        } else
            throw std::invalid_argument(std::string(text));
        // return RGB({ 0, 0, 0 });
        if (i % 2 == 0)
            ptr_rgb++;
    }
    return rgb;
}
fdata Reline(const std::string& text)
{
    std::smatch pieces_match;
    std::regex_match(text, pieces_match, regex);
    fdata data;
    int i = 1;
    data.name = pieces_match[i].str();
    i += 2;
    data.startpoint = stoll(pieces_match[i].str());
    i++;
    data.endpoint = stoll(pieces_match[i].str());
    i++;
    auto color = pieces_match[i].str();
    if (color.empty() == true)
        // Default Color
        data.color = defaultArrowcolor;
    else if (color[0] == '#') {
        // HEX Code
        data.color = changeCharToRGB(color.c_str());
        data.color.R /= 255.0;
        data.color.G /= 255.0;
        data.color.B /= 255.0;
    } else {
        // Str code.
        if (color == std::string("red"))
            data.color = SDK_Core::NormalColor::RED;
        else if (color == std::string("blue"))
            data.color = SDK_Core::NormalColor::BLUE;
        else if (color == std::string("green"))
            data.color = SDK_Core::NormalColor::GREEN;
        else if (color == std::string("black"))
            data.color = SDK_Core::NormalColor::BLACK;
        else if (color == std::string("white"))
            data.color = SDK_Core::NormalColor::WHITE;
        else if (color == std::string("purple"))
            data.color = SDK_Core::NormalColor::PURPLE;
        else if (color == std::string("brown"))
            data.color = SDK_Core::NormalColor::BROWN;
        else if (color == std::string("skyblue"))
            data.color = SDK_Core::NormalColor::SKYBLUE;
        else if (color == std::string("pink"))
            data.color = SDK_Core::NormalColor::PINK;
        else
            data.color = defaultArrowcolor;
    }
    if (pieces_match[2].str().empty() == false)
        std::swap(data.startpoint, data.endpoint);
    return data;
}
}