silentFileLocation PROTO C
qword01Address  PROTO C
qword02Address  PROTO C

.data
minusOne dd -1.0

.code

HookSilentGetter PROC
	mov [rsp + 28h], r9
	push rcx
	mov rcx, qword ptr [qword01Address]
	mov rcx, qword ptr [rcx]
	cmp rcx, qword ptr [rsp]
	pop rcx
	jnz Done
	mov rdx, qword ptr [silentFileLocation]
	Done:
	ret
HookSilentGetter ENDP

HookTimerSet1 PROC
	push rcx
	mov rcx, qword ptr [qword02Address]
	mulss xmm0, dword ptr [rcx]
	movss dword ptr [rsi+38Ch], xmm0
	mov rcx, qword ptr [qword01Address]
	mov rcx, qword ptr [rcx]
	cmp rcx, rsi
	pop rcx
	jnz Done
	mov dword ptr [rsi+38Ch], 38d1b717h
	Done:
	ret
HookTimerSet1 ENDP

HookTimerSet2 PROC
	mov qword ptr [rsp + 88h], rbp
	mov qword ptr [rsp + 80h], rdi
	push rcx
	mov rcx, qword ptr [qword01Address]
	mov rcx, qword ptr [rcx]
	cmp rcx, rsi
	pop rcx
	jnz Done
	movss xmm0, dword ptr [minusOne]
	Done:
	ret
HookTimerSet2 ENDP

END
