#include "pmc.h"

    .section ".text"

    .code 32
    .globl _start_arm_mode
    .type _start_arm_mode, %function
_start_arm_mode:
    ldr r0, =_start
    bx r0

    .code 16
    .globl _start
    .type _start, %function
_start:
    ldr r0, =__bss_start
    mov r1, #0
    ldr r2, =__bss_end
    sub r2, r0, r0
    bl memset
    bl main
    ldr r1, =PMC(PMC_SCRATCH0)
    str r0, [r1, #4]
    mov r2, #(1 << 1)
    str r2, [r1]
    ldr r1, =PMC(0)
    mov r2, #(1 << 4)
    str r2, [r1]
L_spin_wait_for_reset:
    b L_spin_wait_for_reset
