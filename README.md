# arm-os-101
This is a minimal OS running on stm32f103.

## build
First, install the GNU toolchains for Arm:
```
sudo apt install gcc-arm-none-eabi
```
Then, install the stlink tools:
```
git clone https://github.com/stlink-org/stlink
cd stlink
sudo apt-get install -y cmake libusb-1.0-0-dev
sudo apt-get -y install cmake
sudo apt-get install libstlink1
make
cd build/Release
sudo make install
```
Build the kernel with make:
```
make
```
Last, flash the kernel to the board with stlink (you must connect it to the board first):
```
make flash
```

## QEMU simulation
First, you should compile a [qemu_stm32](https://github.com/beckus/qemu_stm32) yourself since the main branch of qemu doesn't support stm32f103. Notice that you should have the python2 environment.
```
sudo apt install device-tree-compiler libfdt-dev
git clone git://github.com/beckus/qemu_stm32.git
cd qemu-stm32
./configure --enable-debug --disable-werror --target-list="arm-softmmu"
make -j`nproc`
```
Second, specify the path of `arm-softmmu/qemu-system-arm` in the Makefile.

Third, use the following command to start the simulation:
```
make qemu
```
## How to play
First of all, you have to have a stm32f103 board and a usb-to-serial module.

Second, build and flash the kernel with above steps.

Third, connect the USART1 of stm32f103 to usb-to-serial module. More specifically, connect the PA9 of stm32 to RXD, connect the PA10 of stm32 to TXD, and connect the GND to GND.

Fourth, set the boot mode to 00.

Fifth, use some tool, for example, minicom to communicate with the board (with the baud rate 9600):
```
sudo minicom -D /dev/ttyUSB0 -b 9600
```
It will not be necessarily `/dev/ttyUSB0`, you can use `dmesg` to check it when you plug in the usb module.

Last but not least, press the reset button and have fun!
