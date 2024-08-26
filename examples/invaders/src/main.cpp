// VDU commands

#include <agon/vdp_vdu.h>
#include <agon/vdp_key.h>
#include <stdio.h>
#include <mos_api.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "config.hpp"
#include <Sprite/Sprite.hpp>
#include <Sprite/SpriteList.hpp>
#include <Sprite/Tile.hpp>
#include "Bullet.hpp"
#include "Alien.hpp"
#include "Bomb.hpp"
#include "Ship.hpp"
#include "barrier.hpp"


void game_loop();
void key_event_handler( KEY_EVENT key_event );
void wait_cnt( int cnt );
void wait_tick();

extern AlienArray *aliens;
extern SpriteList *bombs;
extern SpriteList *bullets;

extern Ship *ship;
extern TileArray *barrier[];

int score;

static volatile SYSVAR *sv;

int main()
{
	// Initialisation of vdp_vdu, vdp_key and Sprites

	sv = vdp_vdu_init();
	if ( vdp_key_init() == -1 ) return 1;

	if ( Sprite::init( MAX_SPRITES ) != MAX_SPRITES ) return 1;

	vdp_mode( SC_MODE );
	vdp_clear_screen();
	vdp_logical_scr_dims( false );
	vdp_cursor_enable( false );

	barrier_init();
	alien_init();					// Do this one first at ship borrows the same explosion bitmaps
	ship_init();
	bullet_init();
	bomb_init();

	// Get ready for game loop & enter game loop

	vdp_set_key_event_handler( key_event_handler );

	score = 0;
	game_loop();									// Actually this never returns - exit via event handler

	vdp_cursor_enable( true );
	
	return 0;	
}

void game_loop()
{
	Bomb *bomb;

	while ( true ) {
//		printf( "Press any key..." ); getchar();
		aliens->next_iter();
		ship->next_frame();
		for ( int s = 0; s < 4; s++ ) {
			int dx = 0, dy = 0;
			if ( vdp_check_key_press( 0x9c ) ) dx = 3;								// right
			if ( vdp_check_key_press( 0x9a ) ) dx -= 3;								// left
			if ( vdp_check_key_press( 0x96 ) ) dy = -3;								// up
			if ( vdp_check_key_press( 0x98 ) ) dy += 3;				 				// down
			ship->move_by( dx, dy );

			bullets->hit( aliens );
			bullets->hit( ship );
			aliens->hit( ship );
			bombs->hit( ship );
			for ( int b = 0; b < BARRIER_NUM; b++ ) {
				barrier[b]->is_hit( aliens );
				barrier[b]->is_hit( ship );
			}

			for ( int c = 0; c < ALIEN_COLS; c++ )
				for ( int r = ALIEN_ROWS-1; r >=0; r-- )
					if ( aliens->elem(c,r) ) {
						if ( rand() <= RAND_MAX / 20 ) {
							bomb = new Bomb( aliens->elem(c,r)->get_bottom_middle(),
											0, 2, BOMB_WIDTH, BOMB_HEIGHT, 0, BOMB_BITMAP );
							bombs->add( bomb );
						}
						break;
					}

			vdp_cursor_tab( 0, 0 );
			printf( "Score: %04d\n", score );
			for ( int w = 0; w < 2; w++ ) {
				bullets->next_step();
				bombs->next_step();
				for ( int b = 0; b < BARRIER_NUM; b++ ) {
					bombs->hit( barrier[b] );
					bullets->hit( barrier[b] );
				}
				wait_cnt( 50 );
			}
		}
	}	
}

static int bullets_visible = 1;

static KEY_EVENT prev_key_event = { 0 };

void key_event_handler( KEY_EVENT key_event )
{
	if ( key_event.key_data == prev_key_event.key_data ) return;
	prev_key_event = key_event;

	if ( key_event.code == 0x7d ) {								// Exit program if esc key pressed
		vdp_cursor_enable( true );
		exit( 1 );						
	}

	Bullet *b;
	Coords b_vec;
	Coords b_pos;

	if ( key_event.down )										// If key has just been pressed
		switch ( key_event.code ) {
		case 0x01:												// Space - fire bullet
			b_vec = ship->get_dir_vec();
			b_pos = ship->get_centre();											
			b = new Bullet( b_pos.x + b_vec.x*3 , b_pos.y + b_vec.y*3, b_vec.x, b_vec.y,
							BULLET_WIDTH, BULLET_HEIGHT, 0, BULLET_BITMAP );
			bullets->add( b );
			break;
		case 0x2f:
			ship->rot_ac_wise();								// 'z' - rotate ship anticlockwise 
			break;
		case 0x2d:					
			ship->rot_c_wise();									// 'x' - rotate ship clockwise
			break;

		// Debug stuff

		case 0x1d:												// 'h' - toggle hiding of ship 
			if ( ship->is_visible() ) {
				ship->hide();
			}
			else ship->show();
			if ( bullets_visible ) {
				bullets->hide();
				aliens->hide();
			}
			else {
				bullets->show();
				aliens->show();
			}
			bullets_visible = 1 - bullets_visible;
			break;
		case 0x19:												// 'd' - print debug info
			aliens->dump();
//			aliens->elem(0,5)->dump();											
//			Sprite::debug();
//			printf( "Ship: " ); ship->dump();
//			printf( "Bullets:-\n" ); bullets->dump();
//			printf( "Alien[0,0]: "); alien.elem(0,0)->dump();
//			ship->hit( aliens );								// Check if aliens hit by ship
//			printf( "Collision: %d\n", ship->collide( alien[0] ) ); 

//			vdp_cursor_tab( 0, 0 );
//			barrier->is_hit( ship );
/*
			Tile *hit;
			if ( (hit = barrier->hit( ship->get_centre() )) ) {
				printf( "Hit tile.\n ");
				hit->set_bitmap( 254 );
				hit->draw();
			}
*/
			break;
		}

/*	Debug info for key pressed bit table

	vdp_cursor_tab( 0, 0 );
//	printf( "Modifier %02x, key-code %02x, up/down %02x\n",
//			key_event.mods, key_event.code, key_event.down );
	for ( int i = 31; i >= 0; i-- ) printf( "%02x", vdp_key_bits[i] );
	return;
*/
}

void wait_cnt( int cnt )
{
	for ( int c = 0; c < cnt; c++ ) vdp_update_key_state();
}

void wait_tick()
{
	long tick = sv->time & 0x02;					// Get bit 2 of time which toggles every vblank

	do {
		vdp_update_key_state();
	} while ( (sv->time & 0x02) == tick );
}
