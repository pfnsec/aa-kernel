
ENTRY (_start)


MEMORY 
{
	ram : ORIGIN = 0x8000, LENGTH = 0x1000000
}


SECTIONS
{
	. = 0x8000;
	_start     = 0x8000;
	init_stack = 0x8000;
	.text : { *(.init*) *(.text*) *(.rodata*) } > ram
	.data : { *(.data*) } > ram
	.bss  : { *(.bss*) *(COMMON*) } > ram

	_seg_data = ALIGN(0x1000);
	
}
