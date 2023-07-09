#include <stdio.h>

// Allocate space for storage of the MOS file stream IDs and the status

FILE _file_streams[FOPEN_MAX];

// Allocate storage for the stdin, stdout, stderr files streams so that 
// assignments can be made to their status value
// - this was previously a bug in the CE Toolkit

FILE stdin[1]  = {{ FH_STDIN, 0, 0 }};
FILE stdout[1] = {{ FH_STDOUT, 0, 0 }};
FILE stderr[1] = {{ FH_STDERR, 0, 0 }};