// scanf and sccanf test programme

#include <stdio.h>
#include <stdbool.h>

void get_integer( const char *format, const char *message );
char *format_str( char * str );

int main( void )
{
	int i, cnt;
	const int max_len = 81;
	char str[max_len];

	const int str_len = 10;
	char char_str[str_len+1];

	printf( "scanf/sscanf/fscanf test program\n"
		    "================================\n\n" );

	// Strings

	printf( "Simple Strings - using scanf( s )\n" );

	printf( "Enter a string: " );
	scanf( "%80s", str );
	printf( "\nYou entered: %s\n", format_str( str ) );

	// Characters

	printf( "\nCharacters using - scanf( c )\n" );

	printf( "Enter a string of %d characters: ", str_len );
	while ( (cnt = scanf( "%10c", char_str )) != str_len ) {
		printf( "\nError reading characters, processed %d fields", cnt );
		char_str[cnt] = '\0';
		printf( "Received characters: '%s' - try again: ", format_str(char_str) );
	}
	char_str[str_len] = '\0';
	printf( "\nReceived characters: '%s'\n", format_str(char_str) );

	// Integers

	printf( "\nIntegers using - scanf()\n" );

	get_integer( "%d", "Enter a decimal integer: " );
	get_integer( "%o", "Enter an octal integer: ");
	get_integer( "%4x", "Enter a hex integer, max 4 digits: " );

	// Floating point

	printf( "\nFloating point using - scanf()\n" );

	float num = 0.0, total = 0.0;
	do {
		printf( "Enter a floating point number, zero to quit: ");
		while ( (cnt = scanf( "%f", &num )) != 1 ) {
			printf( "\nError reading number, processed %d fields", cnt );
			printf( "Received number: %f - try again: ", num );
			num = 0.0;
		}
		total += num;
		printf( "\nTotal = %f\n", total );
	}
	while ( num != 0.0 );

	// sscanf

	printf( "Strings - using gets_s() sscanf()\n" );

	int day = 0, month = 0, year = 0;
	printf( "Enter a date (dd/mm/yyyy): " );

	do
	{
		if ( !gets_s( str, max_len ) ) {
			printf( "Error getting line - Quiting program.\n" );
			return 0;
		}
		if ( (cnt = sscanf( str, "%2u%*[ /-:]%2u%*[ /-:]%4u", &day, &month, &year)) == 3 ) break;

		printf( "\nError reading data, processed %d fields.\n", cnt );
		printf( "Received data: (%02d/%02d/%04d) - try again: ", day, month, year );
		day = 0, month = 0, year = 0;
	}
	while ( true ); 

	printf( "\nThe date is: (%02d/%02d/%04d)\n", day, month, year );

	// fscanf

	printf( "Numbers - using fscanf()\n" );

	FILE *fp;
	do {
		printf( "Enter file name of file containing integers: " );
		scanf( "%80s", str );
		printf( "\n" );
		if ( !(fp = fopen( str, "r" )) )
			printf( "Error open file %s - please retry.\n", str );
	} while ( !fp );

	for ( cnt = 0; cnt < 10; cnt++ ) {
		if ( fscanf( fp, "%d", &i ) != 1 ) break;
		printf( "Number: %d\n", i);
	}
	fclose( fp );

	return 0;
}

char *format_str( char * str )
{
	if (str) for ( char *s = str; *s; s++ )				// Replace controls characters with '.'
		if ( *s < 32 || *s >= 127) *s = '.';
	return str;
}

void get_integer( const char *format, const char *message )
{
	int i, cnt;

	printf( "%s", message );
	while ( (cnt = scanf( format, &i )) != 1 ) {
		printf( "\nError reading number, processed %d fields\n", cnt );
		printf( "Received number: %d - try again: ", i );
	}

	printf( "\nDecimal %d, octal %o, hex %x\n", i, i, i );
}