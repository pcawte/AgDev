/*
 * Title:			time - tests mos rtc & timer functions
 * Author:			Paul Cawte
 * Created:			02/07/2023
 *
 * Modinfo:
 */
 
#include <stdio.h>
#include <stdint.h>
#include <mos_api.h>

static char rtc_buffer[33];

int main( void )
{
	volatile RTC_DATA *rtc = getsysvar_rtc();
	RTC_DATA rtc_cur, rtc_prev;

	printf("MOS timer & RTC program\r\n\r\n");

	printf("Demonstrates:\r\n");
	printf("- mos_getrtc command: correct to nearest second\r\n");
	printf("- sysvar_time: centi-seconds updated by 2 on vsync\r\n");
	printf("- sysvar_rtc: updated every second from VDP\r\n\r\n");

	rtc_prev = *rtc;
	for ( int i = 0; i < 30; i++ ) 
	{
		int len = mos_getrtc( rtc_buffer );
		rtc_buffer[len] = '\0';
	
		uint32_t t = getsysvar_time();
		rtc_cur = *rtc;
		printf( "%s timer %ld\r\n", rtc_buffer, (long)t );
		if ( rtc_cur.rtc_data != rtc_prev.rtc_data ) {
			printf( "RTC changed: %d, %d, %d, %d, %d, %d, %d, %d\r\n",
				rtc->year+1980, rtc->month+1, rtc->day, rtc->day_of_year, rtc->day_of_week,
				rtc->hour, rtc->minute, rtc->second );
			rtc_prev = rtc_cur;
		}
		for ( int j = 0; j < 10; j++ ) waitvblank();
	}
	return 0;
}