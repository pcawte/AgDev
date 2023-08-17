#ifndef _DUMMYSPRITEGROUP_HPP

#define _DUMMYSPRITEGROUP_HPP

// Dummy Sprite Group doesn't do anything - but allows "members" to access functionality such as viewport
// Doesn't actually store anything related to its members

#include <stddef.h>
#include "Sprite.hpp"
#include "SpriteGroup.hpp"

class DummySpriteGroup : public SpriteGroup {
public:
	friend class Sprite;

// Constructor
	DummySpriteGroup( int x0, int y0, int x1, int y1 ) : SpriteGroup( x0, y0, x1, y1 ) {}

// Elements
	void add( Sprite *s ) { s->sprite_grp = this; }
	Sprite *remove( Sprite *s ) { return NULL; }

// Required by iterators
	Sprite *begin() { return NULL; }
	Sprite *next() { return NULL; }
};

#endif