// VDU commands

#include <stdio.h>
#include <mos_api.h>
#include <stdbool.h>
#include <stdlib.h>
#include <agon/vdp_vdu.h>

int main( void )
{
	volatile SYSVAR *sv = vdp_vdu_init();

	int img_width;
	int img_height;
	char fname[41];
	int screen_mode;

	printf( "Enter file name for RGBA bitmap: " );
	scanf( "%40s", fname );
	printf( "Enter width and height: " );
	scanf( "%d %d", &img_width, &img_height );
	printf( "Enter screen mode to use: " );
	scanf( "%d", &screen_mode );

	vdp_select_bitmap( 1 );
	printf( "Sending bitmap to VDP...\n");
	if ( vdp_load_bitmap_file( fname, img_width, img_height ) ) {
		printf( "Error loading bitmap. Quitting.\n" );
		return 1;
	}
	vdp_mode( screen_mode );
	vdp_logical_scr_dims( false );
	vdp_clear_screen();
	vdp_draw_bitmap( (sv->scrWidth)/2-(img_width/2), (sv->scrHeight)/2-(img_height)/2 );
}
