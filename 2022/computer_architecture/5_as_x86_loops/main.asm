	; vim: ft=masm

	.586P
	.MODEL FLAT, STDCALL

	_DATA SEGMENT
	m                  DD 7
	n                  DD 8
	a                  DD -46
	b                  DD 63
	tempColumn         DD 0
	scalarProduct      DD 0
	condPickedElements DD 0
	condPickedSum      DD 0
	matrix             DD 1, 18, 8, 4, 15, -19, 4, -13
	DD                 1, -1, 7, 20, -2, -1, -8, -19
	DD                 3, 8, 11, 14, -4, 1, 14, 2
	DD                 -9, -5, 20, -16, 4, -12, 4, -1
	DD                 -6, 4, -8, 3, 13, 2, 11, 13
	DD                 19, -15, 13, 17, -12, -9, 10, -13
	DD                 -1, 3, 17, 10, 9, 2, 16, -18
	transposedMatrix   DD 56 DUP(?)
	_DATA ENDS

	_TEXT SEGMENT

START:
	lea esi, matrix; source index
	lea edi, transposedMatrix; destination index
	mov ebx, m; outer loop

OUTER_LOOP:
	mov ecx, n; inner loop

INNER_LOOP:
	mov eax, [esi]
	mov [edi], eax
	add esi, 4; move pointer by 1 element
	add edi, 28; 7(m) * 4(bytes) move pointer to element of the next row
	dec ecx
	jnz INNER_LOOP

	add tempColumn, 4
	lea edi, transposedMatrix
	add edi, tempColumn
	dec ebx
	jnz OUTER_LOOP

SCALAR_PREPARE:
	lea esi, [matrix+16]
	lea edi, [matrix+20]
	mov ecx, m

SCALAR_COMPUTATIONS:
	mov  eax, [esi]
	imul eax, [edi]
	add  scalarProduct, eax
	add  esi, 32; 8(m) * 4(bytes) move pointer to element of the next row
	add  edi, 32; 8(m) * 4(bytes) move pointer to element of the next row
	loop SCALAR_COMPUTATIONS

CONDITION_PREPARE:
	mov ecx, m; loop by rows of column
	lea esi, [matrix+24]; start from 6th column

CONDITION:
	cmp [esi], a
	jl  TRUE
	jnl FALSE

	cmp  [esi], b
	jge  TRUE
	jnge FALSE

TRUE:
	inc condPickedElements
	add condPickedSum, [esi]
	jmp NEXT

FALSE:
	jmp NEXT

NEXT:
	add  esi, 32; 8(m) * 4(bytes) move pointer to element of the next row
	loop CONDITION

	RET
	_TEXT ENDS
	END START
