/*
 * Title:			cat - copy stdin to stdout
 * Author:			Paul Cawte
 * Created:			13/07/2022
 *
 * Modinfo:
 */
 
#include <stdio.h>
#include <string.h>

int main( void )
{
	const int max_line_len = 83;		// 80 characters + CR/LF pair + '\0'
	char line[max_line_len];

	while ( gets_s( line, max_line_len ) )
		if ( *line != '\0' ) {
			putchar( '"' );
			int l = strlen( line );
			line[l++] = '"';
			line[l] = '\0';
//			fputs( line, stderr );
			puts( line );
		}
		else break;

	return 0;
} 
