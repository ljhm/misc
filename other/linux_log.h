//linux_log.h

#ifndef LINUX_LOG_H
#define LINUX_LOG_H

#include <syslog.h>

/*
1.
  openlog(argv[0], 0, LOG_USER);
2.
//formatting string as a literal rather than a variable
//syslog(LOG_INFO, str); //Wrong
//syslog(LOG_INFO, num); //Wrong
  syslog(LOG_INFO, "hello");
  syslog(LOG_INFO, "%s", "hello");
  syslog(LOG_INFO, "number: %f", 3.14);
  syslog(LOG_ERR, "err level test");
3.
  closelog();
*/

/*
$ tail -f /var/log/messages
$ tail -f /var/log/syslog

Dec  2 19:57:28 ubuntu ./a.out: main.c:7:main: hello
Dec  2 19:57:28 ubuntu ./a.out: main.c:8:main: hello
Dec  2 19:57:28 ubuntu ./a.out: main.c:9:main: number: 3.140000
Dec  2 19:57:28 ubuntu ./a.out: main.c:10:main: err level test
*/


#define syslog(priority, fmt, ...) \
do { \
	syslog(priority, "%s:%d (%s): " fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
} while (0) /* no trailing semicolon ; */

#endif
