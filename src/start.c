#include <string.h>
#include <unistd.h>

#include "pmc.h"

extern uintptr_t __bss_start, __bss_end;

extern int main(void);

extern uintptr_t __syscalls[];

extern void ___exit(int ret);
void _start(void);

__attribute__((target("arm"), noreturn, section(".text_entry")))
void _start_arm_mode(void) {
	_start();
}

__attribute__((noreturn))
void _start(void) {
	memset((void *)__bss_start, 0, (size_t)(__bss_end - __bss_start));
	__syscalls[1] = (uintptr_t)___exit;
	int res = main();
	_exit(res);
}
