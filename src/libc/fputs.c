/* fputs
   -----

The C library function int fputs(const char *str, FILE *stream) writes a string to the specified
stream up to but not including the null character.

Declaration: Following is the declaration for fputs() function.
  int fputs(const char *str, FILE *stream)

Parameters
  str −     This is an array containing the null-terminated sequence of characters to be written.
  stream −  This is the pointer to a FILE object that identifies the stream where the string is
            to be written.

Return Value
  This function returns a non-negative value, or else on error it returns EOF.
*/

#include <stdio.h>

int fputs(const char *__restrict str, FILE *__restrict stream)
{
    unsigned int i = 0;
    char c;

    while ((c = str[i]))
    {
        if (fputc(c, stream) == EOF) return EOF;
        i++;
    }

    if (fputc('\r', stream) == EOF) return EOF;
    if (fputc('\n', stream) == EOF) return EOF;

    return 1;
}
