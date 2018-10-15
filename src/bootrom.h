#pragma once

#include <stddef.h>

void wait_us(unsigned int us);

int usb_send_w_ret_len(const void *buf, size_t size, size_t *size_sent);
int usb_recv_w_ret_len(void *buf, size_t size, size_t *size_recv);

int usb_clear_endpoint(const void *usb_ctx, int usb_ep);

extern void *usb_ctx_ptr;
