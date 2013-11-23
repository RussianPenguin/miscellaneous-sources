masm
.model small
.stack 100h
;-----------------------------------------------;
;---------------Сегмент данных------------------;
;-----------------------------------------------;
.data
  kchle db 3
  mname db 6,"Максим",7,"Валерий",5,"Ирина"
  motch db 9,"Валерьвич",8,"Петрович",8,"Ивановна"
  mfami db 6,"Зубков",6,"Зубков",7,"Зубкова"
  mday  db 13,18,06
  mmoun db 03,06,02
  myear dw 1987,1962,1963
  mcury dw 2005 ;Текущий год
  mold  db 3 dup (0);Возраст членов семьи
  glasn	db 18,"АаЕеИиОоУуЫыЭэЮюЯя"
  mrazn db 2 dup (0)
  glas  db 3 dup (3 dup (0))
  sogl	db 3 dup (3 dup (0))
  zraz  db 50

;-----------------------------------------------;
;-----------------Сегмент кода------------------;
;-----------------------------------------------;
.code
start:
  mov ax,DGROUP
  mov ds,ax
  xor ax,ax
  mov bl,glasn
  xor dx,dx
  ;Подготовка начальных значений

  ;Вычисляем количество гласных и согласных
  ;в именах и отчествах
  ;Результат в массивах glas и sogl размерностью 3x3
  mov cl,kchle
  mov dl,cl
  mov si,offset mname
  call glasn_sogl
  xor dx,dx
  mov dl,cl
  mov si,offset motch
  call glasn_sogl
  xor dx,dx
  mov dl,cl
  mov si,offset mfami
  call glasn_sogl
  xor cx,cx
  
  call bukvi

  ;Вычисление разности между количеством
  ;гласных и согласных
  ;Завершение работы программы
  jmp endc

;-----------------------------------------------;
;----Процедура сравнения букв в имени и др.-----;
;-----------------------------------------------;
bukvi proc
  xor cx,cx
  mov cl,kchle
  xor si,si
  xor ax,ax
  xor bx,bx
buk1:
  push si
  mov ah,sogl[si]
  mov al,glas[si]
  add si,cx
  mov bl,sogl[si]
  add si,cx
  mov bh,sogl[si]
  cmp al,bl
  jbe buk2
  cmp ah,bh
  ja caller
buk2:
  pop si
  inc si
  cmp si,cx
  jb buk1
  jmp buk3
caller:
  pop si
  call vozrast
buk3:
  ret
bukvi endp
;-----------------------------------------------;
;----------------Еонец процедуры----------------;
;-----------------------------------------------;

;-----------------------------------------------;
;----Процедура подсчета гласных и согласных-----;
;-----------------------------------------------;
glasn_sogl proc
  push dx
nacname:
  xor dx,dx
  pop dx
  cmp dl,0
  je konname
  dec dl
  push dx
  xor dx,dx
  mov dl,[si]
  mov di,si
  add di,dx
m0:
  inc si
  mov dh,[si]
  push di
  xor di,di
m1:
  inc di
  cmp dh,glasn[di]
  je ustanovka
  cmp di,bx
  jb m1
  jmp m2
ustanovka:
  xchg si,bp
  mov ch,glas[si]
  inc ch
  mov glas[si],ch
  xchg si,bp
  jmp m3
m2:
  xchg si,bp
  mov ch,sogl[si]
  inc ch
  mov sogl[si],ch
  xchg si,bp
m3:
  pop di
  cmp si,di
  ;Прыжок если si < di
  jb m0
  inc si
  inc bp
  jmp nacname
konname:
  ret
glasn_sogl endp
;-----------------------------------------------;
;----------------Еонец процедуры----------------;
;-----------------------------------------------;

;-----------------------------------------------;
;--------Процедура вычисления разности----------;
;-----------между моим возрастом и--------------;
;---------возрастом всех членов семьи-----------;
;-----------------------------------------------;
raznost proc
  xor si,si
  xor di,di
  mov al,kchle
  mov si,ax
  xor ax,ax
  mov ah,mold[di]
  dec si
cikl:
  mov al,mold[si]
  sub al,ah
  mov mrazn[di],al
  dec si
  inc di
  cmp si,0
  jne cikl
  call sravraz
  ret
raznost endp
;-----------------------------------------------;
;---------------Конец процедуры-----------------;
;-----------------------------------------------;

;-----------------------------------------------;
;-------Процедура сравнения максимальной--------;
;------------------разности---------------------;
;-----------------------------------------------;
sravraz proc
  xor ax,ax
  mov al,kchle
  sub ax,2
  xor si,si
  xor bx,bx
  mov bl,mrazn[si]
  inc si
sravraz1:
  cmp bl,mrazn[si]
  ja net
  mov bl,mrazn[si]
net:
  inc si
  cmp si,ax
  jb sravraz1
  cmp bl,zraz
  ja endsrav
  call firstnd
  call twothree
  call zamena
endsrav:
  ret
sravraz endp
;-----------------------------------------------;
;---------------Конец процедуры-----------------;
;-----------------------------------------------;

;-----------------------------------------------;
;----------Процедура замены первого и-----------;
;---последнего бита в массиве день рождения-----;
;-----------------------------------------------;
firstnd proc
  xor si,si
  xor ax,ax
  mov al,kchle
firstend1:
  xor bx,bx
  mov bl,mmoun[si]
  shr bl,1
  jc sl1
  shl bl,2
  jc sl2
  shr bl,1
  jmp konecfe
sl2:
  shr bl,1
  add bl,1h
  jmp konecfe
sl1:
  shl bl,2
  jc sl3
  shr bl,1
  add bl,80h
  jmp konecfe
sl3:
  shr bl,1
  add bl,81h 
konecfe:
  inc si
  cmp si,ax
  jb firstend1
  ret
firstnd endp
;-----------------------------------------------;
;---------------Конец процедуры-----------------;
;-----------------------------------------------;

;-----------------------------------------------;
;----------Процедура замены 2 и 3 бита----------;
;-----------в массиве месяц рождения------------;
;-----------------------------------------------;
twothree proc
  xor si,si
twothree1:
  xor mmoun[si],0Ch
  inc si
  cmp si,ax
  jb twothree1
  ret
twothree endp
;-----------------------------------------------;
;---------------Конец процедуры-----------------;
;-----------------------------------------------;


;-----------------------------------------------;
;-----Процедура замены четных бит в 1, а--------;
;-----------------нечетных в 0------------------;
;-----------------------------------------------;
zamena proc
;01010101 = 55h
  xor si,si
zamena1:
  mov mmoun[si],55h
  inc si
  cmp si,ax
  jb twothree1
  ret
zamena endp
;-----------------------------------------------;
;---------------Конец процедуры-----------------;
;-----------------------------------------------;


;-----------------------------------------------;
;--------Процедура вычисления возраста----------;
;-------------всех членов семьи-----------------;
;----------Результат в массиве mold-------------;
;-----------------------------------------------;
vozrast proc
  xor si,si
  xor di,di
  xor ax,ax
  mov al,kchle
  shl ax,1 ;Умножение содержимого ax на 2
  xor bx,bx
  xor cx,cx
nachalo:
  mov bx,mcury
  mov cx, myear[si]
  sub bx, cx
  mov mold[di],bl
  inc si
  inc si
  inc di
  cmp si,ax
  jb nachalo
  call raznost
  ret
vozrast endp
;-----------------------------------------------;
;--------------Конец процедуры------------------;
;-----------------------------------------------;

endc:
;-----------------------------------------------;
;--------Завершение работы программы------------;
;-----------------------------------------------;
  mov ax,4c00h
  int 21h
end start

  
  