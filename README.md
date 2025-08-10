# arm-os-101
This is a minimal multitasking OS running on stm32f103.

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
First, you should compile a [qemu_stm32](https://github.com/beckus/qemu_stm32) yourself since the main branch of qemu doesn't support stm32f103.

Don't worry, I have written a simple shell script to help you. You just have to execute the following command under the `arm-os-101` directory.
```
chmod +x qemu-build.sh
./qemu-build.sh
```
After doing this, you can simply use the following command to boot the OS:
```
make qemu
```
## How to play it on real board
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

## Features
- kernel and user process
- preemptive scheduler
- schedulable syscall function
## TODO
- filesystem
- interrupt for I/O event
- advanced schedule policy
- ...
