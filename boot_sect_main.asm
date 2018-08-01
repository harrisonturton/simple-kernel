;
; Simple bootsector that prints a line
;
[org 0x7c00]            ; Offset for start of loaded bootsector at mem address 0x7c00
                        ; Offets are treated absolutely -- i.e. from the beginning of memory, but
                        ; our code gives the offset from the start of our loaded code, i.e. the 

mov ax, boot_message    ; Load "Booting HarryOS..."
call print_str          ; Print
call print_nl

jmp $                   ; Loop infinitely

%include "lib_str.asm"

; Data
boot_message:
  db "Booting custom OS...", 0

; Padding & magic number (indicates boot sector)
times 510 - ($-$$) db 0
dw 0xaa55
