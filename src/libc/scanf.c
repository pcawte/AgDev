/************************************************************************/
/*									*/
/*			Copyright (C)1987-2008 by				*/
/*		            Zilog, Inc.           			*/
/*									*/
/*		        San Jose, California     			*/
/*									*/
/************************************************************************/

// This version is a simplified version with the multi-threading stripped out

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
int scanf( const char *fmt,...)
{
  va_list ap;

  va_start(ap,fmt);
  return(_u_scan((void *)NULL,fmt,ap));
}
