#include "barrier.hpp"
#include "Sprite/Tile.hpp"
#include "config.hpp"
#include <agon/vdp_vdu.h>

TileArray *barrier[BARRIER_NUM];

void barrier_init()
{
	vdp_select_bitmap( SOLID_BITMAP );
	vdp_solid_bitmap( BARRIER_BLOCK_W, BARRIER_BLOCK_H, 255, 255, 255, 255 );
	vdp_select_bitmap( BLANK_BITMAP );
	vdp_solid_bitmap( BARRIER_BLOCK_W, BARRIER_BLOCK_H, 0, 0, 0, 255 );


	int b_x = BARRIER_X;
	for ( int b = 0; b < BARRIER_NUM; b++ )
	{
		barrier[b] = new TileArray( BARRIER_COLS, BARRIER_ROWS, b_x, BARRIER_Y,
								BARRIER_BLOCK_W, BARRIER_BLOCK_H, SOLID_BITMAP, BLANK_BITMAP );
		barrier[b]->clear( BARRIER_CLEAR_C0, BARRIER_CLEAR_R0, BARRIER_CLEAR_C1, BARRIER_CLEAR_C1 );
		barrier[b]->draw();
		b_x += BARRIER_SPACING;
	}
}