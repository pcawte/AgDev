/*
 * Title:			exit example
 * Author:			Paul Cawte
 * Created:			24/07/2023
 * Last Updated:	24/07/2023 
 *
 * Modinfo:
 */
 
#include <stdlib.h>

void f1( void );

int main( void )
{
	f1();
	return 0;
} 

void f1( void ) {
	exit( EXIT_ABORT );
}