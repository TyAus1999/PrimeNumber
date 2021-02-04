.code
;RCX=max lessthan or equal
;returns amount
public primeNumberCheck
primeNumberCheck proc
	push	rbx
	push	r15
	push	r14;Amount of Primes
	;Move the start and the max to unused registers
	mov		r8, rcx

	mov		rcx, 2
	jmp		primeNumberCheck_L1
	;for(rcx=2;rcx<=r8;rcx++)
	primeNumberCheck_L1_le:
			mov		r9,2	;Inner loop counter
			xor		r15,r15	;factors for current
			jmp primeNumberCheck_L2
		;for(r9=2;r9<rcx;r9++)
		primeNumberCheck_L2_le:
			xor		rdx,rdx
			mov		rax,rcx
			div		r9
			cmp		rdx,0
			;if 0 it r9 is a factor of r13
			;else non factor
			jg primeNumberCheck_L2_NonFactor
			inc		r15
			cmp		r15,1
			jg primeNumberCheck_L2_End
			primeNumberCheck_L2_NonFactor:
			inc		r9
		primeNumberCheck_L2:
			cmp		r9,rcx
			jle		primeNumberCheck_L2_le
			cmp		r15,1
			jg primeNumberCheck_L2_End
			inc		r14
			
		primeNumberCheck_L2_End:
		inc		rcx
	primeNumberCheck_L1:
		cmp		rcx, r8
		jle primeNumberCheck_L1_le
	;End loop

	mov		rax,r14
	pop		r14
	pop		r15
	pop		rbx
	ret
primeNumberCheck endp
;RCX is max, less than or equal too
;RDX is where to start
public primeNumberCheckOp
primeNumberCheckOp proc
	push	rbx;Inner loop var
	push	r15;factors
	push	r14;Amount of primes
	push	r13;Half of innerLoop
	push	r12;Temp register for use in factors
	push	r11;Value to stop at

	mov		r11,rdx
	mov		r14, 1

	primeNumberCheckOp_L1:
		cmp		rcx,r11
		je		primeNumberCheckOp_End
		xor		r15,r15
		mov		rbx,2
		xor		rdx,rdx
		mov		rax,rcx
		div		rbx
		mov		r13,rax
		inc		rax
		cmp		rdx,0
		cmovnz	r13,rax
		;r13 is the value to test too
		primeNumberCheckOp_L2:
			xor		rdx,rdx
			mov		rax,rcx
			div		rbx
			mov		rax,1
			xor		r12,r12
			cmp		rdx,0;Check for remainders
			cmovz	r12,rax;If remainders move 1 into r12
			add		r15,r12;Add r12 to r15 
			cmp		r15,1;Check if there are more than 1 factor
			jg		primeNumberCheckOp_L2_End;If there are more than 1 factor number is garbage
			;else inc and carry on
			inc		rbx
			cmp		rbx,r13
			jle		primeNumberCheckOp_L2;if rbx is lessthan or equal to r13 jump
			primeNumberCheckOp_L2_End:
			mov		rax,1
			xor 	r12,r12
			cmp		r15,1
			cmovl	r12,rax
			add		r14,r12

		dec		rcx
		jmp primeNumberCheckOp_L1
	primeNumberCheckOp_End:
	mov		rax,r14
	pop		r11
	pop		r12
	pop		r13
	pop		r14
	pop		r15
	pop		rbx
	ret
primeNumberCheckOp endp
end