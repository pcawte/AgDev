#include "Alien.hpp"
#include "config.hpp"
#include <agon/vdp_vdu.h>

SpriteArray *aliens;

void alien_init()
{
	// Red galaxians - load bitmaps, create SpriteList and Sprites

	vdp_load_sprite_bitmaps( ALIEN_FNAME_PREFIX, ALIEN_FNAME_FORMAT,
								ALIEN_WIDTH, ALIEN_HEIGHT,
								ALIEN_BITMAP_ID_START, ALIEN_BITMAP_ID_NUM );
	vdp_load_sprite_bitmaps( EXPLODE_FNAME_PREFIX, EXPLODE_FNAME_FORMAT,
								EXPLODE_WIDTH, EXPLODE_HEIGHT,
								EXPLODE_BITMAP_ID_START, EXPLODE_BITMAP_ID_NUM );

	aliens = new AlienArray( ALIEN_COLS, ALIEN_ROWS, ALIEN_X_SPACING, ALIEN_Y_SPACING,
								ALIEN_X, ALIEN_Y, ALIEN_SPEED, 0,
								0, 0, SC_WIDTH + ALIEN_X_SPACING - ALIEN_WIDTH, SC_HEIGHT );
								// Note - Adjust the size of the viewport to allow for the space at right or array

	int x = ALIEN_X, y = ALIEN_Y;

	for ( int c = 0; c < ALIEN_COLS; c++ ) {
		for ( int r = 0; r < ALIEN_ROWS; r++ ) {
			Alien *a = new Alien( x, y, ALIEN_SPEED, 0, ALIEN_WIDTH, ALIEN_HEIGHT, ALIEN_BORDER );
			a->add_bitmaps(ALIEN_BITMAP_ID_START, ALIEN_BITMAP_ID_NUM, 0);				// add regular bitmaps
			a->add_bitmaps(EXPLODE_BITMAP_ID_START, EXPLODE_BITMAP_ID_NUM, 1);			// add die frame bitmaps
			a->show();
			aliens->set_elem(c, r, a);
			y += ALIEN_Y_SPACING;
		}
		x += ALIEN_X_SPACING;
		y = ALIEN_Y;
	}
}

// Alien member functions /////////////

// Events

Alien *Alien::hit_by( Sprite *s )
{
	die();
	return this;
}

Alien *Alien::dead()
{
	delete this;
	score += 1;
	return NULL;
}

Alien *Alien::at_left()
{
	s_dx = -s_dx;
	move_to( s_x + s_dx, s_y + ALIEN_STEP ); 
	return this;
}

Alien *Alien::at_right()
{
	s_dx = -s_dx;
	move_to( s_x + s_dx, s_y + ALIEN_STEP ); 
	return this;
}

// AlienArray member functions ///////////////////

void AlienArray::at_left()
{
	Coords pos = get_pos();
	Coords speed = get_speed();
	set_speed( -speed.x, speed.y );
	for ( Sprite *s = begin(); s; s = next() ) move_by( 0, ALIEN_STEP );
	set_pos( pos.x, pos.y + ALIEN_STEP);
}

void AlienArray::at_right()
{
	Coords pos = get_pos();
	Coords speed = get_speed();
	set_speed( -speed.x, speed.y );
	for ( Sprite *s = begin(); s; s = next() ) move_by( 0, ALIEN_STEP );
	set_pos( pos.x, pos.y + ALIEN_STEP);
}
