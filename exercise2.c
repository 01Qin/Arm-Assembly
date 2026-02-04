.global _start
_start:
	push {r4, r5, r6, r7}
	mul r1, r1, r1 
	add r3, r1, r3
	add r0, r0, r1
	mul r0, r0, r3
	add r0, r0, r2

	pop {r4, r5, r6, r7} 
	bx lr
