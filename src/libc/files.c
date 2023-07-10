#include <stdio.h>

// Allocate space for storage of the MOS file stream IDs and the status

FILE _file_streams[FOPEN_MAX];

// Allocate storage for the stdin, stdout, stderr files streams so that 
// assignments can be made to their status value
// - this was previously a bug in the CE Toolkit

FILE stdin[1]  = {{ FH_STDIN, 0, 0 }};
FILE stdout[1] = {{ FH_STDOUT, 0, 0 }};
FILE stderr[1] = {{ FH_STDERR, 0, 0 }};

// The following initialistion is called from crt0.src to re-initialise stdin, stdout, stderr
// - this is necessary in case these have been redirected and the program is re-run

void _stdio_init( void ) {
	*stdin  = (FILE){ FH_STDIN, 0, 0 };
	*stdout = (FILE){ FH_STDOUT, 0, 0 };
	*stderr = (FILE){ FH_STDERR, 0, 0 };
}