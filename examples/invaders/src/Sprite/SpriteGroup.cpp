#include "SpriteList.hpp"
#include <stdbool.h>
#include <stdlib.h>
#include <agon/vdp_vdu.h>
#include <stdio.h>

////////////// Sprite Group Class //////////////

// Constructor

SpriteGroup::SpriteGroup( int x0, int y0, int x1, int y1 )
{
	sg_x0 = x0; sg_y0 = y0;
	sg_x1 = x1; sg_y1 = y1;
}

// Actions

void SpriteGroup::move_by( int dx, int dy )
{
	for ( Sprite *s = begin(); s; s = next() ) s->move_by( dx, dy );
} 

void SpriteGroup::next_frame()
{
	for ( Sprite *s = begin(); s; s = next() ) s->next_frame();
} 

void SpriteGroup::prev_frame()
{
	for ( Sprite *s = begin(); s; s = next() ) s->prev_frame();
} 

void SpriteGroup::next_step()
{
	for ( Sprite *s = begin(); s; s = next() ) s->next_step();
} 

void SpriteGroup::prev_step()
{
	for ( Sprite *s = begin(); s; s = next() ) s->prev_step();
} 

void SpriteGroup::next_iter()
{
	for ( Sprite *s = begin(); s; s = next() ) s->next_iter();
} 

void SpriteGroup::prev_iter()
{
	for ( Sprite *s = begin(); s; s = next() ) s->prev_iter();
} 

void SpriteGroup::hide()
{
	for ( Sprite *s = begin(); s; s = next() ) s->hide();
} 

void SpriteGroup::show()
{
	for ( Sprite *s = begin(); s; s = next() ) s->show();
} 

// Collisions ////////////////////////////////////////

// If Sprite s hits member of SpriteGroup, sp 
//	- trigger hit_by() events on sp and hitting() events on s
// 	- repeat for all memembers of the SpriteGroup - i.e. s may hit multiple SpriteGroup members
//  - note that s and/or sp may be deleted as a result in the event handler
//	- so explicitly check wether s becomes NULL as part of the for loop condition

void SpriteGroup::is_hit( Sprite *s )
{
	for ( Sprite *sp = begin(); s && sp; sp = next() ) s->hit( sp );
}

// If member of SpriteGroup sp hits member of Sprite s 
//	- trigger hittting() events on sp and hit_by() events on s
// 	- repeat for all memembers of the SpriteGroup
//  - note that s and/or sp may be deleted as a result in the event handler
//	- so explicitly check wether s becomes NULL as part of the for loop condition

void SpriteGroup::hit( Sprite *s )
{
	for ( Sprite *sp = begin(); s && sp; sp = next() ) sp->hit( s );
}

// If member of SpriteGroup sp hits member of SpriteGroup sg 
//	- trigger hitting() events on sp and hit_by() events on the member of sg
// 	- repeat for all memembers of the SpriteGroup
//  - note that members of either SpriteGroup maybe deleted as a result of events
//	- this dealt with by the called routines - don't need to explicitly handle here

void SpriteGroup::hit( SpriteGroup *sg )
{
	for ( Sprite *sp = begin(); sp; sp = next() ) sg->is_hit( sp );
}

// If members of SpriteList sp hits elements of TileArray ta 
//	- trigger hitting() events on sp and hit_by() events on the elements of ta
// 	- repeat for all memembers of the SpriteGroup
//  - note that members of the SpriteGroup or TileArray maybe deleted as a result of events
//	- this dealt with by the called routines - don't need to explicitly handle here

void SpriteGroup::hit( TileArray *ta )
{
	for ( Sprite *sp = begin(); sp; sp = next() ) ta->is_hit( sp );
}

// Debugging

void SpriteGroup::dump()
{
	printf( "SpriteGroup Elements: %d\n", num_elements );
	int i = 0;
	for ( Sprite *s = begin(); i <= num_elements; s = next(), i++ )
		printf( "Sprite[%d] at %p\n", i, s );
}
