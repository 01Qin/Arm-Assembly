.global _start
_start:
	push {r4, r5, r6, r7}
    cmp r0, r1
    bge no_swap
    sub r0, r1, r0
    b end
    no_swap:
    sub r0, r0, r1
    end:  
    pop {r4, r5, r6, r7} 
    bx lr 
