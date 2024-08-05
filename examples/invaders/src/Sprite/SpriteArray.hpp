#ifndef _SPRITEARRAY_HPP

#define _SPRITEARRAY_HPP

#include <stddef.h>
#include "Sprite.hpp"
#include "SpriteGroup.hpp"
#include "Coords.hpp"

class Sprite;

// SpriteArray - A SpriteGroup consisting of an [c][r] array of Sprites
//	- can be sparsely populated with Sprites

class SpriteArray : public SpriteGroup {
	Sprite **array = NULL;					// Pointer to array of pointers to Sprites
	int num_cols = 0;						// Number of columns in the array
	int num_rows = 0;						// Number of rows in the array
	int array_size = 0;
	Sprite **cur_elem = NULL;				// Pointer to current element for iteration

	int sa_x, sa_y;							// Top left corner
	int sa_dx, sa_dy;						// Speed (increment for next step)
	int sa_col_w, sa_row_h;					// Column width & row height (spacing between Sprites)
	int *col_num_remain;					// Array for number of aliens remaining per column
	int col_min, col_max;					// Section of array with non-zero columns
	int *row_num_remain;					// Array for number of aliens remaining per row
	int row_min, row_max;					// Section of array with non-zero rows

public:
	friend class Sprite;

	// Constuctors

	SpriteArray( int cols, int rows, int col_w, int row_h,	// Size of array and spacing of Sprites
				int x, int y, int dx, int dy,				// Top left corner & speed (indepdent of sprite positions)
				int x0, int y0, int x1, int y1 );			// Viewport

	// Required Iterator for anything derived from SpriteGroup

	Sprite *begin();
	Sprite *next();

	// Elements

	Sprite *elem( int col, int row );
	void set_elem( int col, int row, Sprite *s );
	Sprite *remove( Sprite *s );

	// Getters

	Coords get_pos() { return Coords( sa_x, sa_y); }
	Coords get_speed() { return Coords( sa_dx, sa_dy ); }

	// Setters

	void set_pos( int x, int y ) { sa_x = x; sa_y = y; }
	void set_speed( int x, int y ) { sa_dx = x; sa_dy = y; }

	// Movement

	void next_iter();
	void next_step();

private:
	void update_min_max_col( int c );
	void update_min_max_row( int r );

public:

	// Events - maybe overridden in derived classes

	virtual void at_left();					// Default is just to reflect of the edge
	virtual void at_right();				// Default is just to reflect of the edge

	// Debugging

	void dump();
};

#endif