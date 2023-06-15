/*
 * Title:			Print address of memory allocated with Malloc
 * 
 *   Can check with .map file to validate that they are correctly within the heap 
 *
 * Author:			Paul Cawte
 * Created:			12/06/2023
 * Last Updated:	12/06/2023
 *
 * Modinfo:
 */
 
#include <stdio.h>
#include <stdlib.h>

const int N = 10;

int main(void)
{
	printf("Malloc test\n\r");

    int size = 1;
    void *ptr[N];

    for (int i = 0; i < N; i++ ){
        ptr[i] = malloc( size );
        printf("Block %i, size %i, address %p\r\n", i, size, ptr[i] );
        size *= 2;
    }

	return 0;
}