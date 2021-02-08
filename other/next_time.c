#include <stdio.h>
#include <time.h>

#define SECOND(n) (1 * (n))
#define MINUTE(n) (60 * SECOND(n))
#define HOUR(n)   (60 * MINUTE(n))
#define DAY(n)    (24 * HOUR(n))
#define WEEK(n)   (7 * DAY(n))

/*
no MONTH, YEAR defined
use DAY(n) instead
DAY(28), DAY(29), DAY(30), DAY(31), 
DAY(360), DAY(365), DAY(366)
*/

int main(int argc, char *argv[])
{
    time_t now = time(NULL);
    time_t next_day = now + DAY(1);
    time_t next_2days = now + DAY(2);
    time_t next_hour = now + HOUR(1);
    time_t next_minute = now + MINUTE(1);
    time_t next_week = now + WEEK(1);
    time_t next_3seconds = now + SECOND(3);

    printf("now           : %s", ctime(&now));
    printf("next day      : %s", ctime(&next_day));
    printf("next 2 days   : %s", ctime(&next_2days));
    printf("next hour     : %s", ctime(&next_hour));
    printf("next minute   : %s", ctime(&next_minute));
    printf("next week     : %s", ctime(&next_week));
    printf("next 3 seconds: %s", ctime(&next_3seconds));
}

/*
now           : Sat Aug 11 02:35:02 2018
next day      : Sun Aug 12 02:35:02 2018
next 2 days   : Mon Aug 13 02:35:02 2018
next hour     : Sat Aug 11 03:35:02 2018
next minute   : Sat Aug 11 02:36:02 2018
next week     : Sat Aug 18 02:35:02 2018
next 3 seconds: Sat Aug 11 02:35:05 2018
*/
