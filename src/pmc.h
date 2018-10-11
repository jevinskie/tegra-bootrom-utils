#ifndef __ASSEMBLER__
#include <stdint.h>
#endif

#define PMC_BASE 0x7000E400

#ifdef __ASSEMBLER__
#define _REG(base, off) ((base) + (off))
#else
#define _REG(base, off) *(volatile uint32_t *)((base) + (off))
#endif

#define PMC(off) _REG(PMC_BASE, off)

#define PMC_SCRATCH0 0x50
#define PMC_SCRATCH1 0x54
#define PMC_SECURE_SCRATCH5 0xc4
