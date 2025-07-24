CROSS_COMPILE ?= arm-linux-gnueabi-
.PHONY: all

BUILD_DIR = build

ARCH = STM32F103

SRCS = src/kernel/main.c src/kernel/io.c src/kernel/mm.c
SRCS += src/arch/$(ARCH)/usart.c src/arch/$(ARCH)/boot.c src/arch/$(ARCH)/usb.c src/arch/$(ARCH)/led.c

LINKER = src/arch/$(ARCH)/linker.ld

OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy

CFLAGS = -mcpu=cortex-m3 -mthumb -nostartfiles -g -nostdlib -ffreestanding
CFLAGS += -Iinclude
CFLAGS += -Iinclude/arch/$(ARCH)

all: kernel.bin

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

kernel.out: $(OBJS) $(LINKER)
	$(LD) -T $(LINKER) -Map=main.map -o $@ $(OBJS)

kernel.bin: kernel.out
	$(OBJCOPY) -O binary $< $@

flash: kernel.bin
	st-flash --reset write $< 0x8000000

clean:
	rm -rf *.o *.out *.bin *.map build/*
