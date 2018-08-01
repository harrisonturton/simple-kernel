[org 0x7c00]            ; Offset for start of loaded boot sector at mem address 0x7c00
                        ; Offets are treated absolutely -- i.e. from the beginning of memory, but
                        ; our code gives the offset from the start of our loaded code, i.e. the 

mov bp, 0x800           ; Set bottom of stack to 0x800 -- slightly above where BIOS
mov sp, bp              ; loads the boot sector, so we won't be overwritten

mov ax, boot_message    ; Load "Booting HarryOS..."
call print_str          ; Print
call print_nl

main:                   ; Loop infinitely
  jmp main

%include "boot_sect_str.asm"

boot_message:
  db "Booting custom OS...", 0

; Fill with 510 zeroes minus the size of the previous code
; $$ is beginning of current section, $-$$ is size of section so far.
times 510 - ($-$$) db 0
; Magic number that indicates this is a boot sector
dw 0xaa55
