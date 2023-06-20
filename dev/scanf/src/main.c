#include "stdio.h"

int main( void )
{
	int cnt;

	printf( "Scanf test program\r\n==================\r\n\r\n" );

	int day = 0, month = 0, year = 0;
	printf( "Enter a date (dd/mm/yyyy): " );

	while ( (cnt = scanf( "%2u%*[ /-:]%2u%*[ /-:]%4u", &day, &month, &year)) != 3 ) {
		printf( "\r\nError reading data, processed %d fields.\r\n", cnt );
		printf( "Received data: (%02d/%02d/%04d) - try again: ", day, month, year );
		day = 0, month = 0, year = 0;
	}
	printf( "\r\nThe date is: (%02d/%02d/%04d)\r\n", day, month, year );

	float num = 0.0, total = 0.0;

	do {
		printf( "Enter a floating point number, zero to quit: ");
		while ( (cnt = scanf( "%f", &num )) != 1 ) {
			printf( "\r\nError reading number, processed %d fields", cnt );
			printf( "Received number: %f - try again: ", num );
			num = 0.0;
		}
		total += num;
		printf( "\r\nTotal = %f\r\n", total );
	}
	while ( num != 0.0 );

	printf( "Thats all folks\r\n" );

	return 0;
}