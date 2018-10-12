#include "usb.h"

// #include <sys/iosupport.h>

#define USB_RECV_BUF 0x40003000
#define USB_XFER_MAX 0x1000

#define min(x,y) ({ \
	typeof(x) _x = (x);	\
	typeof(y) _y = (y);	\
	(void) (&_x == &_y);	\
	_x < _y ? _x : _y; })

typedef int (*usb_send_bootrom_t)(const void *buf, size_t size, size_t *size_sent);
typedef int (*usb_recv_bootrom_t)(void *buf, size_t size, size_t *size_recv);

int usb_send_w_ret_len(const void *buf, size_t size, size_t *size_sent) {
	return ((usb_send_bootrom_t)(0xFFF05092 + 1))(buf, size, size_sent);
}

int usb_recv_w_ret_len(void *buf, size_t size, size_t *size_recv) {
	return ((usb_recv_bootrom_t)(0xFFF050DE + 1))(buf, size, size_recv);
}

int usb_send(const void *buf, size_t size) {
	size_t dummy_ret_len;
	return usb_send_w_ret_len(buf, size, &dummy_ret_len);
}

int usb_recv(void *buf, size_t size) {
	size_t dummy_ret_len;
	return usb_recv_w_ret_len(buf, size, &dummy_ret_len);
}

#if 0

static ssize_t usb_write(struct _reent *r, void *fd, const char *ptr, size_t len) {
	(void)r;
	(void)fd;
	return (ssize_t)usb_send(ptr, len);
}

static ssize_t usb_read(struct _reent *r, void *fd, char *ptr, size_t len) {
	(void)r;
	(void)fd;
	return (ssize_t)usb_recv(ptr, min(len, (size_t)USB_RECV_BUF));
}

const devoptab_t dotab_stdout_usb = {
	"stdout",	// device name
	0,			// size of file structure
	NULL,		// device open
	NULL,		// device close
	usb_write,	// device write
	NULL,		// device read
	NULL,		// device seek
	NULL,		// device fstat
	NULL,		// device stat
	NULL,		// device link
	NULL,		// device unlink
	NULL,		// device chdir
	NULL,		// device rename
	NULL,		// device mkdir
	0,		// dirStateSize
	NULL,		// device diropen_r
	NULL,		// device dirreset_r
	NULL,		// device dirnext_r
	NULL,		// device dirclose_r
	NULL,		// device statvfs_r
	NULL,		// device ftruncate_r
	NULL,		// device fsync_r
	NULL,		// deviceData
	NULL,		// chmod_r
	NULL,		// fchmod_r
	NULL,		// rmdir_r
	NULL,		// lstat_r
	NULL,		// utimes_r
};

const devoptab_t dotab_stdin_usb = {
	"stdin",	// device name
	0,			// size of file structure
	NULL,		// device open
	NULL,		// device close
	NULL,		// device write
	usb_read,	// device read
	NULL,		// device seek
	NULL,		// device fstat
	NULL,		// device stat
	NULL,		// device link
	NULL,		// device unlink
	NULL,		// device chdir
	NULL,		// device rename
	NULL,		// device mkdir
	0,		// dirStateSize
	NULL,		// device diropen_r
	NULL,		// device dirreset_r
	NULL,		// device dirnext_r
	NULL,		// device dirclose_r
	NULL,		// device statvfs_r
	NULL,		// device ftruncate_r
	NULL,		// device fsync_r
	NULL,		// deviceData
	NULL,		// chmod_r
	NULL,		// fchmod_r
	NULL,		// rmdir_r
	NULL,		// lstat_r
	NULL,		// utimes_r
};

const devoptab_t dotab_stderr_usb = {
	"stderr",	// device name
	0,			// size of file structure
	NULL,		// device open
	NULL,		// device close
	usb_write,	// device write
	NULL,		// device read
	NULL,		// device seek
	NULL,		// device fstat
	NULL,		// device stat
	NULL,		// device link
	NULL,		// device unlink
	NULL,		// device chdir
	NULL,		// device rename
	NULL,		// device mkdir
	0,		// dirStateSize
	NULL,		// device diropen_r
	NULL,		// device dirreset_r
	NULL,		// device dirnext_r
	NULL,		// device dirclose_r
	NULL,		// device statvfs_r
	NULL,		// device ftruncate_r
	NULL,		// device fsync_r
	NULL,		// deviceData
	NULL,		// chmod_r
	NULL,		// fchmod_r
	NULL,		// rmdir_r
	NULL,		// lstat_r
	NULL,		// utimes_r
};

extern const devoptab_t dotab_stdnull;

const devoptab_t *devoptab_list[STD_MAX] = {
	&dotab_stdout_usb, &dotab_stdin_usb, &dotab_stderr_usb, &dotab_stdnull,
	&dotab_stdnull, &dotab_stdnull, &dotab_stdnull, &dotab_stdnull,
	&dotab_stdnull, &dotab_stdnull, &dotab_stdnull, &dotab_stdnull,
	&dotab_stdnull, &dotab_stdnull, &dotab_stdnull, &dotab_stdnull
};

#endif
