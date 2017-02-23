
ENTRY (_start)

MEMORY
{
   ddr  : ORIGIN = 0x00100000, LENGTH = 0x1FF00000
   ram0 : ORIGIN = 0x00000000, LENGTH = 0x00030000
   ram1 : ORIGIN = 0xFFFF0000, LENGTH = 0x0000FE00
}


SECTIONS
{
	. = 0x00100000;

	init_stack_bot = .;
	init_stack = init_stack_bot + 0x1000;

	. = init_stack;

	irq_stack_bot = .;
	irq_stack = irq_stack_bot + 0x1000;

	. = irq_stack;

	.text . : { *(.init*) *(.text*) *(.rodata*) *(.note.gnu.build-id*) } > ddr
	.data   : { *(.data*) } > ddr
	.bss    : { *(.bss*) *(COMMON*) } > ddr

	_seg_data = ALIGN(0x1000);
	
}
