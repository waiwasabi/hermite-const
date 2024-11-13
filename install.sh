#!/bin/bash

cwd=$(pwd)

wget https://libntl.org/ntl-11.5.1.tar.gz
wget https://gmplib.org/download/gmp/gmp-6.0.0a.tar.xz
gunzip ntl-11.5.1.tar.gz
tar xf ntl-11.5.1.tar
tar xf gmp-6.0.0a.tar.xz

cd gmp-6.0.0
./configure --prefix=$cwd/sw
make
# make check
make install
cd $cwd

cd ntl-11.5.1/src
./configure PREFIX=$cwd/sw GMP_PREFIX=$cwd/sw
make
make check
make install
cd $cwd

rm -rf ntl-11.5.1
rm -rf gmp-6.0.0
rm ntl-11.5.1.tar
rm gmp-6.0.0a.tar.xz

wget https://github.com/waiwasabi/sphere-packing/archive/refs/tags/0.1.0.tar.gz
gunzip 0.1.0.tar.gz
tar xf 0.1.0.tar
rm 0.1.0.tar