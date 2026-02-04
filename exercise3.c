.global _start
_start:
	push {r4, r5, r6, r7}
	ldr r4, [r0]
	ldr r1, [r1]
	ldr r2, [r2]
	ldr r3, [r3]
	mul r1, r1, r1
	add r4, r4, r1
	add r3, r3, r1
	mul r4, r4, r3
	add r4, r4, r2
	str r4, [r0]
	pop {r4, r5, r6, r7}
	bx lr
