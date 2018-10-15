#include <unistd.h>

#include "bootrom.h"
#include "cmd.h"
#include "pmc.h"
#include "usb.h"
#include "util.h"

__attribute__((noreturn))
void _exit(int status) {
	PMC(PMC_SCRATCH1) = status;
	PMC(PMC_SCRATCH0) = (1 << 1);

	usb_clear_endpoint(usb_ctx_ptr, USB_EP_BULK_OUT);

	cmd_notify_reboot_t *cmd = (cmd_notify_reboot_t *)usb_send_buf0;
	cmd->hdr.cmd_type = CMD_NOTIFY_REBOOT;
	cmd->hdr.cmd_size = sizeof(*cmd);
	cmd->status = status;
	usb_send_start(cmd, sizeof(*cmd));

	wait_ms(1000);

	PMC(0) = (1 << 4);
	while (1);
}