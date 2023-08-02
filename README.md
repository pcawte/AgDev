# AgDev - an Agon Light port of CE C/C++ Toolchain

Based on LLVM toolchain, generating eZ80 ADL code and fasmg eZ80 assembler and linker.

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

25/06/2023:

- `scanf` and `sscanf` moved into standard library (libc)

30/06/2023:

- bug in `strncpy.src` which used a ZDS pseudo op that is not implemented in fasmg assembler. Replaced by individual assembly instructions. This problem may occur in other libraries copied from ZDS. For the moment, just fixed in this one location.

- C-runtime `crt0.src` updated to added back functionality previously removed as part of the proof of concept
  
  - Supports the following C-functions:
    
    - `atexit()`, `on_exit()` - which register functions to be called at the end of the program
    
    - `exit()`, `_Exit()`, `abort()` - which exits the programme in various ways
  
  - Supports initialisers, constructors, destructors, finalisers (needs testing)
  
  - Added extensive commenting 

- Included a simple example of a user defined type (complex) which overloads a number of operators.

- Changed default location of BSS & heap to 0x080000 to 0x09ffff

02/07/2023:

- mos_api updated:
  
  - `unit32_t getsysvar_time()` function added
  
  - typedef `RTC_DATA` created for the format of data returned from `getsysvar_rtc()`
  
  - `getsysvar_rtc()` updated to  `volatile RTC_DATA *getsysvar_rtc()` to reflect that the returned pointer refers to a value that is dynamically changed by MOS - and shouldn't there be optimised. Changed to return type `RTC_DATA *`
  
  - Added example under `tests/mos_time`

- `clock_t clock()` function implemented using the Agon timer. Other RTC related functions are in the process of being ported.

03/07/2023:

- Corrected` lib/crt/fpftol.src` to remove ZDS pseudo op not supported by fasmg and removed other ZDS assembler features that are different in fasmg

- Corrected `lib/crt/fpultof.src` to remove ZDS assembler directives that are different in fasmg

- Ported time functions: `difftime()`, `mktime()`, `time()`, `localtime()`, `gmtime()`, `asctime()`, `ctime()` 

- Updated comments in `mos_api.h` to note that `getsysvar_rtc()` data is only updated when `mos_getrtc()` is called. This is taken account of in `time()`.

04/07/2023:

- Dhrystone benchmark added under full `ansibench/dhrystone`.

09/07/2023:

- Support for output re-direction added for stdout. Cannot currently be done from the command line (todo), but can be done programmatically using `freopen()`.
  
  - `freopen()` added
  
  - `puts()` and `printf()` updated to call `putchar()` instead of directly calling `outchar()`
  
  - `putchar()` modified to either call `outchar()` of `fputc()` depending on whether output redirected
  
  - `fputc()` modified to call `outchar()` when outputting to `stdout` or `stderr` to avoid any danger of function call loops
  
  - `fclose()` modified to allow stdout to be closed if it has been redirected
  
  - `stdio.h` and `files.c` modified to support input / output redirection
  
  - `linker.script` updated to include `freopen()`
  
  - Test / demonstration program added under `test/stdout-redirect`

10/07/2023:

- Support for input re-direction added for stdin. Cannot currently be done from the command line (todo), but can be done programmatically using `freopen()`.
  
  - `getchar()`- calls `inchar()`to get the character and `outchar()`to echo the character (even if the output has been redirected). If output has not been re-directed calls `fgetc()`and does not echo the character.
  
  - `gets_s`- calls `getchar()`if input has not been redirected (line are terminated with CR). Calls `fgets()` of input has been redirected (lines are terminated with CR/LF pair).
  
  - `fgetc` - calls `mos_fgetc()` unless called on `stdin` when calls `inchar()` and echos with `outchar()` - avoids calling `getchar()` so that no risk of function call loops
  
  - Test / demonstration program added under `test/stdin-redirect`

- Bug fixed previously if a program was run again from the command line without re-loading it, stdin, stdout and stderr were not reset.
  
  - Added re-run handling in `crt0.src` (currently very simplistic as only initialises stdio)
  
  - `_stdio_init()` function added to files.c. This is only called from `crt0.src` and is not declared in any header file. 

- Added fasmg quick reference guide (from [Assembling eZ80 code with flat assembler g - Cemetech | Forum | Your Projects [Topic]](https://www.cemetech.net/forum/viewtopic.php?t=13913&start=0)) - but formatted to make readable / intelligible.

12/07/2023:

- `puts()` modified to print "(NULL)" if called with a null pointer. Code shortened. Defines 2 static strings which can be used elsewhere. Note there is still an issue with `printf()`.
  
  - `__null_literal_str` as "(NULL)"
  
  - `__end_of_line_str` as CR/LF pair

13/07/2023:

- `fopen()` modified to correct apparent bug in MOS. Now seeks to end of file when file opened for append ("a"). Previously wrote from the beginning. Now writes from the end.

- `gets_s()` corrected to also output LF after CR pressed by the user. 

- `puts()` corrected was outputting LF/CR not CR/LF

- `gets_s()` corrected to strip CR/LF pair if used with input redirected

14/07/2023:

- support for input / output redirection added on the MOS command line, e.g. `RUN &040000 <in.txt >out.txt`. Enabled by including `LDHAS_ARG_PROCESSING = 1` in the makefile.
- This also supports quoting of command line arguments with double quotes.
- `tests/args` updated to demonstrate the effect of quoting
- `tests/quote` added to demonstrate input / output redirection from the MOS command line

16/07/2023:

- `linker_script` corrected to include` strncmp`, which was missing.

17/07/2023:

- And support for text and binary file modes - text mode has LF translation for input and output. Binary does not translate. At same time at support for unget of one character.
  
  - Definition of `FILE` changed in `stdio.h` and `file.c` to store mode and unget character in FILE struct. Note, need to recompile the whole of stdio library because of change in definition of FILE.

- Translate LF (`'\n'`) to CR/LF when writing to console and file. For files this is done by default, but not if the file is opened in binary mode.
  
  - `putchar.src` modified to do translation when stdio is not redirected
  
  - `puts.src` modified to no longer send CR/LF at end of line - now just sends LF and allows `putchar` to do the translation.
  
  - `fputc.c` modified to translate LF to CR/LF if FILE was opened in text mode
  
  - `fputs.c` modified to no longer send CR/LF at end of line - now just sends LF and allows `fputc` to do the translation.
  
  - `getchar.src` modified to do translation of CR to LF and support `ungetc()`. Note that console keyboard only generates CR and not CR/LF pair.
  
  - `gets_s.c` modified - as translation is now done by `getchar()`, only needs to look for LF.
  
  - `fgetc.c` modified to do translation of CR/LF pair to LF and support `ungetc()`
  
  - `fgets.c` modified - as translation is now done by `fgetc()`, only needs to look for LF.

- `fprintf()` and `vfprintf()` functions added in `nanoprintf.c`
  
  - CE toolchain option to use built in system printf function removed. Aliasing of names in `printf.src` no longer used. Naming simplified in `nanoprintf.c`. Linker option `HAS_PRINTF` no longer does anything. Entry for `printf.src` removed from `linker_script`

- `ungetc()` function added - can only unget one character
  
  - `fseek()`,  `fflush()` all modified to clear the character pushed back on the stream.

- `fseek()` modified to allow seeking on redirected `stdin`, `stdout` or `stderr`.

- `ftell()` modified to allow calling on redirected `stdin`, `stdout` or `stderr`.

- `maptab.c` updated to include all white space characters. Is used by isspace() function. Previously it only had the actual space character listed as white space, causing problems for `scanf()`.
  
  - `isspace.src` comments added

18/07/2023

- `setjmp.src` and `longjmp.src` corrected to fix bugs in conversion from ZDS to fasmg assembler - moved public statements inside section and replace ZDS pseudo ops.

- `strstr.src` corrected to replace ZDS pseudo op

- `memcmp.src` added to `linker_script` - was previously missing

22/07/2023

- `crt0.src` and `sbrk.src` updated to fix reset start of heap if program is rerun. Previously if a program was rerun the start of heap used by malloc was not reset - potentially leading to not enough memory for malloc.

- `crt0.src` updated to optimise the initialisation of BSS

- `README.md` updated to included documentation on VDP and VDU commands

- `mos_api.h` updated to include a structure for manipulating SYSVAR

- `tests/malloc` updated to demonstrate correct functioning of `malloc()`

- `tests/vdu` added to demonstrate use of VDU commands - part of developing VDP/VDU wrapper library

23/07/2023

- Started process of converting  VDP/VDU demo to a library with creation of `vdp_vdu.c` and `vdp_vdu.h` - although still in `tests/vdu` directory.
  
  - Added `tests/big-bitmap` to demonstrate the load of large bit maps from a file - this works on the emulator, but not on actual Agon Light HW, where there does not seem to be enough available memory in VDP (not sure of the reason for this).

24/07/2023

- `crt0.src` problem fixed with return value from `exit()` or `_Exit()` not being properly returned to MOS

25/07/2023

- Exit handler added to print error / exit message at end of program. This is required if program returns non-zero, as MOS interprets this as one of various file errors. 
  
  - Added in `crt0.src`
  
  - If not required (to slightly shorted the code) can be disabled setting `LDHAS_EXIT_HANDLER:=0` in `makefile`
    
    - `makefile.mk` has been updated to include the exit handler by default
  
  - `stdlib.h `updated to include 3 exit codes
    
    - EXIT_SUCCESS
    
    - EXIT_FAILURE
    
    - EXIT_ABORT
  
  - Added test/exit to test/demonstrate the functionality

26/07/2023

- `scanf` library updated
  
  - Handling of backspace, cursor left and control-C during input
  
  - Added `fscanf()`
  
  - Updated `tests/scanf` to include test of `fscanf()`

- `gets_s()` updated to handle backspace, cursor left and control-C during input

01/08/2023

- `Agon-HW.md` file started to collect documentation on Agon hardware
  
  - Section on UART0 / VDP interrupt with a focus on understanding keyboard input

- `lib/agon/intagon.src` created - intercepts Agon UART0 interrupt to maintain an array of bits for key presses (one bit per key). This allows multiple key presses to be detected at the same time

- `vdp_vdu` library created for using VDP graphics via the VDU commands
  
  - `vdp_bell()`
  
  - `vdp_cursor_left()`
  
  - `vdp_cursor_right()`
  
  - `vdp_cursor_down()`
  
  - `vdp_cursor_up()`
  
  - `vdp_clear_screen()`
  
  - `vdp_clear_graphics()`
  
  - `vdp_cursor_home()`
  
  - `vdp_cursor_tab()`
  
  - vdp_set_`text_colour()`
  
  - `vdp_mode()`
  
  - `vdp_graphics_origin()`
  
  - `vdp_get_scr_dims()`
  
  - `vdp_logical_scr_dims()`
  
  - `vdp_cursor_enable()`
  
  - `vdp_move_to()`
  
  - `vdp_line_to()`
  
  - `vdp_point()`
  
  - `vdp_triangle()`
  
  - `vdp_circle_radius()`
  
  - `vdp_circle()`
  
  - `vdp_select_bitmap()`
  
  - `vdp_draw_bitmap()`
  
  - `vdp_load_bitmap()`
  
  - `vdp_load_bitmap_file()`
  
  - `vdp_load_sprite_bitmaps()`
  
  - `vdp_create_sprite()`
  
  - `vdp_select_sprite()`
  
  - `vdp_move_sprite_to()`
  
  - `vdp_move_sprite_by()`
  
  - `vdp_show_sprite()`
  
  - `vdp_hide_sprite()`
  
  - `vdp_next_sprite_frame()`
  
  - `vdp_prev_sprite_frame()`
  
  - `vdp_nth_sprite_frame()`
  
  - `vdp_activate_sprites()`
  
  - `vdp_refresh_sprites()`
  
  - `vdp_reset_sprites()`

- `vdp_key` library created for accessing VDP keyboard data to maintain a bit map of key presses (can be simultaneous)
  
  - `vdp_key_init():` initialise the VDP keyboard routines, which hook into the UART0 interrupt handler and maintains an array `vdp_key_bits[32]` of up/down status per key.
  
  - `vdp_key_reset_interrupt()`: resets the original interrupt vector. This does not normally need to be explicitly as it is registered to be call at the end of the program via `atexit()`. It can however be safely called. 
  
  - `vdp_set_key_event_handler()`: sets a handler function to be called when a key is pressed. It is passed a KEY_EVENT
  
  - `vdp_update_key_state()`:  this should be called frequently in the main game loop, otherwise events might be missed - there is in any case a small chance of this (could consider integrating into the interrupt routine). It is the routine that tiggers the event handler.
  
  - `vdp_check_key_press()`: checks for a key press by examining `vdp_key_bits[]`.

- `linker_script`: updated to include the above 3 items and remove some CE items left over from the original version.

- `tests/sprite` added to demonstrate sprites and keyboard handling

02/08/2023

- Added sprite related functions
  
  - `vdp_clear_sprite()`
  
  - `vdp_add_sprite_bitmap()`

### To-Do / Known Issues:

- Testing / validation

- Check for ZDS pseudo ops in any assembly language source files copied from ZDS

- Review and improved efficiency / size of crt0.src and resulting binary - including the use of compile time options

- For stdio remove stuff inherited from CE Toolchain (there is nothing used, but some remnants in the various files)

- Change printf %s with NULL pointers to do something sensible

- Close files that have not been closed on `exit()` as MOS does not close them and runs out of file handles - plus this is part of the C standard

### To-Do - New Features

- Complete vdp_vdu library - for example, need to add routines for colours and palette

- Add command line support for redirection of stderr

- Add simulation of pipes

- Port / replace / expand library where necessary to the Agon Light. Including:
  
  - investigate benefits of buffering for stdio.
  - VDP/VDU library

- Create own repository that is not dependent on CE Toolchain
  
  - Clean out the CE specific stuff

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
  -i 'range .bss $080000 : $09ffff'
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

- lib/crt/crt0.src: C runtime (this has been customised for Agon)

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

- BSSHEAP_LOW = 080000: this seems to work for a small programme - but not sure what should really be used

- BSSHEAP_HIGH = 09FFFF: as above

- STACK_HIGH = 0AFFFF: this seems to work - but not sure what should really be used - or even if this really needs to be set. For the moment this has been removed from the fasmg flags and whatever stack that is provided by MOS is used.

See details below for memory layout.

### C runtime - crt0.src

This has been re-written based on a combination of code from the reverse engineered CE Toolchain version and some of the original [Agon projects]([GitHub - breakintoprogram/agon-projects: Official AGON QUARK Firmware: Projects](https://github.com/breakintoprogram/agon-projects)) which used the Zilog toolchain, some of the optimisations used in the CE Toolchain have been removed for clarity. Note that the Zilog assembler, fasmg assembler used by CE toolkit and ez80asm used by many in the Agon community all have different formats and different waves of organising program sections, etc. Part of the challenge of this proof of concept has been in understanding the fasmg assembler.

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
BSSHEAP_LOW ?= 080000
BSSHEAP_HIGH ?= 09FFFF
STACK_HIGH ?= 0AFFFF
```

The layout can be checked by examining the following labels in the `.map` file.

```
___low_bss             = 080000
___len_bss             = 000000
___heaptop             = 05FFFF
___heapbot             = 080000
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

- Standard IO: uses nanoprintf
  
  - scanf and sscanf have been added based on the Zilog ZDS code

- File IO: re-written / adapted from CE-Toolchain

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

- `fopen`, `fclose`

- `fputc`, `fputs`

- `fgetc`, `fgets`

- `feof`, `ferror`, `fflush`

- `fread`, `frwite`

- `fseek`, `rewind`, `ftell` 

- `clearerr`

- `remove`

And includes files

- `files.c`

- `stdio.h`

On the Agon there are two different APIs for accessing the FatFS - MOS routines and FatFS routines. Having examined the MOS source code, the MOS routines are simple wrappers around the FatFS routines, just managing / storing the FatFS file descriptors in a table (supports 8 open files). Consequently it makes sense just to use the MOS routines.

##### Text and Binary Files

The stdio library has been modified to differentiate between text and binary files.

- When files are opened, they are assumed to be texted, unless binary is specified in the mode flags (see `fopen()` documentation).

- stdin, stdout and stderr are assumed to be text - if reopened via `freopen()`, it is possible to change to binary.

For text files, a translation is done between standard C, where '\n' (LF) is the end of a line and the operating system, which requires CR/LF pair at the end of a line. This applies to the following functions:

- `putchar()`, `puts()`

- `fputc()`, `fputs()`

- `printf()`, `fprintf()` - but not `sprintf()`

Note that the following functions do not differentiate between text and binary files:

- `fread()`, `frwite()`

- `fseek()`, `ftell()`

### Libcxx (standard C++ library)

This is very limited, mainly just C++ wrapper around C libraries

### Libload (dynamic library - I think)

Contains .lib library files - needs to be investigated further

## C Calling Conventions

See Zilog application note "an0333 - Calling C from asm.pdf"

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

Programs are called from MOS using the the `_exec24()` function built into MOS :

- This function will call the 24 bit address and keep the eZ80 in ADL mode. 

- The called function must do a RET and take care of preserving registers

- On entry, HL contains the address of the command line parameter string - used for argc / argv processing. There is 256 bytes for storage of the command line including the terminating '`\0'`.

- Save AF, BC, DE, IX and IY registers

- Return with HL=0

On exit from a program, MOS interprets the value in HL as a "file error", with the following being defined (0=OK, 1=Error accessing SC card, etc):

    "OK",
    "Error accessing SD card",
    "Assertion failed",
    "SD card failure",
    "Could not find file",
    "Could not find path",
    "Invalid path name",
    "Access denied or directory full",
    "Access denied",
    "Invalid file/directory object",
    "SD card is write protected",
    "Logical drive number is invalid",
    "Volume has no work area",
    "No valid FAT volume",
    "Error occurred during mkfs",
    "Volume timeout",
    "Volume locked",
    "LFN working buffer could not be allocated",
    "Too many open files",
    "Invalid parameter",
    "Invalid command",
    "Invalid executable",

## Standard IO Library

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

### Stdio Redirection

Can redirect output by using `freopen() `on `stdout` or `stderr`:

- `putchar()` - outputs to `outchar()` unless the output is redirected, in which case outputs to `fputc()`

- `puts()` - calls `putchar()`

- `printf()` (and `vprintf()`) - calls `npf_putc_std()`, which calls `putchar()` in `nanoprintf.c`

- `fputc()` - calls `mos_fputc()` unless called on `stdout` when calls `outchar()`- avoids calling `putchar()` so that no risk of function call loops

Can redirect input by using `freopen()` on `stdin`:

- `getchar()` - calls `inchar()` to get the character and `outchar()` to echo the character (even if the output has been redirected). If output has not been re-directed calls `fgetc()` and does not echo the character.

- `gets_s()`- calls `getchar()` if input has not been redirected (line are terminated with CR). Calls`fgets()` of input has been redirected (lines are terminated with CR/LF pair).

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

### Simple Command Line Processing

This is automatically included if the main function is defined as

```
int main( int argc, char* argv[] )
```

the splits the command line up using space as a delimiter. The command line options are available in the `argv[]` array as normal. 

### Complex Command Line Processing - for Redirection & Quoting

This is optionally included if the makefile includes:

```
LDHAS_ARG_PROCESSING = 1
```

This supports

- Quoting with double quotes

- Input / output redirection
  
  - `>out_file.txt` - redirects stdout to `out_file.txt`, creating a new file
  
  - `>>out_file.txt` - redirects stdout to `out_file.txt`, appending to the end of the file
  
  - `<in_file.txt` - redirects stdin to be from `in_file.txt`
  
  - TODO: add redirection for stderr

## VDP / VDU Commands

The VDP (video display processor) accepts a text stream from MOS, acting like a text / graphics terminal. The text stream can contain:

- Normal text

- Escape sequences / commands to control the display and send graphics

When results are returned by MOS as a result of sending a command, these are stored in the SYSVARs and not returned directly in response to the command. The response is asynchronous, to check that a result has been returned:

- Set `vpd_pflags` in `SYSVAR` to zero

- Issue the VDU command

- Wait for the relevant bit into in `vpd_pflags` to be set - see `<mos_api.h>`  for the bit masks

Commands can be sent by:

- `putch()` - single character (this is not part of the C standard library, on MS-DOS systems it is defined in `<conio.h>`

- `mos_puts()` - multi-character string

Both of  which output directly to MOS/VDP - note that they are not part of STDIO library and not subject to CR/LF translation or redirection.

### VDU Commands

From [VDP - breakintoprogram/agon-docs GitHub Wiki](https://github-wiki-see.page/m/breakintoprogram/agon-docs/wiki/VDP), with any clarifications from testing or examining the VDP source code. 

- `VDU 32-126`: normal ASCII text output

- `VDU 4`: seems to be setGlyphOptions for text

- `VDU 5`: seems to be setGlyphOptions for graphics

- `VDU 7`: bell - plays a note

- `VDU 8`: cursor left

- `VDU 9`: cursor right

- `VDU 10`: cursor down (line-feed)

- `VDU 11`: cursor up

- `VDU 12`: clear screen

- `VDU 13`: carriage return

- `VDU 14`: page mode on

- `VDU 15`: page mode off

- `VDU 16`: CLG (clear graphics - presumably)

- `VDU 17, colour`: set the text foreground colour

- `VDU 18, mode, colour`: GCOL (graphics colour - presumably)

- `VDU 19, l, p, r, g, b`: define logical palette - colour l, p / colour l, r, g, b

- `VDU 22, n`: mode n

- `VDU 23, n`: UDG / system commands

- `VDU 24, left; bottom; right; top;`: define a graphics viewport (VDP 1.04 or later)

- `VDU 25, mode, x; y;`: PLOT mode, x, y

- `VDU 26`: reset text and graphics viewports (VDP 1.04 or later)

- `VDU 28, left, bottom, right, top`: define a text viewport (VDP 1.04 or later)

- `VDU 29, x; y;`: set graphics origin

- `VDU 30`: cursor home (move cursor to top left of viewport)

- `VDU 31, x, y`: tab(X, Y)

- `VDU 127`: backspace

Values followed by `;` are two byte words (little endian), otherwise value are single bytes.

#### VDU 23 Commands

##### VDU 23,0: VPD Commands

VDU 23, 0 is reserved for commands sent to the VDP

- `VDU 23, 0, &81, n`: Set the keyboard locale (0=UK, 1=US, etc)
- `VDU 23, 0, &82`: Request cursor position
- `VDU 23, 0, &83, x; y;`: Get ASCII code of character at character position x, y
- `VDU 23, 0, &84, x; y;`: Get colour of pixel at pixel position x, y
- `VDU 23, 0, &85, channel, waveform, volume, freq; duration;`: Send a note to the VDP audio driver
- `VDU 23, 0, &86`: Fetch the screen dimensions
- `VDU 23, 0, &87`: RTC control (Requires MOS 1.03 or above)
  - `VDU 23, 0, &87, 0`: Read the RTC
  - `VDU 23, 0, &87, 1, y, m, d, h, m, s`: Set the RTC
- `VDU 23, 0, &88, delay; rate; led`: Keyboard Control (Requires MOS 1.03 or above)
- `VDU 23, 0, &C0, n`: Turn logical screen scaling on and off, where 1=on and 0=off (Requires MOS 1.03 or above)
- `VDU 23, 0, &FF`: Switch to terminal mode for CP/M (This will disable keyboard entry in BBC BASIC/MOS)

Commands between &82 and &88 will return their data back to the eZ80 via the serial protocol

##### VDU 23, 1: Cursor display

- `VDU 23, 1, 0`: Disable the text cursor
- `VDU 23, 1, 1`: Enable the text cursor

##### VDU 23, 7: Scrolling

- `VDU 23, 7, extent, direction, speed`: Scroll a rectangle on the screen
  - Extent (0 = text viewport, 1 = entire screen, 2 = graphics viewport)
  - Direction (0 = right, 1 = left, 2 = down, 3 = up)
  - Speed: number of pixels to scroll

##### VDU 23, 16: Define Cursor Behaviour (Requires VDP 1.04 or greater)

- `VDU 23, 16, setting, mask`: Specify by ANDing with mask then XORing with setting

The following bits are implemented in VDU 23, 16

- `Bit 0 = 1`: Enable scroll protection - text cursor will not scroll when it moves off the bottom/right of the viewport
- `Bit 0 = 0`: Disable scroll protection (default)
- `Bit 4 = 1`: Text cursor will wrap to top of screen when it moves off the bottom of the screen
- `Bit 4 = 0`: Text cursor will scroll when it moves off the bottom of the screen (default)
- `Bit 5 = 1`: Cursor does not move right after a character is printed
- `Bit 5 = 0`: Cursor moves right after a character is printed (default)
- `Bit 6 = 1`: Graphics cursor (VDU 5 mode) carries on off edge of graphics viewport
- `Bit 6 = 0`: Graphics cursor does an implicit cr/lf when it moves off right of graphics viewport (default)

##### VDU 23, 27: Sprites and Bitmaps

VDU 23, 27 is reserved for the bitmap and sprite functionality

Note that there are differences between the way the emulator and Agon Light hardware handles bitmaps.

- Emulator does not have a memory limit, which means it is possible to load large bitmaps
  
  - On the real hardware if a large bitmap is loaded this starts to reduce the amount of memory for the display. For example in mode 3, if a 180x50 bitmap is loaded, the vertical height of mode 3 is reduced from 480 to 356 pixels.

- In mode 0 which is 2 colour, emulator still shows multi-colour images, whereas on the actual HW they are black and white

**Bitmaps**

- `VDU 23, 27, 0, n`: Select bitmap n

- `VDU 23, 27, 1, w; h; r1, g1, b1, a1, r2, g2, b2, a2, ...`: Load colour bitmap data into current bitmap
  
  - Data is in RGBA format - i.e. 32 bits per pixel

- `VDU 23, 27, 2, w; h; r, g, b, a`: Load solid bitmap data into current bitmap
  
  - Note that this is from checking the code - this is what the documentation says, but does not align with the code - `VDU 23, 27, 2, w; h; col1; col2; b1, b2 ... bn`: Load monochrome bitmap data into current bitmap

- `VDU 23, 27, 3, x; y;`: Draw current bitmap on screen at pixel position x, y

Up to 255 bitmaps are supported

Images (.png) can be converted to the correct format using imagemagick:

```
convert source.png dest.rgba
```

 **Sprites**

- `VDU 23, 27, 4, n`: Select sprite n
- `VDU 23, 27, 5`: Clear frames in current sprite
- `VDU 23, 27, 6, n`: Add bitmap n as a frame to current sprite
- `VDU 23, 27, 7, n`: Activate n sprites
- `VDU 23, 27, 8`: Select next frame of current sprite
- `VDU 23, 27, 9`: Select previous frame of current sprite
- `VDU 23, 27, 10, n`: Select the nth frame of current sprite
- `VDU 23, 27, 11`: Show current sprite
- `VDU 23, 27, 12`: Hide current sprite
- `VDU 23, 27, 13, x; y;`: Move current sprite to pixel position x, y
- `VDU 23, 27, 14, x; y;`: Move current sprite by x, y pixels
- `VDU 23, 27, 15`: Update / refresh the sprites in the GPU
- `VDU 23, 27, 16`: Reset the sprites and clear all data (Requires MOS 1.03 or above)

Sprites reference underlying bit maps

Sprite creation order:

1) Create bitmap(s) for sprite, or re-use bitmaps already created

2) Select the correct sprite ID (0-255). The GDU only accepts sequential sprite sets, starting from ID 0. All sprites must be adjacent to 0

3) Clear out any frames from previous program definitions

4) Add one or more frames to each sprite

5) Activate sprite to the GDU

6) Show sprites on screen / move them around as needed

7) Refresh

##### VDU 23, ASCII-code: User Defined Characters (UDG)

- `VDU 23, ascii-code, n1, n2, n3, n4, n5, n6, n7, n8`: redefine character with ASCII code (>=32).

#### VDU 25 Plot Commands

- `VDU 25, &04, x; y;`: move to

- `VDU 25, &05, x; y;`: line to

- `VDU 25, &40-&47, x; y;`: point
  
  - &40-&47: makes no difference which value is used

- `VDU 25, &50-&57, x; y;`: triangle (filled)
  
  - &50-&57: makes no difference which value is used

- `VDU 25, &90-&97, x; y;`: circle (not filled)
  
  - &90-93: circle centred on current point, with radius specified by either x or y
  
  - &94-97: circle centred on current point passing through x, y

Three successive points are maintained, updated whenever a call is made to VDU25. These are used, for example, for the vertices of the triangle.

## VDP / Keyboard Interrupts

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
  setLibcall(RTLIB::UINTTOFP_I64_F64, "_ulltod",   CallingConv::Z80_LibCall   );c
```

## Appendix - FASMG Quick Reference Guide

From: https://www.cemetech.net/forum/viewtopic.php?t=13913&start=0

### Expressions

Each line is a precedence level, except where specified otherwise, operators within a precedence level are evaluated ltr.

| Ops                                         | Meaning                                                                                                                                                                                                                                                  |
| ------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
|                                             | ***Logical expressions***                                                                                                                                                                                                                                |
| ~                                           | unary logical not, arguments can also be                                                                                                                                                                                                                 |
| &, \|                                       | binary logical conjunction and disjunction                                                                                                                                                                                                               |
|                                             | ***All the operators below this line can only have basic expressions as arguments***                                                                                                                                                                     |
| =, <, >, <=, >=, <>, eq, eqtype, relativeto | Comparison, <> is not equal, eq is like = but returns false for uncomparable operands, eqtype returns true if both operands are the same (algebraic, string, float) type, relativeto returns true if both operands are comparable (differ by a constant) |
| defined, used                               | true if the basic expression to the right is entirely defined, true if the variable name to the right is used                                                                                                                                            |
|                                             | ***Basic expressions***                                                                                                                                                                                                                                  |
| lengthof, elementsof, float, trunc          | length of a string in characters, length of a poly in terms, int to float, float to int                                                                                                                                                                  |
| sizeof, elementof, scaleof, metadataof      | rtl size associated with a label, poly op idx for element,  scale,   metadata    idx op poly                                                                                                                                                             |
| not, bsf, bsr                               | complement, index of lowest set bit, index of highest set bit                                                                                                                                                                                            |
| shl, shr, bswap                             | shifts, byte swap (second arg is the size of the value to swap, in bytes)                                                                                                                                                                                |
| xor, and, or                                | bitwise                                                                                                                                                                                                                                                  |
| mod                                         | remainder                                                                                                                                                                                                                                                |
| *, /                                        | multiplication, division                                                                                                                                                                                                                                 |
| +, -                                        | addition, subtraction (includes unary ops)                                                                                                                                                                                                               |
| string                                      | converts a number to a string (strings are usually converted to numbers implicitly, or explicitly with a unary + operator)                                                                                                                               |

### Builtin symbolic variable

- `<name>#<name>` ; concatenates two names into a single identifier, but each side may get replaced individually if it matches a parameter name

- `$` ; current pc

- `$$` ; base of the current output section (address passed to last org)

- `$@` ; address after last non-reserved data

- `$%` ; offset within output file, does not work with tiformat.inc

- `$%%` ; offset after last non-reserved data within output file, does not work with tiformat.inc

- `%t` ; assembly timestamp

- `__file__` ; current file

- `__line__` ; current line

### Commands

#### Program Layout

- `org <basic expr>` ; start a new output area to appear next in the file and assembled starting at address `<basic expr>`

- `section <basic expr>` ; same as org but do not output reserved bytes, does not work with tiformat.inc

- `virtual [<basic expr>] `; start a new output area that does not get output to the file
  end virtual ; restore the previous output area

- `<name>::` ; creates an area label that references the current output area

- `load <name>[ : <size>] from [<area label> : ]<addr>` ; loads `<size>` (defaults to `sizeof <addr>`) outputted bytes from address `<addr>` in output area `<area label>` (defaults to current output area) and store in variable `<name>`

- `store <name>[ : <size>] at [<area label> : ]<addr>` ; stores `<size>` (defaults to `sizeof <addr>`) bytes to address `<addr>` in output area `<area label>` (default to current output area) and store in variable `<name>`

#### Data / Storage

- `db <basic expr 1>[, <basic expr 2>...] `; define 1-byte values

- `rb <basic expr>` ; reserve `<basic expr>` 1-byte locations

- `dw <basic expr 1>[, <basic expr 2>...]` ; define 2-byte values

- `rw <basic expr>` ; reserve `<basic expr>` 2-byte locations

- `dl <basic expr 1>[, <basic expr 2>...] `; define 3-byte values

- `rl <basic expr>` ; reserve `<basic expr>` 3-byte locations

- `dd <basic expr 1>[, <basic expr 2>...] `; define 4-byte values

- `rd <basic expr>` ; reserve `<basic expr>` 4-byte locations

- `emit|dbx <size> : <basic expr 1>[, <basic expr 2>...] `; define `<size>`-byte values;

If any reserve or definition is preceded by a name with no colon, that name gets defined as a label to the first item, with a sizeof the item size

Inside any definition

- `<basic expr 1> rep <basic expr 2>` ; repeats `<basic expr 2>` `<basic expr 1>` times, to include more than one value in the repetition, enclose them with <>

#### Names

- `<name> equ <anything>` ; define an arbitrary text substitution for a symbol

- `<name> reequ <anything>` ; same as equ but don't discard previous value

- `define <name> <anything>` ; same as equ, but <anything> is not checked for recursive substitutions until use

- `redefine <name> <anything>` ; same as define but don't discard previous value

- `<name> = <basic expr>` ; assign a value to a symbol, discarding current value

- `<name> =: <basic expr>` ; assign a value to a symbol, remembering the current value

- `<name> := <basic expr>` ; assign a value to a constant symbol only once, attempts to redefine will error, therefore it can always be forward referenced

- `<name>:` ; like `<name> := $`

- `label <name>[ : <size>][ at <addr>] `; defines a constant symbol with <size> size at address <addr> (defaults to $)

- `restore <name 1>[, <name 2>...] `; restore the previously remembered value for each symbol

#### Namespaces

Namespaces can be created by assigning anything to any symbol

- `namespace <name 1>` ; switches to, but does not create, the namespace associated with the symbol <name>

- All new symbols `<name 2>` defined in here can be referenced outside the namespace block with <name 1>.<name 2>

- `end namespace`

#### Macros

- `macro <name> [<param 1>[, <param 2>...]] `; defines a macro, remembering the current contents. Macro body, parameters get substituted with their values every time the macro is executed

- `end macro`

- `purge <name>` ; restores the previously remembered contents of a macro

- `struc <name> [(<label name>) ][<param 1>[, <param 2>...]]` ; defines a labeled macro, remembering the current contents. Macro body, parameters get substituted with their values every time the macro is executed, Both `.` and `<label name>` refer to the label

- `end struc`

- `restruc <name>` ; restores the previously remembered contents of a labeled macro

Macro and struc args can be suffixed with `*` to mean required, `:` to give a default value if not specified, and `&` on the last argument means it takes on the value of all the remaining arguments

- `local <name 1>[, <name 2>...] `; makes the specified symbols local to the current macro or struc invocation

- `esc macro ...` ; exactly like macro, but does not require an extra end macro to end the enclosing macro

- `esc end macro` ; exactly like end macro, but does not close the enclosing macro even if there was no opening macro

#### Conditional Assembly & Loops / Iteration

- `[else ]if <cond expr>` ; run these commands if `<cond expr>` is true, with else only if the previous command was false or didn't match

- `[else ]match <pattern>, <anything>` ; run these command if `<pattern>` matches `<anything>`, with else only if the previous command was false or didn't match

- `[else ]rmatch <pattern>, <anything>`; run these command if `<pattern>` matches `<anything>`, discarding context, with else only if the previous if was false or match didn't match

- `else`; run these commands if previous if was false or match didn't match

- `end if|match|rmatch` ; ends if, match, or rmatch, use whichever was used last (before the optional else)

- `while <cond expr>`; run these commands while `<cond expr>` is true

- `end while`

- `repeat <basic expr>[, <name 1> : <basic expr 1>[, <name 2> : <basic expr 2>...]]`; run these commands `<basic expr>` times, symbols start at their initial value and go up by one each iteration

- `end repeat`

- `iterate|irp <name>[, <first>[, <second>...]]`; run these commands

- `end iterate|irp`

- `irpv <name 1>, <name 2>`; run these commands with name 1 equal to each remembered value of name 2, starting from the oldest, only works with define/equ

- `end irpv`

Inside all looping commands:

- `%` ; current iteration starting from 1

- `%%` ; total iterations

- `indx <basic expr>` ; switches to a different iteration index

- `break` ; break out of loop

#### General

- `include '<file>'` ; assembles `<file>` at the current location in the source

- `file '<file>'[ : <start>[, <size>]]` ; outputs `<size>` (defaults to entire file) bytes from a file starting at byte `<start>` (defaults to beginning)

- `display <basic expr 1>[, <basic expr 2>...] `; outputs strings as strings and numbers as characters to stdout

- `eval <basic expr 1>[, <basic expr 2>...]` ; same syntax as display, evaluates the concatenation of all the arguments as assembly code at the current location in the source

- `err <basic expr 1>[, <basic expr 2>...] `; same syntax as display, displays a custom error the causes assembly to fail if this is the last pass

- `assert <cond expr>` ; causes assembly to fail if <cond expr> is false on the last pass
