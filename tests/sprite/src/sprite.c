// VDU commands

#include "vdp_vdu.h"
#include "vdp_key.h"
#include <stdio.h>
#include <mos_api.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define SC_MODE 1
#define SC_WIDTH 512
#define SC_HEIGHT 384

#define ALIEN_COLS 10
#define ALIEN_ROWS 5
#define ALIEN_X 64
#define ALIEN_Y 64

typedef struct{
	int x;
	int y;
} ALIEN;

void game_loop( int num_sprite );
void key_event_handler( KEY_EVENT key_event );
void wait_clock( clock_t ticks );


static ALIEN aliens[ALIEN_COLS][ALIEN_ROWS];

int main( void )
{
	volatile SYSVAR *sv;

	sv = vdp_vdu_init();
	if ( vdp_key_init() == -1 ) return 1;

	vdp_mode( SC_MODE );
	vdp_clear_screen();
	vdp_logical_scr_dims( false );
	vdp_cursor_enable( false );

	// Load bitmaps to use for the red galaxian sprites & the gun / ship

	vdp_load_sprite_bitmaps( "bitmaps/gal-red", "%s%1d.rgba", 16, 16, 4, 0 );
	vdp_load_sprite_bitmaps( "bitmaps/ship", "%s%02d.rgba", 16, 16, 24, 4 );

	// Create the sprite for the ship (sprite 0)

	vdp_create_sprite( 0, 4, 24 );
	vdp_select_sprite( 0 );
	vdp_move_sprite_to( 256, 300 );
	vdp_show_sprite();

	// Create the rows and columns of sprites at their initial positions

	int sprite = 1;
	int x = ALIEN_X, y = ALIEN_Y;

	for ( int c = 0; c < ALIEN_COLS; c++ ) {
		for ( int r = 0; r < ALIEN_ROWS; r++ ) {
			vdp_create_sprite( sprite, 0, 4 );
			vdp_select_sprite( sprite++ );
			vdp_move_sprite_to( x, y );
			vdp_show_sprite();
			y += 32;
		}
		x += 32;
		y = ALIEN_Y;
	}
	vdp_activate_sprites( sprite );

	vdp_set_key_event_handler( key_event_handler );

	game_loop( sprite );

	vdp_cursor_enable( true );
	printf( "Press any key to continue...\n" );
	getchar();
	
	return 0;	
}

void game_loop( int num_sprite )
{
	while ( true ) {
		for ( int s = 1; s < num_sprite; s++ ) {
			vdp_select_sprite( s );
			vdp_next_sprite_frame();
		}
		for ( int s = 0; s < 4; s++ ) {
			vdp_select_sprite( 0 );
			if ( vdp_check_key_press( 0x2f ) ) vdp_prev_sprite_frame();				// z-key
			if ( vdp_check_key_press( 0x2d ) ) vdp_next_sprite_frame();				// x-key
			if ( vdp_check_key_press( 0x9c ) ) vdp_move_sprite_by( +3, 0 );			// right
			if ( vdp_check_key_press( 0x9a ) ) vdp_move_sprite_by( -3, 0 );			// left
			if ( vdp_check_key_press( 0x96 ) ) vdp_move_sprite_by( 0, -3 );			// up
			if ( vdp_check_key_press( 0x98 ) ) vdp_move_sprite_by( 0, +3 ); 		// down
			wait_clock( 4 );
//			for ( int w = 0; w < 2; w++ ) {
//				vdp_update_key_state();
//				waitvblank();			
//			}
		}
	}	
}

void key_event_handler( KEY_EVENT key_event )
{
	if ( key_event.code == 0x7d ) {
		vdp_cursor_enable( true );
		exit( 1 );						// Exit program if esc pressed
	}
	vdp_cursor_tab( 0, 0 );
//	printf( "Modifier %02x, key-code %02x, up/down %02x\n",
//			key_event.mods, key_event.code, key_event.down );
	for ( int i = 31; i >= 0; i-- ) printf( "%02x", vdp_key_bits[i] );
	return;
}

void wait_clock( clock_t ticks )
{
	clock_t ticks_now = clock();

	do {
		vdp_update_key_state();
	} while ( clock() - ticks_now < ticks );
}