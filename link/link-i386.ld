ENTRY (_start)

SECTIONS
{
	. = 1M;
	.text : { *(.text*) *(.rodata*) }
	.data : { *(.data*) }
	.bss : { *(.bss*) *(COMMON*) }
	_seg_data = .;
	
}
