.syntax unified
.cpu cortex-m3
.thumb

/* stack top comes from linker */
.word  0x20005000        /* initial SP */
.word  Reset_Handler     /* Reset */
.word  Default_Handler   /* NMI */
.word  Default_Handler   /* HardFault */

.text
.thumb_func
.global Reset_Handler
Reset_Handler:
    /* copy .data from flash to sram */
    ldr  r0, =_sdata
    ldr  r1, =_edata
    ldr  r2, =_sidata
1:  cmp  r0, r1
    bge  2f
    ldr  r3, [r2], #4
    str  r3, [r0], #4
    b    1b
2:
    /* zero .bss */
    ldr  r0, =_sbss
    ldr  r1, =_ebss
    mov  r2, #0
3:  cmp  r0, r1
    bge  4f
    str  r2, [r0], #4
    b    3b
4:
    bl   main
    b    .

.thumb_func
Default_Handler:
    b .