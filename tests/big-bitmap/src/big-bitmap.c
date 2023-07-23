// VDU commands

#include <stdio.h>
#include <mos_api.h>
#include <stdbool.h>
#include <stdlib.h>

#include "vdp_vdu.h"

int main( void )
{
	volatile SYSVAR *sv = vdp_vdu_init();

	int img_width;
	int img_height;
	char fname[41];
	int load_rows;

	printf( "Enter file name: " );
	scanf( "%40s", fname );
	printf( "Enter width and height: " );
	scanf( "%d %d", &img_width, &img_height );
	printf( "For %s (%d, %d) enter number of rows to load: ", fname, img_width, img_height );
	scanf( "%d", &load_rows );

	vdp_select_bitmap( 1 );
	printf( "Loading bitmap (%d,%d) to VDP\n", img_width, load_rows );
	if ( vdp_load_bitmap_file( fname, img_width, load_rows ) ) {
		printf( "Error loading bitmap. Quitting.\n" );
		return 1;
	}
	vdp_mode( 3 );
	vdp_logical_scr_dims( false );

	mos_puts( "Large bitmap test program\r\n", 0, 0 );
	mos_puts( "=========================\r\n", 0, 0 );

	vdp_draw_bitmap( 0, 480-427 );

//	printf( "Press any key to continue...\n" );
//	getchar();	
}
