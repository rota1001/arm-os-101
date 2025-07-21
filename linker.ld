MEMORY {
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 128k
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 20k
}

SECTIONS {
    . = 0x0;
    .isr_vector : {
        KEEP(*(.isr_vector))
        KEEP(*(.reset))
    } > FLASH
    . = ALIGN(4);
    _text_lma = .;
    .text : AT (_text_lma) {
        _text = .;
        *(.text)
        *(.rodata)
        . = ALIGN(4);
        _etext = .;
    } > SRAM
    .data : AT (_text_lma + _etext - _text) {
        _data = .;
        *(.data)
        . = ALIGN(4);
        _edata = .;
    } > SRAM

    .bss (NOLOAD) : {
        _bss = .;
        *(.bss)
        . = ALIGN(4);
        _ebss = .;
    } > SRAM

    _estack = ORIGIN(SRAM) + LENGTH(SRAM);
}
