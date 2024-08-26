#include "Bomb.hpp"
#include "Sprite/SpriteList.hpp"
#include "config.hpp"
#include <agon/vdp_vdu.h>

SpriteList *bombs;

void bomb_init()
{
	// Bombs - create bitmap and create SpriteList - Bullet Sprites will be created later

	vdp_select_bitmap( BOMB_BITMAP );
	vdp_solid_bitmap( BOMB_WIDTH, BOMB_HEIGHT,
						BOMB_COLOUR_R, BOMB_COLOUR_G, BOMB_COLOUR_B, BOMB_COLOUR_A );

	bombs = new SpriteList( 0, 0, SC_WIDTH, SC_HEIGHT );
}

// Bomb member functions //////////////////

// Events

Bomb *Bomb::at_bottom()
{
	delete this;						// Removal from SpriteGroup is handled in the base class destructor
	return NULL;
}

Bomb *Bomb::hitting( Sprite *s )
{
	delete this;
	return NULL;
}


Bomb *Bomb::hitting( TileArray *ta )
{
	delete this;
	return NULL;
}