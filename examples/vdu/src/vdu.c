// VDU commands

#include "vdp_vdu.h"
#include <stdio.h>
#include <mos_api.h>
#include <stdbool.h>
#include <stdlib.h>

int main( void )
{
	volatile SYSVAR *sv;

	sv = vdp_vdu_init();

	FILE *fp;
	uint32_t *img_buf;
	const int img_width = 180;
	const int img_height = 180;
	const char *fname = "parrot.rgba";
	int load_height;

	printf( "Opening file \"%s\"\n", fname);
	if ( !(fp = fopen( fname, "rb" ) ) ) {
		printf( "Error opening file \"%sa\". Quitting.\n", fname );
		exit( 1 );
	}
	if ( !(img_buf = (uint32_t *)malloc( img_width*img_height*sizeof(uint32_t) ) ) ) {
		printf( "Failed to allocated memory. Quitting.\n" );
		exit( 1 );
	}

	size_t cnt = fread( (void *)img_buf, sizeof(uint32_t), img_width*img_height, fp );
	if ( cnt != img_width*img_height ) {
		printf( "Loaded wrong number of pixels: %d. Quitting.\n", cnt );
		exit( 1 );
	}
	fclose( fp );

	printf( "Enter number of rows to load to VDP: " );
	scanf( "%d", &load_height );

	printf( "Loading bitmap (%d,%d) to VDP\n", img_width, load_height );

	vdp_select_bitmap( 1 );
	vdp_load_bitmap( img_width, load_height, img_buf );
	free( img_buf );

	for ( int m = 0; m < 4; m++) {
		vdp_mode( m );
		vdp_logical_scr_dims( false );
		vdp_get_scr_dims( true );

		mos_puts( "MOS VDU test program\r\n", 0, 0 );
		mos_puts( "====================\r\n", 0, 0 );

		printf( "Mode %d.\n", m );
		printf( "Screen width %d, height %d (pixels).\n", sv->scrWidth, sv->scrHeight );
		printf( "Text rows %d, columns %d.\n", sv->scrRows, sv->scrCols );
		printf( "Colours %d.\n", sv->scrColours );

		int blocks = sv->scrCols / 10;
		for ( int b = 0; b < blocks; b++ ) {
			printf( ".........%1d", b+1 );
		}
		printf( "\n" );
		for ( int b = 0; b < blocks; b++ ) {
			printf( "1234567890");
		}
		printf( "\n" );
		for ( int r = 3; r <= sv->scrRows-10; r++) printf( "%2d\n", r );

		vdp_move_to( 0, 0 );
		vdp_line_to( sv->scrWidth-1, sv->scrHeight-1 );
		vdp_move_to( sv->scrWidth-1, 0 );
		vdp_line_to( 0, sv->scrHeight-1 );
		vdp_line_to( sv->scrWidth-1, sv->scrHeight-1 );
		vdp_triangle( sv->scrWidth / 2, sv->scrHeight / 2);

		const int x1 = 10, y1 = 10;
		const int x2 = 190, y2 = 190;

		vdp_move_to( x1, y1 );
		vdp_line_to( x2, y1 );
		vdp_line_to( x2, y2 );
		vdp_line_to( x1, y2 );
		vdp_line_to( x1, y1 );

		vdp_circle( x2, y2 );

		vdp_line_to( x1, y1 );
		vdp_circle_radius( 180, 0 );

		vdp_draw_bitmap( 100, 100 );

		printf( "Press any key to continue...\n" );
		getchar();
	}		
}

