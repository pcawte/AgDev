/* fgets
   -----

The C library function char *fgets(char *str, int n, FILE *stream) reads a line from the
specified stream and stores it into the string pointed to by str. It stops when either (n-1)
characters are read, the CR/LF character pair is read, or the end-of-file is reached, whichever
comes first.

Declaration: Following is the declaration for fgets() function.
  char *fgets(char *str, int n, FILE *stream)

Parameters
  str −     This is the pointer to an array of chars where the string read is stored.
  n −       This is the maximum number of characters to be read (including the final
            null-character). Usually, the length of the array passed as str is used.
  stream −  This is the pointer to a FILE object that identifies the stream where characters
            are read from.

Return Value
  On success, the function returns the same str parameter. If the End-of-File is encountered
  and no characters have been read, the contents of str remain unchanged and a null pointer
  is returned.

  If an error occurs, a null pointer is returned.
*/

#include <stdio.h>

char* fgets(char *__restrict str, int num, FILE *__restrict stream)
{
    int c;
    char *p = str;

    if (num == 1)
    {
        *p = '\0';
        return str;
    }

    for (; num > 1; num--)
    {
        if ((c = fgetc(stream)) == EOF) break;
        *p++ = c;
        if (c == '\n') break;
    }

    if (p == str) return NULL;
 
    *p = '\0';

    return str;
}
