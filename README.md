# AgDev proof of concept - based on CEdev

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

Install the CE Toolchain - see [getting started]([Getting Started &mdash; CE C/C++ Toolchain documentation](https://ce-programming.github.io/toolchain/static/getting-started.html)) page. The tool-chain can be installed on Windows, Linux or MacOS.  Follow the instructions to complete the install, and test that the tool-chain works by compiling some of the examples for the TI calculator.

To adapt the the tool-chain for Agon, for this proof of concept, a number of files should be replaced 



## Build process for proof of concept

In the `AgExamples/hello_world` issue the `make` command (use V=1 not necessary but provides much more details on the commands used): 

```
make V=1
```

The `make clean`command can be used to delete the results of previous compilations and thereby force a recompilation.

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
  -i 'range .bss $041000 : $042000'
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

- BSSHEAP_LOW = 041000: this seems to work for a small programme - but not sure what should really be used

- BSSHEAP_HIGH = 042000: as above

- STACK_HIGH = 04FFFF: this seems to work - but not sure what should really be used - or even if this really needs to be set. For the moment this has been removed from the fasmg flags and whatever stack that is provided by MOS is used.

Note BSS is the heap - it used for memory allocated by malloc, etc. I don't what this should be set to, or can we just arbitrarily use memory. In the examples from the Zilog C-toolchain, `__low_bss`and `len_bss`are defined by

```
DEFINE __low_bss = base of BSS
DEFINE __len_bss = length of BSS
```

In the Release.linkcmd, but not given any actual numeric values.

### C-compiler runtime - crt0.src

This has been re-written based on a combination of code from the original [Agon projects]([GitHub - breakintoprogram/agon-projects: Official AGON QUARK Firmware: Projects](https://github.com/breakintoprogram/agon-projects)) which used the Zilog toolchain, and the CE Toolkit version. Note that the Zilog assembler, fasmg assembler used by CE toolkit and ez80asm used by many in the Agon community all have different formats and different waves of organising program sections, etc. Part of the challenge of this proof of concept has been in understanding the fasmg assembler.

## Libraries

Contains mainly eZ80 ADL assembly (.src) files.

Items mentioned have been checked - see details. Others have not been checked.

- Public functions are part of the externally available library

- Weak functions are internal to the library

### CE (TI 84 plus CE specific stuff)

### CRT (C-runtime)

- crt0 (public): updated to target Agon - sufficient for the proof of concept, will likely need to be developed further to support the full library and C++. 

- inchar.src (weak): updated to input from MOS rst 008h GETKEY command

### Libc (standard C-library)

- outchar.src (weak): updated to output to VDP by MOS rst 010h

- putchar.src (public): okay. Calls outchar (which needs to be modified)

- getchar.src (public): updated to remove bug now typecasts from unsigned char to int (the CE version typecasts from signed char - which is contrary to the C-standard) . Call inchar to get character and outchar to echo on consolse

### Libcxx (standard C++ library)

### Libload (dynamic library - I think)

Contains .lib library files - needs to be investigated further

## 

Annotated log of the build process for the "Hello, world" example from CEdev before any changes:

```
Generated by
============

    make -n                                Don't actually run any commands; just print them (30/05/2023)


mkdir -p 'obj/src'

Compilation
===========

echo [compiling] src/main.c

/Users/pcawte/CEdev/bin/ez80-clang -MD -c -emit-llvm -nostdinc -isystem /Users/pcawte/CEdev/include -Isrc -fno-threadsafe-statics -Xclang -fforce-mangle-main-argc-argv -mllvm -profile-guided-section-prefix=false -DNDEBUG  -g0 -Wall -Wextra -Oz 'src/main.c' -o 'obj/src/main.c.bc'

Using eZ80 version of clang:
-MD                                        write a depfile containing user and system headers
-c                                        only run preprocess, compile and assemble steps
-emit-llvm                                use LLVM representation for assembler and object files
-nostdinc                                disable standard include directories
-isystem <path>                            add <path> th SYSTEM include search path
-Isrc                                    add src directory to the to the end of the list of include search paths
-fno-threadsafe-statics                    Do not emit code to make initialization of local statics thread safe
-Xclang                                    Pass <arg> to the clang compiler
  -fforce-mangle-main-argc-argv                Can't find proper docs - but something to do with mangling the name of __main                                               to __main_argcv_argv
-mllvm                                    Additional arguments to forward to LLVM's option processing
  -profile-guided-section-prefix=false        seems to be related to optimisation (but haven't found proper documentation)
-DNDEBUG                                Define macro NDEBUG to be equal to 1
-g0                                        Don't generate any debug into (default)
-Wall                                    Enable all warnings
-Wextra                                    Enable extra warnings
-Oz                                        Controls optimisation:
                                            -Oz is based on -Os, but drops: -slp-vectorizer
                                            -Os is similar to -O2, but drops: -libcalls-shrinkwrap and -pgo-memopt-opt
                                            See documentation for -O2 which is based on -O1 (also see documentation)
'src/main.c'                            source file to be compiled
-o 'obj/src/main.c.bc'                    write output to file - the format is a hex dump


Files generated:
  obj/src/main.c.bc                     output file (see above) - LLVM bitcode format
  obj/src/main.c.d                         dependencies list for main.c.bc: 
                                              source file (main.c)
                                              various include (.h) files

LLVM bit code
-------------

Can use llvm-bcanlayzer to dump a the bitcode in human readable format (see main.c.bc.dmp which I have generated)
- but still is not intelligable


LLVM bitcode linking
====================

echo [lto opt] obj/lto.bc

/Users/pcawte/CEdev/bin/ez80-link '/Users/pcawte/CEdev/examples/hello_world/obj/src/main.c.bc' -o '/Users/pcawte/CEdev/examples/hello_world/obj/lto.bc'

Output when run with -v option (verbose)
  Loading '/Users/pcawte/CEdev/examples/hello_world/obj/src/main.c.bc'
  Linking in '/Users/pcawte/CEdev/examples/hello_world/obj/src/main.c.bc'
  Writing bitcode...

Use -d option to get human-readable version of the output bitcode file (see lto.log)

Files genereated:
  obj/lto.bc                             LLVM bitcode format


Generating eZ80 assembly language
=================================

/Users/pcawte/CEdev/bin/ez80-clang -S -mllvm -profile-guided-section-prefix=false -Wall -Wextra -Oz '/Users/pcawte/CEdev/examples/hello_world/obj/lto.bc' -o '/Users/pcawte/CEdev/examples/hello_world/obj/lto.src'

Using eZ80 version of clang:
-S                                         Only run preprocess and compilations steps
obj/lto.bc                                 source file to be compiled
-o obj/lto.src                             output file (eZ80 assembly language)

Files genereated:
  obj/lto.src                             eZ80 assembly language


Converting icon to assembly
===========================

mkdir -p 'obj'

echo [convimg] icon.png

/Users/pcawte/CEdev/bin/convimg --icon 'icon.png' --icon-output 'obj/icon.src' --icon-format asm --icon-description "CE C Toolchain Demo"

Files generated:
  obj/icon.src                             assembly language data for icon

Assembling and linking
======================

mkdir -p 'bin'

echo [linking] bin/DEMO.bin

/Users/pcawte/CEdev/bin/fasmg -n '/Users/pcawte/CEdev/meta/ld.alm' -i 'DEBUG := 0' -i 'HAS_PRINTF := 1' -i 'HAS_LIBC := 1' -i 'HAS_LIBCXX := 1' -i 'PREFER_OS_CRT := 0' -i 'PREFER_OS_LIBC := 1' -i 'include "/Users/pcawte/CEdev/meta/linker_script"' -i 'range .bss $D052C6 : $D13FD8' -i 'provide __stack = $D1A87E' -i 'locate .header at $D1A87F' -i map -i 'source "obj/icon.src", "/Users/pcawte/CEdev/lib/crt/crt0.src", "obj/lto.src"' -i 'library "/Users/pcawte/CEdev/lib/libload/fatdrvce.lib", "/Users/pcawte/CEdev/lib/libload/fileioc.lib", "/Users/pcawte/CEdev/lib/libload/fontlibc.lib", "/Users/pcawte/CEdev/lib/libload/graphx.lib", "/Users/pcawte/CEdev/lib/libload/keypadc.lib", "/Users/pcawte/CEdev/lib/libload/msddrvce.lib", "/Users/pcawte/CEdev/lib/libload/srldrvce.lib", "/Users/pcawte/CEdev/lib/libload/usbdrvce.lib"'  bin/DEMO.bin

Using flat assembler (fasmg):
-n                                        Do not show logo nor summary

'/Users/pcawte/CEdev/meta/ld.alm'        Some sort of control / config file, which includes the following files:-
                                            commands.alm
                                            ez80.alm

-i 'DEBUG := 0'                            -i flag inserts instructions at the beginning of the source file
-i 'HAS_PRINTF := 1'
-i 'HAS_LIBC := 1'
-i 'HAS_LIBCXX := 1'
-i 'PREFER_OS_CRT := 0'
-i 'PREFER_OS_LIBC := 1'
-i 'include "/Users/pcawte/CEdev/meta/linker_script"'

                                        includes library directive (never optional) for
                                            ../lib/libload.lib (only 22 bytes long)
                                        includes source directive for many library source files under
                                            ../lib/crt
                                            ../lib/ce
                                            ../lib/libc    (if HAS_LIBC)
                                            ../lib/libcxx  (if HAS_LIBCXX)

-i 'range .bss $D052C6 : $D13FD8'        bss - portion of the object file containing statically allocated variables
-i 'provide __stack = $D1A87E'
-i 'locate .header at $D1A87F'
-i map

-i 'source     "obj/icon.src",                assembler source for icon
            "/Users/pcawte/CEdev/lib/crt/crt0.src",
                                        c startup routines (compiler-run-time)
                                        - calls _main (or __main_argc_argv) after some CE specific initialisation
                                        - there is also a fair amount of CE specific clean-up code
                                        - this will need to be modified for a different target, e.g, Agon

            "obj/lto.src"'                assembly language for main.c

-i 'library "/Users/pcawte/CEdev/lib/libload/fatdrvce.lib",
            "/Users/pcawte/CEdev/lib/libload/fileioc.lib",
            "/Users/pcawte/CEdev/lib/libload/fontlibc.lib",
            "/Users/pcawte/CEdev/lib/libload/graphx.lib",
            "/Users/pcawte/CEdev/lib/libload/keypadc.lib",
            "/Users/pcawte/CEdev/lib/libload/msddrvce.lib",
            "/Users/pcawte/CEdev/lib/libload/srldrvce.lib",
            "/Users/pcawte/CEdev/lib/libload/usbdrvce.lib"'

bin/DEMO.bin                             Output file


Files generated:
  DEMO.bin
  DMEO.map

The map files provides information on where things are located:

Section          Base   Top    High   Length
---------------- ------ ------ ------ -------
.icon            D1A882 D1A99D           11Bh         following .header section
.init.libs       D1A99D D1A99D             0h         following .init.libs (zero length)
.libs            D1A99D D1A99D             0h         as above
.init.clock      D1A99D D1A99D             0h         as above
.init.reruncheck D1A99D D1A99D             0h         as above
.init            D1A99D D1A9BD            20h         following .init.reruncheck
.fini            D1A9BD D1A9F1            34h         following .init
.text            D1A9F1 D1AA3B            4Ah        following .fini
.data            D1AA3B D1AA3B             0h
.rodata          D1AA3B D1AA49             Eh
.init_array      000000 000000             0h
.ctors           000000 000000             0h
.dtors           000000 000000             0h
.fini_array      000000 000000             0h
.bss             D052C6 D052C6 D13FD8      0h         location as defined above in command line
.header          D1A87F D1A882             3h         location as defined above in command line

Label                       Value
-------------------------   ------
___low_bss                = D052C6
___len_bss                = 000000
___heaptop                = D13FD8
___heapbot                = D052C6
___libs                   = D1A99D
___init_array_count       = 000000
___ctors_count            = 000000
___dtors_count            = 000000
___fini_array_count       = 000000
__stack                   = D1A87E                    location as defined above in commands
_os_DisableHomeTextBuffer = D1A9F1
_os_EnableHomeTextBuffer  = D1AA03
_os_ClrLCD                = 02080C
_os_HomeUp                = 020828
_os_DrawStatusBar         = 021A3C
_os_PutStrFull            = 021D2C
_os_GetCSC                = 021D3C
__start                   = D1A99D                     entry point to programme, start of .init section
___exithl                 = D1A9BD
skip._exit                = D1A9BD
skip.__Exit               = D1A9BD
skip._abort               = D1A9BD
_exit.sp                  = D1A9BE
_exit.flash_wait_states   = D1A9C8
_main                     = D1AA15
_.str                     = D1AA3B


Hexdump of the bin file (xxd DEMO.bin) mixed with code from crt0.src verified by comparing with disassembled code
00000000: ef7b 00
                 c3 9da9 d101 1010 ffff ffff feb5  .{..............

    section    .header
    db    $EF, $7B
    db    $00        ; C program identifier (nop)

00000010: b5b6 b6b5 b5fe ffff ffff ffff ffb5 fedf  ................
00000020: 9676 7696 dffe b5ff ffff ffff b5df 560e  .vv...........V.
00000030: 0d0d 0d0d 0e4e dfb5 ffff ffb5 df2e 0d0d  .....N..........
00000040: 0d0d 0d0d 0d0d 2edf b5ff fefe 560d 0d05  ............V...
00000050: 0505 0505 050d 0d4e fefe b5df 0d05 4db6  .......N......M.
00000060: df96 4dd6 d6b6 050d d6b5 b596 052d ffdf  ..M..........-..
00000070: 7696 4dff 966e 0505 76b5 b64e 0576 ff0d  v.M..n..v..N.v..
00000080: 0505 4dff b676 0505 4db6 b64e 0576 ff05  ..M..v..M..N.v..
00000090: 2424 4dff b676 0505 4db6 b576 052d ffd6  $$M..v..M..v.-..
000000a0: 7576 4dff 764d 0505 6db5 b5bf 0505 4dde  uvM.vM..m.....M.
000000b0: ff96 2ddf dfb7 0505 b6b5 fefe 6d05 2404  ..-.........m.$.
000000c0: 0404 0404 2405 052d defe ffb5 df2d 2404  ....$..-.....-$.
000000d0: 0404 0404 2405 0dd6 b5ff ffff b5df 4d24  ....$.........M$
000000e0: 0404 0424 242d b6b5 ffff ffff ffb5 feb6  ...$$-..........
000000f0: 6d2d 2d4d 96de b5ff ffff ffff ffff feb5  m--M............
00000100: b5b6 b6b5 b5fe ffff ffff 4345 2043 2054  ..........CE C T
00000110: 6f6f 6c63 6861 696e 2044 656d 6f00       oolchain Demo.

                                             cd48                .H         .init at offset 0x11E
00000120: 0802 cdf4 0400 f3cd f1a9 d121 0503 e07e  ...........!...~
00000130: 32c8 a9d1 74ed 73be a9d1 cd15 aad1       2...t.s.....

    section    .init                                                             matches disassembled code
    weak    __start
__start:
    call    0020848h                    ; _RunInicOff, assumes iy = flags
    call    00004F4h                    ; _usb_DisableTimer
    di                                    ; disable interrupts
    call    _os_DisableHomeTextBuffer
    ld    hl,0E00305h
    ld    a,(hl)
    ld    (_exit.flash_wait_states),a
    ld    (hl),h                            ; set flash wait states to 3; 1 was definitely
                                        ; too low, 2 is untested
    ld    (_exit.sp),sp                    ; save sp for exiting                                 

if defined ___main_argc_argv                                                Not defined

    ... <code deleted for clarity> ...

end if

if ___len_bss > 0                                                             len_bss = 0

    ... <code deleted for clarity> ...

end if

.init_count := ___init_array_count + ___ctors_count                         will be zero
if .init_count <= 21

    ... <code deleted for clarity> ...

end if


ifextern ___main_argc_argv                                                    Not defined 
    call    ___main_argc_argv
else
    call    _main                                                             00013A: CD15AAD1  call label_D1AA15
end if
    public    __start._main
__start._main := $ - 3
    require    ___exithl

                                             3100              ..1.
00000140: 0000 e5fd 2180 00d0 3e00 3205 03e0 cdf0  ....!...>.2.....
00000150: 0400 cd03 aad1 3e01 3208 00f0 fdcb 09a6  ......>.2.......
00000160: fdcb 03c6 cd08 0802 cd28 0802 cd3c 1a02  .........(...<..
00000170: e1c9                                     ..

.fini            D1A9BD D1A9F1            34h
___exithl                 = D1A9BD
skip._exit                = D1A9BD
skip.__Exit               = D1A9BD
skip._abort               = D1A9BD
_exit.sp                  = D1A9BE                    location where stack point has been saved - self modifying
_exit.flash_wait_states   = D1A9C8


None of the following is assembled / included

    section    .fini
    public    ___exithl
___exithl:

    ... <code deleted for clarity> ...

Included from below

    section    .fini
    private    skip._abort
skip._abort:
    ld    sp,0
    public    _exit.sp
_exit.sp := $-3                                             located of the 0 above for self modifying code to save SP
    push    hl
    ld    iy,0D00080h
    ld    a,0

    private    _exit.flash_wait_states
_exit.flash_wait_states := $-1
    ld    (0E00305h),a
    call    00004F0h    ; _usb_ResetTimer
    call    _os_EnableHomeTextBuffer
    ld    a,1
    ld    (0F00008h),a    ; clear on interrupt
    res    4,(iy+9)    ; onInterrupt,(iy+onFlags)
    set    0,(iy+3)    ; graphDraw,(iy+graphFlags)
    call    020808h        ; _ClrLCDFull
    call    020828h        ; _HomeUp
    call    021A3Ch        ; _DrawStatusBar
    pop    hl        ; hl = exit code
    ret

               fd21 8000 d0fd cb0d 8efd cb4a 9efd    .!.........J..         .text segment at offset 0x172
00000180: cb4c eec9 

_os_DisableHomeTextBuffer = D1A9F1
    000172: FD218000D0    ld        iy, D00080                                included from a library
    000177: FDCB0D8E      res       1, (iy + 0D)
    00017B: FDCB4A9E      res       3, (iy + 4A)
    00017F: FDCB4CEE      set       5, (iy + 4C)
    000183: C9            ret

                    fd21 8000 d0fd cb0d cefd cb4a  .L...!.........J
00000190: 9efd cb4c aec9

_os_EnableHomeTextBuffer  = D1AA03
    000184: FD218000D0    ld        iy, D00080                                included from a library
    000189: FDCB0DCE      set       1, (iy + 0D)
    00018D: FDCB4A9E      res       3, (iy + 4A)
    000191: FDCB4CAE      res       5, (iy + 4C)
    000195: C9            ret


                         fd21 8000 d0cd 0c08 02cd  ...L...!........
000001a0: 2808 02cd 3c1a 0221 3baa d1e5 cd2c 1d02  (...<..!;....,..
000001b0: e1cd 3c1d 02b7 28f9 b7ed 62c9            ..<...(...b.

_main                     = D1AA15                                            info from map file
    public    _main                                                             from lto.src (compiled from main.c)
_main:
    ld    iy, 0D00080h
    call    _os_ClrLCD
    call    _os_HomeUp
    call    _os_DrawStatusBar
    ld    hl, _.str
    push    hl
    call    _os_PutStrFull
    pop    hl
BB0_1:
    call    _os_GetCSC
    or    a, a
    jr    z, BB0_1
    or    a, a
    sbc    hl, hl
    ret

                                        4865 6c6c              Hell
000001c0: 6f2c 2057 6f72 6c64 2e00                 o, World..

    section    .rodata,"a",@progbits
    private    _.str
_.str:
    db    "Hello, World.", 0


Convert to 8xp for transfer to TI-84
==============

mkdir -p 'bin'

/Users/pcawte/CEdev/bin/convbin -r -k 8xp -u -b '2023-05-30T11:05:34+0700 v11.1' -n DEMO -i 'bin/DEMO.bin' -o 'bin/DEMO.8xp'


Notes on address space breakdown
================================

See https://ce-programming.github.io/toolchain/static/faq.html

2 blocks

Block 1 (65535 bytes long)
 .rodata (read-only /constant data)
 .data (data)
 .text (code)
 stack (4k long out of the above)
Up to address 0xD1987E

Block 2 (60989 bytes long)
 heap
 .bss (bss - statically allocated data)
Up to address 0xD052C6

Not sure that these addresses match the directives above

Dynamic Libraries
=================

On the CE, the libraries are delivered as AppVars and reside in the calculator's archive, and are dynamically linked at runtime by the LibLoad library.
```
