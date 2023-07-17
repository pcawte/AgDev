/* ftell
   -----

The C library function long ftell(FILE *stream) gets the current position of a file pointer.

Declaration: Following is the declaration for ftell() function.
  long ftell(FILE *stream)

Parameters
  stream −  This is the pointer to a FILE object that specifies the stream.
 
Return Value
  ftell return the current file position. The value returned by ftell may not reflect the
  physical byte offset for streams opened in text mode, because text mode causes carriage
  return-line feed translation.

  On error, ftell invoke the invalid parameter handler, as described in Parameter validation.
  If execution is allowed to continue, these functions return -1L and set errno to one of two
  constants, defined in ERRNO.H. EINVAL means an invalid stream argument was passed to the
  function, also returns this for devices incapable of seeking
  (such as terminals and printers).
  On Agon there is currently no "invalid parameter handler"
*/

#include <stdio.h>
#include <errno.h>
#include <mos_api.h>

long int ftell(FILE *stream)
{
    if (stream == NULL || stream->fhandle >= FH_STDIN)
    {
        errno = EINVAL;
        return -1L;
    }

    FIL *file_struct = mos_getfil( stream->fhandle );

    return (long)(file_struct->fptr);
}
