ENTRY(boot)

SECTIONS {
    . = 0x80200000;
    /* 程序*/
    .text :{
        KEEP(*(.text.boot));
        *(.text .text.*);
    }
    /* 只读常量*/
    .rodata : ALIGN(4) {
        *(.rodata .rodata.*);
    }
    /*可读可写数据*/
    .data : ALIGN(4) {
        *(.data .data.*);
    }
    /*初始值为0的可读写数据*/
    .bss : ALIGN(4) {
        __bss = .;
        *(.bss .bss.* .sbss .sbss.*);
        __bss_end = .;
    }

    . = ALIGN(4);
    . += 128 * 1024; /* 128KB */
    __stack_top = .;
}