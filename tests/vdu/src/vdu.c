// VDU commands

#include <stdio.h>
#include <mos_api.h>
#include <stdbool.h>
#include <stdlib.h>

int vdp_mode( int mode );
void vdp_get_scr_dims( bool );
void vdp_logical_scr_dims( bool );

void vdp_move_to( int x, int y );
void vdp_line_to( int x, int y );
void vdp_point( int x, int y );
void vdp_triangle( int x, int y );
void vdp_circle_radius( int x, int y );
void vdp_circle( int x, int y );

void vdp_select_bitmap( int n );
void vdp_load_bitmap( int width, int height, uint32_t *data );
void vdp_draw_bitmap( int x, int y );

static volatile SYSVAR *sv;

int main( void )
{
	sv = (SYSVAR *)mos_sysvars();

	FILE *fp;
	uint32_t *img_buf;
	const int img_width = 180;
	const int img_height = 180;
	const char *fname = "parrot.rgba";

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

	printf( "Loading bitmap (%d,%d) to VDP\n", img_width, img_height );

	vdp_select_bitmap( 1 );
	vdp_load_bitmap( img_width, img_height, img_buf );
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

static struct { uint8_t vdu_22; uint8_t mode; }
	_vdp_mode = { 22, 0 };

int vdp_mode( int mode )
{
	if ( mode < 0 || mode >= 4 ) return -1;
	_vdp_mode.mode = mode;
	mos_puts( (char *)&_vdp_mode, sizeof(_vdp_mode), 0 );
	return mode;
}

static struct { uint8_t vdu23; uint8_t vdu_23_0; uint8_t vdu_23_0_0x86; }
	_vdp_get_scr_dims = { 23, 0, 0x86 };

void vdp_get_scr_dims( bool wait )
{
	if ( wait ) sv->vpd_pflags = 0;

	mos_puts( (char *)&_vdp_get_scr_dims, sizeof(_vdp_get_scr_dims), 0 );

	// wait for results of mode change to be reflected in SYSVARs
	if ( wait ) while ( !(sv->vpd_pflags & vdp_pflag_mode) );
}

static struct { uint8_t vdu_23; uint8_t vdu_23_0; uint8_t vdu_23_0_0xC0; uint8_t flag; }
	_vdp_logical_scr_dims = { 23, 0, 0xC0, 0 }; 

void vdp_logical_scr_dims( bool flag )
{
	_vdp_logical_scr_dims.flag = 0;
	if ( flag ) _vdp_logical_scr_dims.flag = 1;

	mos_puts( (char *)&_vdp_logical_scr_dims, sizeof(_vdp_logical_scr_dims), 0 );
}

// VDU 25 - plot command

typedef struct { uint8_t vdu_25; uint8_t plot_mode;
	uint16_t x;
	uint16_t y;
} VDU_25;

static VDU_25 vdu_25_move_to = { 25, 0x04, 0, 0 };
static VDU_25 vdu_25_line_to = { 25, 0x05, 0, 0 };
static VDU_25 vdu_25_point = { 25, 0x40, 0, 0 };
static VDU_25 vdu_25_triangle = { 25, 0x50, 0, 0 };
static VDU_25 vdu_25_circle_radius = { 25, 0x90, 0, 0 };
static VDU_25 vdu_25_circle = { 25, 0x94, 0, 0 };

void vdp_move_to( int x, int y )
{
	vdu_25_move_to.x = x;
	vdu_25_move_to.y = y;
	mos_puts( (char *)&vdu_25_move_to, sizeof(vdu_25_move_to), 0 );
}

void vdp_line_to( int x, int y )
{
	vdu_25_line_to.x = x;
	vdu_25_line_to.y = y;
	mos_puts( (char *)&vdu_25_line_to, sizeof(vdu_25_line_to), 0 );
}

void vdp_point( int x, int y )
{
	vdu_25_point.x = x;
	vdu_25_point.y = y;
	mos_puts( (char *)&vdu_25_point, sizeof(vdu_25_point), 0 );
}

void vdp_triangle( int x, int y )
{
	vdu_25_triangle.x = x;
	vdu_25_triangle.y = y;
	mos_puts( (char *)&vdu_25_triangle, sizeof(vdu_25_triangle), 0 );
}

void vdp_circle_radius( int x, int y )
{
	vdu_25_circle_radius.x = x;
	vdu_25_circle_radius.y = y;
	mos_puts( (char *)&vdu_25_circle_radius, sizeof(vdu_25_circle_radius), 0 );
}

void vdp_circle( int x, int y )
{
	vdu_25_circle.x = x;
	vdu_25_circle.y = y;
	mos_puts( (char *)&vdu_25_circle, sizeof(vdu_25_circle), 0 );
}

static struct { uint8_t vdu23; uint8_t vdu_23_27; uint8_t vdu_23_27_0; uint8_t n; }
	_vdp_select_bitmap = { 23, 27, 0, 0 };

void vdp_select_bitmap( int n )
{
	_vdp_select_bitmap.n = n;
	mos_puts( (char *)&_vdp_select_bitmap, sizeof(_vdp_select_bitmap), 0 );
}

static struct { uint8_t vdu23; uint8_t vdu_23_27; uint8_t vdu_23_27_1;
	uint16_t width; uint16_t height; }
	_vdp_load_bitmap = { 23, 27, 1, 0, 0 };

#define LOAD_BMAP_BLOCK 65535

void vdp_load_bitmap( int width, int height, uint32_t *data )
{
	_vdp_load_bitmap.width = width;
	_vdp_load_bitmap.height = height;
	mos_puts( (char *)&_vdp_load_bitmap, sizeof(_vdp_load_bitmap), 0 );

	int size;
	char *ptr = (char *)data;
	for ( size = width*height*sizeof(uint32_t); size > LOAD_BMAP_BLOCK; size -= LOAD_BMAP_BLOCK ) {
		mos_puts( (char *)ptr, LOAD_BMAP_BLOCK, 0 );
		ptr += LOAD_BMAP_BLOCK;
	}
	mos_puts( (char *)ptr, size, 0 );
}

static struct { uint8_t vdu23; uint8_t vdu_23_27; uint8_t vdu_23_27_3;
	uint16_t x; uint16_t y; }
	_vdp_draw_bitmap = { 23, 27, 3, 0, 0 };

void vdp_draw_bitmap( int x, int y )
{
	_vdp_draw_bitmap.x = x;
	_vdp_draw_bitmap.y = y;
	mos_puts( (char *)&_vdp_draw_bitmap, sizeof(_vdp_draw_bitmap), 0 );
}
