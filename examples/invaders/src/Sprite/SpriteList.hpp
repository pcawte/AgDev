#ifndef _SPRITELIST_HPP

#define _SPRITELIST_HPP

#include <stddef.h>
#include "Sprite.hpp"
#include "SpriteGroup.hpp"

class Sprite;

// SpriteList - A SpriteGroup consisting of a linked list of Sprites

class SpriteListElem {
	Sprite *sprite;
	SpriteListElem *next = NULL;
	SpriteListElem( Sprite *s ) { sprite = s; };
public:
	friend class SpriteList;
};

class SpriteList : public SpriteGroup {
	SpriteListElem *first = NULL;			// Linked list pointer to first element
	SpriteListElem *last = NULL;			// Pointer to last element - so easy to add new elements
	SpriteListElem *current = NULL;			// Current element in iteration
public:
	friend class Sprite;

	// Constuctors

	SpriteList( int x0, int y0, int x1, int y1 );

	// Required Iterator for anything derived from SpriteGroup

	Sprite *begin();
	Sprite *next();

	// Elements

	void add( Sprite *sprite );
	Sprite *remove( Sprite *s );
};

#endif