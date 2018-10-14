#include "bootrom.h"

typedef void (*NvOsWaitUS_t)(int us);

void NvOsWaitUS(int us) {
	((NvOsWaitUS_t)(0xFFF00B9A + 1))(us);
}

typedef int (*usb_send_bootrom_t)(const void *buf, size_t size, size_t *size_sent);
typedef int (*usb_recv_bootrom_t)(void *buf, size_t size, size_t *size_recv);

int usb_send_w_ret_len(const void *buf, size_t size, size_t *size_sent) {
	return ((usb_send_bootrom_t)(0xFFF05092 + 1))(buf, size, size_sent);
}

int usb_recv_w_ret_len(void *buf, size_t size, size_t *size_recv) {
	return ((usb_recv_bootrom_t)(0xFFF050DE + 1))(buf, size, size_recv);
}
