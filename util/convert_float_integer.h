#ifndef convert_float_integer_h
#define convert_float_integer_h

#include <math.h>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "trunc_pad_trail.h"

// stod(str_money) * num //WRONT! may cause precision loss
// stod("33.3") * 100000000 //WRONG! may return 3299999999

//convert money (in string) to smaller unit from float to integer
//and keep the precision properly with multiplication of 10^n
//      "33.3"
// 10^8: 3330000000
unsigned long long convert_float_integer(std::string money, int n) {
    std::vector<std::string> vec;
    boost::trim(money);
    boost::split(vec, money, boost::is_any_of("."));

    if (vec.size() == 1) {
        std::string s0 = vec[0];
        if (s0.empty())
            s0 = "0";
        return std::stoull(s0) * (unsigned long long)std::pow(10, n);
    }

    if (vec.size() == 2) {
        std::string s0 = vec[0];
        std::string s1 = vec[1];
        if (s0.empty())
            s0 = "0";
        if (s1.empty())
            s1 = "0";
        unsigned long long u1 = std::stoull(s0) * (unsigned long long)std::pow(10, n);
        unsigned long long u2 = std::stoull(trunc_pad_trail(s1, n, '0'));
        return u1 + u2;
    }

    return 0; //invalid float input
}

/*
    string money = "3.33";
    int n = log10(100000000);
    unsigned long long value = convert_float_integer(money, n);
    cout << value << endl;
*/

#endif
