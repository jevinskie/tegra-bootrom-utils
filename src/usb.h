#include <stddef.h>
#include <stdint.h>

#define USB_XFER_MAX 0x1000

extern uint8_t usb_recv_buf0[USB_XFER_MAX];
extern uint8_t usb_recv_buf1[USB_XFER_MAX];
extern uint8_t usb_send_buf0[USB_XFER_MAX];
extern uint8_t usb_send_buf1[USB_XFER_MAX];

uint8_t *usb_recv_bufs[2] = { usb_recv_buf0, usb_recv_buf1 };
uint8_t *usb_send_bufs[2] = { usb_send_buf0, usb_send_buf1 };

int usb_send_w_ret_len(const void *buf, size_t size, size_t *size_sent);
int usb_recv_w_ret_len(void *buf, size_t size, size_t *size_recv);
int usb_send(const void *buf, size_t size);
int usb_recv(void *buf, size_t size);
