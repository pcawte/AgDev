// VDP VDU Commands wrapper

#include <vdp_vdu.h>
#include <stdio.h>
#include <mos_api.h>
#include <stdbool.h>
#include <stdlib.h>

// Different patterns for the VDU commands
// - when defining VDU commands the values A, B and CMD should be set in the structure initialiser
// - values N (8-bit), R (8-bit), C (8-bit), X (16-bit) and Y (16-bit) should be set in the code 

typedef struct { uint8_t a; } VDU_A;
typedef struct { uint8_t a; uint8_t n; } VDU_A_N;
typedef struct { uint8_t a; uint8_t cmd; } VDU_A_CMD;
typedef struct { uint8_t a; uint8_t cmd; uint8_t n; } VDU_A_CMD_N;
typedef struct { uint8_t a; uint8_t c; uint8_t r; } VDU_A_C_R;
typedef struct { uint8_t a; uint16_t x; uint16_t y; } VDU_A_X_Y;
typedef struct { uint8_t a; uint8_t cmd; uint16_t x; uint16_t y; } VDU_A_CMD_X_Y;
typedef struct { uint8_t a; uint8_t b; uint8_t cmd; } VDU_A_B_CMD;
typedef struct { uint8_t a; uint8_t b; uint8_t cmd; uint8_t n; } VDU_A_B_CMD_N;
typedef struct { uint8_t a; uint8_t b; uint8_t cmd; uint16_t x; uint16_t y; } VDU_A_B_CMD_X_Y;


static volatile SYSVAR *sys_vars = NULL;

volatile SYSVAR *vdp_vdu_init( void )
{
	sys_vars = (SYSVAR *)mos_sysvars();
	return (SYSVAR *)sys_vars;
}

// Basic VDU commands

static VDU_A vdu_bell = { 7 };
static VDU_A vdu_cursor_left = { 8 };
static VDU_A vdu_cursor_right = { 9 };
static VDU_A vdu_cursor_down = { 10 };
static VDU_A vdu_cursor_up = { 11 };
static VDU_A vdu_clear_screen = { 12 };
static VDU_A vdu_clear_graphics = { 16 };
static VDU_A_N vdu_set_text_colour = { 17, 0 };
static VDU_A_N vdu_mode = { 22, 0 };
static VDU_A_X_Y vdu_graphics_origin = { 29, 0, 0 };
static VDU_A vdu_cursor_home = { 30 };
static VDU_A_C_R vdu_cursor_tab = { 31, 0, 0 };

void vdp_bell( void ) { VDP_PUTS( vdu_bell ); }
void vdp_cursor_left( void ) { VDP_PUTS( vdu_cursor_left ); }
void vdp_cursor_right( void ) { VDP_PUTS( vdu_cursor_right ); }
void vdp_cursor_down( void ) { VDP_PUTS( vdu_cursor_down ); }
void vdp_cursor_up( void ) { VDP_PUTS( vdu_cursor_up ); }
void vdp_clear_screen( void ) { VDP_PUTS( vdu_clear_screen ); }
void vdp_clear_graphics( void ) { VDP_PUTS( vdu_clear_graphics ); }
void vdp_cursor_home( void ) { VDP_PUTS( vdu_cursor_home ); }

void vdp_cursor_tab( int row, int col )
{
	vdu_cursor_tab.r = row;
	vdu_cursor_tab.c = col;
	VDP_PUTS( vdu_cursor_tab );
}

void vdp_set_text_colour( int colour )
{
	vdu_set_text_colour.n = colour;
	VDP_PUTS( vdu_set_text_colour );
}

int vdp_mode( int mode )
{
	if ( mode < 0 || mode >= 4 ) return -1;
	vdu_mode.n = mode;
	VDP_PUTS( vdu_mode );
	return mode;
}

void vdp_graphics_origin( int x, int y )
{
	vdu_graphics_origin.x = x;
	vdu_graphics_origin.y = y;
	VDP_PUTS( vdu_graphics_origin );
}

// VDU 23 commands

static VDU_A_B_CMD vdu_get_scr_dims = { 23, 0, 0x86 };
static VDU_A_B_CMD_N vdu_set_logical_scr_dims = { 23, 0, 0xC0, 0 }; 
static VDU_A_CMD_N vdu_cursor_enable = { 23, 1, 0 };

void vdp_get_scr_dims( bool wait )
{
	if ( !sys_vars ) vdp_vdu_init();

	if ( wait ) sys_vars->vpd_pflags = 0;

	VDP_PUTS( vdu_get_scr_dims );

	// wait for results of mode change to be reflected in SYSVARs
	if ( wait ) while ( !(sys_vars->vpd_pflags & vdp_pflag_mode) );
}

void vdp_logical_scr_dims( bool flag )
{
	vdu_set_logical_scr_dims.n = 0;
	if ( flag ) vdu_set_logical_scr_dims.n = 1;
	VDP_PUTS( vdu_set_logical_scr_dims );
}

void vdp_cursor_enable( bool flag )
{
	vdu_cursor_enable.n = 0;
	if ( flag ) vdu_cursor_enable.n = 1;
	VDP_PUTS( vdu_cursor_enable );
}

// VDU 25 - plot command

static VDU_A_CMD_X_Y vdu_move_to = { 25, 0x04, 0, 0 };
static VDU_A_CMD_X_Y vdu_line_to = { 25, 0x05, 0, 0 };
static VDU_A_CMD_X_Y vdu_point = { 25, 0x40, 0, 0 };
static VDU_A_CMD_X_Y vdu_triangle = { 25, 0x50, 0, 0 };
static VDU_A_CMD_X_Y vdu_circle_radius = { 25, 0x90, 0, 0 };
static VDU_A_CMD_X_Y vdu_circle = { 25, 0x94, 0, 0 };

void vdp_move_to( int x, int y )
{
	vdu_move_to.x = x;
	vdu_move_to.y = y;
	VDP_PUTS( vdu_move_to );
}

void vdp_line_to( int x, int y )
{
	vdu_line_to.x = x;
	vdu_line_to.y = y;
	VDP_PUTS( vdu_line_to );
}

void vdp_point( int x, int y )
{
	vdu_point.x = x;
	vdu_point.y = y;
	VDP_PUTS( vdu_point );
}

void vdp_triangle( int x, int y )
{
	vdu_triangle.x = x;
	vdu_triangle.y = y;
	VDP_PUTS( vdu_triangle );
}

void vdp_circle_radius( int x, int y )
{
	vdu_circle_radius.x = x;
	vdu_circle_radius.y = y;
	VDP_PUTS( vdu_circle_radius );
}

void vdp_circle( int x, int y )
{
	vdu_circle.x = x;
	vdu_circle.y = y;
	VDP_PUTS( vdu_circle );
}

// Bitmaps

static VDU_A_B_CMD_N vdu_select_bitmap = { 23, 27, 0, 0 };
static VDU_A_B_CMD_X_Y vdu_load_bitmap = { 23, 27, 1, 0, 0 };
static VDU_A_B_CMD_X_Y vdu_draw_bitmap = { 23, 27, 3, 0, 0 };

void vdp_select_bitmap( int n )
{
	vdu_select_bitmap.n = n;
	VDP_PUTS( vdu_select_bitmap );
}

void vdp_draw_bitmap( int x, int y )
{
	vdu_draw_bitmap.x = x;
	vdu_draw_bitmap.y = y;
	VDP_PUTS( vdu_draw_bitmap );
}

#define LOAD_BMAP_BLOCK 65535

void vdp_load_bitmap( int width, int height, uint32_t *data )
{
	vdu_load_bitmap.x = width;
	vdu_load_bitmap.y = height;
	VDP_PUTS( vdu_load_bitmap );

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

	if ( !(buffer = (char *)malloc( LOAD_BMAP_BLOCK ) ) ) return -1;
	if ( !(fp = fopen( fname, "rb" ) ) ) return -1;

	vdu_load_bitmap.x = width;
	vdu_load_bitmap.y = height;
	VDP_PUTS( vdu_load_bitmap );

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


// VDU 23, 27 - sprite commands

static VDU_A_B_CMD_N vdu_sprite_select = { 23, 27, 4, 0 };
static VDU_A_B_CMD vdu_sprite_clear = { 23, 27, 5 };
static VDU_A_B_CMD_N vdu_sprite_add_bitmap = { 23, 27, 6, 0 };
static VDU_A_B_CMD_N vdu_sprite_activate = { 23, 27, 7, 0 };
static VDU_A_B_CMD vdu_sprite_next_frame = { 23, 27, 8 };
static VDU_A_B_CMD vdu_sprite_prev_frame = { 23, 27, 9 };
static VDU_A_B_CMD_N vdu_sprite_nth_frame = { 23, 27, 10, 0 };
static VDU_A_B_CMD vdu_sprite_show = { 23, 27, 11 };
static VDU_A_B_CMD vdu_sprite_hide = { 23, 27, 12 };
static VDU_A_B_CMD_X_Y vdu_sprite_moveto = { 23, 27, 13, 0, 0 };
static VDU_A_B_CMD_X_Y vdu_sprite_moveby = { 23, 27, 14, 0, 0 };
static VDU_A_B_CMD vdu_sprite_update = { 23, 27, 15 };
static VDU_A_B_CMD vdu_sprite_reset = { 23, 27, 16 };


static char sprite_fname[32];

int vdp_load_sprite_bitmaps( const char *fname_prefix, const char *fname_format,
						int width, int height, int num, int bitmap_num )
{
	uint32_t *img_buf;
	FILE *fp;
	int cnt = 0;

	if ( !(img_buf = (uint32_t *)malloc( width*height*sizeof(uint32_t) ) ) ) return cnt;

	for ( int i = 0; i < num; i++ ) {
		sprintf( sprite_fname, fname_format, fname_prefix, i );
		if ( !(fp = fopen( sprite_fname, "rb" ) ) ) return cnt;

		size_t pixel_cnt = fread( (void *)img_buf, sizeof(uint32_t), width*height, fp );
		fclose( fp );
		if ( pixel_cnt != (size_t)(width*height) ) return cnt;
		
		vdp_select_bitmap( bitmap_num++ );
		vdp_load_bitmap( width, height, img_buf );
		cnt++;
	}
	free( img_buf);
	return cnt;
}


void vdp_create_sprite( int sprite, int bitmap_num, int frames )
{
	vdu_sprite_select.n = sprite;
	VDP_PUTS( vdu_sprite_select );
	VDP_PUTS( vdu_sprite_clear );
	for ( int i = 0; i < frames; i++ ) {
		vdu_sprite_add_bitmap.n = bitmap_num++;
		VDP_PUTS( vdu_sprite_add_bitmap );
	}
	vdu_sprite_activate.n = sprite;
}

void vdp_select_sprite( int n )
{
	vdu_sprite_select.n = n;
	VDP_PUTS( vdu_sprite_select );
}

void vdp_clear_sprite( void )
{
	VDP_PUTS( vdu_sprite_clear );
}

void vdp_add_sprite_bitmap( int n )
{
	vdu_sprite_add_bitmap.n = n;
	VDP_PUTS( vdu_sprite_add_bitmap );
}

void vdp_move_sprite_to( int x, int y )
{
	vdu_sprite_moveto.x = x;
	vdu_sprite_moveto.y = y;
	VDP_PUTS( vdu_sprite_moveto );
}

void vdp_move_sprite_by( int x, int y )
{
	vdu_sprite_moveby.x = x;
	vdu_sprite_moveby.y = y;
	VDP_PUTS( vdu_sprite_moveby );
}

void vdp_show_sprite( void )
{
	VDP_PUTS( vdu_sprite_show );
}

void vdp_hide_sprite( void )
{
	VDP_PUTS( vdu_sprite_hide );
}

void vdp_next_sprite_frame( void )
{
	VDP_PUTS( vdu_sprite_next_frame );
}

void vdp_prev_sprite_frame( void )
{
	VDP_PUTS( vdu_sprite_prev_frame );
}

void vdp_nth_sprite_frame( int n )
{
	vdu_sprite_nth_frame.n = n;
	VDP_PUTS( vdu_sprite_nth_frame );
}

void vdp_activate_sprites( int n )
{
	vdu_sprite_activate.n = n;
	VDP_PUTS( vdu_sprite_activate );
}

void vdp_refresh_sprites( void )
{
	VDP_PUTS( vdu_sprite_update );
}

void vdp_reset_sprites( void )
{
	VDP_PUTS( vdu_sprite_reset );
}

