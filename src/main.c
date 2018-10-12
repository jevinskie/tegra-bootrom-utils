#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#include "usb.h"

static const char hello[] = "hello, world";

typedef void (*NvOsWaitUS_t)(int us);

void NvOsWaitUS(int us) {
	((NvOsWaitUS_t)(0xFFF00B9A + 1))(us);
}

int main(void) {
	int ret = usb_send(hello, sizeof(hello));
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 100; ++j) {
			NvOsWaitUS(1000);
		}
		usb_send(hello, sizeof(hello));
	}
	puts("o hai");
	fflush(stdout);
	assert(0xDEADBEEF == 0xBAADF00D);
	// assert(!ret);
	return 0;
}
