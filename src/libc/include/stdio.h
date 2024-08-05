#ifndef _STDIO_H
#define _STDIO_H

#include <cdefs.h>
#include <stdarg.h>

typedef struct
{
    unsigned char fhandle;              // storage for the MOS file handle
    unsigned char eof;
    unsigned char err;
    unsigned char text_mode;            // Text or binary mode (true if text mode)
    unsigned char unget_char;           // unget character, 0 if none
} FILE;

// Agon MOS allows for 8 open files these will have indexes 0-7

#define FOPEN_MAX 8
#define FH_STDIN 128                    // This is the minimum can check if not real file
#define FH_STDOUT 129                   // by >= FH_STDIN
#define FH_STDERR 130

/* Original CE Toolchain definitions are not real pointers - but are assinged to
#define stdin  ((FILE*)1)
#define stdout ((FILE*)2)
#define stderr ((FILE*)3)
*/
extern FILE stdin[1];
extern FILE stdout[1];
extern FILE stderr[1];

#ifndef EOF
#define EOF (-1)
#endif

#ifndef SEEK_CUR
#define SEEK_CUR  1
#endif
#ifndef SEEK_END
#define SEEK_END  2
#endif
#ifndef SEEK_SET
#define SEEK_SET  0
#endif

__BEGIN_DECLS

/* weak user-defined functions */
char inchar(void);

void outchar(char character);

FILE *fopen(const char *__restrict filename, const char *__restrict mode);

int fclose(FILE *stream);

int fflush(FILE *stream);

int ferror(FILE *stream);

int feof(FILE *stream);

//void clearerr(FILE *stream);

int fputs(const char *__restrict str, FILE *__restrict stream);

size_t fread(void *ptr, size_t size, size_t count, FILE *__restrict stream);

size_t fwrite(const void *__restrict ptr, size_t size, size_t count,
    FILE *__restrict stream);

long int ftell(FILE *stream) __attribute__((__warn_unused_result__));

int fseek(FILE *stream, long int offset, int origin);

int fgetc(FILE *stream);
#define getc(...) fgetc(__VA_ARGS__)

int fputc(int c, FILE *stream);
#define putc(...) fputc(__VA_ARGS__)

char *fgets(char *__restrict str, int num, FILE *__restrict stream);

int remove(const char *fname);

//void rewind(FILE *stream);

/* standard impls */
int getchar(void);

int putchar(int character);

int puts(const char *str);

int printf(const char *__restrict format, ...)
    __attribute__((format(__printf__, 1, 2)));

int vprintf(const char *__restrict format, va_list va)
    __attribute__((format(__printf__, 1, 0)));

int vsprintf(char *__restrict buffer, const char *__restrict format,
    va_list va)
    __attribute__((format(__printf__, 1, 0)));

int snprintf(char* buffer, size_t count, const char *__restrict format, ...)
    __attribute__((format(__printf__, 3, 4)));

int vsnprintf(char* buffer, size_t count, const char *__restrict format,
    va_list va)
    __attribute__((format(__printf__, 3, 0)));

int sprintf(char *__restrict buffer,
    const char *__restrict format, ...)
    __attribute__ ((format (__printf__, 2, 3)));

// Functions added to the CE Toolchain stdio library

int fprintf(FILE *stream, const char *__restrict format, ...)
    __attribute__((format(__printf__, 2, 3)));

int vfprintf(FILE *stream, const char *__restrict format, va_list va)
    __attribute__((format(__printf__, 2, 0)));

typedef size_t rsize_t;

char *gets_s( char *__restrict str, rsize_t n );
int scanf( const char *format, ...);
int sscanf( const char *s, const char *format, ...);
int fscanf( FILE *fp, const char *fmt,...);
FILE *freopen( const char *__restrict filename, const char *__restrict mode, FILE *stream );
int ungetc(int c, FILE *stream);


__END_DECLS

#endif /* _STDIO_H */
