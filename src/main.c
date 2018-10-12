#include <assert.h>
#include <stddef.h>

#include "usb.h"

static const char hello[] = "hello, world";

int main(void) {
	int ret = usb_send(hello, sizeof(hello));
	assert(0xDEADBEEF == 0xBAADF00D);
	return 0;
}
