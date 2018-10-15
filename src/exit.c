#include <unistd.h>

#include "pmc.h"
#include "util.h"

__attribute__((noreturn))
void _exit(int status) {
	PMC(PMC_SCRATCH1) = status;
	PMC(PMC_SCRATCH0) = (1 << 1);

	wait_ms(1000);

	PMC(0) = (1 << 4);
	while (1);
}