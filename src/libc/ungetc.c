/* ungetc
   ------

The C library function int ungetc(int char, FILE *stream) pushes the character char (an unsigned
char) onto the specified stream so that the this is available for the next read operation.

Declaration: Following is the declaration for ungetc() function.
  int ungetc(int char, FILE *stream)

Parameters
  char −    This is the character to be put back. This is passed as its int promotion.
  stream −  This is the pointer to a FILE object that identifies the stream where the character
            is to be written.

Return Value
  If successful, it returns the character that was pushed back
  otherwise, EOF is returned and the stream remains unchanged.
*/

#include <stdio.h>

int ungetc(int c, FILE *stream)
{
    if (stream == NULL || stream == stdout || stream == stderr) return EOF;
    if (stream->unget_char) return EOF;
    
    stream->unget_char = c;
    return c;
}
