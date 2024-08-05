#include "SpriteArray.hpp"
#include <stdio.h>

////////////// SpriteArray Class - derived from SpriteGroup //////////////

// Constructor

SpriteArray::SpriteArray( int cols, int rows, int col_w, int row_h, int x, int y, int dx, int dy,	
							int x0, int y0, int x1, int y1 )				
	: SpriteGroup( x0, y0, x1, y1 )
{
	array_size = rows * cols;
	num_cols = cols; num_rows = rows;
	sa_col_w = col_w; sa_row_h = row_h;

	array = new Sprite *[array_size];

	sa_x = x; sa_y = y;
	sa_dx = dx; sa_dy = dy;

	col_num_remain = new int[cols];
	for ( int c = 0; c < cols; c++ ) col_num_remain[c] = rows;
	col_min = 0;
	col_max = cols - 1;

	row_num_remain = new int[rows];
	for ( int r = 0; r < rows; r++ ) row_num_remain[r] = cols;
	row_min = 0;
	row_max = rows - 1;
}

// Elements

Sprite *SpriteArray::elem( int col, int row )
{
	return array[row + col*num_rows];
}

void SpriteArray::set_elem( int col, int row, Sprite *s )
{
	array[row + col*num_rows] = s;
	s->sprite_grp = this;
	num_elements++;
}

Sprite *SpriteArray::remove( Sprite *s )					// Removes element & returns it or NULL if not found
{
	Sprite **spp = array;

	for ( int c = 0; c < num_cols; c ++ )
		for ( int r = 0; r < num_rows; r++, spp++ )
			if ( *spp == s ) {
				*spp = NULL;
				num_elements--;
				update_min_max_col( c );
				update_min_max_row( r );
				return s;
			}
	return NULL;
}

void SpriteArray::update_min_max_col( int c ) {
	if ( !--col_num_remain[c] ) {
		if ( c == col_min ) {
			col_min++;
			while ( !col_num_remain[col_min] && col_min < col_max ) col_min++;
		}
		else if ( c == col_max ) {
			col_max--;
			while ( !col_num_remain[col_max] && col_max > col_min ) col_max--;
		}
	}	
}


void SpriteArray::update_min_max_row( int r ) {
	if ( !--row_num_remain[r] ) {
		if ( r == row_min ) {
			row_min++;
			while ( !row_num_remain[row_min] && row_min < row_max ) row_min++;
		}
		else if ( r == row_max ) {
			row_max--;
			while ( !row_num_remain[row_max] && row_max > row_min ) row_max--;
		}
	}	
}


// Required for iterators

Sprite *SpriteArray::begin()
{
	if ( !(cur_elem = array) ) return NULL;				// Return NULL if not initialised

	while ( cur_elem < array + array_size )				// Return element skipping over any blanks
		if ( *cur_elem ) return *cur_elem;
		else cur_elem++;
	return NULL;
}

Sprite *SpriteArray::next()
{
	while ( ++cur_elem < array + array_size )
		if ( *cur_elem ) return *cur_elem;
	return NULL;
}

// Movement

void SpriteArray::next_iter()
{
	next_step();
	next_frame();
}


void SpriteArray::next_step()
{
	// Check if about to move off the edge of the viewport (left & right)
	if ( sa_x + col_min*sa_col_w + sa_dx < sg_x0 ) at_left();
	if ( sa_x + (col_max+1)*sa_col_w + sa_dx >= sg_x1 ) at_right();

	for ( Sprite *s = begin(); s; s = next() ) {
		s->set_speed( sa_dx, sa_dy );
		s->next_step();
	}
	sa_x += sa_dx; sa_y += sa_dy;
}

// Events

void SpriteArray::at_left()
{
	sa_dx = -sa_dx;
}

void SpriteArray::at_right()
{
	sa_dx = -sa_dx;
}


// Debugging

void SpriteArray::dump()
{
	printf( "Alien columns [%d to %d]: ", col_min, col_max );
	for ( int c = 0; c <= col_max; c++ )
		printf( " %d", col_num_remain[c] );
	printf( "\nAlien rows [%d to %d]: ", row_min, row_max );
	for ( int r = 0; r <= row_max; r++ )
		printf( " %d", row_num_remain[r] );
	printf( "\n" );
}
