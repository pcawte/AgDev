### Floating point divide test

Just floating point divide and then return result cast to int - this works okay

When include printf("%f", f) crashes (at least in the emulator)

From printf.src

```
assume    adl=1

    section    .text
    public    _sprintf

if HAS_PRINTF

    public    _printf
    public    _vprintf
    public    _vsprintf
    public    _snprintf
    public    _vsnprintf

_printf := __printf_c
_vprintf := __vprintf_c
_vsprintf := __vsprintf_c
_snprintf := __snprintf_c
_vsnprintf := __vsnprintf_c
_sprintf := __sprintf_c

    extern    __printf_c
    extern    __vprintf_c
    extern    __vsprintf_c
    extern    __snprintf_c
    extern    __vsnprintf_c
    extern    __sprintf_c

else

_sprintf := 0000BCh

end if
```

If HAS_PRINTF is not set (it is) in the makefile then uses OS version of printf.

However, in this case uses __printf__c - not sure where this is located it is not in the lib directories. It is listed in the map file.

In the map file, there are a number of labels that point to the CE OS.

```
__fcmp                 = 000274
__ftol                 = 00027C
__ftoul                = 00027C
__ltof                 = 000284
__setflag              = 000218
__ultof                = 000280
```

Suggests that these are the problems. These are defined in os.src

ftol, ftoul, ltof, ultof are called in operations.ll as part of the LLVM eZ80 code generation.

I haven't found __fcmp or __setflag

There are also some similar things defined in intrinisics.II - but these have assembler versions in the CE Toolchain distribution. Trying to define find where these come from. The file Z80ISelLowering.cpp lists the calling convention for each of these functions (_fcmp and _setflag are mentioned in here). This is under llvm/test/CodeGen/Z80. There is also a Z80 folder llvm/lib/Target/Z80 and llvm/unittests/Target/Z80.

Seems like they should be contained somewhere in compiler-rt (https://github.com/jacobly0/llvm-project/pull/10)https://github.com/jacobly0/llvm-project/pull/10. Seems like they come from the Zilog toolchain

```
    assume    adl=1

    section    .text

    public    __fadd
__fadd      := 000270h
    public    __fcmp
__fcmp      := 000274h
    public    __fdiv
__fdiv      := 000278h
    public    __fmul
__fmul      := 000288h
    public    __fsub
__fsub      := 000290h
    public    __ftol
__ftol      := 00027Ch
    public    __ftoul
__ftoul     := __ftol
    public    __dtol
__dtol      := __ftol
    public    __dtoul
__dtoul     := __ftoul
    public    __imul_b
__imul_b    := 000150h
    public    __indcall
__indcall   := 00015Ch
    public    __ishl_b
__ishl_b    := 000178h
    public    __ishrs_b
__ishrs_b   := 000180h
    public    __ishru_b
__ishru_b   := 000188h
    public    __itol
__itol      := 000194h
    public    __ltof
__ltof      := 000284h
    public    __ltod
__ltod      := __ltof
    public    __setflag
__setflag   := 000218h
    public    __sshl_b
__sshl_b    := 000244h
    public    __sshrs_b
__sshrs_b   := 00024Ch
    public    __sshru_b
__sshru_b   := 000254h
    public    __stoi
__stoi      := 000260h
    public    __stoiu
__stoiu     := 000264h
    public    __ultof
__ultof     := 000280h
    public    __ultod
__ultod     := __ultof
```

Not sure why floating point division seems to be working, although __fdiv above points to OS

Notes from CE Toolchain documentation

> In the toolchain, `float` is the standard IEEE 32-bit float. However, IEEE floats have limited precision and have unintuitive rouding behavior. So when TI designed the TI-81, they wrote their own special floating-point number format, which is much more suitable for precision scientific calculations. Unfortunately, it also much slower.

This suggests that most floating point does not use the CE OS 

The include file ti/real.h includes header info for using the TI real number format
