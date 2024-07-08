set -ex
rm -rf test && mkdir test && cd test
git clone https://github.com/astralaster/Agon-Raytracer.git --depth 1 && cd Agon-Raytracer
make
cd ..
git clone https://github.com/envenomator/agon-ez80asm.git --depth 1 && cd agon-ez80asm
make -f Makefile-agon
cd ..
git clone https://github.com/BlastBrothers/agon-mega-io.git --depth 1 && cd agon-mega-io
make
cd ..
git clone https://github.com/lennart-benschop/agon-utilities.git --depth 1 && cd agon-utilities/mc
make
cd ../..
echo "All tests done."