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
