/*
 * Title:			Example of stdout redirection using freopen() 
 * Author:			Paul Cawte
 * Created:			09/07/2023
 * Last Updated:	09/07/2023
 *
 * Modinfo:
 */
 
#include <stdio.h>

int main(void)
{
	printf( "To console> 'Hello World!'\r\n");
    freopen( "Out.txt", "w", stdout );
    printf( "To file> 'Hello, world!'\r\n" );
    fclose( stdout );

	return 0;
}