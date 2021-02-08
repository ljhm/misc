//print_log.h

#ifndef print_log_h
#define print_log_h

#include <stdio.h>
#include <sys/time.h>
#include <time.h>

//PRINT_LOG("%s", "hello");
//a.c:6 (main): hello

#define PRINT_LOG(fmt, ...) \
do { \
	char buf[1024] = {0}; \
	snprintf(buf, sizeof(buf), "%s:%d (%s): " fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
	printf("%s\n", buf); \
} while (0)  /* no trailing semicolon ; */


// PRINT_LOG2("%s", "hello");
// [20181127 10:08:38.818831] a.cpp:25 (main): hello

#define PRINT_LOG2(fmt, ...) \
do { \
	char _buf[1024] = {0}; \
	char _time[32] = {0}; \
	timeval _tv; \
	struct tm _tm; \
	gettimeofday(&_tv, NULL); \
	localtime_r(&_tv.tv_sec, &_tm); \
	snprintf(_time, sizeof(_time), "%04d%02d%02d %02d:%02d:%02d.%06ld", _tm.tm_year + 1900, _tm.tm_mon + 1, _tm.tm_mday, _tm.tm_hour, _tm.tm_min, _tm.tm_sec, _tv.tv_usec); \
	snprintf(_buf, sizeof(_buf), "[%s] %s:%d (%s): " fmt, _time, __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
	printf("%s\n", _buf); \
	fflush(stdout); \
} while (0) // ; no trailing semicolon


//main.cpp:23 (main): hello, 123
//main.cpp:24 (main): hello, 123

#include <iostream>

#define COUT \
    std::cout << __FILE__ << ":" << __LINE__ << " (" << __func__ << "): " 


#endif
