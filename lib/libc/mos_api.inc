;
; Title:	AGON MOS - API for user projects
; Author:	Dean Belfield
; Created:	03/08/2022
; Last Updated:	15/04/2023
; Adjusted for fasmg assembler (Paul Cawte, 16/06/2023)
;
; Modinfo:
; 05/08/2022:	Added mos_feof
; 09/08/2022:	Added system variables: cursorX, cursorY
; 18/08/2022:	Added system variables: scrchar, scrpixel, audioChannel, audioSuccess, vpd_pflags
; 05/09/2022:	Added mos_ren, vdp_pflag_mode
; 24/09/2022:	Added mos_getError, mos_mkdir
; 13/10/2022:	Added mos_oscli
; 23/02/2023:	Added more sysvars, fixed typo in sysvar_audioSuccess, offsets for sysvar_scrCols, sysvar_scrRows
; 04/03/2023:	Added sysvar_scrpixelIndex
; 08/03/2023:	Renamed sysvar_keycode to sysvar_keyascii, added sysvar_vkeycode
; 15/03/2023:	Added mos_copy, mos_getrtc, mos_setrtc, rtc, vdp_pflag_rtc
; 21/03/2023:	Added mos_setintvector, sysvars for keyboard status, vdu codes for vdp
; 22/03/2023:	The VDP commands are now indexed from 0x80
; 29/03/2023:	Added mos_uopen, mos_uclose, mos_ugetc, mos_uputc
; 13/04/2023:	Added FatFS file structures (FFOBJID, FIL, DIR, FILINFO)
; 15/04/2023:	Added mos_getfil, mos_fread, mos_fwrite and mos_flseek

; VDP control (VDU 23, 0, n)
;
vdp_gp			:= 	080h
vdp_keycode		:= 	081h
vdp_cursor		:=	082h
vdp_scrchar		:=	083h
vdp_scrpixel		:=	084h
vdp_audio		:=	085h
vdp_mode		:=	086h
vdp_rtc			:=	087h
vdp_keystate		:=	088h
vdp_logicalcoords	:=	0C0h
vdp_terminalmode	:=	0FFh

; MOS high level functions
;
mos_getkey		:=	000h
mos_load		:=	001h
mos_save		:=	002h
mos_cd			:=	003h
mos_dir			:=	004h
mos_del 		:=	005h
mos_ren			:=	006h
mos_mkdir		:=	007h
mos_sysvars		:=	008h
mos_editline		:=	009h
mos_fopen		:=	00Ah
mos_fclose		:=	00Bh
mos_fgetc		:=	00Ch
mos_fputc		:=	00Dh
mos_feof		:=	00Eh
mos_getError		:=	00Fh
mos_oscli		:=	010h
mos_copy		:=	011h
mos_getrtc		:=	012h
mos_setrtc		:=	013h
mos_setintvector	:=	014h
mos_uopen		:=	015h
mos_uclose		:=	016h
mos_ugetc		:=	017h
mos_uputc		:= 	018h
mos_getfil		:=	019h
mos_fread		:=	01Ah
mos_fwrite		:=	01Bh
mos_flseek		:=	01Ch

; FatFS file access functions
;
ffs_fopen		:=	080h
ffs_fclose		:=	081h
ffs_fread		:=	082h
ffs_fwrite		:=	083h
ffs_flseek		:=	084h
ffs_ftruncate		:=	085h
ffs_fsync		:=	086h
ffs_fforward		:=	087h
ffs_fexpand		:=	088h
ffs_fgets		:=	089h
ffs_fputc		:=	08Ah
ffs_fputs		:=	08Bh
ffs_fprintf		:=	08Ch
ffs_ftell		:=	08Dh
ffs_feof		:=	08Eh
ffs_fsize		:=	08Fh
ffs_ferror		:=	090h

; FatFS directory access functions
;
ffs_dopen		:=	091h
ffs_dclose		:=	092h
ffs_dread		:=	093h
ffs_dfindfirst		:=	094h
ffs_dfindnext		:=	095h

; FatFS file and directory management functions
;
ffs_stat		:=	096h
ffs_unlink		:=	097h
ffs_rename		:=	098h
ffs_chmod		:=	099h
ffs_utime		:=	09Ah
ffs_mkdir		:=	09Bh
ffs_chdir		:=	09Ch
ffs_chdrive		:=	09Dh
ffs_getcwd		:=	09Eh

; FatFS volume management and system configuration functions
;
ffs_mount		:=	09Fh
ffs_mkfs		:=	0A0h
ffs_fdisk		:=	0A1h
ffs_getfree		:=	0A2h
ffs_getlabel		:=	0A3h
ffs_setlabel		:=	0A4h
ffs_setcp		:=	0A5h
	
; File access modes
;
fa_read			:=	001h
fa_write		:=	002h
fa_open_existing	:=	000h
fa_create_new		:=	004h
fa_create_always	:=	008h
fa_open_always		:=	010h
fa_open_append		:=	030h
	
; System variable indexes for api_sysvars
; Index into _sysvars in globals.asm
;
sysvar_time		:=	000h	; 4: Clock timer in centiseconds (incremented by 2 every VBLANK)
sysvar_vpd_pflags	:=	004h	; 1: Flags to indicate completion of VDP commands
sysvar_keyascii		:=	005h	; 1: ASCII keycode, or 0 if no key is pressed
sysvar_keymods		:=	006h	; 1: Keycode modifiers
sysvar_cursorX		:=	007h	; 1: Cursor X position
sysvar_cursorY		:=	008h	; 1: Cursor Y position
sysvar_scrchar		:=	009h	; 1: Character read from screen
sysvar_scrpixel 	:=	00Ah	; 3: Pixel data read from screen (R,B,G)
sysvar_audioChannel	:=	00Dh	; 1: Audio channel 
sysvar_audioSuccess	:=	00Eh	; 1: Audio channel note queued (0 = no, 1 = yes)
sysvar_scrWidth 	:=	00Fh	; 2: Screen width in pixels
sysvar_scrHeight	:=	011h	; 2: Screen height in pixels
sysvar_scrCols		:=	013h	; 1: Screen columns in characters
sysvar_scrRows		:=	014h	; 1: Screen rows in characters
sysvar_scrColours	:=	015h	; 1: Number of colours displayed
sysvar_scrpixelIndex	:=	016h	; 1: Index of pixel data read from screen
sysvar_vkeycode 	:=	017h	; 1: Virtual key code from FabGL
sysvar_vkeydown		:=	018h	; 1: Virtual key state from FabGL (0=up, 1=down)
sysvar_vkeycount	:=	019h	; 1: Incremented every time a key packet is received
sysvar_rtc		:=	01Ah	; 8: Real time clock data
sysvar_keydelay		:=	022h	; 2: Keyboard repeat delay
sysvar_keyrate		:=	024h	; 2: Keyboard repeat reat
sysvar_keyled		:=	026h	; 1: Keyboard LED status
	
; Flags for the VPD protocol
;
vdp_pflag_cursor	:=	00000001b
vdp_pflag_scrchar	:=	00000010b
vdp_pflag_point		:=	00000100b
vdp_pflag_audio		:=	00001000b
vdp_pflag_mode		:=	00010000b
vdp_pflag_rtc		:=	00100000b

;
; FatFS structures
; These mirror the structures contained in src_fatfs/ff.h in the MOS project
;
; Object ID and allocation information (FFOBJID)
;
;FFOBJID	.STRUCT
;	fs:		DS	3	; Pointer to the hosting volume of this object
;	id:		DS	2	; Hosting volume mount ID
;	attr:		DS	1	; Object attribute
;	stat:		DS	1	; Object chain status (b1-0: =0:not contiguous, =2:contiguous, 
;					;  =3:fragmented in this session, b2:sub-directory stretched)
;	sclust:		DS	4	; Object data start cluster (0:no cluster or root directory)
;	objsize:	DS	4	; Object size (valid when sclust != 0)
;FFOBJID_SIZE .ENDSTRUCT FFOBJID
;
; File object structure (FIL)
;
;FIL .STRUCT
;	obj:		.TAG	FFOBJID	; Object identifier
;	flag:		DS	1	; File status flags
;	err:		DS	1	; Abort flag (error code)
;	fptr:		DS	4	; File read/write pointer (Zeroed on file open)
;	clust:		DS	4	; Current cluster of fpter (invalid when fptr is 0)
;	sect:		DS	4	; Sector number appearing in buf[] (0:invalid)
;	dir_sect:	DS	4	; Sector number containing the directory entry
;	dir_ptr:	DS	3	; Pointer to the directory entry in the win[]
;FIL_SIZE .ENDSTRUCT FIL
;
; Directory object structure (DIR)
; 
;DIR .STRUCT
;	obj:		.TAG	FFOBJID	; Object identifier
;	dptr:		DS	4	; Current read/write offset
;	clust:		DS	4	; Current cluster
;	sect:		DS	4	; Current sector (0:Read operation has terminated)
;	dir:		DS	3	; Pointer to the directory item in the win[]
;	fn:		DS	12	; SFN (in/out) {body[8],ext[3],status[1]}
;	blk_ofs:	DS	4	; Offset of current entry block being processed (0xFFFFFFFF:Invalid)
;DIR_SIZE .ENDSTRUCT DIR
;
; File information structure (FILINFO)
;
;FILINFO .STRUCT
;	fsize:		DS 	4	; File size
;	fdate:		DS	2	; Modified date
;	ftime:		DS	2	; Modified time
;	fattrib:	DS	1	; File attribute
;	altname:	DS	13	; Alternative file name
;	fname:		DS	256	; Primary file name
;FILINFO_SIZE .ENDSTRUCT FILINFO
;
;
; Macro for calling the API
; Parameters:
; - function: One of the function numbers listed above
;
;MOSCALL:		MACRO	function
;			LD	A, function
;			RST.LIS	08h
;			ENDMACRO 	
