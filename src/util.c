#include "util.h"

#include "bootrom.h"

void wait_ms(unsigned int ms) {
	for (unsigned int i = 0; i < ms; ++i) {
		wait_us(1000);
	}
}
