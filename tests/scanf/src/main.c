// scanf and sccanf test programme

#include <stdio.h>
#include <stdbool.h>

void get_integer( const char *format, const char *message );

int main( void )
{
	int cnt;

	printf( "S(s)canf test program\r\n=====================\r\n\r\n" );

	// Strings

	printf( "Strings - using sscanf()\r\n" );

	const int max_len = 81;
	char str[max_len];

	int day = 0, month = 0, year = 0;
	printf( "Enter a date (dd/mm/yyyy): " );

	do
	{
		if ( !gets_s( str, max_len ) ) {
			printf( "Error getting line - Quiting program.\r\n" );
			return 0;
		}
		if ( (cnt = sscanf( str, "%2u%*[ /-:]%2u%*[ /-:]%4u", &day, &month, &year)) == 3 ) break;

		printf( "\r\nError reading data, processed %d fields.\r\n", cnt );
		printf( "Received data: (%02d/%02d/%04d) - try again: ", day, month, year );
		day = 0, month = 0, year = 0;
	}
	while ( true ); 

	printf( "\r\nThe date is: (%02d/%02d/%04d)\r\n", day, month, year );

	// Integers

	printf( "\r\nIntegers using - scanf()\r\n" );

	get_integer( "%d", "Enter a decimal integer: " );
	get_integer( "%o", "Enter an octal integer: ");
	get_integer( "%4x", "Enter a hex integer, max 4 digits: " );

	// Characters

	printf( "\r\nCharacters using - scanf()\r\n" );

	const int str_len = 10;
	char char_str[str_len+1];

	printf( "Enter a string of %d characters: ", str_len );
	while ( (cnt = scanf( "%10c", char_str )) != str_len ) {
		printf( "\r\nError reading characters, processed %d fields", cnt );
		char_str[cnt] = '\0';
		printf( "Received characters: '%s' - try again: ", char_str );
	}
	char_str[str_len] = '\0';
	printf( "\r\nReceived characters: '%s'\r\n", char_str );

	// Floating point

	printf( "\r\nFloating point using - scanf()\r\n" );

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

void get_integer( const char *format, const char *message )
{
	int i, cnt;

	printf( "%s", message );
	while ( (cnt = scanf( format, &i )) != 1 ) {
		printf( "\r\nError reading number, processed %d fields\r\n", cnt );
		printf( "Received number: %d - try again: ", i );
	}

	printf( "\r\nDecimal %d, octal %o, hex %x\r\n", i, i, i );
}