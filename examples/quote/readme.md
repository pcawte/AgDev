### Quote input / output redirection demo

Echos the input to the output, with each line quoted (i.e. in double speech marks).

For input / output redirection to work, makefile should include

```
LDHAS_ARG_PROCESSING = 1
```

Example command lines

```
*load args.bin
*run &040000 <numbers.txt >>num_out.txt
```

Reads from the file numbers.txt and appends the quoted lines to the file num_out.txt.
