//win_log.h

//use DebugView.exe to read the messages

#ifndef WIN_LOG_H
#define WIN_LOG_H

#include <windows.h>
#include <stdio.h>

//example:
//	LOG("hello");
//	LOG("number: %f", 3.14);

#define LOG(fmt, ...) \
do { \
	char str[1024] = {0}; \
	snprintf(str, sizeof (str), "%s:%d (%s): " fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
	OutputDebugString(str); \
} while (0)  /* no trailing semicolon ; */

#endif
