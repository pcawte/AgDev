### Args Demo

Tests handling of argc and argv 

Relies on printf and putchar to stdout

To run on MOS with command line paramers:

```
*load args.bin
*run &040000 Hello world
```

Should output

```
Args example:
Arguements:
- argc: 3
- argv[0]: args.BIN
- argv[1]: Hello
- argv[2]: world
```

Can use command line processing option which supports quoting and input / output redirection, for this, the makefile should include

```
LDHAS_ARG_PROCESSING = 1
```

Example of quoting 

```
*load args.bin
*run &040000 "Hello, world!"
```

Should output

```
Args example:
Arguements:
- argc: 2
- argv[0]: args.BIN
- argv[1]: Hello, world!
```
