#ifndef _VDP_VDU_H
#define _VDP_VDU_H

#include <stdbool.h>
#include <stdint.h>
#include <mos_api.h>

#ifdef __cplusplus
extern "C" {
#endif

#define VDP_PUTS(S) mos_puts( (char *)&(S), sizeof(S), 0)

volatile SYSVAR *vdp_vdu_init( void );
void vdp_write_at_text_cursor( void );
void vdp_write_at_graphics_cursor( void );
void vdp_enable_screen( void );
void vdp_bell( void );
void vdp_cursor_left( void );
void vdp_cursor_right( void );
void vdp_cursor_down( void );
void vdp_cursor_up( void );
void vdp_cursor_up( void );
void vdp_clear_screen( void );
void vdp_page_mode_on( void );
void vdp_page_mode_off( void );
void vdp_clear_graphics( void );
void vdp_reset_graphics( void );
void vdp_disable_screen( void );
void vdp_cursor_home( void );
void vdp_cursor_tab( int row, int col );
void vdp_set_text_colour( int colour );
void vdp_set_graphics_colour( int mode, int colour );
#define vdp_gcol( M, C ) vdp_set_graphics_colour( M, C )
void vdp_define_colour (int logical, int red, int green, int blue );
void vdp_graphics_origin( int x, int y );
int vdp_mode( int mode );
void vdp_swap( void );
void vdp_get_scr_dims( bool );
void vdp_redefine_character( int chnum, uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7 );
void vdp_logical_scr_dims( bool );
void vdp_cursor_enable( bool flag );
void vdp_scroll_screen_extent( int extent, int direction, int speed );
void vdp_scroll_screen(int direction, int speed);

void vdp_reset_viewports( void );
void vdp_set_graphics_viewport( int left, int bottom, int right, int top );
void vdp_set_text_viewport( int left, int bottom, int right, int top );

void vdp_move_to( int x, int y );
void vdp_line_to( int x, int y );
void vdp_point( int x, int y );
void vdp_triangle( int x, int y );
void vdp_circle_radius( int x, int y );
void vdp_circle( int x, int y );
void vdp_filled_rect( int x, int y );

void vdp_select_bitmap( int n );
void vdp_load_bitmap( int width, int height, uint32_t *data );
int vdp_load_bitmap_file( const char *fname, int width, int height );
void vdp_solid_bitmap( int width, int height, int r, int g, int b, int a );
void vdp_draw_bitmap( int x, int y );

int vdp_load_sprite_bitmaps( const char *fname_prefix, const char *fname_format,
							int width, int height, int num, int bitmap_num );
void vdp_create_sprite( int sprite, int bitmap_num, int frames );

void vdp_select_sprite( int n );
void vdp_clear_sprite( void );
void vdp_add_sprite_bitmap( int n );
void vdp_move_sprite_to( int x, int y );
void vdp_move_sprite_by( int x, int y );
void vdp_show_sprite( void );
void vdp_hide_sprite( void );
void vdp_next_sprite_frame( void );
void vdp_prev_sprite_frame( void );
void vdp_nth_sprite_frame( int n );
void vdp_activate_sprites( int n );
void vdp_refresh_sprites( void );
void vdp_reset_sprites( void );

void vdp_adv_write_block(int bufferID, int length);
void vdp_adv_clear_buffer(int bufferID);
void vdp_adv_create(int bufferID, int length);
void vdp_adv_stream(int bufferID);
void vdp_adv_adjust(int bufferID, int operation, int offset);
void vdp_adv_consolidate(int bufferID);
void vdp_adv_select_bitmap(int bufferId);
void vdp_adv_bitmap_from_buffer(int width, int height, int format);

int vdp_adv_load_sprite_bitmaps( const char *fname_prefix, const char *fname_format, int width, int height, int num, int bitmap_num );
void vdp_adv_add_sprite_bitmap( int b );
void vdp_adv_create_sprite( int sprite, int bitmap_num, int frames );

#ifdef __cplusplus
}
#endif

#endif

