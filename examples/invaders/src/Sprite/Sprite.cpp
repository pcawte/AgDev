#include "Sprite.hpp"
#include <stdbool.h>
#include <stdlib.h>
#include <agon/vdp_vdu.h>
#include <stdio.h>


//////////////// Sprite Class ///////////////////

// static int num_vdp_sprites = 0;				// Number of VDP sprites used
												// At the moment do dumb allocation of next id with no reclaim

// Static members

int Sprite::sprites_max_num = 0;
int Sprite::sprites_num = 0;
int Sprite::sprites_next_free = 0;
Sprite **Sprite::sprites_vdp = NULL;

// Constructors, destructors & associated helper functions

int Sprite::init( int num_sprites )
{
	if ( num_sprites > 255 ) return 0;
	sprites_max_num = num_sprites;

	if ( !(sprites_vdp = (Sprite **)calloc( sprites_max_num, sizeof(Sprite *) )) ) return 0;
	return sprites_max_num;
}

Sprite::Sprite( int x, int y, int dx, int dy, int width, int height, int border, int bitmap )
{
	printf("Setting sprite details... ");
	set_details( x, y, dx, dy, width, height, border, bitmap );
	printf("Done\n");
}

Sprite::Sprite( Coords coords, int dx, int dy, int width, int height, int border, int bitmap )
{
	set_details( coords.x, coords.y, dx, dy, width, height, border, bitmap );
}

int Sprite::get_free_sprite_id()
{
	int cnt = sprites_max_num;
	while ( cnt-- > 0 ) {
		if ( !sprites_vdp[sprites_next_free] ) return sprites_next_free;
		sprites_next_free++;
		if ( sprites_next_free >= sprites_max_num ) sprites_next_free = 0;
	}
	return -1;
}

void Sprite::set_details( int x, int y, int dx, int dy, int width, int height, int border, int bitmap )
{
	if ( sprites_num > sprites_max_num ) {
		printf( "Too many sprites %d out of %d\n used", sprites_num, sprites_max_num );
		vdp_cursor_enable( true );
		exit( 1 ); 											// For the moment exit, really should throw exception
	}
	if ( ( s_vdp_id = get_free_sprite_id() ) < 0 ) {
		printf( "Failed to find free sprite id, %d\n", s_vdp_id );
		vdp_cursor_enable( true );
		exit( 1 );
	}
	sprites_vdp[s_vdp_id] = this;
	sprites_num++;

	s_x = x; s_y = y;
	s_w = width; s_h = height;
	s_dx = dx; s_dy = dy;
	s_brd = border;
	visible = false;
	sprite_grp = NULL;
	vdp_select_sprite( s_vdp_id );
	vdp_clear_sprite();
	vdp_move_sprite_to( x, y );

	if ( bitmap >= 0 ) {							// And single bit map if one specified
		add_bitmap( bitmap );
		vdp_show_sprite();
		visible = true;
	} else vdp_hide_sprite();						// Hide the sprite as has no bitmaps

	vdp_activate_sprites( sprites_max_num ); 		// Update GPU with total no. of sprites	
}

Sprite::~Sprite()
{
	vdp_select_sprite( s_vdp_id );
	vdp_clear_sprite();
	vdp_hide_sprite();
	if ( sprite_grp ) {										// If in SpriteList
		sprite_grp->remove( this );
	}
	sprites_vdp[s_vdp_id] = NULL;							// Clear it from the vdp table
	sprites_num--;									
}

// Getters

Coords Sprite::get_centre()
{
	return Coords( s_x + s_w/2, s_y + s_h/2 );
}

Coords Sprite::get_top_middle()
{
	return Coords( s_x + s_w/2, s_y + s_brd );
}

Coords Sprite::get_bottom_middle()
{
	return Coords( s_x + s_w/2, s_y + s_h - s_brd );
}

Coords Sprite::get_left_middle()
{
	return Coords( s_x + s_brd, s_y + s_h/2 );
}

Coords Sprite::get_right_middle()
{
	return Coords( s_x + s_w - s_brd, s_y + s_h/2 );
}

Coords Sprite::get_top_left()
{
	return Coords( s_x + s_brd, s_y + s_brd );
}

Coords Sprite::get_bottom_right()
{
	return Coords( s_x + s_w - s_brd, s_y + s_h - s_brd );
}

bool Sprite::get_viewport( int *x0, int *y0, int *x1, int *y1 )
{
	if ( !sprite_grp ) return false;
	*x0 = sprite_grp->sg_x0; *y0 = sprite_grp->sg_y0;
	*x1 = sprite_grp->sg_x1; *y1 = sprite_grp->sg_y1;
	return true;
}

// Bitmap handling

void Sprite::add_bitmap( int bitmap_id, int die )
{
	vdp_select_sprite( s_vdp_id );
	vdp_add_sprite_bitmap( bitmap_id );
	if ( !die ) frames++;
	else die_frames++;
}

void Sprite::add_bitmaps( int bitmap_id, int num, int die ) {
	printf("add_bitmaps: begin. ID %d | num %d | die %d\n", bitmap_id, num, die);
	vdp_select_sprite( s_vdp_id );
	printf("add_bitmaps: sprite selected\n");
	for ( int i = 0; i < num; i++ ) {
		vdp_add_sprite_bitmap( bitmap_id++ ); 
	}
	printf("add_bitmaps: vdp_add_sprite_bitmap done\n");
	if ( !die ) frames += num;
	else die_frames += num;
	printf("add_bitmaps: frames increment done\n");
}

// Visibility

void Sprite::show()
{
	printf("#Showing sprite......\n");
	if ( !visible ) {
		vdp_select_sprite( s_vdp_id );
		vdp_show_sprite();
		visible = true;
	}
}

void Sprite::hide()
{
	if ( visible ) {
		vdp_select_sprite( s_vdp_id );
		vdp_hide_sprite();
		visible = false;
	}
}

// Positioning

void Sprite::move_to( int xcoord, int ycoord )
{
	s_x = xcoord;
	s_y = ycoord;
	vdp_select_sprite( s_vdp_id );
	vdp_move_sprite_to( xcoord, ycoord );
}

void Sprite::move_by( int dx, int dy )
{
	s_x += dx;
	if ( sprite_grp ) { 
		if ( s_x + s_w >= sprite_grp->sg_x1 ) at_right();
		else if ( s_x < sprite_grp->sg_x0 ) at_left();
	}
	s_y += dy;
	if ( sprite_grp ) {
		if ( s_y + s_h >= sprite_grp->sg_y1 ) at_bottom();
		else if ( s_y < sprite_grp->sg_y0 ) at_top();
	}
	vdp_select_sprite( s_vdp_id );
	vdp_move_sprite_by( dx, dy );
}

// Frames

void Sprite::next_frame()
{
	vdp_select_sprite( s_vdp_id );
	switch( state )
	{
	case ALIVE:
		if ( ++cur_frame >= frames ) cur_frame = 0;
		vdp_nth_sprite_frame( cur_frame );
		break;
	case DYING:
		if ( ++cur_frame >= frames + die_frames ) dead();
		else vdp_nth_sprite_frame( cur_frame );
		break;
	case DEAD:
		break;
	}
}

void Sprite::prev_frame()
{
	vdp_select_sprite( s_vdp_id );
	if ( --cur_frame < 0 ) cur_frame = frames - 1;
	vdp_nth_sprite_frame( cur_frame );
}

void Sprite::set_frame( int n )
{
	vdp_select_sprite( s_vdp_id );
	cur_frame = n;
	vdp_nth_sprite_frame( cur_frame );
}

// Iterations (steps + frames)

void Sprite::next_iter() 
{
	next_step();
	next_frame();
}

void Sprite::prev_iter()
{
	prev_step();
	prev_frame();
}

// Collisions

int Sprite::collide( Sprite *s )
{
	if ( s->state != ALIVE ) return 0;

	int x0 = s_x + s_brd, y0 = s_y + s_brd;
	int x1 = s_x + s_w - s_brd, y1 = s_y + s_h - s_brd;
	int xs0 = s->s_x + s->s_brd, ys0 = s->s_y + s->s_brd;
	int xs1 = s->s_x + s->s_w - s->s_brd, ys1 = s->s_y + s->s_h - s->s_brd;
/*
	printf( "Bouding rectangles: ((%d, %d) (%d, %d)) ((%d, %d) (%d, %d))\n",
			x0, y0, x1, y1,
			xs0, ys0, xs1, ys1 );
*/
	int overlap_x = 0, overlap_y = 0;
	if ( xs0 < x1 && xs1 > x0 ) overlap_x = 1;
	if ( ys0 < y1 && ys1 > y0 ) overlap_y = 1;

//	printf ( "Overlap x %d, overap y %d\n", overlap_x, overlap_y );

	return overlap_x & overlap_y;
}

int Sprite::hit( Sprite *s )
{
	if ( collide( s ) ) {
		s->hit_by( this );
		hitting( s );
		return 1;
	}
	return 0;
}

void Sprite::hit( SpriteGroup *sg )
{
	sg->is_hit( this );
}

int Sprite::is_hit( Sprite *s )
{
	if ( collide( s ) ) {
		hit_by( s );
		s->hitting( this );
		return 1;
	}
	return 0;
}


// Events

Sprite *Sprite::at_left()
{
	s_dx = -s_dx;
	s_x += s_dx;
	return this;
}

Sprite *Sprite::at_right()
{
	s_dx = -s_dx;
	s_x += s_dx;
	return this;
}

Sprite *Sprite::at_top()
{
	s_dy = -s_dy;
	s_y += s_dy;
	return this;
}

Sprite *Sprite::at_bottom()
{
	s_dy = -s_dy;
	s_y += s_dy;
	return this;
}

Sprite *Sprite::hit_by( Sprite *s )
{
	return this;
}

Sprite *Sprite::hitting( Sprite *s )
{
	return this;
}

Sprite *Sprite::hitting( TileArray *ta )
{
	return this;
}

Sprite *Sprite::die()
{
	vdp_select_sprite( s_vdp_id );
	cur_frame = frames;							// set to first die frame
	if ( die_frames > 0 ) {
		vdp_nth_sprite_frame( cur_frame );
		state = DYING;
	}
	else dead();
	return this;
}

Sprite *Sprite::dead()
{
	vdp_select_sprite( s_vdp_id );
	vdp_hide_sprite();
	state = DEAD;
	return this;
}

// Debugging

void Sprite::dump()
{
	printf( "x %d, y %d, w %d, h %d, brd %d, dx %d, dy %d\n", s_x, s_y, s_w, s_h, s_brd, s_dx, s_dy );
	printf( "Sprite normal %d, die %d, current %d, state %d\n", frames, die_frames, cur_frame, state );
} 

void Sprite::debug()
{
	printf( "Number of sprites %d\n", sprites_num );
}

