#include "usb.h"

#include "bootrom.h"

usb_buf_t *usb_recv_bufs[2] = { &usb_recv_buf0, &usb_recv_buf1 };
usb_buf_t *usb_send_bufs[2] = { &usb_send_buf0, &usb_send_buf1 };

int active_usb_recv_buf_idx;
int active_usb_send_buf_idx;

int usb_send(const void *buf, size_t size) {
	size_t dummy_ret_len;
	return usb_send_w_ret_len(buf, size, &dummy_ret_len);
}

int usb_recv(void *buf, size_t size) {
	size_t dummy_ret_len;
	return usb_recv_w_ret_len(buf, size, &dummy_ret_len);
}
