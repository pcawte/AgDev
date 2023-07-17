/* ferror
   ------

The C library function int fflush(FILE *stream) flushes the output buffer of a stream.

Declaration: Following is the declaration for fflush() function.
  int fflush(FILE *stream)

Parameters
  stream −  This is the pointer to a FILE object that specifies a buffered stream.

Return Value
  This function returns a zero value on success. If an error occurs, EOF is returned and
  the error indicator is set (i.e. feof).

Notes:
  This currently does nothing as stdio is not buffered.
*/

#include <stdio.h>

int fflush(FILE *stream)
{
    stream->unget_char = 0;
    return 0;
}
