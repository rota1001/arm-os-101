#!/bin/sh

# Build python2
sudo apt install build-essential
wget https://www.python.org/ftp/python/2.7.18/Python-2.7.18.tgz
tar -zxvf Python-2.7.18.tgz
cd Python-2.7.18
./configure
make -j `nproc`
cd ..

# Build qemu
sudo apt install device-tree-compiler libfdt-dev
git clone https://github.com/beckus/qemu_stm32.git
cd qemu_stm32
./configure --enable-debug --disable-werror --target-list="arm-softmmu" --python=`pwd`/../Python-2.7.18/python
make -j `nproc`
