/* fgetc
   -----

The C library function int fgetc(FILE *stream) gets the next character (an unsigned char) from
the specified stream and advances the position indicator for the stream.

Declaration: Following is the declaration for fgetc() function.
  int fgetc(FILE *stream)

Parameters
  stream −  This is the pointer to a FILE object that identifies the stream on which the
            operation is to be performed.

Return Value
    This function returns the character read as an unsigned char cast to an int or EOF on end
    of file or error.
*/

#include <stdio.h>
#include <mos_api.h>

int fgetc(FILE *stream)
{
    int c;
    uint8_t mos_fh = stream->fhandle;

    if (stream == NULL || stream == stdout || stream == stderr) c = EOF;
    else if (mos_fh == FH_STDIN) {
        c = inchar();
        putchar(c);
    }
    else c = mos_fgetc(stream->fhandle);

    if ( c == 0 ) c = EOF;              // mos routine returns zero if error

    if ( stream ) {
        if (c == EOF) stream->eof = 1;
    }

    return c;
}
