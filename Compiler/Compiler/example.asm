.386P
.MODEL FLAT, C
.STACK
.DATA
.CODE
example PROC num: dword, arr: word, len: dword
	xor eax, eax
	xor ebx, ebx
	xor edx, edx; some comment n1

	mov eax, num
	rcl eax, 1
	mov ebx, 10
	sbb ebx, 1

	; some comment n2
	mov ecx, 2
	mov si, arr
c1: xor eax, eax
	lodsw
	add edx,     eax
	cmp ecx, len
	jg exit
	add ecx, 1
	jmp      c1
exit:       

	mov eax, edx
	add eax, ebx
         ret
example ENDP
END