#include <Sprite/Tile.hpp>
#include <agon/vdp_vdu.h>
#include <stdio.h>
#include <stdlib.h>

////////////// Tile Class //////////////

// Constructor

Tile::Tile( int xcoord, int ycoord, int width, int height, int bitmap )
{
	t_x = xcoord; t_y = ycoord;
	t_w = width; t_h = height;
	t_bitmap = bitmap;
}	

// Member functions

void Tile::set_bitmap( int bitmap )
{
	t_bitmap = bitmap;
}

void Tile::draw()
{
	if ( t_bitmap > 0 ) {							// Draw if not blank
		vdp_select_bitmap( t_bitmap );
		vdp_draw_bitmap( t_x, t_y );
	}
}

void Tile::blank( int blank_bitmap )
{
	t_bitmap = -1;
	vdp_select_bitmap( blank_bitmap );
	vdp_draw_bitmap( t_x, t_y );
}

// Events

void Tile::hit_by( int blank_bitmap, Sprite *s )
{
	blank( blank_bitmap );
}

////////////// TileArray Class //////////////

// Constructor

TileArray::TileArray( int c, int r, int xcoord, int ycoord, int width, int height,
						int bitmap, int blank_bitmap )
{
	ta_rows = r, ta_cols = c;
	ta_x = xcoord; ta_y = ycoord;
	ta_w = width; ta_h = height;
	ta_blank_bitmap = blank_bitmap;

	if ( !(array = new Tile[ta_rows*ta_cols]) ) {
		printf( "Can't allocated memory for TileArray.\n" );
		exit( 1 );
	}

	Tile *tp = array;
	for ( c = 0; c < ta_cols; c++ ) {
		ycoord = ta_y;
		for ( r = 0; r < ta_rows; r++, tp++ ) {
			tp->t_x = xcoord; tp->t_y = ycoord;
			tp->t_w = width; tp->t_h = height;
			tp->t_bitmap = bitmap;
			ycoord += height;
		}
		xcoord += width;
	}
}

Tile *TileArray::elem( int c, int r )
{
	return array + r + c*ta_rows;
}

void TileArray::set_bitmap( int bitmap )
{
	int r, c;
	for ( r = 0; r < ta_rows; r ++ )
		for ( c = 0; c < ta_cols; c++ )
			elem(c, r)->t_bitmap = bitmap;
}

void TileArray::clear( int c0, int r0, int c1, int r1 )
{

	if ( c1 < 0 || r1 < 0 ) return;

	if ( c0 >= ta_cols || r0 >= ta_rows ) return;

	if ( c0 < 0 ) c0 = 0;
	if ( r0 < 0 ) r0 = 0;
	if ( c1 >= ta_cols ) c1 = ta_cols-1;
	if ( r1 >= ta_rows ) r1 = ta_rows-1;

	for ( int c = c0; c <= c1; c++ )
		for ( int r = r0; r <= r1; r++ )
			elem(c, r)->t_bitmap = -1;
}

void TileArray::draw()
{
	int r, c;
	for ( r = 0; r < ta_rows; r ++ )
		for ( c = 0; c < ta_cols; c++ )
			elem(c, r)->draw();
}

Tile *TileArray::collide( int x, int y )
{
	x -= ta_x;
	y -= ta_y;
	if ( x < 0 || y < 0) return NULL;

	int c = x / ta_w;
	int r = y / ta_h;
	if ( c >= ta_cols || r >= ta_rows ) return NULL; 

	if ( elem(c, r)->t_bitmap > 0 ) return elem(c, r); 			// check if not blank 
	else return NULL;
}

void TileArray::is_hit( Sprite *s )
{
	Coords coord0 = s->get_top_left();
	Coords coord1 = s->get_bottom_right();

	int x0 = coord0.x - ta_x, y0 = coord0.y - ta_y;
	int x1 = coord1.x - ta_x, y1 = coord1.y - ta_y;

	if ( x1 < 0 || y1 < 0 ) return;

	int c0 = x0 / ta_w, r0 = y0 / ta_h;
	int c1 = x1 / ta_w, r1 = y1 / ta_h;

	if ( c0 >= ta_cols || r0 >= ta_rows ) return;

	if ( c0 < 0 ) c0 = 0;
	if ( r0 < 0 ) r0 = 0;
	if ( c1 >= ta_cols ) c1 = ta_cols-1;
	if ( r1 >= ta_rows ) r1 = ta_rows-1;
/*
	printf( "Sprite rel coords (%03d, %03d)-(%03d, %03d)", x0, y0, x1, y1 );
	printf( " c/r (%02d,%02d)-(%02d,%02d)\n", c0, r0, c1, r1 );
	printf( "TileArray c/r (%02d,%02d) w/h (%02d,%02d)\n", ta_cols, ta_rows, ta_w, ta_h );
*/
	int hit = 0;
	for ( int c = c0; c <= c1; c++ )
		for ( int r = r0; r <= r1; r++ )
			if ( elem(c, r)->t_bitmap > 0 ) {
				elem(c, r)->hit_by( ta_blank_bitmap, s );
				hit = 1;
			}
	if ( hit ) s->hitting( this );
}

void TileArray::is_hit( SpriteGroup *sg )
{
	for ( Sprite *s = sg->begin(); s; s = sg->next() ) is_hit( s );
}

