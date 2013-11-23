#include <windows.h>
#include "r0.h"

__declspec(naked) void Ring0Proc()
{
	__asm {
		PUSHAD
        MOV     AX, 100
        MOV     BX, 100
        MOV     CX, AX
        MOV     AL, 0b6h
        out     43h, AL
        MOV     DX, 0012h
        MOV     AX, 34dch
        DIV     CX
        out     42h, AL
        MOV     AL,AH
        out     42h, AL
        in      AL, 61h
        MOV     AH, AL
        OR      AL, 03h
        out     61h, AL
        l1:
        MOV     ECX,0fffffh
        l2:
        LOOP    l2
        DEC     BX
        JNZ     l1
        MOV     AL, AH
        out     61h, AL
        POPAD
		ret
	}
}

int __stdcall WinMain(HINSTANCE, HINSTANCE, PTSTR, int)
{

	R0(Ring0Proc);
	return 0;
}

