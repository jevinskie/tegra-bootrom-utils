ENTRY(_start_arm_mode)

SECTIONS {
	. = LOAD_ADDR;
	.text : {
		*(.text_entry);
		*(.text*);
	}
	.data : {
		*(.data*);
		*(.rodata*);
	}
	. = ALIGN(0x10);
	__bss_start = .;
	.bss : {
		*(COMMON)
		*(.bss*)
	}
	__bss_end = .;
	__end__ = .;
	PROVIDE(usb_recv_buf0 = 0x40003000);
	PROVIDE(usb_recv_buf1 = 0x40004000);
	PROVIDE(usb_send_buf0 = 0x40005000);
	PROVIDE(usb_send_buf1 = 0x40006000);
}
