#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "usb.h"

// __attribute__((aligned(0x100)))
// __attribute__((used))
// static const char hello[] = "hello, world";

extern void say_hello(void);

extern const char hello_str[];

extern const char dummy[];

static void sink(const void *buf, size_t size) {
	size_t num_words = size / sizeof(uint32_t) + 1;
	volatile uint32_t dummy;
	for (size_t i = 0; i < num_words; ++i) {
		dummy = ((volatile uint32_t*)buf)[i];
	}
	(void)dummy;
}

int main(void) {
	usb_send(hello_str, 13);
	usb_send(&hello_str, 13);
	// sink(hello, sizeof(hello));
	// memcpy((void *)0x40003000, hello, sizeof(hello));
	// usb_send((void *)0x40003000, sizeof(hello));
	// usb_send(hello, sizeof(hello));
	// usb_send(&hello, sizeof(hello));
	// say_hello();
	// return (int)dummy + (int)hello;
	return (int)dummy;
}
