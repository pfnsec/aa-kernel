#include "config.h"

#if ARCH == i386

.code32
.text

.set ALIGN,    1<<0
.set MEMINFO,  1<<1
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.text
.global _stack_bot
_stack_bot:

.skip 0x10000 // Reserve 4k stack in the BSS

.global _stack
_stack:


.global _start
_start:
	movl _stack, %esp
	call init
	cli
	hlt

#endif
