#pragma once

#include <stddef.h>
#include <stdint.h>

#define USB_XFER_MAX 0x1000

enum usb_ep {
	USB_EP_CTRL_OUT	= 0,
	USB_EP_CTRL_IN	= 1,
	USB_EP_BULK_OUT	= 2,
	USB_EP_BULK_IN	= 3,
};

typedef uint8_t usb_buf_t[USB_XFER_MAX];

extern usb_buf_t usb_recv_buf0;
extern usb_buf_t usb_recv_buf1;
extern usb_buf_t usb_send_buf0;
extern usb_buf_t usb_send_buf1;

extern usb_buf_t *usb_recv_bufs[2];
extern usb_buf_t *usb_send_bufs[2];

extern int active_usb_recv_buf_idx;
extern int active_usb_send_buf_idx;

int usb_send(const void *buf, size_t size);
int usb_recv(void *buf, size_t size);
