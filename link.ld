MEMORY {
    ROM (rx) : ORIGIN = 0x0000, LENGTH = 16K
    RAM (rw) : ORIGIN = 0x4000, LENGTH = 16K
}

SECTIONS
{
    .text : {
        *(.text)
        *(_CODE)
    } > ROM

    .data : {
        __data_start__ = .;
        *(.data)
        __data_end__ = .;
        __data_load__ = LOADADDR(.data);
    } > RAM AT > ROM

    .bss : {
        *(.bss)
    } > RAM
}
