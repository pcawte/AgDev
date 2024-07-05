# AgDev - a port of the CEdev C/C++ Toolchain to the Agon Platform

## Overview

The [Agon Light](https://agonconsole8.github.io/agon-docs/) and other Agon Platform revisions are based on the Zilog eZ80 processor. The eZ80 has a 24 bit address space supporting 16 megabytes of memory, compared to the 64 kilobytes of the original Z80. The eZ80 has two modes of operation: the standard Z80 mode, which has 16-bit registers making it easy to address 64k of memory, but requiring the use of "banking" to access more than 64k of memory; and ADL (address data long) mode of operation, which extends the registers to 24 bits, making the whole address space readily accessible. 

When we consider high-level programming languages, there are a number available for the Z80, but they are limited to 64k of memory or have awkward bank switching methods to access greater memory.

Considering the C-programming languages, there are a number of Z80 C-compilers available. To date, the Agon community has focused on two:

- **Zilog ZDS II development environment** which can produce eZ80 ADL code. This was the original set of tools used by the developers of Agon, but it is closed source, runs on Windows only, and only supports the data C89 standard

- **SDCC (small devices C-compiler)**, a popular choice for 8-bit computers, and adapting this for Agon has been a focus of a number of people in the Agon computer. This is a good compiler for Z80, but it only supports Z80 and not ADL mode.

As an alternative, the [CEdev C/C++ toolchain](https://ce-programming.github.io/toolchain/index.html) is an open-source compiler that can produce ADL code. It targets the TI-84 Plus CE calculator (based on the eZ80 processor) and has a reasonably sized community. CEdev is based on eZ80 versions of the LLVM compiler and fasmg assembler. It produces ADL code with 24 bit pointers, 24 bit integers, 32 bit longs, 16 bit shorts, and 32 bit floats. There is also quite an extensive library for C and C++ programs (though it is not ISO compliant... yet).

AgDev is the result of an effort to modify CEdev to accommodate the feature set and hardware design of the Agon Platform. The result is a more powerful, and C++ capable, toolchain, compared to other options for the Agon.

### Installation

Download a [release build](https://github.com/pcawte/agdev/releases/latest) or [build from source yourself](COMPILE.md). Place the build in a directory of your choosing. 

Afterward, make sure the `/bin` folder can be found in `PATH`; if you're on Windows, follow [this guide](https://www.architectryan.com/2018/03/17/add-to-the-path-on-windows-10/), or you can run cedev.bat and execute commands from there instead. On Linux, run `export PATH=/<insert path here>/bin:$PATH` in a terminal window.

### Building programs

This follows the same approach as the original CE Toolchain (see bottom of the [CEdev getting started page](https://ce-programming.github.io/toolchain/static/getting-started.html#building-programs)). The build process had been modified to stop on the generation of the `.bin` file. This is the Agon Light executable.

I recommend to use:

```shell
make clean
make V=1
```

The `make clean` command can be used to delete the results of previous compilations and thereby force a recompilation.

The build process goes through the following steps:

1. Compilation of .c source files to LLVM bitcode (.bc) using `ez80-clang`

2. Linking of LLVM bitcode using `ez80-link`. This includes link time optimization 

3. Generation of eZ80 assembly code (.src) for the source programs using `ez80-clang`

4. Assembling and linking of the of the generated assembly code (from step 3) with the libraries and compiler run-time using `fasmg` - this includes building the executable targeted at a specific memory location. This is the main part of the build process that needs to be adjusted.  

## C Calling Conventions (for interfacing with ASM applications)

See Zilog application note ["Calling C from asm.pdf"](https://www.zilog.com/docs/appnotes/an0333.pdf).

Only IX register and stack need to be preserved by called functions.

### Arguments

Arguments are pushed from last to first corresponding to the C prototype. In eZ80, 3 bytes are always pushed to the stack regardless of the actual size. However, the assembly function must be careful to only use the valid bytes that are pushed. For example, if a *short* type is used, the upper byte of the value pushed on the stack will contain arbitrary data. This table lists the locations relative to *sp* from within the called function. Note that `sp + [0,2]` contains the return address.

| C/C++ Type | Size    | Stack Location |
| ---------- | ------- | -------------- |
| char       | 1 byte  | sp + [3]       |
| short      | 2 bytes | sp + [3,4]     |
| int        | 3 bytes | sp + [3,5]     |
| long       | 4 bytes | sp + [3,6]     |
| long long  | 8 bytes | sp + [3,10]    |
| float      | 4 bytes | sp + [3,6]     |
| double     | 4 bytes | sp + [3,6]     |
| pointer    | 3 bytes | sp + [3,5]     |

Note that eZ80 is little endian - i.e. the least significant byte is stored first.

### Returns

This table lists which registers are used for return values from a function. The type’s sign does not affect the registers used, but may affect the value returned. The LSB is located in the register on the far right of the expression, e.g. `E:UHL` indicates register `L` stores the LSB.

| C/C++ Type | Return Register |
| ---------- | --------------- |
| char       | A               |
| short      | HL              |
| int        | UHL             |
| long       | E:UHL           |
| long long  | BC:UDE:UHL      |
| float      | E:UHL           |
| double     | E:UHL           |
| pointer    | UHL             |

## Standard IO Library

**Not ISO compliant!**

Consists of the following:

File IO:

- `fopen()`, `freopen(),` `fclose()`

- `fputc()`, `fputs()`

- `fgetc()`,  `ungetc()`, `fgets()`

- `feof()`, `ferror()`, `fflush()`

- `fread()`, `fwrite()`

- `fseek()`, `rewind()`, `ftell()`

- `clearerr()`

- `remove()`

Stdin / stdout IO:

- `putchar()`, `puts()`

- `getchar()`, `gets_s()`

Formatted output

- `printf()` (and  `vprintf()`)

- `sprintf()` (and `vsprintf()`)

- `snprintf()` (and `vsnprintf()`)

Formatted input

- `scanf()`

- `sscanf()`

There's some other stuff in here - like `stdint` and such - but it should mostly match expectations for the normal standard library. Mostly.

### `stdio` Redirection

Can redirect output by using `freopen()` on `stdout` or `stderr`:

- `putchar()` - outputs to `outchar()` unless the output is redirected, in which case outputs to `fputc()`

- `puts()` - calls `putchar()`

- `printf()` (and `vprintf()`) - calls `npf_putc_std()`, which calls `putchar()` in `nanoprintf.c`

- `fputc()` - calls `mos_fputc()` unless called on `stdout` when calls `outchar()` - avoids calling `putchar()` so that no risk of function call loops

Can redirect input by using `freopen()` on `stdin`:

- `getchar()` - calls `inchar()` to get the character and `outchar()` to echo the character (even if the output has been redirected). If output has not been re-directed calls `fgetc()` and does not echo the character.

- `gets_s()` - calls `getchar()` if input has not been redirected (line are terminated with CR). Calls`fgets()` of input has been redirected (lines are terminated with CR/LF pair).

- `scanf()` - calls `getchar()` in `uscan.c` (doesn't need updating)

- `fgetc()` - calls `mos_fgetc()` unless called on stdin when calls `inchar()` and echos with `outchar() `- avoids calling `getchar() `so that no risk of function call loops

Requires `FILE *`, which is a pointer to a file handle returned by `fopen` and passed to the file IO routines to indicate the file the action is to be performed upon.

Other related files:

`stdio.h` - normal header files, which defines the various functions and the typedef for `FILE`

`files.c`- instantiates the storage for files handles including: stdout, stderr, stdin.

The following standard file handles are defined:

- `stdout` - default output

- `stderr` - default output for error message

- `stdin` - default input

MOS does not implement input / output redirection, so by default these all use the console. 

## Command Line Processing and Input / Output Redirection

Two options are available for command line processing.

#### Simple Command Line Processing

This is automatically included if the main function is defined as

```cpp
int main( int argc, char* argv[] )
```

the splits the command line up using space as a delimiter. The command line options are available in the `argv[]` array as normal. 

#### Complex Command Line Processing - for Redirection & Quoting

This is optionally included if the application makefile includes:

```makefile
LDHAS_ARG_PROCESSING = 1
```

This supports

- Quoting with double quotes

- Input / output redirection
  
  - `>out_file.txt` - redirects stdout to `out_file.txt`, creating a new file
  
  - `>>out_file.txt` - redirects stdout to `out_file.txt`, appending to the end of the file
  
  - `<in_file.txt` - redirects stdin to be from `in_file.txt`

## MOS Commands

For current documentation on MOS commands, see the [Agon Console8 Documentation](https://agonconsole8.github.io/agon-docs/vdp/MOS-API/).

The MOS (machine operating system) provides an interface to the Agon file system and some hardware peripherals, like the mouse. It keeps information on system variables in a large `SYSVAR` struct that can be accessed on the Z80 side. Generally your C code will declare a pointer to this struct, initialized like so:

```cpp
static volatile SYSVAR* sv; 
sv = vdp_vdu_init();
```

For more information see `<mos_api.h>`.

## VDP / VDU Commands

For current documentation on VDU commands, see the [Agon Console8 Documentation](https://agonconsole8.github.io/agon-docs/vdp/VDU-Commands/).

The VDP (video display processor) accepts a text stream from MOS, acting like a text / graphics terminal. The text stream can contain:

- Normal text

- Escape sequences / commands to control the display and send graphics/sound/etc commands

When results are returned by MOS as a result of sending a command, these are stored in the `SYSVAR`'s and not returned directly in response to the command. The response is asynchronous - to check that a result has been returned:

- Set `vdp_pflags` in `SYSVAR` to zero

- Issue the VDU command

- Wait for the relevant bit into in `vdp_pflags` to be set - see `<mos_api.h>`  for the bit masks

Commands can be sent by:

- `putch()` - single character (this is not part of the C standard library)

- `mos_puts()` - multi-character string

Both of these output directly to MOS/VDP - note that they are not part of STDIO library and not subject to CR/LF translation or redirection.

Convenience functions for many VDU commands are supplied in AgDev. For example, to change the screen MODE to 3, the C call `vdp_mode(3);` will send `22,3` as single bytes to the output, equivalent to `putch(22); putch(3);` For a list of these functions see `<vdp_vdu.h>`. Additional functions related to keyboard handling are found in `<vdp_key.h>`.
