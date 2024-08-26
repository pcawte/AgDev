#ifndef _ALIEN_HPP

#define _ALIEN_HPP

#include "Sprite/Sprite.hpp"
#include "Sprite/SpriteArray.hpp"

void alien_init();

class Alien : public Sprite {
public:
	// Constructors & Destructors

	Alien( int x = 0, int y = 0, int dx = 0, int dy = 0, int w = 0, int h = 0, int brd = 0, int bitmap = -1 )
		: Sprite( x, y, dx, dy, w, h, brd, bitmap ) {}
	Alien( Coords coords, int dx = 0, int dy = 0, int w = 0, int h = 0, int brd = 0, int bitmap = -1 )
		: Sprite( coords, dx, dy, w, h, brd, bitmap ) {}
	~Alien() {};
	
	// Events

	Alien *hit_by( Sprite *s );
	Alien *dead();
	Alien *at_left();
	Alien *at_right();

};

class AlienArray : public SpriteArray {
public:
	// Constructor

	AlienArray( int cols, int rows, int col_w, int row_h,	// Size of array and spacing of Sprites
				int x, int y, int dx, int dy,				// Top left corner & speed (indepdent of sprite positions)
				int x0, int y0, int x1, int y1 )			// Viewport
		: SpriteArray( cols, rows, col_w, row_h, x, y, dx, dy, x0, y0, x1, y1 ) {};

	// Events

	void at_left();
	void at_right();

};

#endif
