//print_log.h

#ifndef print_log_h
#define print_log_h

#include <stdio.h>

/*
PRINT_LOG();
PRINT_LOG("hello");
PRINT_LOG("%f", 3.14);

a.c:18 (main)
a.c:19 (main) hello
a.c:20 (main) 3.140000
*/

// CFLAGS  += -Wno-gnu-zero-variadic-macro-arguments

#define PRINT_LOG(fmt, ...) \
do { \
	printf("%s:%d (%s) " fmt "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
} while (0)  /* no trailing semicolon ; */

#endif
