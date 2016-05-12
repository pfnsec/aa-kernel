
ENTRY (_start)


MEMORY 
{
	ram : ORIGIN = 0x40001000, LENGTH = 0x80000000
}


SECTIONS
{
	. = 0x40001000;

	init_stack = . ;
	_start     = . ;

	.text : { *(.init*) *(.text*) *(.rodata*) } > ram
	.data : { *(.data*) }             > ram
	.bss  : { *(.bss*) *(COMMON*) }   > ram

	_seg_data = ALIGN(0x1000);
	
}
