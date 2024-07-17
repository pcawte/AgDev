#ifndef _SPRITEGROUP_HPP

#define _SPRITEGROUP_HPP

#include <stddef.h>
#include "Sprite.hpp"
#include "Coords.hpp"
#include "Tile.hpp"

class Sprite;
class TileArray;

// SpriteGroup - A collection of sprites to which common actions can be applied or collisions detected

class SpriteGroup {
	int num_elements = 0;					// Number of elements
	int sg_x0, sg_y0;						// View port - top left
	int sg_x1, sg_y1;						// View port - bottom right
public:
	friend class Sprite;
	friend class SpriteList;
	friend class SpriteArray;

	// Constuctors

	SpriteGroup( int x0, int y0, int x1, int y1 );			// New SpriteGroup with view port

	// Elements

	int num_elem() { return num_elements; }
	virtual Sprite *remove( Sprite *s ) = 0;				// Remove Sprite from SpriteGroup - but don't delete it

	// Required for iterators

	virtual Sprite *begin() = 0;							// First element
	virtual Sprite *next() = 0;								// Next element

	// Actions - performned on all SpriteGroup members

	void move_by( int dx, int dy );
	void next_frame();
	void prev_frame();
	void next_step();
	void prev_step();
	void next_iter();
	void prev_iter();
	void hide();
	void show();

	// Collisions

	void is_hit( Sprite *s );					// Trigger events on members of Sprite group hit by Sprite
	void hit( Sprite *s );
	void hit( SpriteGroup *sg );
	void hit( TileArray *ta );

	// Debugging

	void dump();
};


#endif