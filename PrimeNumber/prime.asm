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
			;if 0 it r9 is a factor of rcx
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
end