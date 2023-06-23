/* remove
   ------

The C library function int remove(const char *filename) deletes the given
filename so that it is no longer accessible.

Declaration: Following is the declaration for remove() function.
  int remove(const char *filename)

Parameters
  filename − This is the C string containing the name of the file to be deleted.

Return Value
  On success, zero is returned. On error, -1 is returned, and errno is set appropriately.
 
*/

#include <stdio.h>
#include <mos_api.h>
#include <errno.h>

int remove(const char *fname)
{
    int stat;

    if ( !(stat = mos_del(fname)) ) return 0;

    switch( stat )
    {
        case FR_NO_FILE:
        case FR_NO_PATH:
        case FR_INVALID_NAME:
            errno = ENOENT;
            break;
        case FR_DENIED:
        case FR_EXIST:
        case FR_WRITE_PROTECTED:
            errno = EACCES;
            break;
        default:
            errno = EINVAL;
    }

    return -1;
}
