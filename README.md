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
