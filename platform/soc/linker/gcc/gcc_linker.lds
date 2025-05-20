#include "flash_linker_config.h"

#define APP_FLASH_END_ADDR (FLASH_START_ADDR + FLASH_SIZE)

#if BLE_SUPPORT
#define USABLE_RAM_SIZE (APP_RAM_SIZE - ROM_RTN_RAM_SIZE - BLE_EM_USED_SIZE)
#else
#define USABLE_RAM_SIZE (APP_RAM_SIZE - ROM_RTN_RAM_SIZE)
#endif // BLE_SUPPORT

MEMORY
{
    FLASH (rx) : ORIGIN = (APP_CODE_RUN_ADDR), LENGTH = (APP_FLASH_END_ADDR - APP_CODE_RUN_ADDR)
    RAM (rwx)  : ORIGIN = (RAM_START_ADDR + ROM_RTN_RAM_SIZE + HIGH_RAM_OFFSET), LENGTH = (USABLE_RAM_SIZE)
}

GROUP(libgcc.a libc.a libm.a libnosys.a)
ENTRY(Reset_Handler)

SECTIONS
{
    .text :
    {
        KEEP(*(.vectors))
        __Vectors_End = .;
        __Vectors_Size = __Vectors_End - __Vectors;
        __end__ = .;
        . = ALIGN(0x200);
        KEEP(*(.app_info));
        *( .text*)
        KEEP(*(.init))
        KEEP(*(.fini))
        *crtbegin.o(.ctors)
        *crtbegin?.o(.ctors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
        *(SORT(.ctors.*))
        *(.ctors)
        *crtbegin.o(.dtors)
        *crtbegin?.o(.dtors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
        *(SORT(.dtors.*))
        *(.dtors)
        *(.rodata*)
        KEEP(*(.eh_frame*))
    } > FLASH

    .ARM.extab :
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > FLASH

    __exidx_start = .;
    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > FLASH

    __exidx_end = .;
    __etext = .;

    .data : AT (__etext)
    {
        __data_start__ = .;
        *(vtable)
        *(.data*)
        *(.ramfunc)
        *(RAM_CODE)
        . = ALIGN(128);
        *(FPB*)
        . = ALIGN(4);
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE_HIDDEN (__preinit_array_end = .);
        . = ALIGN(4);
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE_HIDDEN (__init_array_end = .);
        . = ALIGN(4);
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE_HIDDEN (__fini_array_end = .);
        KEEP(*(.jcr*))
        . = ALIGN(4);
        __data_end__ = .;
    } > RAM

    .bss :
    {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .;
    } > RAM

    __HeapBase = STACK_END_ADDR - SYSTEM_HEAP_SIZE - SYSTEM_STACK_SIZE;
    end = __HeapBase;
    __StackTop = STACK_END_ADDR;
    __StackLimit = SYSTEM_STACK_SIZE;
    PROVIDE(__stack = __StackTop);
    ASSERT(__HeapBase >= __bss_end__, "region RAM overflowed with HEAP & STACK")

}
