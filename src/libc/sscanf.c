/************************************************************************/
/*									*/
/*			Copyright (C)1987-2008 by				*/
/*		            Zilog, Inc.           			*/
/*									*/
/*		        San Jose, California     			*/
/*									*/
/************************************************************************/
#include "format.h"
#include <stdarg.h>
#include <stdio.h>

/*************************************************
*
* sscanf - scan from a string
*
* Inputs:
*	string - string to print to
*	fmt - format string
*	args - argument list
*
* Returns:
*	Number of characters transmitted, or
*	-1 if an error occured.
*
*************************************************/

// simplidied version with multi-threading option stripped out

int sscanf( const char *string, const char *fmt,...)
{
  va_list ap;

  if(string == NULL)
	  return EOF;

  va_start(ap,fmt);
  return(_u_scan(string,fmt,ap));
}
