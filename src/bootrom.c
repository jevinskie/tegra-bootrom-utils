#include "bootrom.h"

typedef void (*wait_us_t)(unsigned int us);

void wait_us(unsigned int us) {
	((wait_us_t)(0xFFF00B9A + 1))(us);
}

typedef int (*usb_send_w_ret_len_t)(const void *buf, size_t size, size_t *size_sent);
typedef int (*usb_recv_w_ret_len_t)(void *buf, size_t size, size_t *size_recv);

int usb_send_w_ret_len(const void *buf, size_t size, size_t *size_sent) {
	return ((usb_send_w_ret_len_t)(0xFFF05092 + 1))(buf, size, size_sent);
}

int usb_recv_w_ret_len(void *buf, size_t size, size_t *size_recv) {
	return ((usb_recv_w_ret_len_t)(0xFFF050DE + 1))(buf, size, size_recv);
}

typedef int (*usb_send_start_t)(const void *buf, size_t size);
typedef int (*usb_recv_start_t)(void *buf, size_t size);

int usb_send_start(const void *buf, size_t size) {
	return ((usb_send_start_t)(0xFFF051A0 + 1))(buf, size);
}

int usb_recv_start(void *buf, size_t size) {
	return ((usb_recv_start_t)(0xFFF051EA + 1))(buf, size);
}

typedef int (*usb_clear_endpoint_t)(const void *usb_ctx, int usb_ep);

int usb_clear_endpoint(const void *usb_ctx, int usb_ep) {
	return ((usb_clear_endpoint_t)(0xFFF047E4 + 1))(usb_ctx, usb_ep);
}

typedef int (*usb_get_ep_status_t)(int usb_ep);

int usb_get_ep_status(int usb_ep) {
	return ((usb_get_ep_status_t)(0xFFF05154 + 1))(usb_ep);
}
