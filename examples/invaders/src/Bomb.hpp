#ifndef _BOMB_HPP

#define _BOMB_HPP

#include "Sprite/Sprite.hpp"

void bomb_init();

class Bomb : public Sprite {
public:
	// Constructors and Destructor

	Bomb( int x = 0, int y = 0, int dx = 0, int dy = 0, int w = 0, int h = 0, int brd = 0, int bitmap = -1 )
		: Sprite( x, y, dx, dy, w, h, brd, bitmap ) {}
	Bomb( Coords coords, int dx = 0, int dy = 0, int w = 0, int h = 0, int brd = 0, int bitmap = -1 )
		: Sprite( coords, dx, dy, w, h, brd, bitmap ) {}
	~Bomb() {};

	// Events
	
	Bomb *at_bottom();
	Bomb *hitting( Sprite *s );
	Bomb *hitting( TileArray *ta );
};

#endif