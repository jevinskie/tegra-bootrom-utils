#include "usb.h"

typedef int (*usb_send_bootrom_t)(const void *buf, size_t size, size_t *size_sent);
typedef int (*usb_recv_bootrom_t)(void *buf, size_t size, size_t *size_recv);

#if 0
// __attribute__((target("arm")))
int usb_send_w_ret_len(const void *buf, size_t size, size_t *size_sent) {
	return ((usb_send_bootrom_t)(0xFFF05092 + 1))(buf, size, size_sent);
}

int usb_recv(void *buf, size_t size, size_t *size_recv) {
	return ((usb_recv_bootrom_t)(0xFFF050DE + 1))(buf, size, size_recv);
}
#else
#if 0
__attribute__((naked))
int usb_send_w_ret_len(const void *buf, size_t size, size_t *size_sent) {
	asm("push {lr}\n\t"
		"ldr r3, =(0xFFF05092 + 1)\n\t"
		"mov lr, pc\n\t"
		"bx r3\n\t"
		"pop {r1}\n\t"
		"bx r1\n\t");
}
#else
__attribute__((naked, target("arm")))
int usb_send_w_ret_len(const void *buf, size_t size, size_t *size_sent) {
	asm("push {lr}\n\t"
		"sub r2, sp, #4\n\t"
		"sub sp, sp, #4\n\t"
		"ldr ip, =(0xFFF05092 + 1)\n\t"
		"mov lr, pc\n\t"
		"bx ip\n\t"
		"add sp, sp, #4\n\t"
		"pop {r1}\n\t"
		"bx r1\n\t");
}
#endif

__attribute__((naked))
int usb_recv_w_ret_len(void *buf, size_t size, size_t *size_recv) {
	asm("push {lr}\n\t"
		"ldr r3, =(0xFFF050DE + 1)\n\t"
		"mov lr, pc\n\t"
		"bx r3\n\t"
		"pop {r1}\n\t"
		"bx r1\n\t");
}
#endif

#if 0
int usb_send(const void *buf, size_t size) {
	size_t dummy_ret_len;
	return usb_send_w_ret_len(buf, size, &dummy_ret_len);
}
#else
__attribute__((naked, target("arm")))
int usb_send(const void *buf, size_t size) {
	asm("push {lr}\n\t"
		"sub r2, sp, #4\n\t"
		"sub sp, sp, #4\n\t"
		"ldr ip, =(0xFFF05092 + 1)\n\t"
		"mov lr, pc\n\t"
		"bx ip\n\t"
		"add sp, sp, #4\n\t"
		"pop {r1}\n\t"
		"bx r1\n\t");
}
#endif
