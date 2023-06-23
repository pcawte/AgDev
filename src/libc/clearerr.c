/* clearerr
   --------

The C library function void clearerr(FILE *stream) clears the end-of-file and error
indicators for the stream pointed to by stream.

Declaration: Following is the declaration for ftell() function.
  void clearerr(FILE *stream)

Parameters
  stream −  This is the pointer to a FILE object that specifies the stream.
 
*/

#include <stdio.h>
#include <errno.h>
#include <mos_api.h>

extern FILE _file_streams[FOPEN_MAX];

void clearerr(FILE *stream)
{
    if ( stream == NULL ) return;

    _file_streams[stream->fhandle].eof = 0;
    _file_streams[stream->fhandle].err = 0;
    return;
}
