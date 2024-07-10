// VDP VDU Commands wrapper

#include "vdp_vdu.h"
#include <stdio.h>
#include <mos_api.h>
#include <stdbool.h>
#include <stdlib.h>

static volatile SYSVAR *sv = NULL;

volatile SYSVAR *vdp_vdu_init( void )
{
	sv = (SYSVAR *)mos_sysvars();
	return sv;
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
	if ( !sv ) vdp_vdu_init();

	if ( wait ) sv->vdp_pflags = 0;

	mos_puts( (char *)&_vdp_get_scr_dims, sizeof(_vdp_get_scr_dims), 0 );

	// wait for results of mode change to be reflected in SYSVARs
	if ( wait ) while ( !(sv->vdp_pflags & vdp_pflag_mode) );
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

int vdp_load_bitmap_file( const char *fname, int width, int height )
{
	FILE *fp;
	char *buffer;
	int exit_code = 0;

	if ( !(buffer = (char *)malloc( LOAD_BMAP_BLOCK ) ) ) {
		printf( "Failed to allocated memory for buffer.\n" );
		return -1;
	}
//	printf( "Opening file \"%s\"\n", fname);
	if ( !(fp = fopen( fname, "rb" ) ) ) {
		printf( "Error opening file \"%sa\". Quitting.\n", fname );
		return -1;
	}

	_vdp_load_bitmap.width = width;
	_vdp_load_bitmap.height = height;
	mos_puts( (char *)&_vdp_load_bitmap, sizeof(_vdp_load_bitmap), 0 );

	int block_size = LOAD_BMAP_BLOCK;
	int size = width * height * sizeof(uint32_t);
	if ( size < block_size ) block_size = size;

	for ( ; size > block_size; size -= block_size ) {
		if ( fread( buffer, 1, block_size, fp ) != (size_t)block_size ) exit_code = -1;
		mos_puts( buffer, block_size, 0 );
	}
	if ( size > 0) {
		if ( fread( buffer, 1, size, fp ) != (size_t)size ) exit_code = -1;
		mos_puts( buffer, size, 0 );
	}
	fclose( fp );
	free( buffer );
	return exit_code;
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
