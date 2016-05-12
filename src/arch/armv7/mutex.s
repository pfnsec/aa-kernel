.section .text

.global mutex_lock
mutex_lock:
	mov r2, #1
test_lock:
	ldrex r1, [r0]
	cmp r1, r2
	beq test_lock
try_lock:
	strex r1, r2, [r0]
	cmp r1, r2
	beq test_lock

//	dmb
	bx lr

.global mutex_try_lock
mutex_try_lock:
	mov r2, #1
	ldrex r1, [r0]
	cmp r1, r2
	bne try_test_lock
	bx lr

try_test_lock:
	strex r1, r2, [r0]
	mov r0, r2
//	dmb
	bx lr
	


.global mutex_unlock
mutex_unlock:
	mov r2, #0
//	dmb
	str r2, [r0]
	bx lr
