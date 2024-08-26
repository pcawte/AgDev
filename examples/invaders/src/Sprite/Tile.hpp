#ifndef _TILE_HPP

#define _TILE_HPP

#include <stddef.h>
#include "Coords.hpp"
#include "Sprite.hpp"
#include "SpriteGroup.hpp"

class Sprite;
class TileArray;

/* Class to represent a graphics tile

	Use bitmaps to draw the image
	Compared to simple bitmaps adds:
	- manages the display of the bitmaps on the screen
	- collision detection
	- update of bitmap 
*/

class Tile {
	int t_x, t_y;						// top left of tile 
	int t_w, t_h;						// size of tile
	int t_bitmap;						// bitmap to use (-1 = blank)

public:
	friend class TileArray;

	// Constructors
	Tile() {};
	Tile( int xcoord, int ycoord, int width = 0, int height = 0, int bitmap = 0 );	

	// Functions

	void set_bitmap( int bitmap );
	void draw();
	void blank( int blank_bitmap );		// Sets tile to blank (can reset it by set_bitmap())

	// Events

	virtual void hit_by( int blank_bitmap, Sprite *s );

};

// Array of graphics tiles - adjacent to each other with same sizes

class TileArray {
	int ta_rows, ta_cols;				// Number of tiles (rows, cols)
	int ta_x, ta_y;						// Position of top left of TileArray
	int ta_w, ta_h;						// Size of each tile (rows, cols)
	int ta_blank_bitmap;
	Tile *array;						// Elements of array

public:
	// Constructors

	TileArray( int c, int r, int xcoord = 0, int ycoord = 0, int width = 0, int height = 0,
				int bitmap = 0, int blank_bitmap = 0 );

	// Functions

	Tile *elem( int c, int r );
	void set_bitmap( int bitmap );
	void draw();
	void clear( int c0, int r0, int c1, int r1 ); 		// Clear a section before drawing 

	// Collision / hit functions
	// 	- collide does generate events
	// 	- hit functions generate events

	Tile *collide( int xcoord, int ycoord );			// Returns tile hit at (xcoord, ycoord) or NULL
	Tile *collide( Coords coords ) { return collide( coords.x, coords.y ); }

	void is_hit( Sprite *s );							// Call hit_by() event for all tiles hit 
	void is_hit( SpriteGroup *sg );

};

#endif