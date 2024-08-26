#ifndef _SHIP_HPP

#define _SHIP_HPP

#include "Sprite/RotSprite.hpp"


void ship_init();

class Ship : public RotSprite {
public:
	// Constructors & destructors

	Ship( int x = 0, int y = 0, int dx = 0, int dy = 0, int w = 0, int h = 0, int brd = 0, int bitmap = -1 )
		: RotSprite( x, y, dx, dy, w, h, brd, bitmap ) {}
	Ship( Coords coords, int dx = 0, int dy = 0, int w = 0, int h = 0, int brd = 0, int bitmap = -1 )
		: RotSprite( coords, dx, dy, w, h, brd, bitmap ) {}
	~Ship() {};
	
	// Events

	Ship *hit_by( Sprite *s );
	Ship *dead();

	// Postioning

	void move_by( int dx, int dy );
};

#endif
