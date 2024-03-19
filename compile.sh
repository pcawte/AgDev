#!/bin/bash -x

# Working directory
BASEDIR=~/agon/compile

GITHUB=$BASEDIR/github
if [ ! -d "$BASEDIR" ]
then
       	mkdir $BASEDIR
fi
if [ ! -d "$GITHUB" ]
then
       	mkdir $GITHUB
fi

# tar file of the CE Toolchain
# Available from here https://github.com/CE-Programming/toolchain/releases/latest/download/CEdev-Linux.tar.gz
CEDEV_TAR=~/agon/CEdev-Linux.tar.gz

# this is where you checkout the Source Code of CEdev
# and you will compile it with the AgDev mods and your own
# customisations.
# See agdev_make.sh for a script to do this build
CEDEV_GIT=$GITHUB/CEdev

# this is where you want your working CEdev directory
# to be - this is where you will build and compile code
CEDEV_FINAL=$BASEDIR/CEdev


# before you start you must have the modified CEdev
# extracted and CEdev/bin in your path
# this is so it can find the ez80-clang compiler
cd $BASEDIR; tar xf $CEDEV_TAR ; PATH=$PATH:$BASEDIR/CEdev/bin

#----------------------------------------
# get latest AgDev code
# Only do this if you want AgDev updates
#----------------------------------------
cd $GITHUB
rm -rf $GITHUB/AgDev
git clone https://github.com/pcawte/AgDev.git

AGDEV_GIT=$BASEDIR/github/AgDev

#----------------------------------------
# get latest CEdev code
# Only do this if you want toolchain updates
#----------------------------------------
cd $GITHUB
rm -rf $GITHUB/CEdev
git clone https://github.com/CE-Programming/toolchain.git CEdev
cd CEdev
git submodule update --init --recursive

CEDEV_GIT=$GITHUB/CEdev

#----------------------------------------
# Copy in AgDev code to CEdev toolchain code
#----------------------------------------
cp -r $AGDEV_GIT/src/* $CEDEV_GIT/src/
cp -r $AGDEV_GIT/include/* $CEDEV_GIT/src/include

# Remove the previous build directory and make
cd $CEDEV_GIT
rm -rf CEdev
#make clean
make install

# will result in a install directory $CEDEV_GIT/CEdev/CEdev
# because of the strange way the AgDev common.mk file sets up the
# install directories

#----------------------------------------
# Install
#----------------------------------------

# delete previous CEdev final directory
rm -rf $CEDEV_FINAL

# Get the full version of CEdev from the TAR file
cd /tmp ; rm -rf CEdev
tar xf $CEDEV_TAR
mv CEdev $CEDEV_FINAL

# ... but now we can get our modified version which was created with agdev_make.sh
cp -rf $CEDEV_GIT/CEdev/CEdev $CEDEV_FINAL

# Copy over the AgDev stuff - this includes the ez80_clang compiler
# and example code
cp -rf $AGDEV_GIT/* $CEDEV_FINAL/

# now copy over the built binaries and libraries
cp $CEDEV_GIT/CEdev/CEdev/bin/* $CEDEV_FINAL/bin/
cp -r $CEDEV_GIT/CEdev/CEdev/lib/libc/vdp* $CEDEV_FINAL/lib/agon/
# finally copy the modified headers to the include directory
cp $CEDEV_FINAL/src/libc/include/vdp*h $CEDEV_FINAL/include/agon/

