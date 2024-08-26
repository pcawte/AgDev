#ifndef _SPRITE_HPP

#define _SPRITE_HPP

#include <stddef.h>
#include "Coords.hpp"
#include "Tile.hpp"
#include "SpriteGroup.hpp"

/* Class to represent a sprite

	These make use of VDP sprite engine for drawing, animation (frames) and movement
	- automatically iterates through frames 
		- there are "normal frames" - potentially want to have different normal sequences
		- and "die" frames
	- automatically move
	Adds:
	- collision detection
	- concept of state & dying 
*/
				
class Sprite {
protected:
	int s_vdp_id;	 							// VDP sprite ID (0-255)
	int s_x, s_y;								// Coordinates (top left)
	int s_w, s_h;								// normal sprite size
	int s_brd;									// reduces size for collision detection
	int s_dx, s_dy;								// Delta x and delta y for sprite movement
	bool visible = false;						// Flag for visibility
	int frames = 0;								// number of normal frames
	int die_frames = 0;							// number of frames for dieing animation
	int cur_frame = 0;							// Current frame
	enum { ALIVE, DYING, DEAD } state = ALIVE;
	SpriteGroup *sprite_grp;					// SpriteGroup (NULL if none)

	// Static data (i.e. for the whole class)

	static int sprites_max_num;					// Maximum sprites
	static int sprites_num;						// Number of active sprites
	static int sprites_next_free;				// Next free sprite
	static Sprite **sprites_vdp;				// Table of sprite usage

private:
	void set_details( int x, int y, int dx, int dy, int w, int h, int brd, int bitmap );
	static int get_free_sprite_id();			// Returns id of next free sprite or -1

public:
	friend class SpriteList;
	friend class SpriteArray;
	friend class DummySpriteGroup;

	// Constructors, Destructors 

	Sprite( int x = 0, int y = 0, int dx = 0, int dy = 0, int w = 0, int h = 0, int brd = 0, int bitmap = -1 );
	Sprite( Coords coords, int dx = 0, int dy = 0, int w = 0, int h = 0, int brd = 0, int bitmap = -1 );
	virtual ~Sprite();

	static int init( int num_sprites );			// Returns no of sprites or zero if failed

	// Bitmap handling

	void add_bitmap( int bitmap_id, int die = 0 );
	void add_bitmaps( int bitmap_id, int num, int die = 0 );

	// Getters

	// 	- position getters - take consideration of the boundary

	Coords get_centre();
	Coords get_top_middle();
	Coords get_bottom_middle();
	Coords get_left_middle();
	Coords get_right_middle();
	Coords get_top_left();
	Coords get_bottom_right();
	bool is_visible() { return visible; };
	bool get_viewport( int *x0, int *y0, int *x1, int *y1 );

	// Setters

	void set_speed( int dx, int dy ) { s_dx = dx; s_dy = dy; };

	// Visibility

	void show();
	void hide();

	// Positioning

	void move_to( int x, int y );
	void move_by( int dx, int dy );

	// Frames

	void set_frame( int n );
	void next_frame();
	void prev_frame();

	// Steps (movement)

	void next_step() { move_by( s_dx, s_dy ); };
	void prev_step() { move_by( -s_dx, -s_dy ); };

	// Iterations (steps + frames)

	void next_iter();
	void prev_iter();

	// Collisions

	int collide( Sprite *s );					// TODO return location - does not trigger events
	int hit( Sprite *s );						// Triggers hit & hitting events if collision
	int is_hit( Sprite *s );					// Same as above but events reversed
	void hit( SpriteGroup *sg );

	// Events - these should be customised by overriding in a derived class
	//	- should return a point to themselves
	//  - or if they delete themselves NULL

	// Movement events are called by move_by() after coordinates has been changed, but not drawn
	//	- default is reflection
	//  - function may be overloaded in a derived class - this may delete the Sprite

	virtual Sprite *at_left();
	virtual Sprite *at_right();
	virtual Sprite *at_top();
	virtual Sprite *at_bottom();

	// Dying & dead actions

	virtual Sprite *die();					// Trigger at beginnng of dying sequence
	virtual Sprite *dead();					// Trigger at end of dying sequence

	// Collision events
	//	- default is to do nothing

	virtual Sprite *hit_by( Sprite *s );		// Object of hitting	
	virtual Sprite *hitting( Sprite *s );		// Subject of hitting
	virtual Sprite *hitting( TileArray *ta );

	// Debugging

	void dump();
	static void debug();
};

#endif