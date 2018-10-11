#include <stddef.h>

#include "usb.h"

static const char hello[] = "hello, world\n";

extern void say_hello(void);

int main(void) {
	// usb_send(hello, sizeof(hello));
	say_hello();
	return 0;
}
