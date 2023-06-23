/* rewind
   ------

The C library function void rewind(FILE *stream) sets the file
position to the beginning of the file of the given stream.

Declaration: Following is the declaration for ftell() function.
  void rewind(FILE *stream)

Parameters
  stream −  This is the pointer to a FILE object that specifies the stream.
 
*/


#include <stdio.h>

extern FILE _file_streams[FOPEN_MAX];

void rewind(FILE *stream)
{
    stream->eof = 0;

    (void)fseek(stream, 0L, SEEK_SET);
    return;
}
