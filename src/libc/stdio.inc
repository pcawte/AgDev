;
; Title:	STDIO constants for stdin, stdout, stderr
; Author:	Paul Cawte
; Created:	09/06/23
; Last Updated:	09/06/23
;
; Modinfo:
; 09/06/23:	Created
; 17/06/23:	Additional offsets into FILE * structure added

; Note - these constants need to be aligned with those used in <stdio.h>

; File stream id's used to denote the default stdin, stdout, stderr in FILE * structure

FH_STDIN 	:=	128
FH_STDOUT 	:=	129
FH_STDERR 	:=	130

; Offsets into FILE * structure

FILE_FH		:=	0
FILE_EOF	:=	1
FILE_ERR	:=	2
FILE_TEXT_MODE	:=	3
FILE_UNGET_CHAR	:=	4
