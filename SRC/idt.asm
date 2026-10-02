global a
global b
global c
global d

global dum1
global dum2

global int0x60

global keyboard

global key

extern int0x60_handler

;dum1 = no error pushed
;dum2 = error pushed so clean up error

dum1:
    iret

dum2:
    add esp, 4
    iret

;save needed registers and call c handler
int0x60:
    mov [a], eax
    mov [b], ebx
    mov [c], ecx
    mov [d], edx

    call int0x60_handler

    mov eax, [a]
    mov ebx, [b]
    mov ecx, [c]
    mov edx, [d]

    iret

;small ps2 keyboard handler
keyboard:
    in al, 0x60
    mov [key], al

    mov al, 0x20
    out 0x20, al

    iret

a: dd 0
b: dd 0
c: dd 0
d: dd 0
key: db 0
