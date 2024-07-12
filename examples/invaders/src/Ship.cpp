#include "Ship.hpp"
#include <Sprite/DummySpriteGroup.hpp>
#include "config.hpp"
#include <agon/vdp_vdu.h>
#include <stdio.h>
#include <stdlib.h>

static ROT_TABLE rot_ship[] = {
	{   0,  0, -4, 6 },
	{  15,  1, -4, 7 },
	{  30,  2, -4, 8 },
	{  45,  3, -3, 9 },
	{  60,  4, -2, 10 },
	{  75,  4, -1, 11 },
	{  90,  4,  0, 12 },
	{ 105,  4,  1, 13 },
	{ 120,  4,  2, 14 },
	{ 135,  3,  3, 15 },
	{ 150,  2,  4, 16 },
	{ 165,  1,  4, 17 },
	{ 180,  0,  4, 18 },
	{ 195, -1,  4, 19 },
	{ 210, -2,  4, 20 },
	{ 225, -3,  3, 21 },
	{ 240, -4,  2, 22 },
	{ 255, -4,  1, 23 },
	{ 270, -4,  0, 0 },
	{ 285, -4, -1, 1 },
	{ 300, -4, -2, 2 },
	{ 315, -3, -3, 3 },
	{ 330, -2, -4, 4 },
	{ 345, -1, -4, 5 }
};

Ship *ship;
static DummySpriteGroup *viewport;

// Ship initialisation
//	- load bitmaps and create Ship Sprite
//	- create DummySpriteGroup to provide a viewport

void ship_init()
{
	vdp_load_sprite_bitmaps( SHIP_FNAME_PREFIX, SHIP_FNAME_FORMAT,
								SHIP_WIDTH, SHIP_HEIGHT,
								SHIP_BITMAP_ID_NUM, SHIP_BITMAP_ID_START );			

	ship = new Ship( SHIP_X, SHIP_Y, 0, 0, SHIP_WIDTH, SHIP_HEIGHT, SHIP_BORDER );
	ship->add_bitmaps( SHIP_BITMAP_ID_START, SHIP_BITMAP_ID_NUM );
	ship->add_bitmaps(4, 4, 1);														// add die frame bitmaps

	ship->add_rotations( rot_ship, SHIP_NUM_ROT, 0, true );
	ship->show();

	viewport = new DummySpriteGroup( 0, 0, SC_WIDTH, SC_HEIGHT );
	viewport->add( ship );
}

// Ship members functions ////////////

// Events

Ship *Ship::hit_by( Sprite *s )
{
	die();
	return this;
}

Ship *Ship::dead()
{
	printf( "\n\nGame over\nScore: %04d\n", score );
	vdp_cursor_enable( true );
	exit( 0 );
}

// Movement

void Ship::move_by( int dx, int dy )
{
	int vp_x0, vp_y0;
	int vp_x1, vp_y1;

	if ( get_viewport( &vp_x0, &vp_y0, &vp_x1, &vp_y1) ) {
		if ( s_x + s_w + dx >= vp_x1 ) dx = 0;
		else if ( s_x + dx < vp_x0 ) dx = 0;

		if ( s_y + s_h + dy >= vp_y1 ) dy = 0;
		else if ( s_y + dy < vp_y0 ) dy = 0;
	}
	s_x += dx;
	s_y += dy;

	vdp_select_sprite( s_vdp_id );
	vdp_move_sprite_by( dx, dy );
}
