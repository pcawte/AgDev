/*
 * Title:			Example of stdin redirection using freopen() 
 * Author:			Paul Cawte
 * Created:			09/07/2023
 * Last Updated:	09/07/2023
 *
 * Modinfo:
 */
 
#include <stdio.h>

int main(void)
{
    const int max_line_len = 80;
    char buf[max_line_len+1];
    int c;
    int i = 0, cnt;

//  FILE *fp;

	printf( "Input redirection test program\r\n");

    for ( int l = 0; l < 1; l++) {
        printf( "> reading from stdin - enter a line: " );

        if ( !gets_s( buf, max_line_len) ) {
            printf( "\r\nError reading line, quitting.\r\n" );
            return -1;
        }
        printf( "\r\nYou entered: %s\r\n", buf );
    }
    
    printf( "\r\nReading chars from stdin - echoed twice (press Q to quit).\r\n" );
    printf( "> " );

    while ( (c = getchar()) != EOF ) {
        putchar(c);
        if ( c == 'Q' || c == 'q' ) break;
    }

    printf( "\r\n\r\nAbout to read characters with getchar() from file via stdin.\r\n" );
    if ( !freopen( "number.txt", "r", stdin ) ) {
        printf("\r\nError opening file 'number.txt', quitting.\r\n" );
        return -1;
    }

    printf( "> " );

    while ( (c = getchar()) != EOF ) {
        putchar(c);
        if ( c == 'Q' || c == 'q' ) break;
    }

// Normal fopen and fgets
/*
    if ( !(fp = fopen( "number.txt", "r" )) ) {
        printf("\r\nError opening file 'number.txt', quitting.\r\n" );
        return -1;
    }

    printf( "\r\n > reading from file via fopen\r\n" );

    if ( !fgets( buf, max_line_len, fp) ) {
        printf( "\r\nError reading line, quitting.\r\n" );
        return -1;
    }
    printf( "\r\nRead: %s\r\n", buf );
    fclose( fp );
*/
// Read from file via stdin

    if ( !freopen( "number.txt", "r", stdin ) ) {
        printf("\r\nError opening file 'number.txt', quitting.\r\n" );
        return -1;
    }

    printf( "\r\nReading with gets_s() from file via stdin\r\n" );

    for ( int l = 0; l < 2; l++ ) {
        if ( !gets_s( buf, max_line_len) ) {
            printf( "\r\nError reading line, quitting.\r\n" );
            return -1;
        }
        printf( "Line %d - read with gets_s(): %s\r\n", l, buf );
    }

    printf( "\r\nReading with scanf() from file via stdin\r\n" );
    if ( (cnt = scanf( "%d", &i )) != 1 ) {
        printf( "\r\nScanf error: read %d items, value %d quitting.\r\n", cnt, i );
        return -1;
    }
    printf( "Read with scanf(): %d\r\n", i );

    fclose( stdin );

    printf( "\r\nTerminating the program.\r\n" );
	return 0;
}