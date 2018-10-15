#pragma once

#include <stdint.h>

enum cmd_type {
	CMD_TTY = 0x1,
};

typedef struct cmd_hdr {
	uint32_t cmd_type;
	uint32_t cmd_size;
} __attribute__((packed)) cmd_hdr_t;

typedef struct cmd_tty {
	cmd_hdr_t hdr;
	char tty_buf[];
} __attribute__((packed)) cmd_tty_t;