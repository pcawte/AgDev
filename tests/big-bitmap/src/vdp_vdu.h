#ifndef _VDP_VDU_H
#define _VDP_VDU_H

#include <stdbool.h>
#include <stdint.h>
#include <mos_api.h>

volatile SYSVAR *vdp_vdu_init( void );
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
int vdp_load_bitmap_file( const char *fname, int width, int height );
void vdp_draw_bitmap( int x, int y );

#endif