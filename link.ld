MEMORY {
    ROM (rx) : ORIGIN = 0x0000, LENGTH = 16K
    RAM (rw) : ORIGIN = 0x4000, LENGTH = 16K
}

SECTIONS
{
    .text : {
        *(.text)
        *(_CODE)

        __drivers_start__ = .;
        *(.drivers)
        __drivers_end__ = .;

        __initializer_start__ = .;
        *(_INITIALIZER)
        __initializer_end__ = .;
    } > ROM

    .data : {
        __data_start__ = .;
        *(.data)
        __data_end__ = .;
        __data_load__ = LOADADDR(.data);

        __initialized_start__ = .;
        *(_INITIALIZED)
        __initialized_end__ = .;
    } > RAM AT > ROM

    .bss : {
        __bss_start__ = .;
        *(.bss)
        __bss_end__ = .;
    } > RAM
}
