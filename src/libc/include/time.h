#ifndef _TIME_H
#define _TIME_H

#include <cdefs.h>

#ifndef LOCALTIME_GMT_OFFSET
#define LOCALTIME_GMT_OFFSET 0
#endif

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 100UL
#endif

/* Time Types

Data Type: clock_t
------------------
clock_t is used to measure processor and CPU time. It may be an integer or a floating-point type.
Its values are counts of clock ticks since some arbitrary event in the past. The number of clock ticks
per second is system-specific.
- On Agon it is an unsigned long & ticks are in centi-seconds. It is incremented by 2 by MOS in
  the vertical blanking interrupt

Data Type: time_t
-----------------
time_t is the simplest data type used to represent simple calendar time.

In ISO C, time_t can be either an integer or a floating-point type, and the meaning of time_t values
is not specified. The only things a strictly conforming program can do with time_t values are:
pass them to difftime to get the elapsed time between two simple calendar times (see Calculating Elapsed
Time), and pass them to the functions that convert them to broken-down time (see Broken-down Time).

On POSIX-conformant systems, time_t is an integer type and its values represent the number of seconds
elapsed since the epoch, which is 00:00:00 on January 1, 1970, Coordinated Universal Time.

The GNU C Library additionally guarantees that time_t is a signed type, and that all of its functions
operate correctly on negative time_t values, which are interpreted as times before the epoch.
- On Agon it is an unsigned long, representing the numer of seconds elapsed since the the epoch

Data Type: struct tm
--------------------
struct tm is a broken-down time is a binary representation of calendar time separated into year, month,
day, and so on. Broken-down time values are not useful for calculations, but they are useful for printing
human readable time information (see details in the struct definition below.
*/

typedef unsigned long time_t;
typedef unsigned long clock_t;

struct tm {
   int tm_sec;          // normally 0-59, can be 60 for leap-second
   int tm_min;          // 0-59
   int tm_hour;         // 0-23
   int tm_mday;         // 1-31 (note starts at 1, not 0)
   int tm_mon;          // 0-11
   int tm_year;         // Number of full calendar years since 1990
   int tm_wday;         // 0-6 (0=Sunday)
   int tm_yday;         // 0-365
   int tm_isdst;        // Daylight saving flag (+ve if in effect, 0 if not, -ve if unknown)
};

__BEGIN_DECLS

clock_t clock(void);

double difftime(time_t time1, time_t time0)
    __attribute__((__const__));

time_t mktime(struct tm *tmp);

time_t time(time_t *timer);

struct tm *localtime(const time_t *timer);

struct tm *gmtime(const time_t *timer);

char *asctime(const struct tm *tmp);

char *ctime(const time_t *timer);

__END_DECLS

#endif /* _TIME_H */
