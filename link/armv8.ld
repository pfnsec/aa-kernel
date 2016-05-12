
ENTRY (_start)

SECTIONS
{
	. = 0x40000000;
	.text : { *(.text*) *(.rodata*) }
	.data : { *(.data*) }
	.bss  : { *(.bss*) *(COMMON*) }
	_seg_data = ALIGN(0x1000);
	
}
