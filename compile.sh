# Note: this script requires ez80-clang to be accessible in PATH
#
set -x
ORIGDIR=$PWD
BASEDIR=$PWD/_temp
GITHUB=$PWD/_temp/github
CEDEV_VER=v11.2
#
if [ ! -d $BASEDIR ]; then
    mkdir $BASEDIR;
fi
cd $BASEDIR
#
if [ ! -d $BASEDIR/CEdev_zip ]; then
        wget https://github.com/CE-Programming/toolchain/releases/download/$CEDEV_VER/CEdev-Linux.tar.gz
        tar -zxvf $BASEDIR/CEdev-Linux.tar.gz;
        find . -type d -exec chmod 755 {} \; # no clue why this is required.
        mv CEdev CEdev_zip;
fi
#
# Get AgDev code
cd $BASEDIR
mkdir $GITHUB
cd $GITHUB
#
if [ -d $GITHUB/AgDev_git ]; then
    rm -r -f $GITHUB/AgDev_git;
fi
mkdir $GITHUB/AgDev_git;
AGDEV_GIT=$GITHUB/AgDev_git
# was a local location for AgDev code passed to us?
if [ ! -z "$1" ]; then
    cd $GITHUB
    cp -r $1/* $AGDEV_GIT;
else
    cd $GITHUB
    git clone https://github.com/pcawte/AgDev.git  AgDev_git;
fi
#
# get CEdev code - using a recent stable release
cd $GITHUB
CEDEV_GIT=$GITHUB/CEdev_git
if [ ! -d $CEDEV_GIT ]; then
    mkdir $CEDEV_GIT;
    git clone https://github.com/CE-Programming/toolchain.git CEdev_git --branch $CEDEV_VER;
    cd $CEDEV_GIT;
    git switch -c tmp;
    git switch master;
    git merge tmp;
    git submodule update --init --recursive;
fi
#
# Duplicate CEdev repo - this will become the basis for the final build
if [ -d $BASEDIR/CEDEV_PLUS_AGDEV ]; then
    rm -r -f $BASEDIR/CEDEV_PLUS_AGDEV;
fi
mkdir $BASEDIR/CEDEV_PLUS_AGDEV
CEDEV_PLUS_AGDEV=$BASEDIR/CEDEV_PLUS_AGDEV
cp -r $CEDEV_GIT/. ./ $CEDEV_PLUS_AGDEV
#
# move some stuff around in src
# the /agon folder in AgDev is based on the /ce folder in CEdev, but with CE-specific stuff removed and Agon-specific stuff added
mkdir $CEDEV_PLUS_AGDEV/src/agon
cp -r $CEDEV_PLUS_AGDEV/src/ce/* $CEDEV_PLUS_AGDEV/src/agon/
mkdir $CEDEV_PLUS_AGDEV/src/agon/include
cp -r $CEDEV_PLUS_AGDEV/src/ce/include* $CEDEV_PLUS_AGDEV/src/agon/
cd $CEDEV_PLUS_AGDEV/src/agon
rm -f eval.src
rm -f getstringinput.src
rm -f gettokeninput.src
rm -f intce.src
rm -f tice.src
rm -f os_textbuffer.src
rm -f runprgm.src
#
# now that we've copied its contents, we don't need /ce anymore
rm -r -f $CEDEV_PLUS_AGDEV/src/ce
#
# delete CEdev allocator code, since AgDev uses its own
rm -r -f $CEDEV_PLUS_AGDEV/src/libc/allocator.src
rm -r -f $CEDEV_PLUS_AGDEV/src/libc/allocator_simple.src
rm -r -f $CEDEV_PLUS_AGDEV/src/libc/allocator_standard.c
#
# delete misc .c files which had handmade asm edits made for AgDev - we will copy over these prebuilt .src files in the next step
rm -r -f $CEDEV_PLUS_AGDEV/src/libc/time.c
rm -r -f $CEDEV_PLUS_AGDEV/src/libc/strftime.c
#
# copy over AgDev source files and build instructions
cp -r $AGDEV_GIT/makefile $CEDEV_PLUS_AGDEV
cp -r $AGDEV_GIT/src/. $CEDEV_PLUS_AGDEV/src/
#
# vdp headers need to be in 2 places for some reason
cp -r $AGDEV_GIT/src/agon/include/agon $CEDEV_PLUS_AGDEV/src/include/
#
# Remove the previous build directory and make
cd $CEDEV_PLUS_AGDEV
if [ $CEDEV_PLUS_AGDEV/CEdev ]; then
    rm -r -f $CEDEV_PLUS_AGDEV/CEdev;
fi
mkdir $CEDEV_PLUS_AGDEV/CEdev
PATH=$PATH:$BASEDIR/CEdev_zip/bin
#
make V=1
make install V=1 DESTDIR=$CEDEV_PLUS_AGDEV/ --debug=j,m
#
# copy over .exe's from CEdev release - CEdev GitHub actions pull each .exe's repo and build, but we shouldn't need to do that.
mkdir $CEDEV_PLUS_AGDEV/CEdev/bin/
cp -r $BASEDIR/CEdev_zip/bin/. $CEDEV_PLUS_AGDEV/CEdev/bin/
#
# copy over AgDev example folder
mkdir $CEDEV_PLUS_AGDEV/CEdev/examples/
cp -r $AGDEV_GIT/examples/* $CEDEV_PLUS_AGDEV/CEdev/examples/
#
# copy resulting build to base directory
if [ -d  $ORIGDIR/AgDev_build/ ]; then
    rm -r -f  $ORIGDIR/AgDev_build/;
fi
mkdir $ORIGDIR/AgDev_build/
cp -r $CEDEV_PLUS_AGDEV/CEdev/* $ORIGDIR/AgDev_build/
#
# Set file permissions
chmod +x $ORIGDIR/AgDev_build/bin/*
#
# clean folders up at the end - TODO make optional
cd "$ORIGDIR"
rm -r -f "$BASEDIR"
#
exit
