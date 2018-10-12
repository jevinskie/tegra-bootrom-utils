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
	.bss : {
		__bss_start = .;
		*(COMMON)
		*(.bss*)
		__bss_end = .;
	}
}
