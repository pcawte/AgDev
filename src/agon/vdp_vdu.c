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
typedef struct { uint8_t A; uint8_t CMD; uint8_t a; uint8_t b; } VDU_A_CMD_a_b;
typedef struct { uint8_t A; uint8_t c; uint8_t r; } VDU_A_c_r;
typedef struct { uint8_t A; uint8_t a; uint8_t b; uint8_t c; uint8_t d; } VDU_A_a_b_c_d;
typedef struct { uint8_t A; uint8_t l; uint8_t p; uint8_t r; uint8_t g; uint8_t b; } VDU_A_l_p_r_g_b;
typedef struct { uint8_t A; uint16_t x; uint16_t y; } VDU_A_x_y;
typedef struct { uint8_t A; uint8_t CMD; uint16_t x; uint16_t y; } VDU_A_CMD_x_y;
typedef struct { uint8_t A; uint8_t B; uint8_t CMD; } VDU_A_B_CMD;
typedef struct { uint8_t A; uint8_t B; uint8_t CMD; uint8_t n; } VDU_A_B_CMD_n;
typedef struct { uint8_t A; uint8_t B; uint8_t CMD; uint16_t x; uint16_t y;
					uint8_t r; uint8_t g; uint8_t b; uint8_t a; } VDU_A_B_CMD_x_y_rgba;
typedef struct { uint8_t A; uint8_t B; uint8_t CMD; uint16_t x; uint16_t y; } VDU_A_B_CMD_x_y;

typedef struct { uint8_t A; uint8_t B; uint8_t CMD; uint8_t b0; } VDU_A_B_CMD_B;
typedef struct { uint8_t A; uint8_t B; uint8_t CMD; uint16_t w0; } VDU_A_B_CMD_W;
typedef struct { uint8_t A; uint8_t B; uint8_t CMD; uint8_t b0; uint16_t w1; } VDU_A_B_CMD_B_W;
typedef struct { uint8_t A; uint8_t B; uint8_t CMD; uint16_t w0; uint16_t w1; uint8_t b2; } VDU_A_B_CMD_W_W_B;
typedef struct { uint8_t A; uint8_t B; uint8_t CMD; uint8_t b0; uint8_t b1; uint8_t b2; uint8_t b3; } VDU_A_B_CMD_B_B_B_B;

typedef struct { uint8_t A; uint8_t B; uint8_t b0; uint8_t b1; uint8_t b2; uint8_t b3; uint8_t b4; uint8_t b5; uint8_t b6; uint8_t b7; } VDU_A_B_ui8x8;
typedef struct { uint8_t A; uint16_t w0; uint16_t w1; uint16_t w2; uint16_t w3; } VDU_A_ui16x4;
typedef struct { uint8_t A; uint8_t B; uint8_t CMD; uint8_t n; uint8_t b0; uint8_t b1; uint8_t b2; uint8_t b3; uint8_t b4; uint8_t b5; uint8_t b6; uint8_t b7; } VDU_A_B_CMD_n_ui8x8;

static volatile SYSVAR *sys_vars = NULL;

volatile SYSVAR *vdp_vdu_init( void )
{
	sys_vars = (SYSVAR *)mos_sysvars();
	return (SYSVAR *)sys_vars;
}

// Basic VDU commands

static VDU_A_n vdu_send_to_printer = { 1, 0 };
static VDU_A vdu_enable_printer = { 2 };
static VDU_A vdu_disable_printer = { 3 };
static VDU_A vdu_write_at_text_cursor = { 4 };
static VDU_A vdu_write_at_graphics_cursor = { 5 };
static VDU_A vdu_enable_screen = { 6 };
static VDU_A vdu_bell = { 7 };
static VDU_A vdu_cursor_left = { 8 };
static VDU_A vdu_cursor_right = { 9 };
static VDU_A vdu_cursor_down = { 10 };
static VDU_A vdu_cursor_up = { 11 };
static VDU_A vdu_clear_screen = { 12 };
static VDU_A vdu_carriage_return = { 13 };
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

void vdp_enable_printer( void ) { VDP_PUTS( vdu_enable_printer ); }
void vdp_disable_printer( void ) { VDP_PUTS( vdu_disable_printer ); }
void vdp_write_at_text_cursor( void ) { VDP_PUTS( vdu_write_at_text_cursor ); }
void vdp_write_at_graphics_cursor( void ) { VDP_PUTS( vdu_write_at_graphics_cursor ); }
void vdp_enable_screen( void ) { VDP_PUTS( vdu_enable_screen ); }
void vdp_bell( void ) { VDP_PUTS( vdu_bell ); }
void vdp_cursor_left( void ) { VDP_PUTS( vdu_cursor_left ); }
void vdp_cursor_right( void ) { VDP_PUTS( vdu_cursor_right ); }
void vdp_cursor_down( void ) { VDP_PUTS( vdu_cursor_down ); }
void vdp_cursor_up( void ) { VDP_PUTS( vdu_cursor_up ); }
void vdp_clear_screen( void ) { VDP_PUTS( vdu_clear_screen ); }
void vdp_carriage_return( void ) { VDP_PUTS( vdu_carriage_return ); }
void vdp_page_mode_on( void ) { VDP_PUTS( vdu_page_mode_on ); }
void vdp_page_mode_off( void ) { VDP_PUTS( vdu_page_mode_off ); }
void vdp_clear_graphics( void ) { VDP_PUTS( vdu_clear_graphics ); }
void vdp_reset_graphics( void ) { VDP_PUTS( vdu_reset_graphics ); }
void vdp_disable_screen( void ) { VDP_PUTS( vdu_disable_screen ); }
void vdp_cursor_home( void ) { VDP_PUTS( vdu_cursor_home ); }

void vdp_send_to_printer( char ch )
{
	vdu_send_to_printer.n = ch;
	VDP_PUTS( vdu_send_to_printer );
}

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
static VDU_A_B_ui8x8 vdu_set_dotted_line_pattern = { 23, 6, 0, 0, 0, 0, 0, 0, 0, 0 };
static VDU_A_a_b_c_d vdu_scroll_screen = { 23, 7, 1, 0, 0};
static VDU_A_CMD_a_b vdu_cursor_behaviour = { 23, 16, 0, 0 };
static VDU_A_CMD_n vdu_set_line_thickness = { 23, 23, 0 };
static VDU_A_B_CMD_n_ui8x8 vdu_redefine_character_special = { 23, 0, 0x90, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static VDU_A_B_CMD_B vdu_define_character = { 23, 0, 0x90, 0 };
static VDU_A_B_CMD vdu_reset_system_font = { 23, 0, 0x91 };
static VDU_A_B_CMD_B_W vdu_map_char_to_bitmap = { 23, 0, 0x92, 0, 0 };
static VDU_A_B_CMD vdu_swap = { 23, 0, 0xC3 };
static VDU_A_B_CMD_B vdu_legacy_modes = { 23, 0, 0xC1, 0 };
static VDU_A_B_CMD vdu_flush_drawing_commands = { 23, 0, 0xCA };
static VDU_A_B_CMD_B vdu_set_dash_pattern_length = { 23, 0, 0xF2, 0 };
static VDU_A_B_CMD_B vdu_console_mode = { 23, 0, 0xFE, 0 };
static VDU_A_B_CMD vdu_terminal_mode = { 23, 0, 0xFF };

void vdp_reset_system_font( void ) { VDP_PUTS( vdu_reset_system_font ); }
void vdp_swap( void ) { VDP_PUTS( vdu_swap ); }
void vdp_flush_drawing_commands( void ) { VDP_PUTS( vdu_flush_drawing_commands ); }
void vdp_terminal_mode( void ) { VDP_PUTS( vdu_terminal_mode ); }

void vdp_redefine_character( int char_num, uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7 )
{
	if ( char_num > 255 ) return;
	if ( char_num < 32 ) vdp_redefine_character_special( char_num, b0, b1, b2, b3, b4, b5, b6, b7 );
	vdu_redefine_character.B = char_num;
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
void vdp_redefine_character_special( int char_num, uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7 )
{
	vdu_redefine_character_special.n = char_num;
	vdu_redefine_character_special.b0 = b0;
	vdu_redefine_character_special.b1 = b1;
	vdu_redefine_character_special.b2 = b2;
	vdu_redefine_character_special.b3 = b3;
	vdu_redefine_character_special.b4 = b4;
	vdu_redefine_character_special.b5 = b5;
	vdu_redefine_character_special.b6 = b6;
	vdu_redefine_character_special.b7 = b7;
	VDP_PUTS( vdu_redefine_character_special );
}
void vdp_define_character( int char_num, uint8_t *data )
{
	if ( !data ) return;
	vdu_define_character.b0 = char_num;
	VDP_PUTS( vdu_define_character );
	mos_puts( (char*)data, 8, 0 );
}
void vdp_map_char_to_bitmap( int char_num, int bitmap_num )
{
	vdu_map_char_to_bitmap.b0 = char_num;
	vdu_map_char_to_bitmap.w1 = bitmap_num;
	VDP_PUTS( vdu_map_char_to_bitmap );
}

void vdp_set_dotted_line_pattern( uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7 )
{
	vdu_set_dotted_line_pattern.b0 = b0;
	vdu_set_dotted_line_pattern.b1 = b1;
	vdu_set_dotted_line_pattern.b2 = b2;
	vdu_set_dotted_line_pattern.b3 = b3;
	vdu_set_dotted_line_pattern.b4 = b4;
	vdu_set_dotted_line_pattern.b5 = b5;
	vdu_set_dotted_line_pattern.b6 = b6;
	vdu_set_dotted_line_pattern.b7 = b7;
	VDP_PUTS( vdu_set_dotted_line_pattern );
}

void vdp_cursor_behaviour( int setting, int mask )
{
	vdu_cursor_behaviour.a = setting;
	vdu_cursor_behaviour.b = mask;
	VDP_PUTS( vdu_cursor_behaviour );
}

void vdp_set_line_thickness( int pixels )
{
	vdu_set_line_thickness.CMD = pixels;
	VDP_PUTS( vdu_set_line_thickness );
}

void vdp_get_scr_dims( bool wait )
{
	if ( !sys_vars ) vdp_vdu_init();
	if ( wait ) sys_vars->vdp_pflags = 0;
	VDP_PUTS( vdu_get_scr_dims );
	// wait for results of mode change to be reflected in SYSVARs
	if ( wait ) while ( !(sys_vars->vdp_pflags & vdp_pflag_mode) );
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
void vdp_legacy_modes( bool on )
{
	vdu_legacy_modes.b0 = on;
	VDP_PUTS( vdu_legacy_modes );
}
void vdp_set_dash_pattern_length( int n )
{
	if ( n > 64 ) return;

	vdu_set_dash_pattern_length.b0 = n;
	VDP_PUTS( vdu_set_dash_pattern_length );
}
void vdp_console_mode( bool on )
{
	vdu_console_mode.b0 = on;
	VDP_PUTS( vdu_console_mode );
}

// viewport commands

static VDU_A vdu_reset_viewports = { 26 };
static VDU_A_ui16x4 vdu_set_graphics_viewport = { 24, 0, 0, 0, 0 };
static VDU_A_n vdu_send_to_screen = { 27, 0 };
static VDU_A_a_b_c_d vdu_set_text_viewport = { 28, 0, 0, 0, 0 };
static VDU_A_B_CMD vdu_set_text_viewport_via_plot = { 23, 0, 0x9C };
static VDU_A_B_CMD vdu_set_graphics_viewport_via_plot = { 23, 0, 0x9C };
static VDU_A_B_CMD vdu_set_graphics_origin_via_plot = { 23, 0, 0x9C };
static VDU_A_B_CMD vdu_move_graphics_origin_and_viewport = { 23, 0, 0x9C };

void vdp_reset_viewports( void ) { VDP_PUTS( vdu_reset_viewports ); }
void vdp_set_text_viewport_via_plot( void ) { VDP_PUTS( vdu_set_text_viewport_via_plot ); }
void vdp_set_graphics_viewport_via_plot( void ) { VDP_PUTS( vdu_set_graphics_viewport_via_plot ); }
void vdp_set_graphics_origin_via_plot( void ) { VDP_PUTS( vdu_set_graphics_origin_via_plot ); }
void vdp_move_graphics_origin_and_viewport( void ) { VDP_PUTS( vdu_move_graphics_origin_and_viewport ); }

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
void vdp_send_to_screen( char ch )
{
	vdu_send_to_screen.n = ch;
	VDP_PUTS( vdu_send_to_screen );
}

static VDU_A_B_CMD_B vdu_set_cursor_start_line = { 23, 0, 0x0A, 0 }; 
static VDU_A_B_CMD_B vdu_set_cursor_end_line = { 23, 0, 0x0B, 0 }; 
static VDU_A_B_CMD_B vdu_set_cursor_start_column = { 23, 0, 0x8A, 0 }; 
static VDU_A_B_CMD_B vdu_set_cursor_end_column = { 23, 0, 0x8B, 0 }; 
static VDU_A_B_CMD vdu_get_text_cursor_position = { 23, 0, 0x82 }; 
static VDU_A_B_CMD_x_y vdu_get_ascii_code_at_position = { 23, 0, 0x83, 0, 0 }; 
static VDU_A_B_CMD_x_y vdu_get_ascii_code_at_graphics_position = { 23, 0, 0x93, 0, 0 }; 
static VDU_A_B_CMD_x_y vdu_get_pixel_colour = { 23, 0, 0x84, 0, 0 }; 
static VDU_A_B_CMD_x_y vdu_move_cursor_relative = { 23, 0, 0x8C, 0, 0 };
static VDU_A_B_CMD_B vdu_request_palette_entry = { 23, 0, 0x94, 0 };

void vdp_set_cursor_start_line( int n )
{
	vdu_set_cursor_start_line.b0 = n;
	VDP_PUTS( vdu_set_cursor_start_line );
}
void vdp_set_cursor_end_line( int n )
{
	vdu_set_cursor_end_line.b0 = n;
	VDP_PUTS( vdu_set_cursor_end_line );
}
void vdp_set_cursor_start_column( int n )
{
	vdu_set_cursor_start_column.b0 = n;
	VDP_PUTS( vdu_set_cursor_start_column );
}
void vdp_set_cursor_end_column( int n )
{
	vdu_set_cursor_end_column.b0 = n;
	VDP_PUTS( vdu_set_cursor_end_column );
}
void vdp_request_text_cursor_position( bool wait )
{
	if ( !sys_vars ) vdp_vdu_init();
	if ( wait ) sys_vars->vdp_pflags = 0;

	VDP_PUTS( vdu_get_text_cursor_position );
	// wait for results to be reflected in SYSVARs
	if ( wait ) while ( !(sys_vars->vdp_pflags & vdp_pflag_cursor) );
}
void vdp_return_text_cursor_position( uint8_t *return_x, uint8_t *return_y )
{
	if ( !sys_vars ) vdp_vdu_init();
	sys_vars->vdp_pflags = 0;

	VDP_PUTS( vdu_get_text_cursor_position );
	while ( !(sys_vars->vdp_pflags & vdp_pflag_cursor) );

	if ( return_x) *return_x = getsysvar_cursorX();
	if ( return_y) *return_y = getsysvar_cursorY();
}

void vdp_request_ascii_code_at_position( int x, int y, bool wait )
{
	if ( !sys_vars ) vdp_vdu_init();
	if ( wait ) sys_vars->vdp_pflags = 0;
	
	vdu_get_ascii_code_at_position.x = x;
	vdu_get_ascii_code_at_position.y = y;
	VDP_PUTS( vdu_get_ascii_code_at_position );
	if ( wait ) while ( !(sys_vars->vdp_pflags & vdp_pflag_scrchar) );
}
uint8_t vdp_return_ascii_code_at_position( int x, int y )
{
	uint8_t code = 0;

	if ( !sys_vars ) vdp_vdu_init();
	sys_vars->vdp_pflags = 0;

	vdu_get_ascii_code_at_position.x = x;
	vdu_get_ascii_code_at_position.y = y;
	VDP_PUTS( vdu_get_ascii_code_at_position );
	while ( !(sys_vars->vdp_pflags & vdp_pflag_scrchar) );

	code = getsysvar_scrchar();
	return code;
}
void vdp_request_ascii_code_at_graphics_position( int x, int y, bool wait )
{
	if ( !sys_vars ) vdp_vdu_init();
	if ( wait ) sys_vars->vdp_pflags = 0;

	vdu_get_ascii_code_at_graphics_position.x = x;
	vdu_get_ascii_code_at_graphics_position.y = y;
	VDP_PUTS( vdu_get_ascii_code_at_graphics_position );
	if ( wait ) while ( !(sys_vars->vdp_pflags & vdp_pflag_scrchar) );
}
uint8_t vdp_return_ascii_code_at_graphics_position( int x, int y )
{
	uint8_t code = 0;

	if ( !sys_vars ) vdp_vdu_init();
	sys_vars->vdp_pflags = 0;

	vdu_get_ascii_code_at_graphics_position.x = x;
	vdu_get_ascii_code_at_graphics_position.y = y;
	VDP_PUTS( vdu_get_ascii_code_at_graphics_position );
	while ( !(sys_vars->vdp_pflags & vdp_pflag_scrchar) );

	code = getsysvar_scrchar();
	return code;
}

void vdp_move_cursor_relative( int x, int y )
{
	vdu_move_cursor_relative.x = x;
	vdu_move_cursor_relative.y = y;
	VDP_PUTS( vdu_move_cursor_relative );
}

void vdp_request_pixel_colour( int x, int y, bool wait )
{
	if ( !sys_vars ) vdp_vdu_init();
	if ( wait ) sys_vars->vdp_pflags = 0;

	vdu_get_pixel_colour.x = x;
	vdu_get_pixel_colour.y = y;
	VDP_PUTS( vdu_get_pixel_colour );
	if ( wait ) while ( !(sys_vars->vdp_pflags & vdp_pflag_point) );
}
uint24_t vdp_return_pixel_colour( int x, int y )
{
	uint24_t pixel = 0;

	if ( !sys_vars ) vdp_vdu_init();
	sys_vars->vdp_pflags = 0;

	vdu_get_pixel_colour.x = x;
	vdu_get_pixel_colour.y = y;
	VDP_PUTS( vdu_get_pixel_colour );
	while ( !(sys_vars->vdp_pflags & vdp_pflag_point) );

	pixel = getsysvar_scrpixel();
	return pixel;
}
void vdp_request_palette_entry( int n, bool wait )
{
	if ( !sys_vars ) vdp_vdu_init();
	if ( wait ) sys_vars->vdp_pflags = 0;

	vdu_request_palette_entry.b0 = n;
	VDP_PUTS( vdu_request_palette_entry );

	if ( wait ) while ( !(sys_vars->vdp_pflags & vdp_pflag_point) );
}
uint24_t vdp_return_palette_entry_colour( int n )
{
	uint24_t pixel = 0;
	if ( !sys_vars ) vdp_vdu_init();
	sys_vars->vdp_pflags = 0;

	vdu_request_palette_entry.b0 = n;
	VDP_PUTS( vdu_request_palette_entry );

	while ( !(sys_vars->vdp_pflags & vdp_pflag_point) );
	pixel = getsysvar_scrpixel();
	return pixel;
}
uint8_t vdp_return_palette_entry_index( int n )
{
	uint8_t index = 0;
	if ( !sys_vars ) vdp_vdu_init();
	sys_vars->vdp_pflags = 0;

	vdu_request_palette_entry.b0 = n;
	VDP_PUTS( vdu_request_palette_entry );

	while ( !(sys_vars->vdp_pflags & vdp_pflag_point) );
	index = getsysvar_scrpixelIndex();
	return index;
}


static VDU_A_B_CMD_B vdu_set_keyboard_locale = { 23, 0, 0x81, 0 }; 
static VDU_A_B_CMD_n vdu_get_rtc = { 23, 0, 0x87, 0 }; 
static VDU_A_B_ui8x8 vdu_set_rtc = { 23, 0, 0x87, 1, 0, 0, 0, 0, 0, 0 };
static VDU_A_B_CMD_W_W_B vdu_keyboard_cotrol = { 23, 0, 0x88, 0, 0, 0 };
static VDU_A_B_CMD_B vdu_control_keys = { 23, 0, 0x98, 0 };

void vdp_set_keyboard_locale( int locale )
{
	vdu_set_keyboard_locale.b0 = locale;
	VDP_PUTS( vdu_set_keyboard_locale );
}
void vdp_request_rtc( bool wait )
{
	if ( !sys_vars ) vdp_vdu_init();
	if ( wait ) sys_vars->vdp_pflags = 0;
	VDP_PUTS( vdu_get_rtc );
	if ( wait ) while ( !(sys_vars->vdp_pflags & vdp_pflag_rtc) );
}
void vdp_set_rtc( int year, int month, int day, int hours, int minutes, int seconds )
{
	vdu_set_rtc.b2 = year;
	vdu_set_rtc.b3 = month;
	vdu_set_rtc.b4 = day;
	vdu_set_rtc.b5 = hours;
	vdu_set_rtc.b6 = minutes;
	vdu_set_rtc.b7 = seconds;
	VDP_PUTS( vdu_set_rtc );
}
void vdp_keyboard_cotrol( int delay, int rate, int led )
{
	vdu_keyboard_cotrol.w0 = delay;
	vdu_keyboard_cotrol.w1 = rate;
	vdu_keyboard_cotrol.b2 = led;
	VDP_PUTS( vdu_keyboard_cotrol );
}
void vdp_control_keys( bool on )
{
	vdu_control_keys.b0 = on;
	VDP_PUTS( vdu_control_keys );
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
static VDU_A_B_CMD vdu_sprite_only_reset = { 23, 27, 17 };
static VDU_A_B_CMD_n vdu_set_sprite_paint_mode = { 23, 27, 18, 0 };


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
	VDP_PUTS( vdu_sprite_activate );
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

void vdp_reset_sprites_only( void )
{
	VDP_PUTS( vdu_sprite_only_reset );
}

void vdp_set_sprite_paint_mode( int n )
{
	vdu_set_sprite_paint_mode.n = n;
	VDP_PUTS( vdu_set_sprite_paint_mode );
}

/* Advanced buffered commands  */
typedef struct { uint8_t A; uint8_t B; uint8_t C; uint16_t BID; uint8_t CMD; } VDU_ADV_CMD;
typedef struct { uint8_t A; uint8_t B; uint8_t C; uint16_t BID; uint8_t CMD; uint8_t b0; } VDU_ADV_CMD_B;
typedef struct { uint8_t A; uint8_t B; uint8_t C; uint16_t BID; uint8_t CMD; uint16_t w0; } VDU_ADV_CMD_W;
typedef struct { uint8_t A; uint8_t B; uint8_t C; uint16_t BID; uint8_t CMD; uint16_t w0; uint16_t w1; } VDU_ADV_CMD_W_W;
typedef struct { uint8_t A; uint8_t B; uint8_t C; uint16_t BID; uint8_t CMD; uint16_t w0; uint16_t w1; uint16_t w2; } VDU_ADV_CMD_W_W_W;
typedef struct { uint8_t A; uint8_t B; uint8_t C; uint16_t BID; uint8_t CMD; uint8_t b0; uint16_t w1; } VDU_ADV_CMD_B_W;
typedef struct { uint8_t A; uint8_t B; uint8_t C; uint16_t BID; uint8_t CMD; uint8_t b0; uint16_t w1; uint16_t w2; } VDU_ADV_CMD_B_W_W;
typedef struct { uint8_t A; uint8_t B; uint8_t C; uint16_t BID; uint8_t CMD; uint24_t ww0; } VDU_ADV_CMD_WW;
typedef struct { uint8_t A; uint8_t B; uint8_t C; uint16_t BID; uint8_t CMD; uint24_t ww0; uint16_t w1; } VDU_ADV_CMD_WW_W;

static VDU_ADV_CMD_W    vdu_adv_write_block  = { 23, 0, 0xA0, 0xFA00, 0, 0 };
static VDU_ADV_CMD      vdu_adv_call_buffer  = { 23, 0, 0xA0, 0xFA00, 1 };
static VDU_ADV_CMD      vdu_adv_clear_buffer = { 23, 0, 0xA0, 0xFA00, 2 };
static VDU_ADV_CMD_W    vdu_adv_create       = { 23, 0, 0xA0, 0xFA00, 3, 0 };
static VDU_ADV_CMD      vdu_adv_stream       = { 23, 0, 0xA0, 0xFA00, 4 };
static VDU_ADV_CMD_B_W  vdu_adv_adjust       = { 23, 0, 0xA0, 0xFA00, 5, 0, 0 };
static VDU_ADV_CMD_B_W_W vdu_adv_call_conditional = { 23, 0, 0xA0, 0xFA00, 6, 0, 0, 0 };
static VDU_ADV_CMD_WW   vdu_adv_jump_offset  = { 23, 0, 0xA0, 0xFA00, 9, 0 };
static VDU_ADV_CMD_WW_W vdu_adv_jump_offset_block = { 23, 0, 0xA0, 0xFA00, 9, 0, 0 };
static VDU_ADV_CMD      vdu_adv_copy_multiple = { 23, 0, 0xA0, 0xFA00, 13 };
static VDU_ADV_CMD      vdu_adv_consolidate  = { 23, 0, 0xA0, 0xFA00, 14 };
static VDU_ADV_CMD_W    vdu_adv_split        = { 23, 0, 0xA0, 0xFA00, 15, 0 };
static VDU_ADV_CMD_W    vdu_adv_split_multiple  = { 23, 0, 0xA0, 0xFA00, 16, 0 };
static VDU_ADV_CMD_W_W  vdu_adv_split_multiple_from = { 23, 0, 0xA0, 0xFA00, 17, 0, 0 };
static VDU_ADV_CMD_W_W  vdu_adv_split_by_width = { 23, 0, 0xA0, 0xFA00, 18, 0, 0 };
static VDU_ADV_CMD_W    vdu_adv_split_by_width_multiple = { 23, 0, 0xA0, 0xFA00, 19, 0 };
static VDU_ADV_CMD_W_W_W vdu_adv_split_by_width_multiple_from = { 23, 0, 0xA0, 0xFA00, 20, 0, 0, 0 };
static VDU_ADV_CMD      vdu_adv_spread_multiple = { 23, 0, 0xA0, 0xFA00, 21 };
static VDU_ADV_CMD_W    vdu_adv_spread_multiple_from = { 23, 0, 0xA0, 0xFA00, 22, 0 };
static VDU_ADV_CMD      vdu_adv_reverse_block_order  = { 23, 0, 0xA0, 0xFA00, 23 };
static VDU_ADV_CMD_B    vdu_adv_reverse_block_data  = { 23, 0, 0xA0, 0xFA00, 24, 0 };
static VDU_ADV_CMD_B_W  vdu_adv_reverse_block_data_add1  = { 23, 0, 0xA0, 0xFA00, 24, 0, 0 };
static VDU_ADV_CMD_B_W_W vdu_adv_reverse_block_data_add2  = { 23, 0, 0xA0, 0xFA00, 24, 0, 0, 0 };
static VDU_ADV_CMD      vdu_adv_copy_multiple_by_reference = { 23, 0, 0xA0, 0xFA00, 25 };
static VDU_ADV_CMD      vdu_adv_copy_multiple_consolidate = { 23, 0, 0xA0, 0xFA00, 26 };
static VDU_ADV_CMD_W    vdu_adv_compress_buffer = { 23, 0, 0xA0, 0xFA00, 64, 0 };
static VDU_ADV_CMD_W    vdu_adv_decompress_buffer = { 23, 0, 0xA0, 0xFA00, 65, 0 };

// VDU 23,27 - extended commands for bufferIds 
static VDU_A_B_CMD_W	vdu_adv_select_bitmap = { 23, 27, 0x20, 0xFA00 };
static VDU_A_B_CMD_W_W_B vdu_adv_bitmap_from_buffer = { 23, 27, 0x21, 0, 0, 0 };
static VDU_A_B_CMD_W	vdu_adv_add_sprite_bitmap = { 23, 27, 0x26, 0xFA00 };

void vdp_adv_write_block( int bufferID, int length )
{
	vdu_adv_write_block.BID = bufferID;
	vdu_adv_write_block.w0 = length;
	VDP_PUTS( vdu_adv_write_block );
}
void vdp_adv_write_block_data( int bufferID, int length, char *data )
{
	vdu_adv_write_block.BID = bufferID;
	vdu_adv_write_block.w0 = length;
	VDP_PUTS( vdu_adv_write_block );
	mos_puts( data, length, 0 );
}

void vdp_adv_clear_buffer( int bufferID )
{
	vdu_adv_clear_buffer.BID = bufferID;
	VDP_PUTS( vdu_adv_clear_buffer );
}

void vdp_adv_create( int bufferID, int length )
{
	vdu_adv_create.BID = bufferID;
	vdu_adv_create.w0 = length;
	VDP_PUTS( vdu_adv_create );
}

void vdp_adv_stream( int bufferID )
{
	vdu_adv_stream.BID = bufferID;
	VDP_PUTS(vdu_adv_stream);
}

/* Adjust - pass the necessary arguments this must then be followed
 * by data appropriate for the operation selected */
void vdp_adv_adjust( int bufferID, int operation, int offset )
{
	vdu_adv_adjust.BID = bufferID;
	vdu_adv_adjust.b0 = operation;
	vdu_adv_adjust.w1 = offset;
	VDP_PUTS( vdu_adv_adjust );
}

void vdp_adv_call_buffer( int bufferID )
{
	vdu_adv_call_buffer.CMD = 1;
	vdu_adv_call_buffer.BID = bufferID;
	VDP_PUTS( vdu_adv_call_buffer );
}

void vdp_adv_call_conditional( int bufferId, int operation, int checkBufferId, int checkOffset )
{
	vdu_adv_call_conditional.CMD = 6;
	vdu_adv_call_conditional.BID = bufferId;
	vdu_adv_call_conditional.b0 = operation;
	vdu_adv_call_conditional.w1 = checkBufferId;
	vdu_adv_call_conditional.w2 = checkOffset;
	VDP_PUTS( vdu_adv_call_conditional );
}

void vdp_adv_jump_buffer( int bufferID )
{
	vdu_adv_call_buffer.CMD = 7;
	vdu_adv_call_buffer.BID = bufferID;
	VDP_PUTS( vdu_adv_call_buffer );
}

void vdp_adv_jump_conditional( int bufferId, int operation, int checkBufferId, int checkOffset )
{
	vdu_adv_call_conditional.CMD = 8;
	vdu_adv_call_conditional.BID = bufferId;
	vdu_adv_call_conditional.b0 = operation;
	vdu_adv_call_conditional.w1 = checkBufferId;
	vdu_adv_call_conditional.w2 = checkOffset;
	VDP_PUTS( vdu_adv_call_conditional );
}

void vdp_adv_jump_offset( int bufferId, int offset )
{
	if ( offset & (1<<23) ) return; // if top bit is set, expect a block
	vdu_adv_jump_offset.CMD = 9;
	vdu_adv_jump_offset.BID = bufferId;
	vdu_adv_jump_offset.ww0 = offset;
	VDP_PUTS( vdu_adv_jump_offset );
}
void vdp_adv_jump_offset_block( int bufferId, int offset, int block )
{
	if ( ! (offset & (1<<23) ) ) return; // expect top bit set
	vdu_adv_jump_offset.CMD = 9;
	vdu_adv_jump_offset_block.BID = bufferId;
	vdu_adv_jump_offset_block.ww0 = offset;
	vdu_adv_jump_offset_block.w1 = block;
	VDP_PUTS( vdu_adv_jump_offset_block );
}

void vdp_adv_jump_offset_conditional( int bufferId, int offset )
{
	if ( offset & (1<<23) ) return; // if top bit is set, expect a block
	vdu_adv_jump_offset.CMD = 10;
	vdu_adv_jump_offset.BID = bufferId;
	vdu_adv_jump_offset.ww0 = offset;
	VDP_PUTS( vdu_adv_jump_offset );
}
void vdp_adv_jump_offset_block_conditional( int bufferId, int offset, int block )
{
	if ( ! (offset & (1<<23) ) ) return; // expect top bit set
	vdu_adv_jump_offset.CMD = 10;
	vdu_adv_jump_offset_block.BID = bufferId;
	vdu_adv_jump_offset_block.ww0 = offset;
	vdu_adv_jump_offset_block.w1 = block;
	VDP_PUTS( vdu_adv_jump_offset_block );
}

void vdp_adv_call_offset( int bufferId, int offset )
{
	if ( offset & (1<<23) ) return; // if top bit is set, expect a block
	vdu_adv_jump_offset.CMD = 11;
	vdu_adv_jump_offset.BID = bufferId;
	vdu_adv_jump_offset.ww0 = offset;
	VDP_PUTS( vdu_adv_jump_offset );
}
void vdp_adv_call_offset_block( int bufferId, int offset, int block )
{
	if ( ! (offset & (1<<23) ) ) return; // expect top bit set
	vdu_adv_jump_offset.CMD = 11;
	vdu_adv_jump_offset_block.BID = bufferId;
	vdu_adv_jump_offset_block.ww0 = offset;
	vdu_adv_jump_offset_block.w1 = block;
	VDP_PUTS( vdu_adv_jump_offset_block );
}

void vdp_adv_call_offset_conditional( int bufferId, int offset )
{
	if ( offset & (1<<23) ) return; // if top bit is set, expect a block
	vdu_adv_jump_offset.CMD = 12;
	vdu_adv_jump_offset.BID = bufferId;
	vdu_adv_jump_offset.ww0 = offset;
	VDP_PUTS( vdu_adv_jump_offset );
}

void vdp_adv_call_offset_block_conditional( int bufferId, int offset, int block )
{
	if ( ! (offset & (1<<23) ) ) return; // expect top bit set
	vdu_adv_jump_offset.CMD = 12;
	vdu_adv_jump_offset_block.BID = bufferId;
	vdu_adv_jump_offset_block.ww0 = offset;
	vdu_adv_jump_offset_block.w1 = block;
	VDP_PUTS( vdu_adv_jump_offset_block );
}

// can make this a var args command as arguments are all 16-bit
void vdp_adv_copy_multiple( int bufferId, int num_buffers, ... )
{
	va_list args;
	uint16_t buffer_list[num_buffers+1];
	vdu_adv_copy_multiple.BID = bufferId;
	va_start( args, num_buffers );
	for (int b = 0; b < num_buffers; b++)
	{
		buffer_list[b] = va_arg( args, int );
	}
	va_end( args );
	buffer_list[num_buffers] = -1; // Terminate the list
	VDP_PUTS( vdu_adv_copy_multiple );
	mos_puts( (char*)buffer_list, (num_buffers+1)*2, 0 );
}

void vdp_adv_consolidate( int bufferID )
{
	vdu_adv_consolidate.BID = bufferID;
	VDP_PUTS( vdu_adv_consolidate );
}

void vdp_adv_split( int bufferID, int blockSize )
{
	vdu_adv_split.BID = bufferID;
	vdu_adv_split.w0 = blockSize;
	VDP_PUTS( vdu_adv_split );
}

// can make this a var args command as arguments are all 16-bit
void vdp_adv_split_multiple( int bufferId, int blockSize, int num_buffers, ... )
{
	va_list args;
	uint16_t buffer_list[num_buffers+1];
	vdu_adv_split_multiple.BID = bufferId;
	vdu_adv_split_multiple.w0 = blockSize;
	va_start( args, num_buffers );
	for (int b = 0; b < num_buffers; b++)
	{
		buffer_list[b] = va_arg( args, int );
	}
	va_end( args );
	buffer_list[num_buffers] = -1; // Terminate the list
	VDP_PUTS( vdu_adv_split_multiple );
	mos_puts( (char*)buffer_list, (num_buffers+1)*2, 0 );
}

void vdp_adv_split_multiple_from( int bufferID, int blockSize, int targetBufferID )
{
	vdu_adv_split_multiple_from.BID = bufferID;
	vdu_adv_split_multiple_from.w0 = blockSize;
	vdu_adv_split_multiple_from.w1 = targetBufferID;
	VDP_PUTS( vdu_adv_split_multiple_from );
}

void vdp_adv_split_by_width( int bufferID, int width, int blockCount )
{
	vdu_adv_split_by_width.BID = bufferID;
	vdu_adv_split_by_width.w0 = width;
	vdu_adv_split_by_width.w1 = blockCount;
	VDP_PUTS( vdu_adv_split_by_width );
}

void vdp_adv_split_by_width_multiple( int bufferId, int width, int num_buffers, ... )
{
	va_list args;
	uint16_t buffer_list[num_buffers+1];
	vdu_adv_split_by_width_multiple.BID = bufferId;
	vdu_adv_split_by_width_multiple.w0 = width;
	va_start( args, num_buffers );
	for (int b = 0; b < num_buffers; b++)
	{
		buffer_list[b] = va_arg( args, int );
	}
	va_end( args );
	buffer_list[num_buffers] = -1; // Terminate the list
	VDP_PUTS( vdu_adv_split_by_width_multiple );
	mos_puts( (char*)buffer_list, (num_buffers+1)*2, 0 );
}

void vdp_adv_split_by_width_multiple_from( int bufferID, int width, int blockCount, int targetBufferID )
{
	vdu_adv_split_by_width_multiple_from.BID = bufferID;
	vdu_adv_split_by_width_multiple_from.w0 = width;
	vdu_adv_split_by_width_multiple_from.w1 = blockCount;
	vdu_adv_split_by_width_multiple_from.w2 = targetBufferID;
	VDP_PUTS( vdu_adv_split_by_width_multiple_from );
}

void vdp_adv_spread_multiple( int bufferId, int num_buffers, ... )
{
	va_list args;
	uint16_t buffer_list[num_buffers+1];
	vdu_adv_spread_multiple.BID = bufferId;
	va_start( args, num_buffers );
	for (int b = 0; b < num_buffers; b++)
	{
		buffer_list[b] = va_arg( args, int );
	}
	va_end( args );
	buffer_list[num_buffers] = -1; // Terminate the list
	VDP_PUTS( vdu_adv_spread_multiple );
	mos_puts( (char*)buffer_list, (num_buffers+1)*2, 0 );
}

void vdp_adv_spread_multiple_from( int bufferID, int targetBufferID )
{
	vdu_adv_spread_multiple_from.BID = bufferID;
	vdu_adv_spread_multiple_from.w0 = targetBufferID;
	VDP_PUTS( vdu_adv_spread_multiple_from );
}

void vdp_adv_reverse_block_order( int bufferID )
{
	vdu_adv_reverse_block_order.BID = bufferID;
	VDP_PUTS( vdu_adv_reverse_block_order );
}

// note valueSize and chunkSize are only used for certain values of options
void vdp_adv_reverse_block_data( int bufferID, int options, int valueSize, int chunkSize )
{
	bool need_valueSize = false;
	bool need_chunkSize = false;
	if ( ( options | 0x3 ) == 0x3 ) need_valueSize = true;
	if ( ( options | 0x4 ) == 0x4 ) need_chunkSize = true;

	if ( !need_valueSize && !need_chunkSize )
	{
		vdu_adv_reverse_block_data.BID = bufferID;
		vdu_adv_reverse_block_data.b0 = options;
		VDP_PUTS( vdu_adv_reverse_block_data );
	} else if ( need_valueSize && !need_chunkSize  ) {
		vdu_adv_reverse_block_data_add1.BID = bufferID;
		vdu_adv_reverse_block_data_add1.b0 = options;
		vdu_adv_reverse_block_data_add1.w1 = valueSize;
		VDP_PUTS( vdu_adv_reverse_block_data_add1 );
	} else if ( !need_valueSize && need_chunkSize  ) {
		vdu_adv_reverse_block_data_add1.BID = bufferID;
		vdu_adv_reverse_block_data_add1.b0 = options;
		vdu_adv_reverse_block_data_add1.w1 = chunkSize;
		VDP_PUTS( vdu_adv_reverse_block_data_add1 );
	} else { // need both
		vdu_adv_reverse_block_data_add2.BID = bufferID;
		vdu_adv_reverse_block_data_add2.b0 = options;
		vdu_adv_reverse_block_data_add2.w1 = valueSize;
		vdu_adv_reverse_block_data_add2.w2 = chunkSize;
		VDP_PUTS( vdu_adv_reverse_block_data_add2 );
	}
}

void vdp_adv_copy_multiple_by_reference( int bufferId, int num_buffers, ... )
{
	va_list args;
	uint16_t buffer_list[num_buffers+1];
	vdu_adv_copy_multiple_by_reference.BID = bufferId;
	va_start( args, num_buffers );
	for (int b = 0; b < num_buffers; b++)
	{
		buffer_list[b] = va_arg( args, int );
	}
	va_end( args );
	buffer_list[num_buffers] = -1; // Terminate the list
	VDP_PUTS( vdu_adv_copy_multiple_by_reference );
	mos_puts( (char*)buffer_list, (num_buffers+1)*2, 0 );
}

void vdp_adv_copy_multiple_consolidate( int bufferId, int num_buffers, ... )
{
	va_list args;
	uint16_t buffer_list[num_buffers+1];
	vdu_adv_copy_multiple_consolidate.BID = bufferId;
	va_start( args, num_buffers );
	for (int b = 0; b < num_buffers; b++)
	{
		buffer_list[b] = va_arg( args, int );
	}
	va_end( args );
	buffer_list[num_buffers] = -1; // Terminate the list
	VDP_PUTS( vdu_adv_copy_multiple_consolidate );
	mos_puts( (char*)buffer_list, (num_buffers+1)*2, 0 );
}

void vdp_adv_compress_buffer( int targetBufferID, int sourceBufferId )
{
	vdu_adv_compress_buffer.BID = targetBufferID;
	vdu_adv_compress_buffer.w0 = sourceBufferId;
	VDP_PUTS( vdu_adv_compress_buffer );
}

void vdp_adv_decompress_buffer( int targetBufferID, int sourceBufferId )
{
	vdu_adv_decompress_buffer.BID = targetBufferID;
	vdu_adv_decompress_buffer.w0 = sourceBufferId;
	VDP_PUTS( vdu_adv_decompress_buffer );
}


void vdp_adv_select_bitmap( int bufferID )
{
	vdu_adv_select_bitmap.w0 = bufferID;
	VDP_PUTS( vdu_adv_select_bitmap );
}

void vdp_adv_bitmap_from_buffer( int width, int height, int format )
{
	vdu_adv_bitmap_from_buffer.w0 = width;
	vdu_adv_bitmap_from_buffer.w1 = height;
	vdu_adv_bitmap_from_buffer.b2 = format;
	VDP_PUTS( vdu_adv_bitmap_from_buffer );
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
void vdp_adv_add_sprite_bitmap( int bitmap_num )
{
	vdu_adv_add_sprite_bitmap.w0 = bitmap_num;
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
	VDP_PUTS( vdu_sprite_activate );
}

// ========= Audio API =========
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
// Command 11: Seek to position
// 	VDU 23, 0, &85, channel, 11, position; positionHighByte
// Command 12: Set duration
// 	VDU 23, 0, &85, channel, 12, duration; durationHighByte
// Command 13: Set sample rate
// 	VDU 23, 0, &85, channel, 13, sampleRate;
// Command 14: Set channel waveform parameters
// 	VDU 23, 0, &85, channel, 14, parameter, value
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
typedef struct { uint8_t A; uint8_t B; uint8_t C; uint8_t channel; uint8_t CMD; uint24_t ww1; } VDU_AUDIO_CMD_WW;
typedef struct { uint8_t A; uint8_t B; uint8_t C; uint8_t channel; uint8_t CMD; uint8_t b1; uint8_t b2; } VDU_AUDIO_CMD_B_B;

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
static VDU_AUDIO_CMD_WW vdu_audio_ww = { 23, 0, 0x85, 0, 0, 0 };
static VDU_AUDIO_CMD_B_B vdu_audio_b_b = { 23, 0, 0x85, 0, 0, 0, 0 };

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

// Command 11: Seek to position
// 	VDU 23, 0, &85, channel, 11, position; positionHighByte
void vdp_audio_sample_seek( int channel, int position )
{
	vdu_audio_ww.channel = channel;
	vdu_audio_ww.CMD = 11;
	vdu_audio_ww.ww1 = position;
       	VDP_PUTS( vdu_audio_ww ); 
}

// Command 12: Set duration
// 	VDU 23, 0, &85, channel, 12, duration; durationHighByte
void vdp_audio_sample_duration( int channel, int duration )
{
	vdu_audio_ww.channel = channel;
	vdu_audio_ww.CMD = 12;
	vdu_audio_ww.ww1 = duration;
       	VDP_PUTS( vdu_audio_ww ); 
}

// Command 13: Set sample rate
// 	VDU 23, 0, &85, channel, 13, sampleRate;
void vdp_audio_sample_rate( int channel, int rate )
{
	vdu_audio_w.channel = channel;
	vdu_audio_w.CMD = 13;
	vdu_audio_w.w1 = rate;
       	VDP_PUTS( vdu_audio_w ); 
}

// Command 14: Set channel waveform parameters
// 	VDU 23, 0, &85, channel, 14, parameter, value
void vdp_audio_set_waveform_parameter( int channel, int parameter, int value )
{
	if ( parameter & 0x80 )
	{
		// send 16-bit value
		vdu_audio_b_w.channel = channel;
		vdu_audio_b_w.CMD = 14;
		vdu_audio_b_w.b1 = parameter;
		vdu_audio_b_w.w2 = value;
		VDP_PUTS( vdu_audio_b_w ); 

	} else {
		// send 8-bit value
		vdu_audio_b_b.channel = channel;
		vdu_audio_b_b.CMD = 14;
		vdu_audio_b_b.b1 = parameter;
		vdu_audio_b_b.b2 = value;
		VDP_PUTS( vdu_audio_b_b ); 
	}
}


// ========= Font Management =========
// VDU 23, 0, &95: Font management
// VDU 23, 0, &95, 0, bufferId; flags: Select font
// VDU 23, 0, &95, 1, bufferId; width, height, ascent, flags: Create font from buffer
// VDU 23, 0, &95, 2, bufferId; field, value;: Set or adjust font property
// VDU 23, 0, &95, 3, bufferId; [<args>]: Reserved
// VDU 23, 0, &95, 4, bufferId;: Clear/Delete font
// VDU 23, 0, &95, 5, bufferId;: Copy system font to buffer

typedef struct { uint8_t A; uint8_t B; uint8_t CMD; uint8_t SUBCMD; uint16_t buffer_id; } VDU_FONT;
typedef struct { uint8_t A; uint8_t B; uint8_t CMD; uint8_t SUBCMD; uint16_t buffer_id;  uint8_t b0; uint8_t b1; } VDU_FONT_B_B;
typedef struct { uint8_t A; uint8_t B; uint8_t CMD; uint8_t SUBCMD; uint16_t buffer_id;  uint8_t b0; uint8_t b1; uint8_t b2; uint8_t b3; } VDU_FONT_B_B_B_B;

static VDU_FONT vdu_font_select = { 23, 0, 0x95, 0, 0 };
static VDU_FONT_B_B_B_B vdu_font_create = { 23, 0, 0x95, 1, 0, 0, 0, 0, 0 };
static VDU_FONT_B_B vdu_font_set_property = { 23, 0, 0x95, 2, 0, 0, 0 };
static VDU_FONT vdu_font_delete = { 23, 0, 0x95, 4, 0 };
static VDU_FONT vdu_font_copy   = { 23, 0, 0x95, 5, 0 };
void vdp_font_select( int buffer_id )
{
	vdu_font_select.buffer_id = buffer_id;
	VDP_PUTS( vdu_font_select );
}
void vdp_font_create( int buffer_id, int width, int height, int ascent, int flags )
{
	vdu_font_create.buffer_id = buffer_id;
	vdu_font_create.b0 = width;
	vdu_font_create.b1 = height;
	vdu_font_create.b2 = ascent;
	vdu_font_create.b3 = flags;
	VDP_PUTS( vdu_font_create );
}
void vdp_font_set_property( int buffer_id, int field, int value )
{
	vdu_font_set_property.buffer_id = buffer_id;
	vdu_font_set_property.b0 = field;
	vdu_font_set_property.b1 = value;
	VDP_PUTS( vdu_font_set_property );
}
void vdp_font_delete( int buffer_id )
{
	vdu_font_delete.buffer_id = buffer_id;
	VDP_PUTS( vdu_font_delete );
}
void vdp_font_copy( int buffer_id )
{
	vdu_font_copy.buffer_id = buffer_id;
	VDP_PUTS( vdu_font_copy );
}


// ========= Context Management =========
// VDU 23, 0, &C8, 0, contextId: Select context stack
// VDU 23, 0, &C8, 1, contextId: Delete context stack
// VDU 23, 0, &C8, 2, flags: Reset
// VDU 23, 0, &C8, 3: Save context
// VDU 23, 0, &C8, 4: Restore context
// VDU 23, 0, &C8, 5, contextId: Save and select a copy of a context
// VDU 23, 0, &C8, 6: Restore all
// VDU 23, 0, &C8, 7: Clear stack

typedef struct { uint8_t A; uint8_t B; uint8_t CMD; uint8_t SUBCMD; } VDU_CONTEXT;
typedef struct { uint8_t A; uint8_t B; uint8_t CMD; uint8_t SUBCMD; uint8_t b0; } VDU_CONTEXT_B;

static VDU_CONTEXT_B vdu_context_select = { 23, 0, 0xC8, 0, 0 };
static VDU_CONTEXT_B vdu_context_delete = { 23, 0, 0xC8, 1, 0 };
static VDU_CONTEXT_B vdu_context_reset = { 23, 0, 0xC8, 2, 0 };
static VDU_CONTEXT vdu_context_save = { 23, 0, 0xC8, 3 };
static VDU_CONTEXT vdu_context_restore = { 23, 0, 0xC8, 4 };
static VDU_CONTEXT_B vdu_context_save_copy = { 23, 0, 0xC8, 5, 0 };
static VDU_CONTEXT vdu_context_restore_all = { 23, 0, 0xC8, 6 };
static VDU_CONTEXT vdu_context_clear_stack = { 23, 0, 0xC8, 7 };

void vdp_context_select( int context_id )
{
	vdu_context_select.b0 = context_id;
	VDP_PUTS( vdu_context_select );
}

void vdp_context_delete( int context_id )
{
	vdu_context_delete.b0 = context_id;
	VDP_PUTS( vdu_context_delete );
}

void vdp_context_reset( int flags )
{
	vdu_context_reset.b0 = flags;
	VDP_PUTS( vdu_context_reset );
}

void vdp_context_save( void )
{
	VDP_PUTS( vdu_context_save );
}

void vdp_context_restore( void )
{
	VDP_PUTS( vdu_context_restore );
}

void vdp_context_save_copy( int context_id )
{
	vdu_context_save_copy.b0 = context_id;
	VDP_PUTS( vdu_context_save_copy );
}

void vdp_context_restore_all( void )
{
	VDP_PUTS( vdu_context_restore_all );
}

void vdp_context_clear_stack( void )
{
	VDP_PUTS( vdu_context_clear_stack );
}

// ========= Mouse Control =========
// VDU 23, 0, &89, command, [<args>]: Mouse control
// 	VDU 23, 0, &89, 0: Enable the mouse
// 	VDU 23, 0, &89, 1: Disable the mouse
// 	VDU 23, 0, &89, 2: Reset the mouse
// 	VDU 23, 0, &89, 3, cursorId;: Set mouse cursor
// 	VDU 23, 0, &89, 4, x; y;: Set mouse cursor position
// 	VDU 23, 0, &89, 5, x1; y1; x2; y2;: Reserved
// 	VDU 23, 0, &89, 6, sampleRate: Set mouse sample rate
// 	VDU 23, 0, &89, 7, resolution: Set mouse resolution
// 	VDU 23, 0, &89, 8, scaling: Set mouse scaling
// 	VDU 23, 0, &89, 9, acceleration;: Set mouse acceleration
// 	VDU 23, 0, &89, 10, wheelAcceleration; wheelAccHighByte: Set mouse wheel acceleration (accepts a 24-bit value)

typedef struct { uint8_t A; uint8_t B; uint8_t CMD; uint8_t SUBCMD; } VDU_MOUSE;
typedef struct { uint8_t A; uint8_t B; uint8_t CMD; uint8_t SUBCMD; uint16_t w0; } VDU_MOUSE_W;
typedef struct { uint8_t A; uint8_t B; uint8_t CMD; uint8_t SUBCMD; uint16_t w0; uint16_t w1; } VDU_MOUSE_W_W;
typedef struct { uint8_t A; uint8_t B; uint8_t CMD; uint8_t SUBCMD; uint8_t b0; } VDU_MOUSE_B;
typedef struct { uint8_t A; uint8_t B; uint8_t CMD; uint8_t SUBCMD; uint24_t ww0; } VDU_MOUSE_WW;

static VDU_MOUSE      vdu_mouse_enable       = { 23, 0, 0x89, 0 };
static VDU_MOUSE      vdu_mouse_disable      = { 23, 0, 0x89, 1 };
static VDU_MOUSE      vdu_mouse_reset        = { 23, 0, 0x89, 2 };
static VDU_MOUSE_W    vdu_mouse_set_cursor   = { 23, 0, 0x89, 3, 0 };
static VDU_MOUSE_W_W  vdu_mouse_set_position = { 23, 0, 0x89, 4, 0, 0 };
static VDU_MOUSE_B    vdu_mouse_sample_rate  = { 23, 0, 0x89, 6, 0 };
static VDU_MOUSE_B    vdu_mouse_resolution   = { 23, 0, 0x89, 7, 0 };
static VDU_MOUSE_B    vdu_mouse_scaling      = { 23, 0, 0x89, 8, 0 };
static VDU_MOUSE_W    vdu_mouse_acceleration = { 23, 0, 0x89, 9, 0 };
static VDU_MOUSE_WW   vdu_mouse_wheel_accel  = { 23, 0, 0x89, 10, 0 };


void vdp_mouse_enable( void ) { VDP_PUTS( vdu_mouse_enable ); }
void vdp_mouse_disable( void ) { VDP_PUTS( vdu_mouse_disable ); }
void vdp_mouse_reset( void ) { VDP_PUTS( vdu_mouse_reset ); }

void vdp_mouse_set_cursor( int cursorId )
{
	vdu_mouse_set_cursor.w0 = cursorId;
	VDP_PUTS( vdu_mouse_set_cursor );
}

void vdp_mouse_set_position( int X, int Y )
{
	vdu_mouse_set_position.w0 = X;
	vdu_mouse_set_position.w1 = Y;
	VDP_PUTS( vdu_mouse_set_position );
}

void vdp_mouse_sample_rate( int sampleRate )
{
	vdu_mouse_sample_rate.b0 = sampleRate;
	VDP_PUTS( vdu_mouse_sample_rate );
}

void vdp_mouse_resolution( int resolution )
{
	vdu_mouse_resolution.b0 = resolution;
	VDP_PUTS( vdu_mouse_resolution );
}

void vdp_mouse_scaling( int scaling )
{
	vdu_mouse_scaling.b0 = scaling;
	VDP_PUTS( vdu_mouse_scaling );
}

void vdp_mouse_acceleration( int acceleration )
{
	vdu_mouse_acceleration.w0 = acceleration;
	VDP_PUTS( vdu_mouse_acceleration );
}

void vdp_mouse_wheel_accel( int wheelAccel )
{
	vdu_mouse_wheel_accel.ww0 = wheelAccel;
	VDP_PUTS( vdu_mouse_wheel_accel );
}


