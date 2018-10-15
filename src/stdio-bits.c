#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>

#include "bootrom.h"
#include "usb.h"
#include "cmd.h"

/* Buffered output routines for newlib-nano stdio */

static ssize_t stdio_read(int fd, void *buf, size_t count) {
	(void)fd;
	size_t recv_size;
	int res = usb_recv_w_ret_len(buf, count, &recv_size);
	if (!res) {
		return (ssize_t)recv_size;
	} else {
		errno = EIO;
		return -1;
	}
}

static ssize_t stdio_write(int fd, const void *buf, size_t count) {
	(void)fd;
	size_t sent_size;
	cmd_tty_t *cmd_tty = (cmd_tty_t *)usb_send_buf0;
	cmd_tty->hdr.cmd_type = CMD_TTY;
	cmd_tty->hdr.cmd_size = sizeof(cmd_hdr_t) + count;
	memcpy(cmd_tty->tty_buf, buf, count);
	int res = usb_send_w_ret_len(cmd_tty, count + sizeof(cmd_hdr_t), &sent_size);
	while (usb_get_ep_status(1) == 1);
	if (!res) {
		return (ssize_t)sent_size - sizeof(cmd_hdr_t);
	} else {
		errno = EIO;
		return -1;
	}
}

static char write_buf[512];
static size_t write_len;

static int
ao_flush(FILE *ignore)
{
	(void)ignore;
	if (write_len) {
		int off = 0;
		while (write_len) {
			int this = stdio_write(1, write_buf + off, write_len);
			if (this < 0) {
				write_len = 0;
				return -1;
			}
			off += this;
			write_len -= this;
		}
	}
	return 0;
}

static int
ao_putc(char c, FILE *ignore)
{
	write_buf[write_len++] = c;
	if (write_len < sizeof(write_buf))
		return 0;
	return ao_flush(ignore);
}

static char read_buf[512];
static size_t read_len;
static size_t read_off;

static int
ao_getc(FILE *ignore)
{
	(void)(ignore);
	if (read_off >= read_len) {
		(void) ao_flush(ignore);
		read_off = 0;
		read_len = stdio_read(0, read_buf, sizeof (read_buf));
		if (read_len <= 0) {
			read_len = 0;
			return -1;
		}
	}
	return (unsigned char) read_buf[read_off++];
}

static FILE __stdio = {
	.flags = __SRD|__SWR,
	.put = ao_putc,
	.get = ao_getc,
	.flush = ao_flush,
};

__attribute__((externally_visible))
FILE *const __iob[3] = { &__stdio, &__stdio, &__stdio };
