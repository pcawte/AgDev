#ifndef _ROT_SPRITE_HPP

#define _ROT_SPRITE_HPP


#include "Sprite.hpp"

typedef struct
{
	int angle;
	int vec_x;
	int vec_y;
	int frame;
} ROT_TABLE;



class RotSprite : public Sprite {
	ROT_TABLE *rs_rot_table = NULL;
	int rs_cur_rot = 0;
	int rs_num_rot = 0;
	int rs_circular = 0;


public:

	// Constructors, Destructors

	RotSprite( int x = 0, int y = 0, int dx = 0, int dy = 0, int w = 0, int h = 0, int brd = 0, int bitmap = -1 );
	RotSprite( Coords coords, int dx = 0, int dy = 0, int w = 0, int h = 0, int brd = 0, int bitmap = -1 );
	~RotSprite() {};

	// Rotation table handling

	void add_rotations( ROT_TABLE *rot_table, int num_rot, int cur_rot = 0, bool circular = 0 );

	// Getters

	Coords get_dir_vec();					// get direction represented as a pair of coords 

	// Functions

	void next_frame();


	// Sprite Events - can overridded from base class to customise behaviour


	// RotSprite Events - that can be overriden in derived classes

	virtual int rot_c_wise();				// returns rotation or -1 if can't rotate further (if not circular)
	virtual int rot_ac_wise();				// reutrns rotation of -1 if can't rotate further (if not circular)


};

#endif