#include "SpriteList.hpp"

////////////// SpriteList Class - derived from SpriteGroup //////////////

// Constructor

SpriteList::SpriteList( int x0, int y0, int x1, int y1 )
	: SpriteGroup( x0, y0, x1, y1 )
{}

// Elements


void SpriteList::add( Sprite *s )
{
	SpriteListElem *sge = new SpriteListElem( s );
	if ( !first ) {			 							// If currently no elements
		first = sge;
		last = sge;
	} else {
		last->next = sge;								// Point last enter to new final element
		last = sge;										// Update last pointer to new final element
	}
	num_elements++;
	s->sprite_grp = this;
}

Sprite *SpriteList::remove( Sprite *s )					// Removes element & returns it or NULL if not found
{
	SpriteListElem *sge = first;
	SpriteListElem *prev = NULL;
	while ( sge ) {
		if ( sge->sprite == s ) {
			if ( !prev ) {								// Remove the element if first
				first = sge->next;
			} else {									// or subsequent
				prev->next = sge->next;
			}

			if ( sge == last ) {						// If last element update last	
				last = prev;
			}
		
			num_elements--;								// decrease the number of elements
			return sge->sprite;							// and return the removed element
		}
		prev = sge;
		sge = sge->next;								// Move on to next element & iterate
	}
	return NULL;										// Reached end of list & not found
}

Sprite *SpriteList::begin()
{
	if ( (current = first) ) return current->sprite;
	return NULL;
}

Sprite *SpriteList::next()
{
	if ( (current = current->next) ) return current->sprite;
	return NULL;
}

