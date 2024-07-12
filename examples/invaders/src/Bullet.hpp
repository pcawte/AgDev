#ifndef _BULLET_HPP

#define _BULLET_HPP

#include <Sprite/Sprite.hpp>


void bullet_init();

class Bullet : public Sprite {
public:
	// Constuctors & Destuctors

	Bullet( int x = 0, int y = 0, int dx = 0, int dy = 0, int w = 0, int h = 0, int brd = 0, int bitmap = -1 )
		: Sprite( x, y, dx, dy, w, h, brd, bitmap ) {}
	Bullet( Coords coords, int dx = 0, int dy = 0, int w = 0, int h = 0, int brd = 0, int bitmap = -1 )
		: Sprite( coords, dx, dy, w, h, brd, bitmap ) {}
	~Bullet() {};

	// Events
	
	Bullet *at_top();
	Bullet *hitting( Sprite *s );
	Bullet *hitting( TileArray *ta );
};

#endif