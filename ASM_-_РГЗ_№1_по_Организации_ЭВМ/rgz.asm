masm
model small
stack 256

.data
	wsize	dw	3			;Количество членов семьи
 	bage	db	43,39,17
 	bday	db	3,17,26
 	bmonth	db	8,9,11
 	bname	db	10,"Константин",5,"Ольга",8,"Владимир"
 	bpname	db	12,"Владимирович",8,"Петровна",14,"Константинович"
	; Переменные:
 	n		db	0		; n:=size-1
 	j		db	0
 	glasn	db	18,"АаЕеИиОоУуЫыЭэЮюЯя"	; Гласные буквы и их кол-во
 	f1		db	0
 	f2		db	0
 	f3		db	0
.code
start:	
	mov	ax,DGROUP
	mov	ds,ax
	xor	si,si					; Инициализация 
	mov	dl,byte ptr bmonth[si]	; переменных
	mov	bp,word ptr [wsize]
	dec	bp
	mov	word ptr[n],bp
next1:	
	inc	si
	mov	al,byte ptr bmonth[si]		; Цикл: поиск 
	cmp	al,dl				;  максимального месяца
	jbe	cont1				;  рождения,
	mov	dl,al				; результат - в DL
cont1:	
	cmp	bp,si
	je	end1
	jmp	next1
end1:	
	xor	si,si
next2:	
	cmp	byte ptr bmonth[si],dl	; Обработка всех
	jne	cont3			; элементов, у которых
	mov	ax,si			; месяц рождения равен
	mov	dh,3			; максимальному
	div	dh
	xor	dh,dh
	push	dx
	push	si
	cmp	ah,0			; Если остаток от деления
	jne	case2			;  номера элемента на 3 равен 0,
	cmp	byte ptr[f1],1		;  и первая процедура
	jne	cont2			;  не выполнялась,
	call	procedure_one		;  то выполняем первую процедуру
	mov	byte ptr[f1],1
	jmp	cont2
case2:	
	cmp	ah,1		; Если остаток равен 1,
	jne	case3		;  выполняем вторую процедуру
	cmp	byte ptr[f2],1
	je	cont2
	call	procedure_two
	mov	byte ptr[f2],1
	jmp	cont2
case3:	
	cmp	byte ptr[f3],1
	je	cont2
	call	procedure_three	; Иначе выполняем третью процедуру
	mov	byte ptr[f3],1
cont2:	
	pop	si
	pop	dx
cont3:	
	cmp	si,word ptr[n]	; Выходим из цикла, если на этом проходе
	je	end2		;  был проверен последний элемент
	inc	si
	jmp	next2
end2:	
	mov	ax,4C00h
	int	21h

;------------------- Процедуры обработки массивов -------------------------
procedure_one:				;------------- Первый случай -------
	xor	dx,dx
	xor	cx,cx			; В регистре CX - количество
	mov	cl,byte ptr glasn	; гласных
	mov	byte ptr j,0
n1_1:	
	mov	di,dx
	xor	bp,bp
	xor	bx,bx
n1_2:	
	inc	di
	xor	si,si
	xor	ax,ax
	mov	al,byte ptr bname[di]	; Ищем гласную
n1_3:	
	cmp	al,byte ptr glasn[si]	
	jne	e1_1
	mov	bp,di			; Нашли первую гласную букву
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
	mov	al,'Б'	
	jmp	e1_4
e1_3:	
	mov	al,byte ptr bname[bx]	; Заменяем гласную на согласную
e1_4:	
	mov	bx,bp
	mov	byte ptr bname[bx],al	
	mov	bx,dx			; Ищем начало следующего имени,
	xor	ax,ax			;  заносим его в DX
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

procedure_two:				;------------- Второй случай -----
	xor	bx,bx
	mov	cx,[wsize]
	xor	dh,dh
for1:	
	mov	dl,byte ptr bpname[bx]	; Заносим в DX длину отчества
	mov	si,bx
	inc	si
	mov	di,bx		; DI:=BX+DX
	add	di,dx
	mov	al,byte ptr bpname[si]	; Меняем первую букву
	mov	ah,byte ptr bpname[di]	;  на последнюю
	mov	byte ptr bpname[si],ah	;
	mov	byte ptr bpname[di],al	;
	mov	bx,di
	inc	bx
	loop	for1
	ret

procedure_three:			;------------- Третий случай -----
	xor	bx,bx
n3_1:	
	or	byte ptr bday[bx],11000000b
	and	byte ptr bday[bx],11111100b
	inc	bx
	cmp	bx,wsize
	jne	n3_1
	ret
end	start
	
