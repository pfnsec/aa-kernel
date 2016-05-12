
ENTRY (_start)

SECTIONS
{
	. = 0x00010000;

	init_stack_bot = .;
	init_stack = init_stack_bot + 0x1000;

	. = init_stack;

	irq_stack_bot = .;
	irq_stack = irq_stack_bot + 0x1000;

	. = irq_stack;

	.text : { *(.init*) *(.text*) *(.rodata*) *(.ivt*) }
	.data : { *(.data*) }
	.bss  : { *(.bss*) *(COMMON*) }
	_boot_fb_mem = ALIGN(0x1000);
	. = _boot_fb_mem + 0x1000;
	_seg_data    = ALIGN(0x1000);
	
}
