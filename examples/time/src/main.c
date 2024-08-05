#include <stdio.h>
#include <time.h>
#include <math.h>
#include <mos_api.h>

void print_MOS_time( void );

int main( void )
{
	clock_t ticks1, ticks2;
	time_t t, time1, time2;
	const int loops = 10000;

	printf( "Testing clock() function\r\n\r\n" );

	t = time(NULL);
	printf( "The current time is: %s\r\n", ctime( &t ) );

	float tot = 0.0;
	printf( "Doing some calculations....\r\n");

	print_MOS_time();
	time1 = time( NULL );
	ticks1 = clock();

	for ( int i = 0; i < loops; i++ )
	{
		float ang, s, c;

		ang = (float)i * 2.0 * M_PI / loops;
		s = sin( ang );
		c = cos( ang );
		tot += s*s + c*c;
		if ( i % 100 == 1 ) putchar( '.' );
	}
	ticks2 = clock();
    time2 = time( NULL );
	print_MOS_time();
	printf( "\r\nAverage = %.4f\r\n", tot/loops );

	int ticks = (ticks2-ticks1) / CLOCKS_PER_SEC;
	int ticks_rem = (ticks2-ticks1) % CLOCKS_PER_SEC;
	printf( "\r\nTime from ticks to complete %d loops: %d.%02d seconds\r\n", loops, ticks, ticks_rem );

	printf( "Time from RTC to complete %d loops: %.0f seconds\r\n", loops, difftime( time2, time1 ) );

	t = time(NULL);
	printf( "The program finished at: %s\r\n", ctime( &t ) );
	return 0;
}

void print_MOS_time( void ) {
	static char rtc_buffer[33];
	volatile RTC_DATA *rtc = getsysvar_rtc();

	int len = mos_getrtc( rtc_buffer );
	rtc_buffer[len] = '\0';
	printf( "\r\nTime according to mos_getrtc() - %s\r\n", rtc_buffer );
	printf( "Time according to getsysvar_rtc() - %02d:%02d:%02d\r\n",
			rtc->hour, rtc->minute, rtc->second );
}