/*
 * Title:			Change stdio to translate LF to CR/LF and vice versa
 *                  add unget at same time modifying file 
 * Author:			Paul Cawte
 * Created:			17/07/2023
 * Last Updated:	17/07/2023
 *
 * Modinfo:
 */
 
#include <stdio.h>
#include <string.h>

int main(void)
{
    printf( "STDIO test - text & binary files\n================================\n" );

    FILE *fp_out, *fp_in;
    char buffer[81];

    if ( !(fp_out = fopen( "testout.txt", "w"))) {
        printf( "Error opening file\nQuitting\n" ); return 1;
    }

    for ( int i = 0; i < 10; i++ )
        fprintf( fp_out, "Line %d: Hello, world.\n", i );


    printf( "Enter a path to a file: " );
    if ( scanf( "%80s", buffer ) != 1 ) { //TODO respond to other returned status codes
        printf( "Error entering file name\nQuitting\n" ); return 1;
    }
    printf( "Opening file '%s'\n", buffer );
    if ( !(fp_in = fopen( buffer, "r"))) {
        printf( "Error opening file\nQuitting\n" ); return 1;
    }

    while( fgets( buffer, 81, fp_in )) {
        int len = strcspn( buffer, "\n" );
        buffer[len] = '\0';
//        printf( "\"%s\"\n", buffer );
        fprintf( fp_out, "\"%s\"\n", buffer );
    }

    fclose( fp_in );

    fclose( fp_out );

    return 0;
}