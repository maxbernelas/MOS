OUTPUT_FORMAT ("elf32-littlearm")

STACK_SIZE = 0x400;

MEMORY
{
    rom (rx) : ORIGIN = 0x00000000, LENGTH = 128K
    ram  (rwx) : ORIGIN = 0x20000000, LENGTH =  20K
}

__stack_base = ORIGIN(ram) + LENGTH(ram);
__stack_limit = __stack_base - STACK_SIZE;

SECTIONS
{
    .text :
    {
        . = 0x00000000;
        *(.interrupt_vectors)
        *(.text*)
        __text_end = .;
    } > rom

    .rodata :
    {
        . = ALIGN(4);
        __rodata_start = .;
        *(.rodata*)
        __rodata_end = .;
    } > rom

    . = ALIGN(4);
    .data : AT (__rodata_end)
    {
        __ram_data_start = .;
        *(.data*)
        __ram_data_end = .;
    } > ram

    .bss :
    {
        . = ALIGN(4);
        __bss_start = .;
        *(.bss*)
        *(COMMON)
        __bss_end = .;
    } > ram

    /* Nothing is put in this section, but it reserves space so that we get an
     * error if it doesn't fit into RAM
     */
    .stack :
    {
        . = ALIGN(4);
        . = . + STACK_SIZE;
        . = ALIGN(4);
    } > ram
}
