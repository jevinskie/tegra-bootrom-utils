#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "usb.h"

static const char hello[] = "hello, world";

int main(void) {
	usb_send(hello, sizeof(hello));
	return 0;
}
