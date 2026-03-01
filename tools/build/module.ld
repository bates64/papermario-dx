SECTIONS
{
    . = 0x80000000;

    .text : {
        __text_start = .;
        *(.text .text.*)
        *(.rodata .rodata.*)
        __text_end = .;
    }

    .ctors : {
        __CTOR_LIST__ = .;
        KEEP(*(.ctors))
        KEEP(*(.init_array))
        __CTOR_END__ = .;
    }

    .dtors : {
        __DTOR_LIST__ = .;
        KEEP(*(.dtors))
        KEEP(*(.fini_array))
        __DTOR_END__ = .;
    }

    .data : {
        __data_start = .;
        *(.data .data.*)
        *(.sdata .sdata.*)
        __data_end = .;
    }

    .bss (NOLOAD) : {
        __bss_start = .;
        *(.bss .bss.*)
        *(.sbss .sbss.*)
        *(COMMON)
        __bss_end = .;
    }

    __module_size = .;

    /DISCARD/ : {
        *(.MIPS.abiflags)
        *(.reginfo)
        *(.comment)
        *(.note.*)
        *(.pdr)
        *(.gnu.attributes)
        *(.eh_frame)
        *(.eh_frame_hdr)
    }
}
