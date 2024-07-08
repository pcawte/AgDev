/* time_t time(time_t *t)
   ----------------------

Description
time() returns the current time as the number of seconds since the Epoch, 1970-01-01 00:00:00 +0000 (UTC).
If t is non-NULL, the return value is also stored in the memory pointed to by t.

Return Value
On success, the value of time in seconds since the Epoch is returned. On error, ((time_t) -1) is
returned, and errno is set appropriately.
*/

#include <time.h>
#include <stdint.h>
#include <mos_api.h>

time_t time(time_t *timer)
{
    volatile RTC_DATA *rtc = getsysvar_rtc();

    static char rtc_buffer[33];
    mos_getrtc( rtc_buffer );         // Seems that need to call mos_getrtc() to update sysvar_rtc

    struct tm tm2;
    time_t res;

    tm2.tm_sec = rtc->second;
    tm2.tm_min = rtc->minute;
    tm2.tm_hour = rtc->hour;
    tm2.tm_mday = rtc->day;
    tm2.tm_mon = rtc->month;
    tm2.tm_year = (unsigned int)rtc->year + 1980 - 1900;

    res = mktime(&tm2);

    if (timer != NULL)
    {
        *timer = res;
    }

    return res;
}
