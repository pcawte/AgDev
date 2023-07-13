/* gets_s
   ------

Paul Cawte 13/06/2023

Reads characters from console until a newline is found or end-of-file occurs.
On Agon assumes CR is end of line and there is no end of file character
Writes only at most n-1 characters into the array pointed to by str, 
and always writes the terminating null character (unless str is a null pointer).
The CR character, if found, is discarded and does not count toward the number of characters
written to the buffer.

When reading from console keyboard, a line is ended by CR
When reading from a file, if stdin is redirected, a line is ended by CR/LF

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

char *gets_s( char *__restrict str, rsize_t n )
{
	rsize_t cnt = 0;							// counter for number of characters read
	int c;										// the current input character
	char *s = str; 								// location to store next character

	if ( !(str || n) ) return( NULL );  		// check error conditions
//	if ( n > RSIZE_MAX ) return( NULL );

	if ( stdin->fhandle != FH_STDIN ) return fgets( str, n, stdin );

	c = getchar();
	while ( c != '\r' )						// Keep collecting input until end of line
	{
		if ( cnt < n ) *s++ = c;			// Store characters if not reached end of buffer
		cnt++;
		c = getchar();
	}
	outchar('\n');							// Output LF otherwise remains on same line (not sure why)
	if ( cnt >= n ) return( NULL );			// Return error if no. of characters received > max -1
	*s = '\0';								// terminate the string

	return( str );
}
