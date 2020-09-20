/*
 * @Author: George Zhao
 * @Date: 2020-03-18 11:53:38
 * @LastEditors: George Zhao
 * @LastEditTime: 2020-03-18 15:40:24
 * @Description: 
 * @Email: 2018221138@email.szu.edu.cn
 * @Company: SZU
 * @Version: 1.0
 */
#include "SDK_Core.hpp"
#include <iostream>
#include <sstream>
namespace SDK_Core {
std::string ltos(const unsigned long long l)
{
    std::ostringstream os;
    os << l;
    std::string result;
    std::istringstream is(os.str());
    is >> result;
    return result;
}
std::string dtos(const double l)
{
    std::ostringstream os;
    os << l;
    std::string result;
    std::istringstream is(os.str());
    is >> result;
    return result;
}
RGB::operator std::string() const
{
    return dtos(this->R) + ", " + dtos(this->G) + ", " + dtos(this->B);
}
ARGB::operator std::string() const
{
    return dtos(this->A) + ", " + dtos(this->R) + ", " + dtos(this->G) + ", " + dtos(this->B);
}

}