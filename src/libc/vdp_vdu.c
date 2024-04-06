// VDP VDU Commands wrapper

#include <vdp_vdu.h>
#include <stdio.h>
#include <mos_api.h>
#include <stdbool.h>
#include <stdlib.h>

// Different patterns for the VDU commands
// - when defining VDU commands the values A, B and CMD should be set in the structure initialiser
// - values N (8-bit), R (8-bit), C (8-bit), X (16-bit) and Y (16-bit) should be set in the code 

typedef struct { uint8_t A; } VDU_A;
typedef struct { uint8_t A; uint8_t n; } VDU_A_n;
typedef struct { uint8_t A; uint8_t CMD; } VDU_A_CMD;
typedef struct { uint8_t A; uint8_t CMD; uint8_t n; } VDU_A_CMD_n;
typedef struct { uint8_t A; uint8_t c; uint8_t r; } VDU_A_c_r;
typedef struct { uint8_t A; uint8_t a; uint8_t b; uint8_t c; uint8_t d; } VDU_A_a_b_c_d;
typedef struct { uint8_t A; uint8_t l; uint8_t p; uint8_t r; uint8_t g; uint8_t b; } VDU_A_l_p_r_g_b;
typedef struct { uint8_t A; uint16_t x; uint16_t y; } VDU_A_x_y;
typedef struct { uint8_t A; uint8_t CMD; uint16_t x; uint16_t y; } VDU_A_CMD_x_y;
typedef struct { uint8_t A; uint8_t B; uint8_t CMD; } VDU_A_B_CMD;
typedef struct { uint8_t A; uint8_t B; uint8_t CMD; uint8_t n; } VDU_A_B_CMD_n;
typedef struct { uint8_t A; uint8_t B; uint8_t CMD; uint16_t b; } VDU_A_B_CMD_b;
typedef struct { uint8_t A; uint8_t B; uint8_t CMD; uint16_t x; uint16_t y; } VDU_A_B_CMD_x_y;
typedef struct { uint8_t A; uint8_t B; uint8_t CMD; uint16_t x; uint16_t y;
						uint8_t r; uint8_t g; uint8_t b; uint8_t a; } VDU_A_B_CMD_x_y_rgba;
typedef struct { uint8_t A; uint8_t B; uint8_t CMD; uint16_t w; uint16_t h; uint8_t f; } VDU_A_B_CMD_w_h_f;

typedef struct { uint8_t A; uint8_t B; uint8_t C; uint16_t BID; uint8_t CMD; } VDU_ADV_CMD;
typedef struct { uint8_t A; uint8_t B; uint8_t C; uint16_t BID; uint8_t CMD; uint16_t ui16; } VDU_ADV_CMD_ui16;
typedef struct { uint8_t A; uint8_t B; uint8_t C; uint16_t BID; uint8_t CMD; uint8_t ui8; uint16_t ui16; } VDU_ADV_CMD_ui8_ui16;
typedef struct { uint8_t A; uint8_t B; uint8_t b0; uint8_t b1; uint8_t b2; uint8_t b3; uint8_t b4; uint8_t b5; uint8_t b6; uint8_t b7; } VDU_A_B_ui8x8;
typedef struct { uint8_t A; uint16_t w0; uint16_t w1; uint16_t w2; uint16_t w3; } VDU_A_ui16x4;

static volatile SYSVAR *sys_vars = NULL;

volatile SYSVAR *vdp_vdu_init( void )
{
	sys_vars = (SYSVAR *)mos_sysvars();
	return (SYSVAR *)sys_vars;
}

// Basic VDU commands

static VDU_A vdu_write_at_text_cursor = { 4 };
static VDU_A vdu_write_at_graphics_cursor = { 5 };
static VDU_A vdu_enable_screen = { 6 };
static VDU_A vdu_bell = { 7 };
static VDU_A vdu_cursor_left = { 8 };
static VDU_A vdu_cursor_right = { 9 };
static VDU_A vdu_cursor_down = { 10 };
static VDU_A vdu_cursor_up = { 11 };
static VDU_A vdu_clear_screen = { 12 };
static VDU_A vdu_page_mode_on = { 14 };
static VDU_A vdu_page_mode_off = { 15 };
static VDU_A vdu_clear_graphics = { 16 };
static VDU_A_n vdu_set_text_colour = { 17, 0 };
static VDU_A_c_r vdu_set_graphics_colour = { 18, 0, 0 };
static VDU_A_l_p_r_g_b vdu_define_colour = { 19, 0, 0, 0, 0, 0 };
static VDU_A vdu_reset_graphics = { 20 };
static VDU_A vdu_disable_screen = { 21 };
static VDU_A_n vdu_mode = { 22, 0 };
static VDU_A_x_y vdu_graphics_origin = { 29, 0, 0 };
static VDU_A vdu_cursor_home = { 30 };
static VDU_A_c_r vdu_cursor_tab = { 31, 0, 0 };
static VDU_A_B_CMD vdu_swap = { 23, 0, 195 };

void vdp_write_at_text_cursor( void ) { VDP_PUTS( vdu_write_at_text_cursor ); }
void vdp_write_at_graphics_cursor( void ) { VDP_PUTS( vdu_write_at_graphics_cursor ); }
void vdp_enable_screen( void ) { VDP_PUTS( vdu_enable_screen ); }
void vdp_bell( void ) { VDP_PUTS( vdu_bell ); }
void vdp_cursor_left( void ) { VDP_PUTS( vdu_cursor_left ); }
void vdp_cursor_right( void ) { VDP_PUTS( vdu_cursor_right ); }
void vdp_cursor_down( void ) { VDP_PUTS( vdu_cursor_down ); }
void vdp_cursor_up( void ) { VDP_PUTS( vdu_cursor_up ); }
void vdp_clear_screen( void ) { VDP_PUTS( vdu_clear_screen ); }
void vdp_page_mode_on( void ) { VDP_PUTS( vdu_page_mode_on ); }
void vdp_page_mode_off( void ) { VDP_PUTS( vdu_page_mode_off ); }
void vdp_clear_graphics( void ) { VDP_PUTS( vdu_clear_graphics ); }
void vdp_reset_graphics( void ) { VDP_PUTS( vdu_reset_graphics ); }
void vdp_disable_screen( void ) { VDP_PUTS( vdu_disable_screen ); }
void vdp_cursor_home( void ) { VDP_PUTS( vdu_cursor_home ); }
void vdp_swap( void ) { VDP_PUTS( vdu_swap ); }

// rg: fixed this so it is X, Y
void vdp_cursor_tab( int col, int row )
{
	vdu_cursor_tab.c = col;
	vdu_cursor_tab.r = row;
	VDP_PUTS( vdu_cursor_tab );
}

void vdp_set_text_colour( int colour )
{
	vdu_set_text_colour.n = colour;
	VDP_PUTS( vdu_set_text_colour );
}

void vdp_set_graphics_colour( int mode, int colour )
{
	vdu_set_graphics_colour.c = mode;
	vdu_set_graphics_colour.r = colour;
	VDP_PUTS( vdu_set_graphics_colour );
}

void vdp_define_colour(int logical, int physical, int red, int green, int blue )
{
	vdu_define_colour.l = logical;
	vdu_define_colour.p = physical;
	vdu_define_colour.r = red;
	vdu_define_colour.g = green;
	vdu_define_colour.b = blue;
	VDP_PUTS( vdu_define_colour );
}

int vdp_mode( int mode )
{
	if ( mode < 0 || mode >= 255 ) return -1;
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

static VDU_A_B_ui8x8 vdu_redefine_character = { 23, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static VDU_A_B_CMD vdu_get_scr_dims = { 23, 0, 0x86 };
static VDU_A_B_CMD_n vdu_set_logical_scr_dims = { 23, 0, 0xC0, 0 }; 
static VDU_A_CMD_n vdu_cursor_enable = { 23, 1, 0 };
static VDU_A_a_b_c_d vdu_scroll_screen = {23, 7, 1, 0, 0};

void vdp_redefine_character( int chnum, uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7 )
{
	vdu_redefine_character.B = chnum;
	vdu_redefine_character.b0 = b0;
	vdu_redefine_character.b1 = b1;
	vdu_redefine_character.b2 = b2;
	vdu_redefine_character.b3 = b3;
	vdu_redefine_character.b4 = b4;
	vdu_redefine_character.b5 = b5;
	vdu_redefine_character.b6 = b6;
	vdu_redefine_character.b7 = b7;
	VDP_PUTS( vdu_redefine_character );
}

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

// extent 0 = current text viewport, 1 = whole screen, 2 = current graphics viewport, 3 = active viewport 
void vdp_scroll_screen_extent( int extent, int direction, int speed )
{
	vdu_scroll_screen.b = extent;
	vdu_scroll_screen.c = direction;
	vdu_scroll_screen.d = speed;
	VDP_PUTS( vdu_scroll_screen );
}
void vdp_scroll_screen( int direction, int speed )
{
	vdu_scroll_screen.b = 1; // whole screen
	vdu_scroll_screen.c = direction;
	vdu_scroll_screen.d = speed;
	VDP_PUTS( vdu_scroll_screen );
}

// viewport commands

static VDU_A vdu_reset_viewports = { 26 };
static VDU_A_ui16x4 vdu_set_graphics_viewport = { 24, 0, 0, 0, 0 };
static VDU_A_a_b_c_d vdu_set_text_viewport = { 28, 0, 0, 0, 0 };

void vdp_reset_viewports( void ) { VDP_PUTS( vdu_reset_viewports ); }
void vdp_set_graphics_viewport( int left, int bottom, int right, int top )
{
	vdu_set_graphics_viewport.w0 = left;
	vdu_set_graphics_viewport.w1 = bottom;
	vdu_set_graphics_viewport.w2 = right;
	vdu_set_graphics_viewport.w3 = top;
	VDP_PUTS( vdu_set_graphics_viewport );
}
void vdp_set_text_viewport( int left, int bottom, int right, int top )
{
	vdu_set_text_viewport.a = left;
	vdu_set_text_viewport.b = bottom;
	vdu_set_text_viewport.c = right;
	vdu_set_text_viewport.d = top;
	VDP_PUTS( vdu_set_text_viewport );
}

// VDU 25 - plot command

static VDU_A_CMD_x_y vdu_plot = { 25, 0, 0, 0 };
static VDU_A_CMD_x_y vdu_move_to = { 25, 0x04, 0, 0 };
static VDU_A_CMD_x_y vdu_line_to = { 25, 0x05, 0, 0 };
static VDU_A_CMD_x_y vdu_point = { 25, 0x45, 0, 0 };
static VDU_A_CMD_x_y vdu_triangle = { 25, 0x50, 0, 0 };
static VDU_A_CMD_x_y vdu_circle_radius = { 25, 0x90, 0, 0 };
static VDU_A_CMD_x_y vdu_circle = { 25, 0x94, 0, 0 };
static VDU_A_CMD_x_y vdu_filled_rect = { 25, 0x65, 0, 0 };

// generic plot command - needs plot-mode
void vdp_plot( int plot_mode, int x, int y )
{
	vdu_plot.CMD = plot_mode;
	vdu_plot.x = x;
	vdu_plot.y = y;
	VDP_PUTS( vdu_plot );
}

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

void vdp_filled_rect( int x, int y )
{
	vdu_filled_rect.x = x;
	vdu_filled_rect.y = y;
	VDP_PUTS( vdu_filled_rect );
}

// Bitmaps

static VDU_A_B_CMD_n vdu_select_bitmap = { 23, 27, 0, 0 };
static VDU_A_B_CMD_x_y vdu_load_bitmap = { 23, 27, 1, 0, 0 };
static VDU_A_B_CMD_x_y_rgba vdu_solid_bitmap = { 23, 27, 2, 0, 0, 0, 0, 0, 0 };
static VDU_A_B_CMD_x_y vdu_draw_bitmap = { 23, 27, 3, 0, 0 };

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

void vdp_solid_bitmap( int width, int height, int r, int g, int b, int a )
{
	vdu_solid_bitmap.x = width;
	vdu_solid_bitmap.y = height;
	vdu_solid_bitmap.r = r;
	vdu_solid_bitmap.g = g;
	vdu_solid_bitmap.b = b;
	vdu_solid_bitmap.a = a;
	VDP_PUTS( vdu_solid_bitmap );
}

// VDU 23, 27 - sprite commands

static VDU_A_B_CMD_n vdu_sprite_select = { 23, 27, 4, 0 };
static VDU_A_B_CMD vdu_sprite_clear = { 23, 27, 5 };
static VDU_A_B_CMD_n vdu_sprite_add_bitmap = { 23, 27, 6, 0 };
static VDU_A_B_CMD_n vdu_sprite_activate = { 23, 27, 7, 0 };
static VDU_A_B_CMD vdu_sprite_next_frame = { 23, 27, 8 };
static VDU_A_B_CMD vdu_sprite_prev_frame = { 23, 27, 9 };
static VDU_A_B_CMD_n vdu_sprite_nth_frame = { 23, 27, 10, 0 };
static VDU_A_B_CMD vdu_sprite_show = { 23, 27, 11 };
static VDU_A_B_CMD vdu_sprite_hide = { 23, 27, 12 };
static VDU_A_B_CMD_x_y vdu_sprite_moveto = { 23, 27, 13, 0, 0 };
static VDU_A_B_CMD_x_y vdu_sprite_moveby = { 23, 27, 14, 0, 0 };
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

/* Advanced buffered commands (selected) */

static VDU_ADV_CMD_ui16 vdu_adv_write_block  = { 23, 0, 0xA0, 0xFA00, 0, 0};
static VDU_ADV_CMD      vdu_adv_clear_buffer = { 23, 0, 0xA0, 0xFA00, 2};
static VDU_ADV_CMD_ui16 vdu_adv_create       = { 23, 0, 0xA0, 0xFA00, 3, 0};
static VDU_ADV_CMD      vdu_adv_stream       = { 23, 0, 0xA0, 0xFA00, 4};
static VDU_ADV_CMD_ui8_ui16 vdu_adv_adjust   = { 23, 0, 0xA0, 0xFA00, 5, 0, 0};
static VDU_ADV_CMD      vdu_adv_consolidate  = { 23, 0, 0xA0, 0xFA00, 14};

// VDU 23,27 - extended commands for bufferIds 
static VDU_A_B_CMD_b	vdu_adv_select_bitmap = { 23, 27, 0x20, 0xFA00};
static VDU_A_B_CMD_w_h_f vdu_adv_bitmap_from_buffer = { 23, 27, 0x21, 0, 0, 0};
static VDU_A_B_CMD_b	vdu_adv_add_sprite_bitmap = { 23, 27, 0x26, 0xFA00};

void vdp_adv_write_block(int bufferID, int length)
{
	vdu_adv_write_block.BID = bufferID;
	vdu_adv_write_block.ui16 = length;
	VDP_PUTS(vdu_adv_write_block);
}

void vdp_adv_clear_buffer(int bufferID)
{
	vdu_adv_clear_buffer.BID = bufferID;
	VDP_PUTS(vdu_adv_clear_buffer);
}

void vdp_adv_create(int bufferID, int length)
{
	vdu_adv_create.BID = bufferID;
	vdu_adv_create.ui16 = length;
	VDP_PUTS(vdu_adv_create);
}

void vdp_adv_stream(int bufferID)
{
	vdu_adv_stream.BID = bufferID;
	VDP_PUTS(vdu_adv_stream);
}

/* Adjust - pass the necessary arguments this must then be followed
 * by data appropriate for the operation selected */
void vdp_adv_adjust(int bufferID, int operation, int offset)
{
	vdu_adv_adjust.BID = bufferID;
	vdu_adv_adjust.ui8 = operation;
	vdu_adv_adjust.ui16 = offset;
	VDP_PUTS(vdu_adv_adjust);
}

void vdp_adv_consolidate(int bufferID)
{
	vdu_adv_consolidate.BID = bufferID;
	VDP_PUTS(vdu_adv_consolidate);
}

void vdp_adv_select_bitmap(int bufferID)
{
	vdu_adv_select_bitmap.b = bufferID;
	VDP_PUTS(vdu_adv_select_bitmap);
}

void vdp_adv_bitmap_from_buffer(int width, int height, int format)
{
	vdu_adv_bitmap_from_buffer.w = width;
	vdu_adv_bitmap_from_buffer.h = height;
	vdu_adv_bitmap_from_buffer.f = format;
	VDP_PUTS(vdu_adv_bitmap_from_buffer);
}

// helper function
// load images using absolute numbered bitmaps (24-bit)
int vdp_adv_load_sprite_bitmaps( const char *fname_prefix, const char *fname_format,
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
		
		vdp_adv_select_bitmap( bitmap_num++ );
		vdp_load_bitmap( width, height, img_buf );
		cnt++;
	}
	free( img_buf);
	return cnt;
}

// select bitmap for sprite using absolute numbered bitmaps (24-bit)
void vdp_adv_add_sprite_bitmap( int b )
{
	vdu_adv_add_sprite_bitmap.b = b;
	VDP_PUTS( vdu_adv_add_sprite_bitmap );
}


// create a sprite using absolute numbered bitmaps (24-bit)
void vdp_adv_create_sprite( int sprite, int bitmap_num, int frames )
{
	vdu_sprite_select.n = sprite;
	VDP_PUTS( vdu_sprite_select );
	VDP_PUTS( vdu_sprite_clear );
	for ( int i = 0; i < frames; i++ ) {
		vdp_adv_add_sprite_bitmap( bitmap_num++ );
	}
	vdu_sprite_activate.n = sprite;
}

// Audio API
// ---------------------------------------------------------------
// Command 0: Play note 
// 	VDU 23, 0, &85, channel, 0, volume, frequency; duration;
// Command 1: Status 
// 	VDU 23, 0, &85, channel, 1
// Command 2: Set volume
// 	VDU 23, 0, &85, channel, 2, volume
// Command 3: Set frequency
//	VDU 23, 0, &85, channel, 3, frequency;
// Command 4: Set waveform
//	VDU 23, 0, &85, channel, 4, waveformOrSample, [bufferId;]
// Command 5: Sample management
// 	VDU 23, 0, &85, channelOrSample, 5, sampleCommand, [parameters]
//	Command 5, 0: Load sample
//		VDU 23, 0, &85, sample, 5, 0, length; lengthHighByte, <sampleData>
// 	Command 5, 1: Clear sample
//		VDU 23, 0, &85, sample, 5, 1
//	Command 5, 2: Create a sample from a buffer
//		VDU 23, 0, &85, channel, 5, 2, bufferId; format, [sampleRate;]
//	Command 5, 3: Set sample base frequency
//		VDU 23, 0, &85, sample, 5, 3, frequency;
//	Command 5, 4: Set sample frequency for a sample by buffer ID
//		VDU 23, 0, &85, channel, 5, 4, bufferId; frequency;
//	Command 5, 5: Set sample repeat start point
//		VDU 23, 0, &85, sample, 5, 5, repeatStart; repeatStartHighByte
//	Command 5, 6: Set sample repeat start point by buffer ID
//		VDU 23, 0, &85, channel, 5, 6, bufferId; repeatStart; repeatStartHighByte
//	Command 5, 7: Set sample repeat length
//		VDU 23, 0, &85, sample, 5, 7, repeatLength; repeatLengthHighByte
//	Command 5, 8: Set sample repeat length by buffer ID
//		VDU 23, 0, &85, channel, 5, 8, bufferId; repeatLength; repeatLengthHighByte
// Command 6: Volume envelope
//	VDU 23, 0, &85, channel, 6, type, [parameters]
// Command 7: Frequency envelope
//	VDU 23, 0, &85, channel, 7, type, [parameters]
// 	Type 0: None
//		VDU 23, 0, &85, channel, 7, 0
//	Type 1: Stepped frequency envelope
//		VDU 23, 0, &85, channel, 7, 1, phaseCount, controlByte, stepLength; [phase1Adjustment; phase1NumberOfSteps; phase2Adjustment; phase2NumberOfSteps; ...]
// Command 8: Enable Channel
// 	VDU 23, 0, &85, channel, 8
// Command 9: Disable Channel
//  	VDU 23, 0, &85, channel, 9
// Command 10: Reset Channel
//  	VDU 23, 0, &85, channel, 10
//

typedef struct { uint8_t A; uint8_t B; uint8_t C; uint8_t channel; uint8_t CMD; } VDU_AUDIO_CMD;
typedef struct { uint8_t A; uint8_t B; uint8_t C; uint8_t channel; uint8_t CMD; uint8_t b1; } VDU_AUDIO_CMD_B;
typedef struct { uint8_t A; uint8_t B; uint8_t C; uint8_t channel; uint8_t CMD; uint16_t w1; } VDU_AUDIO_CMD_W;
typedef struct { uint8_t A; uint8_t B; uint8_t C; uint8_t channel; uint8_t CMD; uint8_t b1; uint16_t w2; } VDU_AUDIO_CMD_B_W;
typedef struct { uint8_t A; uint8_t B; uint8_t C; uint8_t channel; uint8_t CMD; uint8_t b1; uint16_t w2; uint8_t b3; } VDU_AUDIO_CMD_B_W_B;
typedef struct { uint8_t A; uint8_t B; uint8_t C; uint8_t channel; uint8_t CMD; uint8_t b1; uint16_t w2; uint16_t w3; } VDU_AUDIO_CMD_B_W_W;
typedef struct { uint8_t A; uint8_t B; uint8_t C; uint8_t channel; uint8_t CMD; uint8_t b1; uint16_t w2; uint16_t w3; uint8_t b4; uint16_t w5; } VDU_AUDIO_CMD_B_W_W_B_W;
typedef struct { uint8_t A; uint8_t B; uint8_t C; uint8_t sample; uint8_t CMD; uint8_t TYPE; uint24_t length; } VDU_AUDIO_LOAD_SAMPLE;
typedef struct { uint8_t A; uint8_t B; uint8_t C; uint8_t sample; uint8_t CMD; uint8_t b1; uint24_t ww2; } VDU_AUDIO_CMD_B_WW;
typedef struct { uint8_t A; uint8_t B; uint8_t C; uint8_t sample; uint8_t CMD; uint8_t b1; uint16_t w2; uint24_t ww3; } VDU_AUDIO_CMD_B_W_WW;
typedef struct { uint8_t A; uint8_t B; uint8_t C; uint8_t channel; uint8_t CMD; uint8_t b1; uint8_t b2; uint8_t b3; uint16_t w4; } VDU_AUDIO_CMD_B_B_B_W;

static VDU_AUDIO_CMD vdu_audio = { 23, 0, 0x85, 0, 0 };
static VDU_AUDIO_CMD_B vdu_audio_b = { 23, 0, 0x85, 0, 0, 0 };
static VDU_AUDIO_CMD_W vdu_audio_w = { 23, 0, 0x85, 0, 0, 0 };
static VDU_AUDIO_CMD_B_W vdu_audio_b_w = { 23, 0, 0x85, 0, 0, 0, 0 };
static VDU_AUDIO_CMD_B_W_B vdu_audio_b_w_b = { 23, 0, 0x85, 0, 0, 0, 0, 0 };
static VDU_AUDIO_CMD_B_W_W vdu_audio_b_w_w = { 23, 0, 0x85, 0, 0, 0, 0, 0 };
static VDU_AUDIO_CMD_B_W_W_B_W vdu_audio_b_w_w_b_w = { 23, 0, 0x85, 0, 0, 0, 0, 0, 0, 0 };
static VDU_AUDIO_LOAD_SAMPLE vdu_audio_load_sample = { 23, 0, 0x85, 0, 5, 0, 0 };
static VDU_AUDIO_CMD_B_WW vdu_audio_b_ww = { 23, 0, 0x85, 0, 0, 0, 0 };
static VDU_AUDIO_CMD_B_W_WW vdu_audio_b_w_ww = { 23, 0, 0x85, 0, 0, 0, 0, 0 };
static VDU_AUDIO_CMD_B_B_B_W vdu_audio_b_b_b_w = { 23, 0, 0x85, 0, 7, 1, 0, 0, 0 };

// Command 0: Play note 
// 	VDU 23, 0, &85, channel, 0, volume, frequency; duration;
void vdp_audio_play_note( int channel, int volume, int frequency, int duration)
{
	vdu_audio_b_w_w.channel = channel;
	vdu_audio_b_w_w.CMD = 0;
	vdu_audio_b_w_w.b1 = volume;
	vdu_audio_b_w_w.w2 = frequency;
	vdu_audio_b_w_w.w3 = duration;
       	VDP_PUTS( vdu_audio_b_w_w ); 
}

// Command 1: Status 
// 	VDU 23, 0, &85, channel, 1
void vdp_audio_status( int channel )
{ 
	vdu_audio.channel = channel;
	vdu_audio.CMD = 1;
       	VDP_PUTS( vdu_audio ); 
}

// Command 2: Set volume
// 	VDU 23, 0, &85, channel, 2, volume
void vdp_audio_set_volume( int channel, int volume )
{ 
	vdu_audio_b.channel = channel;
	vdu_audio_b.CMD = 2;
	vdu_audio_b.b1 = volume;
       	VDP_PUTS( vdu_audio_b ); 
}

// Command 3: Set frequency
//	VDU 23, 0, &85, channel, 3, frequency;
void vdp_audio_set_frequency( int channel, int frequency )
{ 
	vdu_audio_w.channel = channel;
	vdu_audio_w.CMD = 3;
	vdu_audio_w.w1 = frequency;
       	VDP_PUTS( vdu_audio_w ); 
}

// Command 4 (types 0-5): Set waveform
//	VDU 23, 0, &85, channel, 4, waveformOrSample, [bufferId;]
void vdp_audio_set_waveform( int channel, int waveform )
{
	// only for waveforms 0-5, use vdp_audio_set_sample for 8,-1
	vdu_audio_b.channel = channel;
	vdu_audio_b.CMD = 4;
	vdu_audio_b.b1 = waveform;
       	VDP_PUTS( vdu_audio_b ); 
}
// Command 4 (type 8): Set sample
void vdp_audio_set_sample( int channel, int bufferID )
{
	// only for waveforms 8,-1, use vdp_audio_set_waveform otherwise
	vdu_audio_b_w.channel = channel;
	vdu_audio_b_w.CMD = 4;
	vdu_audio_b_w.b1 = 8; // waveform=8 is sample
	vdu_audio_b_w.w2 = bufferID;
       	VDP_PUTS( vdu_audio_b_w ); 
}

// Command 5: Sample management
// 	VDU 23, 0, &85, channelOrSample, 5, sampleCommand, [parameters]
//	Command 5, 0: Load sample
//		VDU 23, 0, &85, sample, 5, 0, length; lengthHighByte, <sampleData>
//		the sample data is assumed to be 8-bit signed PCM samples at 16kHz
void vdp_audio_load_sample( int sample, int length, uint8_t *data)
{
	vdu_audio_load_sample.sample = sample;
	vdu_audio_load_sample.length = length;
	VDP_PUTS( vdu_audio_load_sample );

	int size;
	char *ptr = (char *)data;
	for ( size = length; size > LOAD_BMAP_BLOCK; size -= LOAD_BMAP_BLOCK ) {
		mos_puts( (char *)ptr, LOAD_BMAP_BLOCK, 0 );
		ptr += LOAD_BMAP_BLOCK;
	}
	mos_puts( (char *)ptr, size, 0 );
}

// 	Command 5, 1: Clear sample
//		VDU 23, 0, &85, sample, 5, 1
void vdp_audio_clear_sample( int sample )
{
	vdu_audio_b.channel = sample;
	vdu_audio_b.CMD = 5;
	vdu_audio_b.b1 = 1;
       	VDP_PUTS( vdu_audio_b ); 
}

//	Command 5, 2: Create a sample from a buffer
//		VDU 23, 0, &85, channel, 5, 2, bufferId; format, [sampleRate;]
void vdp_audio_create_sample_from_buffer( int channel, int bufferID, int format)
{
	vdu_audio_b_w_b.channel = channel;
	vdu_audio_b_w_b.CMD = 5;
	vdu_audio_b_w_b.b1 = 2;
	vdu_audio_b_w_b.w2 = bufferID;
	vdu_audio_b_w_b.b3 = format;
	VDP_PUTS( vdu_audio_b_w_b );
}

//	Command 5, 3: Set sample base frequency
//		VDU 23, 0, &85, sample, 5, 3, frequency;
void vdp_audio_set_sample_frequency( int sample, int frequency )
{
	vdu_audio_b_w.channel = sample;
	vdu_audio_b_w.CMD = 5;
	vdu_audio_b_w.b1 = 3;
	vdu_audio_b_w.w2 = frequency;
	VDP_PUTS( vdu_audio_b_w );
}

//	Command 5, 4: Set sample frequency for a sample by buffer ID
//		VDU 23, 0, &85, channel, 5, 4, bufferId; frequency;
void vdp_audio_set_buffer_frequency( int channel, int bufferID, int frequency )
{
	vdu_audio_b_w_w.channel = channel;
	vdu_audio_b_w_w.CMD = 5;
	vdu_audio_b_w_w.b1 = 4;
	vdu_audio_b_w_w.w2 = bufferID;
	vdu_audio_b_w_w.w3 = frequency;
	VDP_PUTS( vdu_audio_b_w_w );
}

//	Command 5, 5: Set sample repeat start point
//		VDU 23, 0, &85, sample, 5, 5, repeatStart; repeatStartHighByte
void vdp_audio_set_sample_repeat_start( int sample, int repeatStart )
{
	vdu_audio_b_ww.sample = sample;
	vdu_audio_b_ww.CMD = 5;
	vdu_audio_b_ww.b1 = 5;
	vdu_audio_b_ww.ww2 = repeatStart;
	VDP_PUTS( vdu_audio_b_ww );
}

//	Command 5, 6: Set sample repeat start point by buffer ID
//		VDU 23, 0, &85, channel, 5, 6, bufferId; repeatStart; repeatStartHighByte
void vdp_audio_set_buffer_repeat_start( int channel, int bufferID, int repeatStart )
{
	vdu_audio_b_w_ww.sample = channel;
	vdu_audio_b_w_ww.CMD = 5;
	vdu_audio_b_w_ww.b1 = 6;
	vdu_audio_b_w_ww.w2 = bufferID;
	vdu_audio_b_w_ww.ww3 = repeatStart;
	VDP_PUTS( vdu_audio_b_w_ww );
}

//	Command 5, 7: Set sample repeat length
//		VDU 23, 0, &85, sample, 5, 7, repeatLength; repeatLengthHighByte
void vdp_audio_set_sample_repeat_length( int sample, int repeatLength )
{
	vdu_audio_b_ww.sample = sample;
	vdu_audio_b_ww.CMD = 5;
	vdu_audio_b_ww.b1 = 7;
	vdu_audio_b_ww.ww2 = repeatLength;
	VDP_PUTS( vdu_audio_b_ww );
}

//	Command 5, 8: Set sample repeat length by buffer ID
//		VDU 23, 0, &85, channel, 5, 8, bufferId; repeatLength; repeatLengthHighByte
void vdp_audio_set_buffer_repeat_length( int channel, int bufferID, int repeatLength )
{
	vdu_audio_b_w_ww.sample = channel;
	vdu_audio_b_w_ww.CMD = 5;
	vdu_audio_b_w_ww.b1 = 8;
	vdu_audio_b_w_ww.w2 = bufferID;
	vdu_audio_b_w_ww.ww3 = repeatLength;
	VDP_PUTS( vdu_audio_b_w_ww );
}

// Command 6: Volume envelope. Type 0: Disable
//	VDU 23, 0, &85, channel, 6, type, [parameters]
void vdp_audio_volume_envelope_disable( int channel )
{
	vdu_audio_b.channel = channel;
	vdu_audio_b.CMD = 6;
	vdu_audio_b.b1 = 0;
       	VDP_PUTS( vdu_audio_b ); 
}
// Command 6: Volume envelope. Type 1: ADSR
// 	VDU 23, 0, &85, channel, 6, 1, attack; decay; sustain, release;
void vdp_audio_volume_envelope_ADSR( int channel, int attack, int decay, int sustain, int release )
{
	vdu_audio_b_w_w_b_w.channel = channel;
	vdu_audio_b_w_w_b_w.CMD = 6;
	vdu_audio_b_w_w_b_w.b1 = 1;
	vdu_audio_b_w_w_b_w.w2 = attack;
	vdu_audio_b_w_w_b_w.w3 = decay;
	vdu_audio_b_w_w_b_w.b4 = sustain;
	vdu_audio_b_w_w_b_w.w5 = release;
	VDP_PUTS( vdu_audio_b_w_w_b_w );
}
// Command 6: Volume envelope. Type 2: Multi-phase ADSR
// 	VDU 23, 0, &85, channel, 6, 2, attackCount, [level, duration;]*, sustainCount, [level, duration;]*, releaseCount, [level, duration;]*
// 	variable length parameters - leave to user to send separately
void vdp_audio_volume_envelope_multiphase_ADSR( int channel )
{
	vdu_audio_b.channel = channel;
	vdu_audio_b.CMD = 6;
	vdu_audio_b.b1 = 2;
       	VDP_PUTS( vdu_audio_b ); 
}

// Command 7: Frequency envelope
//	VDU 23, 0, &85, channel, 7, type, [parameters]
// 	Type 0: None
//		VDU 23, 0, &85, channel, 7, 0
void vdp_audio_frequency_envelope_disable( int channel )
{
	vdu_audio_b.channel = channel;
	vdu_audio_b.CMD = 7;
	vdu_audio_b.b1 = 0;
       	VDP_PUTS( vdu_audio_b ); 
}

//	Type 1: Stepped frequency envelope
//		VDU 23, 0, &85, channel, 7, 1, phaseCount, controlByte, stepLength; [phase1Adjustment; phase1NumberOfSteps; phase2Adjustment; phase2NumberOfSteps; ...]
void vdp_audio_frequency_envelope_stepped( int channel, int phaseCount, int controlByte, int stepLength )
{
	vdu_audio_b_b_b_w.channel = channel;
	vdu_audio_b_b_b_w.CMD = 7;
	vdu_audio_b_b_b_w.b1 = 1;
	vdu_audio_b_b_b_w.b2 = phaseCount;
	vdu_audio_b_b_b_w.b3 = controlByte;
	vdu_audio_b_b_b_w.w4 = stepLength;
       	VDP_PUTS( vdu_audio_b_b_b_w ); 
}

// Command 8: Enable Channel
// 	VDU 23, 0, &85, channel, 8
void vdp_audio_enable_channel( int channel )
{ 
	vdu_audio.channel = channel;
	vdu_audio.CMD = 8;
       	VDP_PUTS( vdu_audio ); 
}
// Command 9: Disable Channel
//  	VDU 23, 0, &85, channel, 9
void vdp_audio_disable_channel( int channel )
{ 
	vdu_audio.channel = channel;
	vdu_audio.CMD = 9;
       	VDP_PUTS( vdu_audio ); 
}
// Command 10: Reset Channel
//  	VDU 23, 0, &85, channel, 10
void vdp_audio_reset_channel( int channel )
{ 
	vdu_audio.channel = channel;
	vdu_audio.CMD = 10;
       	VDP_PUTS( vdu_audio ); 
}
