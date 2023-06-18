/* fseek
   -----

The C library function int fseek(FILE *stream, long int offset, int origin)
moves the file pointer to a specified location.

Declaration: Following is the declaration for fseek() function.
  int fseek(FILE *stream, long int offset, int origin)

Parameters
  stream −  This is the pointer to a FILE object that specifies the stream.
  offset −  Number of bytes from origin
  origin −  Initial position.

    The argument origin must be one of the following constants, defined in STDIO.H:
    SEEK_CUR    Current position of file pointer.
    SEEK_END    End of file.
    SEEK_SET    Beginning of file.

    NOTE: Due to limitation of MOS API, currently only SEEK_SET is supported

Return Value
  If successful, fseek and returns 0. Otherwise, it returns a nonzero value. On
  devices incapable of seeking, the return value is undefined. If stream is a null pointer,
  or if origin isn't one of allowed values described below, the function invokes the
  invalid parameter handler, as described in Parameter validation. If execution is allowed
  to continue, these functions set errno to EINVAL and return -1.
  On Agon there is currently no "invalid parameter handler"

*/

#include <stdio.h>
#include <mos_api.h>
#include <errno.h>

int fseek(FILE *stream, long int offset, int origin)
{
    if (stream == NULL || stream == stdin || stream == stdout || stream == stderr )
    {
        errno = EINVAL;
        return -1;
    }
    if ( origin != SEEK_SET )
    {
        errno = EMOSNOSUPPORT;
        return -1;
    }

    return mos_flseek( stream->fhandle, offset );
}
