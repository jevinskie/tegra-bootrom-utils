#pragma once

#include <stdint.h>

enum cmd_type {
	CMD_TTY = 0x1,
	CMD_NOTIFY_REBOOT = 0x2,
};

typedef struct cmd_hdr {
	uint32_t cmd_type;
	uint32_t cmd_size;
} __attribute__((packed)) cmd_hdr_t;

typedef struct cmd_tty {
	cmd_hdr_t hdr;
	char tty_buf[0];
} __attribute__((packed)) cmd_tty_t;

typedef struct cmd_notify_reboot {
	cmd_hdr_t hdr;
	int status;
} __attribute__((packed)) cmd_notify_reboot_t;
