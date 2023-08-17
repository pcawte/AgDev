#include "Bullet.hpp"
#include <Sprite/SpriteList.hpp>
#include "config.hpp"
#include <agon/vdp_vdu.h>

SpriteList *bullets;

void bullet_init()
{
	// Bullets - create bitmap and create SpriteList - Bullet Sprites will be created later

	vdp_select_bitmap( BULLET_BITMAP );
	vdp_solid_bitmap( BULLET_WIDTH, BULLET_HEIGHT,
						BULLET_COLOUR_R, BULLET_COLOUR_G, BULLET_COLOUR_B, BULLET_COLOUR_A );

	bullets = new SpriteList( 0, 0, SC_WIDTH, SC_HEIGHT );
}


// Bullet member functions //////////////////

// Events

Bullet *Bullet::at_top()
{
	delete this;						// Removal from SpriteGroup is handled in the base class destructor
	return NULL;
}

Bullet *Bullet::hitting( Sprite *s )
{
	delete this;
	return NULL;
}


Bullet *Bullet::hitting( TileArray *ta )
{
	delete this;
	return NULL;
}