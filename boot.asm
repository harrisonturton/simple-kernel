[org 0x7c00]

mov bp, 0x9000
mov sp, bp

mov ax, BOOT_MSG_REAL
call print_str
call print_nl

call switch_to_protected

jmp $

; Imports
%include "print.asm"
%include "gdt.asm"
%include "print_pm.asm"
%include "switch_to_protected.asm"
 
[bits 32]
begin_pm:
  mov ebx, BOOT_MSG_PROT
  call print_str_pm
  jmp $

; Vars
BOOT_MSG_REAL: db "Started in 16-bit Real Mode", 0
BOOT_MSG_PROT: db "Loaded 32-bit Protected Mode", 0

; Bootsector padding
times 510 - ($ - $$) db 0
dw 0xaa55
