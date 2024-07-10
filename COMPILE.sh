# AgDev - compile instructions

A script ```compile.sh``` can be used to compile this source tree, however it depends on 2 things:

1. The original CEdev tar file which includes the ez80 compiler. You can get it from https://github.com/CE-Programming/toolchain/releases/latest/download/CEdev-Linux.tar.gz
2. This is a linux compile script so won\'t work with windows or macos. 

Choose a place to build the compiled library and set BASEDIR to that in `compile.sh`
I recommend this is a new directory, the script should create it if it doesn\'t exist.

After the code is compiled, move the CEdev directory to wherever you desire and add the CEdev/bin directory to your path.

