#Implementations of standard aeabi builtins for processors that do not natively support integer divide

.global __aeabi_uidiv
.global __aeabi_uidivmod

__aeabi_uidiv:
__aeabi_uidivmod:
	subs    r2, r1, #0
	bxeq    lr

	cmp     r2, r0
	movhi   r1, r0
	movhi   r0, #0
	bxhi    lr

	mov     r1, r0

	clz     r3, r1
	clz     r0, r2
	rsb     r0, r3, r0
	mov     r3, #1
	mov     r2, r2, asl r0
	mov     r3, r3, asl r0
	mov     r0, #0
1:
	cmp     r1, r2
	rsbcs   r1, r2, r1
	orrcs   r0, r0, r3
	movs    r3, r3, lsr #1
	mov     r2, r2, lsr #1
	bne     1
	bx lr
