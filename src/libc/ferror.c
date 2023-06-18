/* ferror
   ------

The C library function int ferror(FILE *stream) tests the error indicator for the given stream.

Declaration: Following is the declaration for ferror() function.
  int ferror(FILE *stream)

Parameters
  stream −  This is the pointer to a FILE object that identifies the stream.

Return Value
  If the error indicator associated with the stream was set, the function returns a non-zero
  value else, it returns a zero value.

  If the stream pointer is NULL, the function invokes the invalid parameter handler, as
  described in Parameter validation. If execution is allowed to continue, errno is set to
  EINVAL and the ferror returns 0.
  Note - currently we don't have "invalid parameter handler"


There doesn't seem to be a standard for stdin, stdout, stderr. If these are to the
console assume 0 - i.e. no error. Otherwise normal for files.
*/

#include <stdio.h>
#include <errno.h>

int ferror(FILE *stream)
{
    if ( stream ) return stream->err;

    // if stream is a NULL pointer
    errno = EINVAL;
    return 0;
}

