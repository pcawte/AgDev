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
#include <stdint.h>

const int N = 17;

extern HEADER _alloc_base;

int main(void)
{
	printf( "Malloc test\n\n" );
    printf( "_alloc_base.ptr %p, _alloc_base.size %d\n\n", _alloc_base.s.ptr, _alloc_base.s.size );

    int size = 1;
    void *ptr[N];

    for (int i = 0; i < N; i++ ){
        ptr[i] = malloc( size );
        printf("Block %i, size %i, address %p\n", i, size, ptr[i] );
        size *= 2;
    }

	return 0;
}