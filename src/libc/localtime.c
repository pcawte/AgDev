/* struct tm *localtime(const time_t *timep)
   -----------------------------------------

The localtime() function converts the calendar time timep to broken-down time representation,
expressed relative to the user's specified timezone. The difference from gmtime() is calculated
based on the value LOCALTIME_GMT_OFFSET defined in <time.h>

It may return NULL when the year does not fit into an integer. The return value points to a
statically allocated struct which might be overwritten by subsequent calls to any of the date
and time functions.

*/

#include <time.h>
#include <stdint.h>
#include <stdbool.h>

#define SECS_PER_MIN 60UL

struct tm *localtime(const time_t *timer)
{
    time_t timer2 = *timer;
    timer2 -= LOCALTIME_GMT_OFFSET * SECS_PER_MIN;

    return gmtime(&timer2);
}
