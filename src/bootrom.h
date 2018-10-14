#pragma once

#include <stddef.h>

void NvOsWaitUS(int us);

int usb_send_w_ret_len(const void *buf, size_t size, size_t *size_sent);
int usb_recv_w_ret_len(void *buf, size_t size, size_t *size_recv);
