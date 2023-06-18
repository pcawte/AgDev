/* fread
   -----

The C library function size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
reads data from the given stream into the array pointed to, by ptr.

Declaration: Following is the declaration for fread() function.
  size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)

Parameters
  ptr −     This is the pointer to a block of memory with a minimum size of size*nmemb bytes.
  size −    This is the size in bytes of each element to be read.
  nmemb −   This is the number of elements, each one with a size of size bytes.
  stream −  This is the pointer to a FILE object that specifies an input stream.

Return Value
  The total number of elements successfully read are returned as a size_t object, which is
  an integral data type. If this number differs from the nmemb parameter, then either an
  error had occurred or the End Of File was reached.
*/

#include <stdio.h>
#include <mos_api.h>

size_t fread(void *ptr, size_t size, size_t count, FILE *__restrict stream)
{
    size_t nbytes;
    size_t len = size * count;

    if (stream == NULL || stream == stdout || stream == stderr) return 0;

    // For stdin read characters one by one using fgetc upto size*count characters

    if (stream == stdin)
    {
        int c;
        char *p = (char *)ptr;

        for ( nbytes = 0; nbytes < len; nbytes++ )
        {
            if ((c = fgetc(stream)) == EOF) break;
            *p++ = c;
        }
        return nbytes / size;
    }

    // For regular file use mos_fread

    nbytes = mos_fread( stream->fhandle, ptr, len );
    if ( nbytes != len ) stream->err = 1;

    return nbytes / size;
}
