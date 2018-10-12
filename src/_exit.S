#include "pmc.h"

	.section ".text"

    .code 16
    .globl _exit
    .type _exit, %function
_exit:
    ldr r1, =PMC(PMC_SCRATCH0)
    str r0, [r1, #4]
    mov r2, #(1 << 1)
    str r2, [r1]
    ldr r1, =PMC(0)
    mov r2, #(1 << 4)
    str r2, [r1]
L_spin_wait_for_reset:
    b L_spin_wait_for_reset
