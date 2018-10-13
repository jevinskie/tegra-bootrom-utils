#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#include "pmc.h"
#include "usb.h"

static const char hello[] = "hello, world";

typedef void (*NvOsWaitUS_t)(int us);

void NvOsWaitUS(int us) {
	((NvOsWaitUS_t)(0xFFF00B9A + 1))(us);
}

__attribute__((used))
int main(void) {
	printf("PMC_SCRATCH0: 0x%08x\n", PMC(PMC_SCRATCH0));
	printf("PMC_SCRATCH1: 0x%08x\n", PMC(PMC_SCRATCH1));
	fflush(stdout);
	usb_send(hello, sizeof(hello));
	puts("o hai");
	fflush(stdout);
	assert(0xDEADBEEF == 0xBAADF00D);
	// assert(!ret);
	return 0;
}
