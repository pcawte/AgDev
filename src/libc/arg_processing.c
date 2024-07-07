/* Complex argument processing for program invocation

Called from within crt0.src - see extract below

; Process the command line into argc & argv[]
; -------------------------------------------
;			
; Parse the parameter string into a C array
; Parameters
; - HL: Address of parameter string (seems to be set by MOS at start of programme)
; - IX: Address for array pointer storage
; Returns:
; -  C: Number of parameters parsed
;
; Only include conditionally if ___main_argc_argv is present

	section .init.args
ifextern ___main_argc_argv

	private _parse_params
_parse_params:

  if HAS_ARG_PROCESSING				; if want to do complex arg processing

  	extern 	___arg_processing

  	ld 		bc, _exec_name			; first value in argv is program name
  	ld 		(ix+0), bc
  	push	ix
  	push	hl
  	call 	___arg_processing 		; call a C function to do this
  	pop     hl
  	pop 	hl
  	lb		bc, 0 					; clear out top part of UBC 
  	ld 		c, a
  	ret
*/

/*
  Processes up to argv_ptrs_max values from zero terminated param_str
  and stores the results in argv[]

  Will need to allocated its own storage, at least in some instances, as can do wild card
  expansion (TBD)
*/

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define ARGV_PTRS_MAX 16 		// this should align with the value defined in crt0.src

int __parse_args( char *param_str, char *argv[] );
int __check_redirect( int in_cnt, char *argv[] );
char *__get_redir_fname( char *s, char *t );
void __close_redir_files( void );

uint8_t __arg_processing( char *param_str, char *argv[] )
{
	int cnt;

//	puts( "Parameter processing including redirection." );
//	puts( param_str );
	cnt = __parse_args( param_str, argv );
	cnt = __check_redirect( cnt, argv );
	return (uint8_t)cnt;
}

// Parse the arguments from the command string, separating out
// - space separated and
// - quoted strings
// the strings are left in place with their locations in argv
// and zero terminated over the delimiter

int __parse_args( char *param_str, char *argv[] )
{
	int cnt = 1;
	char *s = param_str;
	char delim = ' ';

	// skip the leading spaces

	while ( cnt < ARGV_PTRS_MAX ) {
		while ( *s != '\0' && *s == delim ) s++;
		if ( *s == '\0' ) return cnt;
		if ( *s == '"' ) {
			delim = '"';
			s++;
		}
		argv[cnt++] = s;

		// skip over the letters

		while ( *s != '\0' && *s != delim ) s++;
		if ( *s == '\0' ) return cnt;
		if ( *s == '"' ) delim = ' ';
		*s++ = '\0';								// terminate the string in place
	}
	return cnt;
}

// Check for input / ouput redirection
//  	> redirect stdout (creates new file)
//		>> redirects stdout (appends)
//   Not implemented yet
//		2> and 2>> as above for stderr
//		p>&q merges output from stream p with stream q (stdin=0, stdout=1, stderr=2)
//  	< redirect stdin
//
// file follows the redirection operator, with or without spaces
// removes redirection operators and associated file names from argv
// by changing the pointer to NULL
// uses freopen to redirect

int __check_redirect( int in_cnt, char *argv[] )
{
	char *s, *t;
	char *fname;
	char *mode;
	FILE *fp;
	bool redirect = false;

	for ( int i = 1; i < in_cnt; i++ ) {
		s = argv[i];
		fname = NULL;

		if ( i+1 < in_cnt) t = argv[i+1];
		else t = NULL;

		if ( *s == '<' ) {
			fname = __get_redir_fname( s+1, t );
			fp = stdin;
			mode = "r";
		} else if ( *s == '>' ) {
			if ( *(++s) == '>' ) {
				fname = __get_redir_fname( s+1, t );
				fp = stdout;
				mode = "a";
			} else {
				fname = __get_redir_fname( s, t );
				fp = stdout;
				mode = "w";	
			}
/*
		} else if ( *s == '&' ) {

		} else if ( *s == '2' ) {
*/
		}
		if ( fname ) {
			argv[i] = NULL;
			if ( fname == t ) argv[++i] = NULL;
//			puts( fname );
//			puts( mode );
//			getchar();
			if ( !freopen( fname, mode, fp ) ) exit( EXIT_FAILURE );
			redirect = true;
		}
	}

	// Register atexit() function to close the filehandles

	if ( redirect ) atexit( __close_redir_files );

	// Re-pack argv to remove any redirection operators and file names

	int cnt = 1;

	for ( int i = 1; i < in_cnt; i++ ) 
		if ( argv[i] ) argv[cnt++] = argv[i];

	return cnt;
}

// Get redirection filename from argv list
// - can either be in the in current parameter (s) or next parameter (t)
// - the current parameter is passed with the redirection operators skipped over
// - if t is NULL will always return s even if there is no file name

char *__get_redir_fname( char *s, char *t )
{
	if ( !t ) return s; 				// if t is NULL then s
	if ( *s != '\0' ) return s; 		// not at the end of the string then s
	return t;							// otherwise t
}

// Called at exit to close any files that are targets of redirection
// - registered via atexit()
// - the check is deliberately <FH_STDIN - i.e. a regular file
// - if STDIN has been redirected to STDERR, won't call fclose

void __close_redir_files( void )
{
//	fputs( "Closing redirect files.", stderr );
	if ( stdin->fhandle < FH_STDIN ) fclose( stdin );
	if ( stdout->fhandle < FH_STDIN ) fclose( stdout );
	if ( stderr->fhandle < FH_STDIN ) fclose( stderr );
}
