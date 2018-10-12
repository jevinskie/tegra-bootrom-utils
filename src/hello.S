#define write_ep1_in_sync (0xFFF05092 + 1)

    .section ".text"
    .code 32
    .globl say_hello
    .type say_hello, %function
say_hello:
    push {lr}
    ldr r0, =hello_str
    mov r1, #hello_str_len
    sub r2, sp, #4
    sub sp, sp, #4
    ldr ip, =write_ep1_in_sync
    mov lr, pc
    bx ip
    # blx ip
    add sp, sp, #4
    pop {r1}
    bx r1

    .globl  hello_str
    .type   hello_str, %object
    .size   hello_str, Lhello_str_end - hello_str
    .align 4
hello_str:
    .asciz "hello, world"
Lhello_str_end:
    .equ    hello_str_len, . - hello_str
