CROSS_COMPILE ?= arm-linux-gnueabi-
.PHONY: all

BUILD_DIR = build

SRCS = src/kernel/boot.c src/kernel/main.c src/kernel/usart.c \
	   src/kernel/usb.c src/kernel/io.c src/kernel/mm.c

OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy

CFLAGS = -mcpu=cortex-m3 -mthumb -nostartfiles -g -nostdlib -ffreestanding
CFLAGS += -Iinclude

all: kernel.bin

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

kernel.out: $(OBJS) linker.ld
	$(LD) -T linker.ld -Map=main.map -o $@ $(OBJS)

kernel.bin: kernel.out
	$(OBJCOPY) -O binary $< $@

flash: kernel.bin
	st-flash --reset write $< 0x8000000

clean:
	rm -rf *.o *.out *.bin *.map build/*
