#include <stddef.h>
#include <string.h>

#include "usb.h"

// __attribute__((aligned(0x100)))
static const char hello[] = "hello, world";

extern void say_hello(void);

extern const char *hello_str;

int main(void) {
	// memcpy((void *)0x40003000, hello, sizeof(hello));
	// usb_send((void *)0x40003000, sizeof(hello));
	usb_send(&hello_str, sizeof(hello));
	// say_hello();
	return 0;
}
