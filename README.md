# AgDev - an Agon Light port of CE C/C++ Toolchain

Based on LLVM toolchain, generating eZ80 ADL code.

### Installation

Install the CE Toolchain - see [getting started]([Getting Started — CE C/C++ Toolchain documentation](https://ce-programming.github.io/toolchain/static/getting-started.html)) page. The tool-chain can be installed on Windows, Linux or MacOS. Follow the instructions to complete the install, and test that the toolchain works by compiling some of the examples for the TI calculator.

To adapt the the tool-chain for Agon, for this proof of concept, a number of files should be replaced with the files from the repository ([GitHub - pcawte/AgDev: Port to Agon Light of TI 84 plus CE Toolchain](https://github.com/pcawte/AgDev)). Clone the repository and copy over the top of the CE toolchain. For example, if the CE Toolchain is installed in AgDev and the downloaded repository in GitHub/AgDev copy the files over the top using:

```
cp -R -f GitHub/AgDev/ AgDev
```

Which should work for MacOS / Linux - not sure the equivalent for windows.

### Building programs using AgDev toolchain

This follows the same make approach as the original CE Toolchain, see bottom of the getting [started page]([Getting Started &mdash; CE C/C++ Toolchain documentation](https://ce-programming.github.io/toolchain/static/getting-started.html)). The build process had been modified to stop on the generation of the `.bin` file. This is the Agon Light executable.

I recommend to use:

```
make clean
make V=1
```

In the relevant: example, test or any other directory created at the same level. The makefile should be edited to contained the desired name of the .bin executable.

### Change Log:

04/06/2023: initial proof of concept completed

06/06/2023: hosted on github

09/06/2023: missing compile run-time routines added (these previously called routines in CE ROM)

12/06/2023:

- correct operation of malloc verified - comments added to `sbrk.src` as part of this

- `crt0.src` updated to initialise stack

- `makefile.mk`
  
  - updated to include program name in the program header
  
  - default locations of stack and BSS adjusted

13/06/2023: 

- missing string and long jump routes added (these previously called routing in the CE ROM)
  
  - `strcasecmp` removed from the library - this previously called the CE ROM. Use the alternative `strncasecmp`. 

- `puts` modified to output CR / LF pair rather than just LF

- `getchar` updated to echo character as per standard C

18/06/2023:

- stdio library updated to work on Agon
  
  - This is a simple, non-buffered library - it may have performance issues writing large volumes as in many cases does a system call for each character.
  
  - `fseek` only implements SEEK_SET (search from beginning of file). Other modes are not implemented, because requires `ftell` functionality (see below).
  
  - `ftell` is not implemented as functionality is not exposed via MOS 

19/06/2023:

- C-runtime modified to include a work-around for emulator hanging
- Config parameter in `makefile.mk` corrected. `PREFER_OS_LIBC` changed to `NO`

20/06/2023:

- C-runtime workaround reversed as issue now resolved in the emulator.
- Development code for `scanf.c` included prior to tidying up and moving into libc 

23/06/2023:

- stdio library updated to include: `ftell`, `clearerr`, `remove` and `rewind`

- `fseek` updated to allow SEEK_SET and SEEK_CUR - note SEEK_END is not supported. If this required, close and reopen the file in append mode.

- additional error codes added in `errno.h`

24/06/2023:

- `fseek` updated to support SEEK_END

- bug it `gets_s` fixed - was assuming buffer was 1 shorter than it was, so input of 1 character, with buffer size 2 previously did not work.

- test program updated (`tests/src/fileio.c`) to test functionality of stdio

### To-Do:

- Testing / validation

- For stdio remove and stuff inherited from CE Toolchain (there is nothing used, but some remnants in the various files)

- Add fprintf

- Implement scanf and sscanf - there is a development version include under dev, but not moved to library yet

- Add fscanf 

- Port / replace / expand library where necessary to the Agon Light. Including:
  
  - investigate benefits of buffering for stdio.

- Add back in support for C++

- Test / proof of concept for other LLVM front-ends. See, for example, [GitHub - maddymakesgames/Rust-CE: A proof-of-concept of rust on the ti-84+ce](https://github.com/maddymakesgames/Rust-CE), which is a proof of concept for running Rust on the TI-84-CE calculator. 

The rest of this file documents the process of porting the CE Toolchain to the Agon Light. This includes the process of discovery with respect to how the CE Toolchain works and the Agon Light, and the steps / decisions made in the porting process. This intended as reminder for myself and a guide to others who follow in my steps.

## Introduction

The Agon Light is based on the Zilog eZ80 processor. The eZ80 has a 24 bit address space supporting 16 megabytes of memory, compared to the 64 kilobytes of the original Z80. The eZ80 has two modes of operation, the standard Z80 mode, which has 16-bit registers making it easy to address 64k of memory, but requiring the use of "banking" to access more than 64k of memory. The other, ADL (address data long), mode of operation extends the registers to 24 bits, making the whole address space readily accessible.

From the point of view of assembly language programming both Z80 and ADL mode are very similar, making it easy to convert programmes from Z80 to ADL mode. 

When we consider high-level programming languages, there are a number available for the Z80, but they are limited to 64k of memory or have awkward bank switching methods to access greater memory. Consequently it is very interesting to have a available high-level languages that make use of the ADL mode to allow use of the full 16M address space.

Considering the C-programming languages, there are a number of Z80 C-compilers available. To date, the Agon community has focussed on two:

- Zilog ZDS II development environment which can produce eZ80 ADL code. This was the original set of tools used by the developers of Agon, but it is closed source, runs on Windows only, and only supports the data C89 standard

- SDCC (small devices C-compiler) this is a popular choice for 8-bit computers, and adapting this for Agon has been a focus of a number of people in the Agon computer. This is a good compile for Z80, but it only support Z80 and not ADL mode.

As an alternative, open-source compiler that can produce ADL code there is the [CE C/C++ toolchain]([Welcome to the CE C/C++ Toolchain! &mdash; CE C/C++ Toolchain documentation](https://ce-programming.github.io/toolchain/index.html)). This has been developed for the  TI 84 Plus CE calculator that is based on the eZ80 processor and has a quite a reasonably sized community. There is a well developed toolchain, which is based on eZ80 versions of LLVM compile and fasmg assembler. It produces ADL code with 24 bit pointers, 24 bit integers, 32 bit long, 16 bit short, 32 bit float. There is also quite an extensive library for C and C++ programs.

Although this toolchain is focused heavily optimised for the TI calculator, work has become to  adept it to support the Agon Light. At the moment a proof of concept has been achieved to demonstrate the feasibility of this by being able to compile and run a "Hello, world!" example, extend also to print the command line. This is an excellent first step. Further work is required to adapt the CE toolchain's extensive library to the Agon Light. The toolchain also supports C++, this has not been tested on the Agon.

## Installation

Install the CE Toolchain - see [getting started]([Getting Started &mdash; CE C/C++ Toolchain documentation](https://ce-programming.github.io/toolchain/static/getting-started.html)) page. The tool-chain can be installed on Windows, Linux or MacOS.  Follow the instructions to complete the install, and test that the toolchain works by compiling some of the examples for the TI calculator.

To adapt the the tool-chain for Agon, for this proof of concept, a number of files should be replaced  with the files from the repository ([GitHub - pcawte/AgDev: Port to Agon Light of TI 84 plus CE Toolchain](https://github.com/pcawte/AgDev)). Clone the repository and copy over the top of the CE toolchain. For example, if the CE Toolchain is installed in AgDev and the downloaded repository in GitHub/AgDev copy the files over the top using:

```
cp -R -f GitHub/AgDev/ AgDev`
```

Which should work for MacOS / Linux - not sure the equivalent for windows.

## Build process for proof of concept

In the `AgExamples/hello_world` issue the `make` command (use V=1 not necessary but provides much more details on the commands used): 

```
make V=1
```

The `make clean`command can be used to delete the results of previous compilations and thereby force a recompilation.

There are other examples in the test directory which can be built in the same way.

The build process goes through the following steps:

1. Compilation of .c source files to LLVM bitcode (.bc) using `ez80-clang`

2. Linking of LLVM bitcode using `ez80-link`. This includes link time optimisation 

3. Generation of eZ80 assembly code (.src) for the source programmes using `ez80-clang`

4. Assembling and linking of the of the generated assembly code (from step 3) with the libraries and compiler run-time using `fasmg` - this includes building the executable targeted at a specific memory location. This is the main part of the build process that needs to be adjusted.  

### Program Execution

The compiler if successful produces the final "DEMO.bin". This should be transferred to the Agon for testing.

On the Agon:

```
*load DEMO.bin
*run &040000 Hello AgDev
```

Should produce the following output:

```
Hello World!
Arguments: 3
- argc: 3
- argv[0]: HELLO.BIN
- argv[1]: Hello
- argv[2]: AgDev
```

### Step 1 compilation:

```
make V=1

ez80-clang -MD -c -emit-llvm -nostdinc
  -isystem /AgDev/include -Isrc -fno-threadsafe-statics
  -Xclang -fforce-mangle-main-argc-argv
  -mllvm -profile-guided-section-prefix=false
  -DNDEBUG  -g0 -Wall -Wextra -Oz
  'src/main.c' -o 'obj/src/main.c.bc'
```

Compiles:

- src/main.c

Generates output:

- obj/src/main.c.bc

- obj/src/main.c.d

The .bc files is an intermediate file in LLVM bitcode

The .d file is a dependencies list for main.c.bc, for the source main.c and various include (.h) files

### Step 2 linking of LLVM (and link time optimisation)

```
ez80-link
  '/AgDev/AgExamples/hello_world/obj/src/main.c.bc'
  -o '/AgDev/AgExamples/hello_world/obj/lto.bc'
```

Links and optimises:

- obj/src/main.c.bc

Generates output:

- obj/lto.bc

### Step 3 eZ80 assembly language generation

```
ez80-clang -S
  -mllvm -profile-guided-section-prefix=false
  -Wall -Wextra -Oz
  '/AgDev/AgExamples/hello_world/obj/lto.bc'
  -o '/AgDev/AgExamples/hello_world/obj/lto.src'
```

Generates assembly language for

- obj/lto.bc

Outputs eZ80 assembly language to

- obj/lto.src

### Step 4 assembly and linking

```
fasmg -n '/AgDev/meta/ld.alm'
  -i 'DEBUG := 0'
  -i 'HAS_PRINTF := 1'
  -i 'HAS_LIBC := 1'
  -i 'HAS_LIBCXX := 1'
  -i 'PREFER_OS_CRT := 0'
  -i 'PREFER_OS_LIBC := 1'
  -i 'include "/AgDev/meta/linker_script"'
  -i 'range .bss $050000 : $05ffff'
  -i 'locate .header at $040000'
  -i map
  -i 'source "obj/icon.src",
             "/AgDev/lib/crt/crt0.src",
             "obj/lto.src"'
   -i 'library "/AgDev/lib/libload/fatdrvce.lib",
               "/AgDev/lib/libload/fileioc.lib",
               "/AgDev/lib/libload/fontlibc.lib",
               "/AgDev/lib/libload/graphx.lib",
               "/AgDev/lib/libload/keypadc.lib",
               "/AgDev/lib/libload/msddrvce.lib",
               "/AgDev/lib/libload/srldrvce.lib",
               "/AgDev/lib/libload/usbdrvce.lib"'
  bin/DEMO.bin
```

Source files:

- lib/crt/crt0.src: C runtime (this has been heavily customised for Agon)

- obj/lto.src: previously generated eZ80 assembly language for all the source files

Files generated

- DEMO.bin

- DEMO.map

The .bin files has no location information in it, but is not position independent (e.g. has absolute jumps in it, etc.). It has an assumed location and needs to be loaded by the OS to the correct location.

The .map files contains information on the locations of code / data sections and the global labels. The entry point to the program is at `__start` which is at the beginning of the `.init` section.

### Summary of directories / files:

- `bin`

- `examples`

- `include`

- `lib`
  
  - `ce`
  
  - `crt`, which includes
    
    - `crt0.src`: the C-compiler runtime / startup & exit routines
    
    - many other runtime functions for basic arithmetic on the basic types, etc. From a quick inspection most of these should not need to be modified. There are likely a few that need to be changed, for example:
      
      - `os.src`: which seems to include addresses of functions in the CE ROM which would need to be replaced or copied somehow
  
  - `libc`
  
  - `libcxx`
  
  - `libload`

- `meta`
  
  - `commands.alm`: defines some macros for the fasmg eZ80 assembly process. Don't need to change anything here
  
  - `ez80.alm`: configuration for fasmg to assemble eZ80 code. Don't need to change anything here
  
  - `ld.alm`: main configuration file for the fasmg assembler. Nothing needs to be changed here. Includes `commands.alm` and then `ez80.alm`
  
  - `linker_script`: included by fasmg as part of the assemblers linking process. Probably changes will need to be made here although it is possible that it is generic enough and just need to update the underlying libraries to the Agon target.
  
  - `makefile.mk`: this is included as part of the make process. It is the main place where configuration of the make compilation, assembly and linking is configured. It is included by the individual project makefile using `include $(shell cedev-config --makefile)` This has been edited to remove generation of icon and 8xp output files. 

## Customisation to change target to Agon

Things to be changed:

- makefile.mk: main makefile includes information of the location in memory of the program and data structures, libraries, etc.

- crt0.src: C-compiler runtime / startup & exit routings

- Various libraries - this needs to be investigated further, starting with something simple and then adding complexity

### Main makefile - makefile.mk

Modified to:

- Don't include an icon - this was a specific TI calculator thing

- Don't generate an 8xp file from the binary. This is a specific TI 84 format for transferring to the calculator

Updated with Agon specific addresses / memory locations:

- INIT_LOC = 040000: executable location - should change to 0B0000 for MOS binary executable that can be run from the command line (not sure what else needs to be changed)

- BSSHEAP_LOW = 050000: this seems to work for a small programme - but not sure what should really be used

- BSSHEAP_HIGH = 05FFFF: as above

- STACK_HIGH = 0AFFFF: this seems to work - but not sure what should really be used - or even if this really needs to be set. For the moment this has been removed from the fasmg flags and whatever stack that is provided by MOS is used.

See details below for memory layout.

### C runtime - crt0.src

This has been re-written based on a combination of code from the original [Agon projects]([GitHub - breakintoprogram/agon-projects: Official AGON QUARK Firmware: Projects](https://github.com/breakintoprogram/agon-projects)) which used the Zilog toolchain, and the CE Toolkit version. Note that the Zilog assembler, fasmg assembler used by CE toolkit and ez80asm used by many in the Agon community all have different formats and different waves of organising program sections, etc. Part of the challenge of this proof of concept has been in understanding the fasmg assembler.

### Memory layout

From the MOS documentation, the memory layout for the Agon is as follows:

- &000000 - &01FFFF: MOS (Flash ROM)
- &040000 - &0BDFFF: User RAM
- &0B0000 - &0B7FFF: Storage for loading MOS star command executables off SD card
- &0BC000 - 0BFFFFF: Global heap and stack

Consequently we assume that the memory from 040000h to 0AFFFFh is useable for programs compiled with the AgDev toolchain (this can be adjusted)

The layout of sections of the program is in the following order with each section immediately following the proceeding one:

- `section .header`: 040000h

- `section .init`: 040045h (this can be referenced by the label `__start`)

- `section .text`: this is where the main program code is located. The code is entered by calling `_main` or `___main_argc_argv` depending on whether `main(void)` or `main(int argc, char *argv[])` is used. Note that is almost certainly not at the beginning of of .text section. 

- `section .data`: contains static and global variables defined in the program code.

- `section .rodata`:  contains constant data, such as string literals in the program code.

There is then a gap before:

- `section .bss`: contains uninitialised global and static variables. This is zeroed as part of the as part of the C-runtime setup (by crt0). 

- `heap`: this is used by malloc to programmatically allocate memory. This grows upwards towards the stack.

- `stack`: used for storing return addresses, parameters for function calls and local variables. This grows downwards towards the heap.

The layout in memory can be checked by examining the `.map` file generated as part of the final linking process.

The location of .bss, heap and stack are configured in the `makefile.mk` which controls the build process:

```
BSSHEAP_LOW ?= 050000
BSSHEAP_HIGH ?= 05FFFF
STACK_HIGH ?= 0AFFFF
```

The layout can be checked by examining the following labels in the `.map` file.

```
___low_bss             = 050000
___len_bss             = 000000
___heaptop             = 05FFFF
___heapbot             = 050000
__stack                = 0AFFFF
```

Memory in heap is managed by the `malloc` function . The malloc used is from Zilog, the comments state:

```
/*   This implements a straight forward version of malloc, allocating   */
/*   memory between the first unused address in RAM (__heapbot) and     */
/*   the current stack pointer; the stack pointer being initialized to  */
/*   the top of RAM (__heaptop).                                        */
```

Note however, in this AgDev Toolchain, `___heaptop` is set up independently of the stack, so that the heap should not overwrite the stack (unless insufficient space has been reserved for the stack).

## Compiler runtime (compiler-rt)

These are short assembly language subroutines that are output as part of the LLVM compiler eZ80 code generation (see discussion here https://github.com/jacobly0/llvm-project/pull/10). There are a number of these not included in the CE Toolkit, instead it calls routines in the CE ROM. The list of compile runtimes is contained in the file: `llvm/lib/Target/Z80/Z80ISelLowering.cpp`which is part of the eZ80 LLVM distribution. This list the calling convention to use. There is no detailed documentation on function of each, but in most cases it can be guessed from the naming. These are thought to derive from the original Zilog compiler distribution. There is documentation for each function at the start of the Zilog files - but it is not clear whether any functionality has been changed. Given that the routines in the CE ROM were most likely compiled using the Zilog compiler, one could reasonably assume that the routines still used in the ROM are the same as the original Zilog routines. 

The compiler-rt routines that are include are in the C runtime directory `lib/crt` of the CE Toolchain. The call address of the routines were the ROM is used is listed in `lib/crt/os.src`, see condensed version below:

```
__fadd      := 000270h
__fcmp      := 000274h
__fdiv      := 000278h
__fmul      := 000288h
__fsub      := 000290h
__ftol      := 00027Ch
__ftoul     := __ftol
__dtol      := __ftol
__dtoul     := __ftoul
__imul_b    := 000150h
__indcall   := 00015Ch
__ishl_b    := 000178h
__ishrs_b   := 000180h
__ishru_b   := 000188h
__itol      := 000194h
__ltof      := 000284h
__ltod      := __ltof
__setflag   := 000218h
__sshl_b    := 000244h
__sshrs_b   := 00024Ch
__sshru_b   := 000254h
__stoi      := 000260h
__stoiu     := 000264h
__ultof     := 000280h
__ultod     := __ultof
```

## Libraries

Contains mainly eZ80 ADL assembly (.src) files.

Items mentioned have been checked - see details. Others have not been checked.

- Public functions are part of the externally available library

- Weak functions are internal to the library

### CE (TI 84 plus CE specific stuff)

### CRT (C-runtime)

- crt0 (public): updated to target Agon - sufficient for the proof of concept, will need to be developed further to support the full library and C++ (constructors, destructors, etc. - this was in the original crt0 - needs to be added back in and tested)

- inchar.src (weak): updated to input from MOS rst 008h GETKEY command

### Libc (standard C-library)

- outchar.src (weak): updated to output to VDP by MOS rst 010h

- putchar.src (public): okay. Calls outchar (which needs to be modified)

- getchar.src (public): updated to remove bug now typecasts from unsigned char to int (the CE version typecasts from signed char - which is contrary to the C-standard) . Call inchar to get character and outchar to echo on console

In general the libc library has been derived from a number of sources:

- Floating point comes from Zilog ZDS. Note that the some additional functions have been added such as hyperbolic trig functions, cubic root, etc. These use calculations from other floating point functions.

- Sort and search from Zilog ZDS, including bsearch and qsort

- Standard IO: uses nanoprintf, there is no scanf

- File IO

- Time

- Memory management from Zilog ZDS. Includes free, malloc, realloc

- Exception handling

- String conversion from Zilog ZDS. Includes: strtof, strtol, strtoll, strtoul, strtoull

#### String Library (and longjmp / setjmp)

In the CE Toolchain, many of the string library routines that are part of libc are called in the CE ROM,  as listed in the `lib/libc/os.src` file. Condensed version below:

```
_longjmp    := 000098h
_memchr     := 00009Ch
_memcmp     := 0000A0h
_memcpy     := 0000A4h
_memmove    := 0000A8h
_setjmp     := 0000B8h
_strcat     := 0000C0h
_strchr     := 0000C4h
_strcmp     := 0000C8h
_strcpy     := 0000CCh
_strcspn    := 0000D0h
_strlen     := 0000D4h
_strncat    := 0000D8h
_strncmp    := 0000DCh
_strcasecmp := 021E3Ch
_strncpy    := 0000E0h
_strpbrk    := 0000E4h
_strspn     := 0000ECh
_strstr     := 0000F0h
_strtok     := 0000F4h
```

These are all available in the Zilog distribution as assembly source code, apart from:

- `strcasecmp`: this is not part of standard libc - and has been deleted. There is, however, `strncasecmp`.

- `strtok`: available as c source code

All of these with the exception of `strcasecmp` have been added to the AgDev toolchain as part of libc .src files.

#### File IO

In the CE Toolchain the file IO functions are wrappers around the fileioc library. This library is CE specific and needs to be replaced. There is already provision in the CE library for doing this, see the CE Toolchain documentation: [Using File I/O Functions ](https://ce-programming.github.io/toolchain/static/fileio.html). Note that the `stdio.h` file has been modified so that there is no need for a `CUSTOM_FILE_FILE` as referred to in the CE documentation.

The library has been modified to use Agon MOS calls and includes:

- fopen, fclose

- fputc, fputs

- fgetc, fgets

- feof, ferror, fflush

- fread, frwite

- fseek - only implements SEEK_SET (seek from beginning), because of the lack of ftell (see below)

- ftell - this returns an error as ftell although implemented in FatFS is not currently exposed by MOS.

And includes files

- files.c

- stdio.h

On the Agon there are two different APIs for accessing the FatFS - MOS routines and FatFS routines. Having examined the MOS source code, the MOS routines are simple wrappers around the FatFS routines, just managing / storing the FatFS file descriptors in a table (supports 8 open files). Consequently it makes sense just to use the MOS routines.

### Libcxx (standard C++ library)

### Libload (dynamic library - I think)

Contains .lib library files - needs to be investigated further

## C Calling Conventions

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

### Returns

This table lists which registers are used for return values from a function. The type’s sign does not affect the registers used, but may affect the value returned. The LSB is located in the register on the far right of the expression, e.g. `E:HL` indicates register `L` stores the LSB.

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

## MOS Calling Conventions

From the MOS documentation:

1. Commands can be abbreviated with a dot, so `DELETE myfile` and `DEL. myfile` are equivalent.
2. Commands are case-insensitive and parameters are space delimited.
3. In the syntax description, optional parameters are written as `<param>`
4. The dot (.) character can be used as a substitution for an optional numeric parameter
5. Default LOAD and RUN address is set to 0x040000
6. Numbers are in decimal and can be prefixed by '&' for hexadecimal.
7. Addresses are 24-bit, unless otherwise specified
   - `&000000 - &01FFFF`: MOS (Flash ROM)
   - `&040000 - &0BDFFF`: User RAM
   - `&0B0000 - &0B7FFF`: Storage for loading MOS star command executables off SD card
   - `&0BC000 - 0BFFFFF`: Global heap and stack
8. The RUN command checks a header embedded from byte 64 of the executable and can run either Z80 or ADL mode executables
9. MOS will also search the `mos` folder on the SD card for any executables, and will run those like built-in MOS commands

Additionally, the following has been assumed:

- On entry, HL contains the address of the command line parameter string - used for argc / argv processing

- Save AF, BC, DE, IX and IY registers

- Return with HL=0

## Appendix - eZ80 compile runtime

```
//===-- Z80ISelLowering.cpp - Z80 DAG Lowering Implementation -------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines the interfaces that Z80 uses to lower LLVM code into a
// selection DAG.
//
//===----------------------------------------------------------------------===//

  setLibcall(RTLIB::ZEXT_I16_I24,     "_stoiu",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::SEXT_I16_I24,     "_stoi",     CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::SEXT_I24_I32,     "_itol",     CallingConv::Z80_LibCall   );

  setLibcall(RTLIB::NOT_I16,          "_snot",     CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::NOT_I24,          "_inot",     CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::NOT_I32,          "_lnot",     CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::NOT_I64,          "_llnot",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::AND_I16,          "_sand",     CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::AND_I24,          "_iand",     CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::AND_I32,          "_land",     CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::AND_I64,          "_lland",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::OR_I16,           "_sor",      CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::OR_I24,           "_ior",      CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::OR_I32,           "_lor",      CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::OR_I64,           "_llor",     CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::XOR_I16,          "_sxor",     CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::XOR_I24,          "_ixor",     CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::XOR_I32,          "_lxor",     CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::XOR_I64,          "_llxor",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::SHL_I8,           "_bshl",     CallingConv::Z80_LibCall_AB);
  setLibcall(RTLIB::SHL_I16,          "_sshl",     CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::SHL_I16_I8,       "_sshl_b",   CallingConv::Z80_LibCall_AC);
  setLibcall(RTLIB::SHL_I24,          "_ishl",     CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::SHL_I24_I8,       "_ishl_b",   CallingConv::Z80_LibCall_AC);
  setLibcall(RTLIB::SHL_I32,          "_lshl",     CallingConv::Z80_LibCall_L );
  setLibcall(RTLIB::SHL_I64,          "_llshl",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::SRA_I8,           "_bshrs",    CallingConv::Z80_LibCall_AB);
  setLibcall(RTLIB::SRA_I16,          "_sshrs",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::SRA_I16_I8,       "_sshrs_b",  CallingConv::Z80_LibCall_AC);
  setLibcall(RTLIB::SRA_I24,          "_ishrs",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::SRA_I24_I8,       "_ishrs_b",  CallingConv::Z80_LibCall_AC);
  setLibcall(RTLIB::SRA_I32,          "_lshrs",    CallingConv::Z80_LibCall_L );
  setLibcall(RTLIB::SRA_I64,          "_llshrs",   CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::SRL_I8,           "_bshru",    CallingConv::Z80_LibCall_AB);
  setLibcall(RTLIB::SRL_I16,          "_sshru",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::SRL_I16_I8,       "_sshru_b",  CallingConv::Z80_LibCall_AC);
  setLibcall(RTLIB::SRL_I24,          "_ishru",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::SRL_I24_I8,       "_ishru_b",  CallingConv::Z80_LibCall_AC);
  setLibcall(RTLIB::SRL_I32,          "_lshru",    CallingConv::Z80_LibCall_L );
  setLibcall(RTLIB::SRL_I64,          "_llshru",   CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::CMP_I32,          "_lcmpu",    CallingConv::Z80_LibCall_F );
  setLibcall(RTLIB::CMP_I64,          "_llcmpu",   CallingConv::Z80_LibCall_F );
  setLibcall(RTLIB::CMP_I16_0,        "_scmpzero", CallingConv::Z80_LibCall_F );
  setLibcall(RTLIB::CMP_I24_0,        "_icmpzero", CallingConv::Z80_LibCall_F );
  setLibcall(RTLIB::CMP_I32_0,        "_lcmpzero", CallingConv::Z80_LibCall_F );
  setLibcall(RTLIB::CMP_I64_0,        "_llcmpzero",CallingConv::Z80_LibCall_F );
  setLibcall(RTLIB::SCMP_I32,         "_lcmps",    CallingConv::Z80_LibCall_F );
  setLibcall(RTLIB::SCMP_I64,         "_llcmps",   CallingConv::Z80_LibCall_F );
  setLibcall(RTLIB::SCMP,             "_setflag",  CallingConv::Z80_LibCall_F );
  setLibcall(RTLIB::NEG_I16,          "_sneg",     CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::NEG_I24,          "_ineg",     CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::NEG_I32,          "_lneg",     CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::NEG_I64,          "_llneg",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::ADD_I32,          "_ladd",     CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::ADD_I32_I8,       "_ladd_b",   CallingConv::Z80_LibCall_AC);
  setLibcall(RTLIB::ADD_I64,          "_lladd",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::SUB_I32,          "_lsub",     CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::SUB_I64,          "_llsub",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::MUL_I8,           "_bmulu",    CallingConv::Z80_LibCall_BC);
  setLibcall(RTLIB::MUL_I16,          "_smulu",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::MUL_I24,          "_imulu",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::MUL_I24_I8,       "_imul_b",   CallingConv::Z80_LibCall_AC);
  setLibcall(RTLIB::MUL_I32,          "_lmulu",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::MUL_I64,          "_llmulu",   CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::SDIV_I8,          "_bdivs",    CallingConv::Z80_LibCall_BC);
  setLibcall(RTLIB::SDIV_I16,         "_sdivs",    CallingConv::Z80_LibCall_16);
  setLibcall(RTLIB::SDIV_I24,         "_idivs",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::SDIV_I32,         "_ldivs",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::SDIV_I64,         "_lldivs",   CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::UDIV_I8,          "_bdivu",    CallingConv::Z80_LibCall_BC);
  setLibcall(RTLIB::UDIV_I16,         "_sdivu",    CallingConv::Z80_LibCall_16);
  setLibcall(RTLIB::UDIV_I24,         "_idivu",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::UDIV_I32,         "_ldivu",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::UDIV_I64,         "_lldivu",   CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::SREM_I8,          "_brems",    CallingConv::Z80_LibCall_AC);
  setLibcall(RTLIB::SREM_I16,         "_srems",    CallingConv::Z80_LibCall_16);
  setLibcall(RTLIB::SREM_I24,         "_irems",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::SREM_I32,         "_lrems",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::SREM_I64,         "_llrems",   CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::UREM_I8,          "_bremu",    CallingConv::Z80_LibCall_AC);
  setLibcall(RTLIB::UREM_I16,         "_sremu",    CallingConv::Z80_LibCall_16);
  setLibcall(RTLIB::UREM_I24,         "_iremu",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::UREM_I32,         "_lremu",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::UREM_I64,         "_llremu",   CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::UDIVREM_I24,      "_idvrmu",   CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::UDIVREM_I32,      "_ldvrmu",   CallingConv::Z80_LibCall   );

  setLibcall(RTLIB::CTLZ_I8,          "_bctlz",    CallingConv::Z80_LibCall_AC);
  setLibcall(RTLIB::CTLZ_I16,         "_sctlz",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::CTLZ_I24,         "_ictlz",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::CTLZ_I32,         "_lctlz",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::CTLZ_I64,         "_llctlz",   CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::POPCNT_I8,        "_bpopcnt",  CallingConv::Z80_LibCall_AC);
  setLibcall(RTLIB::POPCNT_I16,       "_spopcnt",  CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::POPCNT_I24,       "_ipopcnt",  CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::POPCNT_I32,       "_lpopcnt",  CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::POPCNT_I64,       "_llpopcnt", CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::BITREV_I8,        "_bbitrev",  CallingConv::Z80_LibCall_AC);
  setLibcall(RTLIB::BITREV_I16,       "_sbitrev",  CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::BITREV_I24,       "_ibitrev",  CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::BITREV_I32,       "_lbitrev",  CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::BITREV_I64,       "_llbitrev", CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::BSWAP_I32,        "_lbswap",   CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::BSWAP_I64,        "_llbswap",  CallingConv::Z80_LibCall   );

  setLibcall(RTLIB::ADD_F32,          "_fadd",     CallingConv::Z80_LibCall_L );
  setLibcall(RTLIB::SUB_F32,          "_fsub",     CallingConv::Z80_LibCall_L );
  setLibcall(RTLIB::MUL_F32,          "_fmul",     CallingConv::Z80_LibCall_L );
  setLibcall(RTLIB::DIV_F32,          "_fdiv",     CallingConv::Z80_LibCall_L );
  setLibcall(RTLIB::REM_F32,          "_frem",     CallingConv::Z80_LibCall_L );
  setLibcall(RTLIB::NEG_F32,          "_fneg",     CallingConv::Z80_LibCall_L );
  setLibcall(RTLIB::CMP_F32,          "_fcmp",     CallingConv::Z80_LibCall_F );
  setLibcall(RTLIB::FPTOSINT_F32_I32, "_ftol",     CallingConv::Z80_LibCall_L );
  setLibcall(RTLIB::FPTOSINT_F32_I64, "_ftoll",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::FPTOUINT_F32_I32, "_ftoul",    CallingConv::Z80_LibCall_L );
  setLibcall(RTLIB::FPTOUINT_F32_I64, "_ftoull",   CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::SINTTOFP_I32_F32, "_ltof",     CallingConv::Z80_LibCall_L );
  setLibcall(RTLIB::SINTTOFP_I64_F32, "_lltof",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::UINTTOFP_I32_F32, "_ultof",    CallingConv::Z80_LibCall_L );
  setLibcall(RTLIB::UINTTOFP_I64_F32, "_ulltof",   CallingConv::Z80_LibCall   );

  setLibcall(RTLIB::ADD_F64,          "_dadd",     CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::SUB_F64,          "_dsub",     CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::MUL_F64,          "_dmul",     CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::DIV_F64,          "_ddiv",     CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::REM_F64,          "_drem",     CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::NEG_F64,          "_dneg",     CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::CMP_F64,          "_dcmp",     CallingConv::Z80_LibCall_F );
  setLibcall(RTLIB::FPEXT_F32_F64,    "_ftod",     CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::FPROUND_F64_F32,  "_dtof",     CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::FPTOSINT_F64_I32, "_dtol",     CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::FPTOSINT_F64_I64, "_dtoll",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::FPTOUINT_F64_I32, "_dtoul",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::FPTOUINT_F64_I64, "_dtoull",   CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::SINTTOFP_I32_F64, "_ltod",     CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::SINTTOFP_I64_F64, "_lltod",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::UINTTOFP_I32_F64, "_ultod",    CallingConv::Z80_LibCall   );
  setLibcall(RTLIB::UINTTOFP_I64_F64, "_ulltod",   CallingConv::Z80_LibCall   );
}
```
