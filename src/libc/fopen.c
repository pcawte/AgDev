/* fopen
   -----

Paul Cawte 13/06/2023

The fopen() function opens the file whose name is the string
pointed to by pathname and associates a stream with it.

The argument mode points to a string beginning with one of the
following sequences (possibly followed by additional characters,
as described below):

r      Open text file for reading.  The stream is positioned at
       the beginning of the file.

r+     Open for reading and writing.  The stream is positioned at
       the beginning of the file.

w      Truncate file to zero length or create text file for
       writing.  The stream is positioned at the beginning of the
       file.

w+     Open for reading and writing.  The file is created if it
       does not exist, otherwise it is truncated.  The stream is
       positioned at the beginning of the file.

a      Open for appending (writing at end of file).  The file is
       created if it does not exist.  The stream is positioned at
       the end of the file.

a+     Open for reading and appending (writing at end of file).
       The file is created if it does not exist.  Output is
       always appended to the end of the file.  POSIX is silent
       on what the initial read position is when using this mode.
       For glibc, the initial file position for reading is at the
       beginning of the file, but for Android/BSD/MacOS, the
       initial file position for reading is at the end of the
       file.

wx     Like w, but returns an error if the file already exists.

w+x    Like w+, but returns an error if the file already exists.
       x modifier can only be appended to the end 


If a file that does not exist is opened for writing or appending, it is created if possible.
Opening an existing file for writing causes the old contents to be discarded, while opening
for appending preserves them. Trying to read a file that does not exist is an error.

The mode string can also include the letter 'b' either as a last character or as a character
between the characters in any of the two-character strings described above.  This is strictly
for compatibility with C89 and has no effect; the 'b' is ignored on all POSIX conforming systems,
including Linux.  (Other systems may treat text files and binary files differently, and adding
the 'b' may be a good idea if you do I/O to a binary file and expect that your program may be
ported to non-UNIX environments.)

Return value:
       Upon successful completion fopen()
       return a FILE pointer.  Otherwise, NULL is returned and errno is
       set to indicate the error.

Calls: uint8_t  mos_fopen(char *fname, unit8_t mode);   // returns filehandle, or 0 on error

Mode flag - from FatFS documentation:

FA_READ             Specifies read access to the file. Data can be read from the file.
FA_WRITE            Specifies write access to the file. Data can be written to the file. Combine with FA_READ for read-write access.
FA_OPEN_EXISTING    Opens a file. The function fails if the file is not existing. (Default)
FA_CREATE_NEW       Creates a new file. The function fails with FR_EXIST if the file is existing.
FA_CREATE_ALWAYS    Creates a new file. If the file is existing, it will be truncated and overwritten.
FA_OPEN_ALWAYS      Opens the file if it is existing. If not, a new file will be created.
FA_OPEN_APPEND      Same as FA_OPEN_ALWAYS except the read/write pointer is set end of the file.

"r"                 FA_READ
"r+"                FA_READ | FA_WRITE
"w"                 FA_CREATE_ALWAYS | FA_WRITE
"w+"                FA_CREATE_ALWAYS | FA_WRITE | FA_READ
"a"                 FA_OPEN_APPEND | FA_WRITE
"a+"                FA_OPEN_APPEND | FA_WRITE | FA_READ
"wx"                FA_CREATE_NEW | FA_WRITE
"w+x"               FA_CREATE_NEW | FA_WRITE | FA_READ
*/

//#include <fileioc.h>

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <mos_api.h>

extern FILE _file_streams[FOPEN_MAX];

uint8_t __fmodeflags(const char *);

FILE* fopen(const char *__restrict filename, const char *__restrict mode)
{
    uint8_t mos_fh;             // file handled returned by MOS (0 = error)
    uint8_t index;              // index into _file_streams table
    uint8_t flags;              // flags computed from the mode string


    /* Check for valid initial mode character */
    if (!strchr("rwa", *mode)) {
        errno = EINVAL;       
        return NULL;
    }

    /* Compute the flags to pass to open() */
    flags = __fmodeflags(mode);


    mos_fh = mos_fopen(filename, flags);
    if (mos_fh == 0)
    {
        return NULL;
    }

    index = mos_fh - 1;
    _file_streams[index].fhandle = mos_fh;
    _file_streams[index].eof = 0;
    _file_streams[index].err = 0;

    return &_file_streams[index];
}


uint8_t __fmodeflags(const char *mode)
{
    uint8_t flags;

    if (strchr(mode, '+')) flags = FA_READ | FA_WRITE;
    else if (*mode == 'r') flags = FA_READ;
    else flags = FA_WRITE;

    if (*mode == 'w') {
       if (strchr(mode, 'x')) flags |= FA_CREATE_NEW;
              else flags |= FA_CREATE_ALWAYS;
       }
    if (*mode == 'a') flags |= FA_OPEN_APPEND;

    return flags;
}

/* Mapping of mode string to flags from FatFS documents (copied here for reference)
"r"                 FA_READ
"r+"                FA_READ | FA_WRITE
"w"                 FA_CREATE_ALWAYS | FA_WRITE
"w+"                FA_CREATE_ALWAYS | FA_WRITE | FA_READ
"a"                 FA_OPEN_APPEND | FA_WRITE
"a+"                FA_OPEN_APPEND | FA_WRITE | FA_READ
"wx"                FA_CREATE_NEW | FA_WRITE
"w+x"               FA_CREATE_NEW | FA_WRITE | FA_READ
*/