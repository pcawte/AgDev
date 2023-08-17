#ifndef _CONFIG_HPP

#define _CONFIG_HPP

// Overall configuration constants

#define SC_MODE 1
#define SC_WIDTH 512
#define SC_HEIGHT 384

#define MAX_SPRITES 255						// Maximum number of simultaneous sprites

// Bitmap allocation
//  0-3		Alien
//  4-7		Alien explosion (this is also used for ship explosion)
//	8-31	Ship rotations
// 	252 	Bomb bitmap
//	253 	Bullet bitmap
//	254 	Solid bitmap
//	255		blank bitmap

// Definitions for ship

#define SHIP_FNAME_PREFIX "bitmaps/ship"
#define SHIP_FNAME_FORMAT "%s%02d.rgba"
#define SHIP_WIDTH 16
#define SHIP_HEIGHT 16
#define SHIP_BITMAP_ID_START 8
#define SHIP_BITMAP_ID_NUM 24

#define SHIP_X 256 							// Top left corner (x)
#define SHIP_Y 300 							// Top left corner (y)
#define SHIP_BORDER 3 						// Border within sprite for collision detection

#define SHIP_NUM_ROT 24

// Definitions for aliens

#define ALIEN_FNAME_PREFIX "bitmaps/gal-red"
#define ALIEN_FNAME_FORMAT "%s%1d.rgba"
#define ALIEN_WIDTH 16
#define ALIEN_HEIGHT 16
#define ALIEN_BITMAP_ID_START 0
#define ALIEN_BITMAP_ID_NUM 4

#define ALIEN_COLS 10
#define ALIEN_ROWS 5
#define NUM_ALIENS 50
#define ALIEN_X 64							// Top left corner (x) of 1st alien
#define ALIEN_Y 64							// Top left corner (y) of first alien
#define ALIEN_X_SPACING 32					// Spacing between aliens (x)
#define ALIEN_Y_SPACING 32					// Spacing between aliens (y)
#define ALIEN_SPEED 2 						// Horizontal step / speed
#define ALIEN_STEP 16						// Vrtical step when reaches end of line
#define ALIEN_BORDER 3 						// Border within sprite for collision detection

#define EXPLODE_FNAME_PREFIX "bitmaps/gal-explode"
#define EXPLODE_FNAME_FORMAT "%s%1d.rgba"
#define EXPLODE_WIDTH 16
#define EXPLODE_HEIGHT 16
#define EXPLODE_BITMAP_ID_START 4
#define EXPLODE_BITMAP_ID_NUM 4

// Definitions for bombs

#define BOMB_BITMAP 252
#define BOMB_WIDTH 2
#define BOMB_HEIGHT 2
#define BOMB_STEP 2

#define BOMB_COLOUR_R 0
#define BOMB_COLOUR_G 255
#define BOMB_COLOUR_B 255
#define BOMB_COLOUR_A 255

// Definitions for bullets

#define BULLET_BITMAP 253
#define BULLET_WIDTH 2
#define BULLET_HEIGHT 4
#define BULLET_STEP -4

#define BULLET_COLOUR_R 255
#define BULLET_COLOUR_G 255
#define BULLET_COLOUR_B 0
#define BULLET_COLOUR_A 255

// Definitions for barrier / bases

#define BLANK_BITMAP 255
#define SOLID_BITMAP 254
#define BARRIER_X 48
#define BARRIER_Y 240
#define BARRIER_BLOCK_W 1
#define BARRIER_BLOCK_H 1
#define BARRIER_ROWS 24
#define BARRIER_COLS 32
#define BARRIER_SPACING 64
#define BARRIER_NUM 7

#define BARRIER_CLEAR_C0 8
#define BARRIER_CLEAR_R0 12
#define BARRIER_CLEAR_C1 23
#define BARRIER_CLEAR_R1 24

extern int score;

#endif