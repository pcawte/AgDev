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
  constants, defined in ERRNO.H. The EBADF constant means the stream argument isn't a valid
  file pointer value or doesn't refer to an open file. EINVAL means an invalid stream argument
  was passed to the function. On devices incapable of seeking (such as terminals and printers),
  or when stream doesn't refer to an open file, the return value is undefined.
  On Agon there is currently no "invalid parameter handler"

  NOTE: this functionality is not currently exposed by MOS and returns -1L with EMOSNOSUPPORT 
*/



#include <stdio.h>
#include <errno.h>

long int ftell(FILE *stream)
{
    if (stream == NULL || stream == stdin || stream == stdout || stream == stderr)
    {
        errno = EINVAL;
        return -1L;
    }

    // return not supported

    errno = EMOSNOSUPPORT;
    return -1L;
}
