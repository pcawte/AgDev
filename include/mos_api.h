/*
 * Title:			AGON MOS - MOS c header interface
 * Author:			Jeroen Venema
 * Created:			15/10/2022
 * Last Updated:	22/07/2023
 * 
 * Modinfo:
 * 15/10/2022:		Added putch, getch
 * 22/10/2022:		Added waitvblank, mos_f* functions
 * 10/01/2023:      Added getsysvar_cursorX/Y functions, removed generic getsysvar8/16/24bit functions
 * 25/03/2023:      Added MOS 1.03 functions / sysvars
 * 16/04/2023:      Added MOS 1.03RC4 mos_fread / mos_fwrite / mos_flseek functions
 * 19/04/2023:		Added mos_getfil
 * 02/07/2023:      Added struct / union for RTC_DATA
 * 22/07/2023:      Added structure for SYSVAR
 */

#ifndef _MOS_H
#define _MOS_H
#include <stdint.h>

typedef uint8_t BYTE;

// File access modes - from mos_api.inc
#define FA_READ				    0x01
#define FA_WRITE			    0x02
#define FA_OPEN_EXISTING	    0x00
#define FA_CREATE_NEW		    0x04
#define FA_CREATE_ALWAYS	    0x08
#define FA_OPEN_ALWAYS		    0x10
#define FA_OPEN_APPEND		    0x30

/* FatFS File function return code (FRESULT) */

typedef enum {
    FR_OK = 0,              /* (0) Succeeded */
    FR_DISK_ERR,            /* (1) A hard error occurred in the low level disk I/O layer */
    FR_INT_ERR,             /* (2) Assertion failed */
    FR_NOT_READY,           /* (3) The physical drive cannot work */
    FR_NO_FILE,             /* (4) Could not find the file */
    FR_NO_PATH,             /* (5) Could not find the path */
    FR_INVALID_NAME,        /* (6) The path name format is invalid */
    FR_DENIED,              /* (7) Access denied due to prohibited access or directory full */
    FR_EXIST,               /* (8) Access denied due to prohibited access */
    FR_INVALID_OBJECT,      /* (9) The file/directory object is invalid */
    FR_WRITE_PROTECTED,     /* (10) The physical drive is write protected */
    FR_INVALID_DRIVE,       /* (11) The logical drive number is invalid */
    FR_NOT_ENABLED,         /* (12) The volume has no work area */
    FR_NO_FILESYSTEM,       /* (13) There is no valid FAT volume */
    FR_MKFS_ABORTED,        /* (14) The f_mkfs() aborted due to any problem */
    FR_TIMEOUT,             /* (15) Could not get a grant to access the volume within defined period */
    FR_LOCKED,              /* (16) The operation is rejected according to the file sharing policy */
    FR_NOT_ENOUGH_CORE,     /* (17) LFN working buffer could not be allocated */
    FR_TOO_MANY_OPEN_FILES, /* (18) Number of open files > FF_FS_LOCK */
    FR_INVALID_PARAMETER    /* (19) Given parameter is invalid */
} FRESULT;

// Indexes into sysvar - from mos_api.inc
#define sysvar_time			    0x00    // 4: Clock timer in centiseconds (incremented by 2 every VBLANK)
#define sysvar_vdp_pflags	    0x04    // 1: Flags to indicate completion of VDP commands
#define sysvar_keyascii		    0x05    // 1: ASCII keycode, or 0 if no key is pressed
#define sysvar_keymods		    0x06    // 1: Keycode modifiers
#define sysvar_cursorX		    0x07    // 1: Cursor X position
#define sysvar_cursorY		    0x08    // 1: Cursor Y position
#define sysvar_scrchar		    0x09    // 1: Character read from screen
#define sysvar_scrpixel		    0x0A    // 3: Pixel data read from screen (R,B,G)
#define sysvar_audioChannel	    0x0D    // 1: Audio channel
#define syscar_audioSuccess	    0x0E    // 1: Audio channel note queued (0 = no, 1 = yes)
#define sysvar_scrWidth	        0x0F	// 2: Screen width in pixels
#define sysvar_scrHeight	    0x11	// 2: Screen height in pixels
#define sysvar_scrCols		    0x13	// 1: Screen columns in characters
#define sysvar_scrRows		    0x14	// 1: Screen rows in characters
#define sysvar_scrColours	    0x15	// 1: Number of colours displayed
#define sysvar_scrpixelIndex    0x16	// 1: Index of pixel data read from screen
#define sysvar_vkeycode	        0x17	// 1: Virtual key code from FabGL
#define sysvar_vkeydown			0x18	// 1: Virtual key state from FabGL (0=up, 1=down)
#define sysvar_vkeycount	    0x19	// 1: Incremented every time a key packet is received
#define sysvar_rtc		        0x1A	// 8: Real time clock data
#define sysvar_keydelay	        0x22	// 2: Keyboard repeat delay
#define sysvar_keyrate		    0x24	// 2: Keyboard repeat reat
#define sysvar_keyled		    0x26	// 1: Keyboard LED status

// Flags for the VPD protocol - sysvar_vpd_pflags
#define vdp_pflag_cursor        0x01
#define vdp_pflag_scrchar       0x02
#define vdp_pflag_point         0x04
#define vdp_pflag_audio         0x08
#define vdp_pflag_mode          0x10
#define vdp_pflag_rtc           0x20

// Stucture / union for accessing RTC data

typedef union {
    uint64_t rtc_data;
    struct {
        uint8_t year;               // offset since 1980
        uint8_t month;              // (0-11)
        uint8_t day;                // (1-31)
        uint8_t day_of_year;        // (0-365) - *** but doesn't fit in 1 byte - wraps round ***
        uint8_t day_of_week;        // (0-6)
        uint8_t hour;               // (0-23)
        uint8_t minute;             // (0-59)
        uint8_t second;             // (0-59)
    };
} RTC_DATA;

// Structure for accesing SYSVAR

typedef struct {
    uint32_t time;
    uint8_t vpd_pflags;
    uint8_t keyascii;
    uint8_t keymods;
    uint8_t cursorX;
    uint8_t cursorY;
    uint8_t scrchar;
    union {
        uint24_t scrpixel;
        struct {
            uint8_t scrpixelR;
            uint8_t scrpixelB;
            uint8_t scrpixelG;
        };
    };
    uint8_t audioChannel;
    uint8_t audioSuccess;
    uint16_t scrWidth;
    uint16_t scrHeight;
    uint8_t scrCols;
    uint8_t scrRows;
    uint8_t scrColours;
    uint8_t scrpixelIndex;
    uint8_t vkeycode;
    uint8_t vkeydown;
    uint8_t vkeycount;
    RTC_DATA rtc;
    uint16_t keydelay;
    uint16_t keyrate;
    uint8_t keyled;
    uint8_t scrMode;
} SYSVAR;


// UART settings for open_UART1
typedef struct {
   int24_t baudRate ;				    //!< The baudrate to be used.
   BYTE dataBits ;				        //!< The number of databits per character to be used.
   BYTE stopBits ;				        //!< The number of stopbits to be used.
   BYTE parity ;				        //!< The parity bit option to be used.
   BYTE flowcontrol ;
   BYTE eir ;
} UART ;

// File Object ID and allocation information (FFOBJID)
typedef struct {
	uint24_t*   fs;		    /* Pointer to the hosting volume of this object */
	uint16_t	id;		    /* Hosting volume mount ID */
	BYTE	    attr;		/* Object attribute */
	BYTE	    stat;		/* Object chain status (b1-0: =0:not contiguous, =2:contiguous, =3:fragmented in this session, b2:sub-directory stretched) */
	uint32_t	sclust;	    /* Object data start cluster (0:no cluster or root directory) */
	uint32_t	objsize;    /* Object size (valid when sclust != 0) */
} FFOBJID;

// File object structure (FIL)
typedef struct {
	FFOBJID	    obj;       /* Object identifier (must be the 1st member to detect invalid object pointer) */
	BYTE	    flag;      /* File status flags */
	BYTE	    err;       /* Abort flag (error code) */
	uint32_t	fptr;      /* File read/write pointer (Zeroed on file open) */
	uint32_t	clust;     /* Current cluster of fpter (invalid when fptr is 0) */
	uint32_t	sect;      /* Sector number appearing in buf[] (0:invalid) */
	uint32_t	dir_sect;  /* Sector number containing the directory entry (not used at exFAT) */ 
	uint24_t*	dir_ptr;   /* Pointer to the directory entry in the win[] (not used at exFAT) */
} FIL;

// Generic IO
extern int   putch(int a);
extern char  getch(void);
extern void  waitvblank(void);
extern void  mos_puts(char * buffer, uint24_t size, char delimiter);

// Get system variables
extern uint32_t getsysvar_time();
extern uint8_t  getsysvar_vpd_pflags();
extern uint8_t  getsysvar_keyascii();
extern uint8_t  getsysvar_keymods();
extern uint8_t  getsysvar_cursorX();
extern uint8_t  getsysvar_cursorY();
extern uint8_t  getsysvar_scrchar();
extern uint24_t getsysvar_scrpixel();
extern uint8_t  getsysvar_audioChannel();
extern uint8_t  getsysvar_audioSuccess();
extern uint16_t getsysvar_scrwidth();
extern uint16_t getsysvar_scrheight();
extern uint8_t  getsysvar_scrCols();
extern uint8_t  getsysvar_scrRows();
extern uint8_t  getsysvar_scrColours();
extern uint8_t  getsysvar_scrpixelIndex();
extern uint8_t  getsysvar_vkeycode();
extern uint8_t  getsysvar_vkeydown();
extern uint8_t  getsysvar_vkeycount();
extern volatile RTC_DATA* getsysvar_rtc();  // mos_getrtc() needs to be called to update the values
extern uint16_t getsysvar_keydelay();
extern uint16_t getsysvar_keyrate();
extern uint8_t  getsysvar_keyled();

// MOS API calls
extern uint8_t  mos_load(const char *filename, uint24_t address, uint24_t maxsize);
extern uint8_t  mos_save(const char *filename, uint24_t address, uint24_t nbytes);
extern uint8_t  mos_cd(const char *path);
extern uint8_t  mos_dir(const char *path);
extern uint8_t  mos_del(const char *filename);
extern uint8_t  mos_ren(const char *filename, const char *newname);
extern uint8_t  mos_copy(const char *source, const char *destination);
extern uint8_t  mos_mkdir(const char *path);
extern uint8_t* mos_sysvars(void);
extern uint8_t  mos_editline(char *buffer, uint24_t bufferlength, uint8_t clearbuffer);
extern uint8_t  mos_fopen(const char * filename, uint8_t mode);   // returns filehandle, or 0 on error
extern uint8_t  mos_fclose(uint8_t fh);					    // returns number of still open files
extern char	    mos_fgetc(uint8_t fh);					    // returns character from file, or 0 on error
extern void	    mos_fputc(uint8_t fh, char c);			    // writes character to file
extern uint8_t  mos_feof(uint8_t fh);					    // returns 1 if EOF, 0 otherwise
extern void     mos_getError(uint8_t code, char *buffer, uint24_t bufferlength);
extern uint8_t  mos_oscli(char *command, char **argv, uint24_t argc);
extern uint8_t  mos_getrtc(char *buffer);
extern void     mos_setrtc(uint8_t *timedata);
extern void*    mos_setintvector(uint8_t vector, void(*handler)(void));
extern uint8_t  mos_uopen(UART *settings);
extern void     mos_uclose(void);
extern int      mos_ugetc(void);                              // 0-255 valid character - >255 error
extern uint8_t  mos_uputc(int a);                           // returns 0 if error
extern uint24_t mos_fread(uint8_t fh, char *buffer, uint24_t numbytes);
extern uint24_t mos_fwrite(uint8_t fh, char *buffer, uint24_t numbytes);
extern uint8_t  mos_flseek(uint8_t fh, uint32_t offset);
extern FIL*     mos_getfil(uint8_t fh);
#endif