/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/

// This version is a simplified version with the multi-threading stripped out

#ifndef FORMAT_H
#define FORMAT_H

#include <stdarg.h>
#include "stdio.h"
#include "features.h"

#ifndef _PTR_
#define _PTR_ *
#endif

/* Note: 24 bits times log(2) is 7.224 decimal digits.
   We only need 14 if and when we support doubles. <THH> */
#define MAXDIGITS 10
#define MINEXP -4
#define DEFAULT_PRECISION 6


/* format status codes */
#define FMT_OK 0
#define FMT_ERR 1
#define FMT_PASS_THRU 2

/* format flags */
#define FMT_FLAG_MINUS	0x01
#define FMT_FLAG_PLUS	0x02
#define FMT_FLAG_SPACE	0x04
#define FMT_FLAG_POUND	0x08
#define FMT_FLAG_IGNORE 0x10    // scanf only.
#define FMT_FLAG_PRECISION 0x10 // Only needed for %s, as 0 is valid precision
#define FMT_FLAG_UPPERCASE 0x20	// Added. <THH>
#define FMT_FLAG_PAD_ZERO 0x40
#define FMT_FLAG_STRIP	0x80	// Output only. <THH>
#define FMT_FLAG_SET	0x80	// Input only; maybe not needed if
				// set_begin != 0 is used instead. <THH>

/*	structures and defines for format routines	                 */
/*      NOTE: Some fields in this structure, and the bits in flags, are  */
/*            known to the optimizer,  If you change this, check out the */
/*            optimizer code in genprintf.c .                            */

struct fmt_type {
  unsigned char status;		/* status, OK, ERR, or PASS_THRU */
  unsigned char flags;		/* flags bit mask */
  char size;			/* size character h,l or L */
  char chr;			/* pass thru character */
  char type;			/* type of argument d,i,o,u,x ... */
  unsigned char field_width;		/* field width */ // LLVM port, changed to unsigned
  char precision;		/* precision */
  const char _PTR_ set_begin;		/* pointer to first char in set */  // LLVM port - const
  const char _PTR_ set_end;   	/* pointer to last char in set */   // LLVM port - const
  unsigned char pad_whole;
  unsigned char pad_pre_fract;
  unsigned char pad_post_fract;
  char _PTR_ pad_at;
  };

/* info flags */
#define FLT_INFO_SIGN	(1<<0)
#define FLT_INFO_INF	(1<<1)
#define FLT_INFO_NAN	(1<<2)

/* Note: using char to represent the (decimal) exponent only works for
   4-byte floats.  If we choose to support 8-byte doubles, then this must
   be increased. <THH> */
struct flt_info {
  unsigned char flags;			/* 1=sign, 2=inf, 4=nan        */
  char exp;				/* (signed) exponent (base 10) */
  unsigned char digits[MAXDIGITS];	/* max significant digits      */
};

extern struct fmt_type __print_fmt;
extern char __print_buff[];
extern unsigned char __print_len;
extern char __print_leading_char;  // Initial +, -, or space for number
extern char _PTR_ __print_out;

extern void __print_send();
extern void __fprint_send();
// The next 2 lines don't seem to be inlcude - remove as solves problem with "reentrant"
//extern reentrant void __print_uputch(char);  // Putch to uart
//extern reentrant void __print_sputch(char);  // Putch to sprintf buffer
extern void (*__print_xputch)(char);
extern void __print_sendstring(char _PTR_);
extern void __print_putch(char);
//extern void __print_putromstring(char rom * sp);

extern void _u_stoa(short);
extern void _u_ustoa(unsigned short);
extern void _u_itoa(int);
extern void _u_uitoa(unsigned int);
extern void _u_ltoa(long);
extern void _u_ultoa(unsigned long);
extern int  _u_print(char _PTR_ src,char _PTR_ fmt,va_list);
extern int  _u_scan(FILE _PTR_ fp, const char _PTR_ src, const char _PTR_ fmt,va_list ap); // LLVM port added const
extern void _u_dtof(double);
extern void _u_dtog(double);

extern char _PTR_ _u_pscan(char _PTR_ fmt,struct fmt_type _PTR_ str, va_list _PTR_ argp);
extern const char _PTR_ _u_sscan( const char _PTR_ fmt,struct fmt_type _PTR_ str);

extern void _u_reverse(char _PTR_ s);
extern char _PTR_ _u_dtoe(double);

extern void _u_flt_info(double,struct flt_info _PTR_);
extern void _u_flt_rnd(struct flt_info _PTR_ , char);
#endif
