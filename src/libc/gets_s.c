/* gets_s
   ------

Paul Cawte 13/06/2023

Reads characters from console until a newline is found or end-of-file occurs.
End of line is translated to LF in getchar()
Writes only at most n-1 characters into the array pointed to by str, 
and always writes the terminating null character (unless str is a null pointer).
The LF character, if found, is discarded and does not count toward the number of characters
written to the buffer.

When reading from console keyboard, a line is ended by LF (after translation)
When reading from a file, if stdin is redirected, a line is ended by LF (after translation)
 - unlike fgets, the LF is discarded

The following errors are detected at runtime:
 - n is zero
 - str is a null pointer
 - endline or eof not encountered after storing n-1 characters to the buffer.
In any case, gets_s first finishes reading and discarding the characters from stdin until new-line
character, end-of-file condition, or read error before returning.

Parameters
 - str character string to be written
 - n   maximum number of string characters (actually n-1)

Return value

str on success, a null pointer on failure.
*/

#include <stdio.h>
#include <string.h>

char *gets_s( char *__restrict str, rsize_t n )
{
	rsize_t cnt = 0;							// counter for number of characters read
	int c;										// the current input character
	char *s = str; 								// location to store next character

	if ( !(str || n) ) return( NULL );  		// check error conditions
//	if ( n > RSIZE_MAX ) return( NULL );

	if ( stdin->fhandle != FH_STDIN ) {
		if ( !fgets( str, n, stdin ) ) return NULL;
		int l = strlen( str );
		if ( str[l-1] == '\n' ) str[l-1] = '\0';
		return str;
	}

	c = getchar();
	while ( c != '\n' )						// Keep collecting input until end of line
	{
		if ( cnt < n ) *s++ = c;			// Store characters if not reached end of buffer
		cnt++;
		c = getchar();
	}
	if ( cnt >= n ) return( NULL );			// Return error if no. of characters received > max -1
	*s = '\0';								// terminate the string

	return( str );
}
