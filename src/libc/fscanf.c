
// This version is a simplified version with the multi-threading stripped out

// Updates by Paul Cawte
// 24/07/2023 - created to add fscanf support to existing scanf library
#include "format.h"
#include <stdarg.h>
#include <stdio.h>

/*************************************************
*
* scanf - scan from stdin
*
* Inputs:
*	fmt - format string
*	args - argument list
*
* Returns:
*	Number of characters transmitted, or
*	-1 if an error occured.
*
*************************************************/
int fscanf( FILE *fp, const char *fmt,...)
{
  va_list ap;

  va_start(ap,fmt);
  return _u_scan( fp, (void *)NULL, fmt, ap );
}
