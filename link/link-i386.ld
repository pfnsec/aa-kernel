ENTRY (_start)

SECTIONS
{
	. = 1M;
	.text BLOCK(4K) : ALIGN(4K) { *(.multiboot*) *(.text*) *(.rodata*) }
	.data BLOCK(4K) : ALIGN(4K) { *(.data*) }
	.bss  BLOCK(4K) : ALIGN(4K) { *(.bss*) *(COMMON*) }
	_seg_data = .;
	
}
