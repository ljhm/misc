#ifndef trunc_pad_trail_h
#define trunc_pad_trail_h

#include <string>
#include <sstream>
#include <iomanip>

//truncate or pad at trailing of string
//   "123456"
//4: "1234"
//8: "12345600"
std::string trunc_pad_trail(std::string str, int width, char pad) {
    std::stringstream stream;

    stream << str;
    stream >> std::setw(width) >> str;
    stream.clear();
    stream.str(std::string());
    stream << std::left << std::setw(width) << std::setfill(pad) << str;

    return stream.str();
}

/*
    cout << trunc_pad_trail("123456", 4, '0') << endl;
    cout << trunc_pad_trail("123456", 8, '0') << endl;
*/

#endif
