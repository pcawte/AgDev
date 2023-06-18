/* fwrite
   ------

The C library function size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
writes data from the array pointed to, by ptr to the given stream.

Declaration: Following is the declaration for fwrite() function.
  size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)

Parameters
  ptr −     This is the pointer to the array of elements to be written.
  size −    This is the size in bytes of each element to be written.
  nmemb −   This is the number of elements, each one with a size of size bytes.
  stream −  This is the pointer to a FILE object that specifies an output stream.

Return Value
    This function returns the total number of elements successfully returned as a size_t object,
    which is an integral data type. If this number differs from the nmemb parameter, it will
    show an error.
*/

#include <stdio.h>
#include <mos_api.h>

size_t fwrite(const void *__restrict ptr, size_t size, size_t count, FILE *__restrict stream)
{
    size_t nbytes;
    size_t len = size * count;

    if (stream == NULL || stream == stdin) return 0;

    // For stdout & stderr write characters one by one using fputc upto size*count characters

    if (stream == stdout || stream == stderr)
    {
        char *p = (char *)ptr;

        for ( nbytes = 0; nbytes < len; nbytes++ )
        {
            if (putchar(*p++) == EOF) break;
        }
        return nbytes / size;
    }

    // For regular file use mos_fwrite

    nbytes = mos_fwrite( stream->fhandle, (char *)ptr, len );
    if ( nbytes != len ) stream->err = 1;

    return nbytes / size;
}
