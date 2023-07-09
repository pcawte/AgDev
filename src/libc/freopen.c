/* freopen
   -------

The C library function FILE *freopen(const char *filename, const char *mode, FILE *stream)
associates a new filename with the given open stream and at the same time closes the old
file in the stream.

The primary use case is to redirect: stdin, stdout and stderr
  - for normal files can just use fclose() and fopen()

Declaration: Following is the declaration for freopen() function.
  FILE *freopen(const char *filename, const char *mode, FILE *stream)

Parameters
  filename −  This is the C string containing the name of the file to be opened.

  mode −      This is the C string containing a file access mode (see fopen())
  stream −    This is the pointer to a FILE object that identifies the stream to be re-opened.

Return Value
  If the file was re-opened successfully, the function returns a pointer to an object
  identifying the stream or else, null pointer is returned.
*/

#include <stdio.h>
#include <mos_api.h>

FILE *freopen( const char *__restrict filename, const char *__restrict mode, FILE *stream )
{
    FILE *fp;
    uint8_t mos_fh;

    if ( stream == NULL ) return NULL;

    mos_fh = stream->fhandle;
    if ( mos_fh != FH_STDIN && mos_fh != FH_STDOUT && mos_fh != FH_STDERR )
        fclose( stream );

    if ( !( fp = fopen( filename, mode ) ) ) return NULL;

    *stream = *fp;
    return stream;
}