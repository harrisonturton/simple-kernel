;
; Simple bootsector that prints a line
;
[org 0x7c00]            ; Offset for start of loaded bootsector at mem address 0x7c00
                        ; Offets are treated absolutely -- i.e. from the beginning of memory, but
                        ; our code gives the offset from the start of our loaded code, i.e. the 

; Initialization
mov [BOOT_DRIVE], dl    ; BIOS stores boot drive in dl. Save for later.

mov bp, 0x8000          ; Set the stack far away from us
mov sp, bp 

; mov ax, BOOT_MESSAGE    ; Load "Booting HarryOS..."
; call print_str          ; Print
; call print_nl

; Load data
mov bx, 0x9000          ; Load sectors  0x0000:0x9000 (ES:BX)
mov dh, 2
mov dl, [BOOT_DRIVE]
call disk_load

mov dx, [0x9000]        ; Print first loaded word (expect to be 0xdada, see EOF)
call print_hex

mov dx, [0x9000 + 512]  ; Print first word from 2nd loaded sector
call print_hex

; Main
jmp $

%include "lib_str.asm"
%include "lib_disk.asm"

; Global variables
BOOT_DRIVE:   db 0
BOOT_MESSAGE: db "Booting custom OS...", 0

; Bootsector padding & magic number
times 510 - ($-$$) db 0
dw 0xaa55

times 256 dw 0xdada
times 256 dw 0xface
