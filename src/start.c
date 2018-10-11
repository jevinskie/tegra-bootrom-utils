#include <stdint.h>
#include <string.h>

#include "pmc.h"

extern uintptr_t __bss_start, __bss_end;

extern int main(void);

__attribute__((target("arm"), naked, noreturn))
void _start_arm_mode(void) {
	asm("ldr r0, =_start\n\t"
		"bx r0\n\t");
}

__attribute__((noreturn))
void _start(void) {
	memset((void *)__bss_start, 0, (size_t)(__bss_end - __bss_start));
	int res = main();
	PMC(PMC_SCRATCH1) = res;
	PMC(PMC_SCRATCH0) = (1 << 4);
	while (1);
}
