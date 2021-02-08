#ifndef print_log_h
#define print_log_h

#include <stdio.h>
#include <sys/time.h>
#include <time.h>

// PRINT_LOG("%s", "hello");
// [20181127 10:08:38.818831] a.cpp:25 (main) hello

#define PRINT_LOG(fmt, ...) \
do { \
	char buf[1024] = {0}; \
	char timebuf[32] = {0}; \
	struct timeval tv; \
	struct tm _tm; \
	gettimeofday(&tv, NULL); \
	localtime_r(&tv.tv_sec, &_tm); \
	snprintf(timebuf, sizeof(timebuf), "%04d%02d%02d %02d:%02d:%02d.%06ld", _tm.tm_year + 1900, _tm.tm_mon + 1, _tm.tm_mday, _tm.tm_hour, _tm.tm_min, _tm.tm_sec, tv.tv_usec); \
	snprintf(buf, sizeof(buf), "[%s] %s:%d (%s) " fmt, timebuf, __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
	printf("%s\n", buf); \
} while (0) // ; no trailing semicolon

#endif
