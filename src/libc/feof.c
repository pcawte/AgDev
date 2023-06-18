/* feof
   -----

The C library function int feof(FILE *stream) tests the end-of-file indicator for the given
stream.

Declaration: Following is the declaration for feof() function.
  int feof(FILE *stream)

Parameters
  stream −  This is the pointer to a FILE object that identifies the stream.

Return Value
  This function returns a non-zero value when End-of-File indicator associated with the
  stream is set, else zero is returned.
  If the stream pointer is NULL, the function invokes the invalid parameter handler, as
  described in Parameter validation. If execution is allowed to continue, errno is set to
  EINVAL and the feof returns 0.
  Note - currently we don't have "invalid parameter handler"

There doesn't seem to be a standard for feof of stdin, stdout, stderr.
  stdin  -  On some system ^Z or ^D is end of file, but Agon getchar does not return this.
            if fgetc(stdin) receives EOF then will set EOF flag
  stdout -  Presumably cannot be EOF
  stderr -  Presumably cannot be EOF
*/

#include <stdio.h>
#include <errno.h>

int feof(FILE *stream)
{
    if ( stream ) return stream->eof;

    // if stream is a NULL pointer
    errno = EINVAL;
    return 0;
}
