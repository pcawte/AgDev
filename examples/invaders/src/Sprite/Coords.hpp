#ifndef _COORDS_HPP

#define _COORDS_HPP


// Simple class to represent coordinates

class Coords {
public:
	int x, y;
	Coords() {}
	Coords( int xcoord, int ycoord ) { x=xcoord; y=ycoord; }
};

#endif