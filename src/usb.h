#include <stddef.h>

int usb_send_w_ret_len(const void *buf, size_t size, size_t *size_sent);
int usb_send(const void *buf, size_t size);
int usb_recv(void *buf, size_t size, size_t *size_recv);