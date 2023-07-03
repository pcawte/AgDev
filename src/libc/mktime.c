/* time_t mktime(struct tm *tm)
   ----------------------------

Description
The amktime() function takes an argument representing broken-down time which is a representation
separated into year, month, day, and so on. Broken-down time is stored in the struct tm which is
defined in <time.h>.

The mktime() function converts a broken-down time structure, expressed as local time, to calendar
time representation. The function ignores the values supplied by the caller in the tm_wday and
tm_yday fields. The value specified in the tm_isdst field informs mktime() whether or not daylight
saving time (DST) is in effect for the time supplied.


The mktime() function modifies the fields of the tm structure as follows:
    tm_wday and tm_yday are set to values determined from the contents of the other fields;
    if structure members are outside their valid interval, they will be normalized
    (so that, for example, 40 October is changed into 9 November);
    tm_isdst is set (regardless of its initial value) to a positive value or to 0, respectively,
    to indicate whether DST is or is not in effect at the specified time.
    Calling mktime() also sets the external variable tzname with information about the current timezone.
*** this implementation does not do this - none of the fields in the argument are modified ***

If the specified broken-down time cannot be represented as calendar time (seconds since the Epoch),
mktime() returns (time_t) -1 and does not alter the members of the broken-down time structure.

Return Value
On success, time in seconds since the epoch, or -1 if error.
*/

#include <time.h>
#include <stdint.h>
#include <stdbool.h>

#define SECS_PER_DAY   86400UL
#define SECS_PER_HOUR  3600UL
#define SECS_PER_MIN   60UL
#define DAYS_PER_YEAR  365UL

extern bool __isleap(int year);

time_t mktime(struct tm *tp)
{
    static const unsigned int dpmt[] =
    {
        0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
    };
    unsigned int i;
    time_t days;

    if (tp->tm_year < (1970 - 1900))
    {
        return -1L;
    }

    days = (tp->tm_year - (1970 - 1900)) * DAYS_PER_YEAR;

    for (i = 1970; i < (unsigned int)tp->tm_year + 1900; ++i)
    {
        if (__isleap(i))
        {
            days++;
        }
    }

    days += dpmt[tp->tm_mon];
    if (__isleap(tp->tm_year))
    {
        days++;
    }

    days += tp->tm_mday - 1;

    days *= SECS_PER_DAY;

    days += (tp->tm_hour * SECS_PER_HOUR) + (tp->tm_min * SECS_PER_MIN) + tp->tm_sec;

    return days;
}
