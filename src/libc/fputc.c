/* fputc
   -----

The C library function int fputc(int char, FILE *stream) writes a character (an unsigned char)
specified by the argument char to the specified stream and advances the position indicator for
the stream.

Declaration: Following is the declaration for fputc() function.
  int fputc(int char, FILE *stream)

Parameters
  char −    This is the character to be written. This is passed as its int promotion.
  stream −  This is the pointer to a FILE object that identifies the stream where the character
            is to be written.

Return Value
  If there are no errors, the same character that has been written is returned. 
  If an error occurs, EOF is returned and the error indicator is set.
*/


#include <stdio.h>
#include <mos_api.h>

void fput_char( int c, FILE *stream );

int fputc(int c, FILE *stream)
{
    int ret = c;

    if (stream == NULL || stream == stdin) ret = EOF;
    else {
        if ( stream->text_mode && c == '\n' ) fput_char( '\r', stream );
        fput_char( c, stream );
    }

    if ( stream ) {
        if (ret == EOF) stream->eof = 1;
        if (ret != c) stream->err = 1;
    }
    
    return ret;
}

void fput_char( int c, FILE *stream )
{
    uint8_t mos_fh = stream->fhandle;

    if ( mos_fh == FH_STDOUT || mos_fh == FH_STDERR ) outchar(c);
    else mos_fputc(stream->fhandle, (char)c );         // The mos routine does not return anything
}