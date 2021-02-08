#ifndef cout_log_h
#define cout_log_h

#include <iostream>

//COUT_LOG << "hello" << endl;
//a.cpp:7 (main) hello

#define COUT_LOG \
    std::cout << __FILE__ << ":" << __LINE__ << " (" << __func__ << ") "

#endif
