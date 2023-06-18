/* fclose
   ------

The C library function int fclose(FILE *stream) function flushes the stream pointed to by stream
(writing any buffered output data using fflush(3)) and closes the underlying file descriptor.
Note that there is currently no buffering in this simple implimentation.

Declaration: Following is the declaration for fclose() function.
  int fclose(FILE *stream)

Parameters
  stream −  This is the pointer to a FILE object that identifies the stream where the character
            is to be written.

Return Value
  Upon successful completion, 0 is returned.  Otherwise, EOF is returned and errno is set to
  indicate the error.  In either case, any further access (including another call to fclose())
  to the stream results in undefined behavior.
*/

#include <stdio.h>
#include <mos_api.h>

extern FILE _file_streams[FOPEN_MAX];

int fclose(FILE *stream)
{
    uint8_t mos_fh;

    if (stream == NULL || stream == stdin || stream == stdout || stream == stderr) return EOF;

    mos_fh = stream->fhandle;
    _file_streams[mos_fh - 1].fhandle = 0;

    mos_fclose( mos_fh );           // Returns number of files still open - not an error indication

    return 0;                       // There is no error from MOS, so assume okay
}
