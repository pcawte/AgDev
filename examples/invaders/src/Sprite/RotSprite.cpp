#include "RotSprite.hpp"
#include <stdio.h>
#include <agon/vdp_vdu.h>

RotSprite::RotSprite( int x, int y, int dx, int dy, int w, int h, int brd, int bitmap )
	: Sprite( x, y, dx, dy, w, h, brd, bitmap )
{}

RotSprite::RotSprite( Coords coords, int dx, int dy, int w, int h, int brd, int bitmap )
	: Sprite( coords, dx, dy, w, h, brd, bitmap )
{}

// Rotation table handling

void RotSprite::add_rotations( ROT_TABLE *rot_table, int num_rot, int cur_rot, bool circular ) {
	rs_rot_table = rot_table;
	rs_num_rot = num_rot;
	rs_cur_rot = cur_rot;
	rs_circular = circular;
	printf("About to set rotation...");
	waitvblank();
	set_frame( rs_rot_table[rs_cur_rot].frame );
	printf("Done\n");
	waitvblank();

}

// Gettters

Coords RotSprite::get_dir_vec()
{
	return Coords( rs_rot_table[rs_cur_rot].vec_x, rs_rot_table[rs_cur_rot].vec_y );
}

// Frames

void RotSprite::next_frame()
{
	vdp_select_sprite( s_vdp_id );
	switch( state )
	{
	case ALIVE:
		break;
	case DYING:
		if ( ++cur_frame >= frames + die_frames ) dead();
		else vdp_nth_sprite_frame( cur_frame );
		break;
	case DEAD:
		break;
	}
}

// Sprite Events - overridden from Sprite base class


// RotSprite Events - that can be overriden in derived classes

int RotSprite::rot_c_wise()
{
	if ( ++rs_cur_rot >= rs_num_rot && !rs_circular ) { --rs_cur_rot; return -1; }

	if ( rs_cur_rot >= rs_num_rot ) rs_cur_rot = 0;
	set_frame( rs_rot_table[rs_cur_rot].frame );
	return rs_cur_rot;
}

int RotSprite::rot_ac_wise()
{
	if ( --rs_cur_rot < 0 && !rs_circular ) { ++rs_cur_rot; return -1; }

	if ( rs_cur_rot < 0 ) rs_cur_rot = rs_num_rot-1;
	set_frame( rs_rot_table[rs_cur_rot].frame );
	return rs_cur_rot;
}
