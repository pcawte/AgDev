/* stdio - test program
* 
* Tests:
*  - puts, putchar (these output directly to console and do not use stdio)
*  - gets_s, which calls getchar (this reads directly from console, not via stdio)
*  - fopen, fclose
*  - fseek (SEEK_SET, SEEK_CUR, SEEK_END), ftell
*  - fwrite, fread
*  - remove
* To add:
* 
***********************/

#include <stdio.h>
#include <string.h>

FILE *open_file( const char *fname, const char *mode, const char *message );
int close_file( FILE *fp );
void cat_file( FILE *fp );
void read_file( FILE *fp, int num, int pos, int origin, const char *message );
int seek_file( FILE *fp, int pos, int origin, const char *message );
void putint( int i );
int remove(const char *fname); //TODO this fixes a compiler error, even though this is also in stdio.h. Why is this necessary?

const int max_line_len = 82;        // 80 characters + CR/LF pair


int main( void )
{
	char fname_str[ max_line_len+1 ];
	char *putchar_str = "====================";

	puts( "File IO test program" );
	for ( char* s = putchar_str; *s != '\0'; s++ ) putchar( *s );
	puts( "\r\n" );

	FILE *fp;
	const int num_text_lines = 5;
	char *text_line[num_text_lines];
	text_line[0] = "The quality of mercy is not strained,";
	text_line[1] = "it dropeth as the gentle rain from heaven";
	text_line[2] = "upon the place below. It is twice blessed:";
	text_line[3] = "It blesseth him that gives and him that takes.";
	text_line[4] = "it is mightiest in the mightiest...";

	puts( "\r\n\r\nEnter a filename:-" );
	putchar( '>' );

	if ( !gets_s( fname_str, max_line_len ) ) {
		puts( "Error!\r\nQuiting program.\r\n" );
		return 0;
	}

	// Write to the file

	if ( !(fp = open_file( fname_str, "w", "Opening file for writing...")) ) return 0;

	puts( "Writing text to file - \r\n" );
	for ( int l = 0; l < num_text_lines; l++ ) {
		putint( l );
		puts( " line" );
		if ( fputs( text_line[l], fp ) == EOF ) {
			puts( "\r\nError writing to file\r\nQuiting program.\r\n" );
			return 0;
		}
	}

	if ( close_file( fp ) ) return 0;

	// Read from the file

	if ( !(fp = open_file( fname_str, "r", "Opening file for reading...")) ) return 0;
	cat_file( fp );

	// Seek file and cat it

	if ( seek_file( fp, 30, SEEK_SET, "Seeking to position 30 to read file" ) ) return 0;
	cat_file( fp );
	if ( close_file( fp ) ) return 0;

	// Open for reading and appending and overwrite some of the file

	if ( !(fp = open_file( fname_str, "a+", "Opening file for read/append...")) ) return 0;
	putint( (int)ftell( fp ) );
	puts( " - opened for appending at this location" );

	if ( seek_file( fp, 30, SEEK_SET, "Seeking to position 30 to overwrite" ) ) return 0;

	int cnt = fwrite( "****", 1, 4, fp);
	if ( cnt != 4 ) {
		puts( "*** frwite() didn't write the correct number of bytes. ***" );
		putint( cnt  );
		puts( " characters." );
		return 0;
	}

	if ( seek_file( fp, 0, SEEK_SET, "Seeking to beginning to read." ) ) return 0;
	cat_file( fp );

	// Do some seeks and reads

	puts( "Doing some seeks - " );

	putint( 30 );
	putchar( '@' );
	read_file( fp, 10, 30, SEEK_SET, "Reading from @30 from start of file" );
	putint( 10 );
	putchar( '+' );
	read_file( fp, 10, 10, SEEK_CUR, "Skipping forward 10" );
	putint( -20 );
	putchar( '-' );
	read_file( fp, 10, -20, SEEK_END, "20 back from end of file" );

	if ( close_file( fp ) ) return 0;

	// Delete the file

	puts( "\r\nAbout to delete the file" );
	puts( fname_str );

	puts( "Press enter to proceed, or 'n' to continue without deleting" );
	putchar( '>' );

	char str[2];
	if ( !gets_s( str, 2 ) ) {
		puts( "Error on input!\r\nQuiting program.\r\n" );
		return 0;
	}

	if ( str[0] != 'n' && str[0] != 'N' ) {
		puts( "Deleting..." );
		int i =  remove( fname_str );
		if ( i ) {
			puts( "Error deleting the file" );
			return 0;
		}
	}

	// Terminate the program

	puts( "\r\n\r\nNormal end of program.\r\n" );

	return 0;
}

// Open file

FILE *open_file( const char *fname, const char *mode, const char *message )
{
	puts( message );

	FILE *fp ;

	if ( !(fp = fopen( fname, mode )) ) {
		puts( "*** Error opening file. ***" );
		return NULL;
	}
	return fp;
}

// Close file

int close_file( FILE *fp )
{
	puts( "Closing file..." );
	if ( fclose( fp ) ){
		puts( "*** Error closing file. ***" );
		return EOF;
	}
	return 0;
}

// Catalogue / print file to console - at most 10 lines

void cat_file( FILE *fp )
{
	char read_str[ max_line_len+1 ];
	int str_len;

	puts( "Reading text from file..." );
	for ( int l = 0; l < 10; l++ )
	{
		putint( l );
		if ( !fgets( read_str, max_line_len, fp ) ) {
			puts( " EOF" );
			break;
		}

		str_len = strlen( read_str );
		if ( str_len >= 2 && read_str[str_len-2] == '\r' && read_str[str_len-1] == '\n' )
			read_str[str_len-2]	= '\0';	
		putchar( ' ' );
		puts( read_str );
	}
	return;
}

// Read from file and output to console using fseek and fread

void read_file( FILE *fp, int num, int pos, int origin, const char *message )
{
	char buf[num+1];

	puts( message );
	if ( seek_file( fp, pos, origin, "Seeking..." ) ) return;

	int cnt = fread( buf, 1, num, fp );

	if ( cnt != num ) {
		puts( "*** frwite() didn't write the correct number of bytes. ***" );
		putint( cnt  );
		puts( " characters." );
		return;
	}
	putchar( '<' );
	for ( int i = 0; i < cnt; i++ ) putchar( buf[i] );
	putchar( '>' );
	puts( " read." );
	buf[cnt] = '\0';
//	puts( "Printing with puts()" );
//	puts( buf );
	return;
}

// Seek to a location in the file

int seek_file( FILE *fp, int pos, int origin, const char *message )
{
	puts( message );
	int err;
	if ( (err = fseek( fp, pos, origin )) ) {
		puts( "Seek failed with" );
		putint( err );
        puts( " error code" );
	}
	putint( (int)ftell( fp ) );
	puts( " @seek location." );
	return err;
}


// Outputs an int to the console - as int is 24 bits, max digits = 8

void putint( int i )
{
	const int max_digits = 8;
	char digits[max_digits];
	int cnt = 0;
	char sign = ' ';

	if ( i < 0 ) { 
		sign = '-';
		i = 0 - i;
	}

	for ( cnt = 0; cnt < max_digits; cnt++ ) {
		digits[cnt] = (char)(i % 10) + '0';
		i = i / 10;
		if ( i == 0 ) break;
	}

	putchar( sign );
	for ( ; cnt >= 0; cnt-- ) {
		putchar( digits[cnt] );
	}
}
