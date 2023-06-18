/************************************************************************/
/*									*/
/*			Copyright (C)1987-2008 by			*/
/*		            Zilog, Inc.           			*/
/*									*/
/*		        San Jose, California     			*/
/*									*/
/************************************************************************/
#include <stddef.h>
#include <string.h>

char *strtok(char *s1, const char *s2)
{
  static char *ptr;
  char *p;
  size_t l;

  if (s1)
    ptr = s1;

/* find first char not in s2 */

  if (!(l = strspn(ptr,s2)) && !*ptr )
    return(NULL);

  ptr += l;	/* ptr points to first token */
  s1 = ptr;		/* save beginning pointer */

/* search for end of token */

  p = strpbrk(ptr,s2);
  if (!p) {
    ptr += strlen(ptr);
    if ( s1 == ptr) 
      return(NULL);
  }
  else
  {
  	*p = '\0';		/* terminate string */
  	ptr = p + 1;		/* update ptr */
  }

  return(s1);
}
