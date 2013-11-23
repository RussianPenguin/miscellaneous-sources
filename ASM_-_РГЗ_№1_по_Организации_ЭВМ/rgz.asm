masm
model small
stack 256

.data
	wsize	dw	3			;������⢮ 童��� ᥬ�
 	bage	db	43,39,17
 	bday	db	3,17,26
 	bmonth	db	8,9,11
 	bname	db	10,"����⠭⨭",5,"��죠",8,"��������"
 	bpname	db	12,"�������஢��",8,"���஢��",14,"����⠭⨭����"
	; ��६����:
 	n		db	0		; n:=size-1
 	j		db	0
 	glasn	db	18,"��������������"	; ����� �㪢� � �� ���-��
 	f1		db	0
 	f2		db	0
 	f3		db	0
.code
start:	
	mov	ax,DGROUP
	mov	ds,ax
	xor	si,si					; ���樠������ 
	mov	dl,byte ptr bmonth[si]	; ��६�����
	mov	bp,word ptr [wsize]
	dec	bp
	mov	word ptr[n],bp
next1:	
	inc	si
	mov	al,byte ptr bmonth[si]		; ����: ���� 
	cmp	al,dl				;  ���ᨬ��쭮�� �����
	jbe	cont1				;  ஦�����,
	mov	dl,al				; १���� - � DL
cont1:	
	cmp	bp,si
	je	end1
	jmp	next1
end1:	
	xor	si,si
next2:	
	cmp	byte ptr bmonth[si],dl	; ��ࠡ�⪠ ���
	jne	cont3			; ����⮢, � ������
	mov	ax,si			; ����� ஦����� ࠢ��
	mov	dh,3			; ���ᨬ��쭮��
	div	dh
	xor	dh,dh
	push	dx
	push	si
	cmp	ah,0			; �᫨ ���⮪ �� �������
	jne	case2			;  ����� ����� �� 3 ࠢ�� 0,
	cmp	byte ptr[f1],1		;  � ��ࢠ� ��楤��
	jne	cont2			;  �� �믮��﫠��,
	call	procedure_one		;  � �믮��塞 ����� ��楤���
	mov	byte ptr[f1],1
	jmp	cont2
case2:	
	cmp	ah,1		; �᫨ ���⮪ ࠢ�� 1,
	jne	case3		;  �믮��塞 ����� ��楤���
	cmp	byte ptr[f2],1
	je	cont2
	call	procedure_two
	mov	byte ptr[f2],1
	jmp	cont2
case3:	
	cmp	byte ptr[f3],1
	je	cont2
	call	procedure_three	; ���� �믮��塞 ����� ��楤���
	mov	byte ptr[f3],1
cont2:	
	pop	si
	pop	dx
cont3:	
	cmp	si,word ptr[n]	; ��室�� �� 横��, �᫨ �� �⮬ ��室�
	je	end2		;  �� �஢�७ ��᫥���� �����
	inc	si
	jmp	next2
end2:	
	mov	ax,4C00h
	int	21h

;------------------- ��楤��� ��ࠡ�⪨ ���ᨢ�� -------------------------
procedure_one:				;------------- ���� ��砩 -------
	xor	dx,dx
	xor	cx,cx			; � ॣ���� CX - ������⢮
	mov	cl,byte ptr glasn	; ������
	mov	byte ptr j,0
n1_1:	
	mov	di,dx
	xor	bp,bp
	xor	bx,bx
n1_2:	
	inc	di
	xor	si,si
	xor	ax,ax
	mov	al,byte ptr bname[di]	; �饬 ������
n1_3:	
	cmp	al,byte ptr glasn[si]	
	jne	e1_1
	mov	bp,di			; ��諨 ����� ������ �㪢�
e1_1:	
	inc	si
	cmp	bp,0
	jne	e1_2
	cmp	si,cx
	jne	n1_3
	mov	bx,di
	je	n1_2	
e1_2:	
	cmp	bx,0	
	jne	e1_3
	mov	al,'�'	
	jmp	e1_4
e1_3:	
	mov	al,byte ptr bname[bx]	; �����塞 ������ �� ᮣ�����
e1_4:	
	mov	bx,bp
	mov	byte ptr bname[bx],al	
	mov	bx,dx			; �饬 ��砫� ᫥���饣� �����,
	xor	ax,ax			;  ����ᨬ ��� � DX
	mov	al,byte ptr bname[bx]
	add	dx,ax
	inc	dx
	mov	al,byte ptr[j]	
	cmp	al,byte ptr[n]
	je	ret1
	inc	byte ptr[j]
	jmp	n1_1
ret1:	
	ret

procedure_two:				;------------- ��ன ��砩 -----
	xor	bx,bx
	mov	cx,[wsize]
	xor	dh,dh
for1:	
	mov	dl,byte ptr bpname[bx]	; ����ᨬ � DX ����� ����⢠
	mov	si,bx
	inc	si
	mov	di,bx		; DI:=BX+DX
	add	di,dx
	mov	al,byte ptr bpname[si]	; ���塞 ����� �㪢�
	mov	ah,byte ptr bpname[di]	;  �� ��᫥����
	mov	byte ptr bpname[si],ah	;
	mov	byte ptr bpname[di],al	;
	mov	bx,di
	inc	bx
	loop	for1
	ret

procedure_three:			;------------- ��⨩ ��砩 -----
	xor	bx,bx
n3_1:	
	or	byte ptr bday[bx],11000000b
	and	byte ptr bday[bx],11111100b
	inc	bx
	cmp	bx,wsize
	jne	n3_1
	ret
end	start
	
