[org 0x7c00]            ; Offset for start of loaded boot sector at mem address 0x7c00
                        ; Offets are treated absolutely -- i.e. from the beginning of memory, but
                        ; our code gives the offset from the start of our loaded code, i.e. the 

mov bp, 0x800           ; Set bottom of stack to 0x800 -- slightly above where BIOS
mov sp, bp              ; loads the boot sector, so we won't be overwritten

mov ax, message         ; Load "Booting HarryOS..."
call print_str          ; Print

main:                   ; Loop infinitely
  jmp main

; print_str prints a null-terminated 
; string to the screen. Assumes that
; the string is at least 1-character
; long.
; --parameters--
; ax: address of string
print_str:
  pusha                 ; Push all registers, because we're polite
  mov bx, ax            ; Need ax for interrupts
print_str_loop:
  mov cx, [bx]          ; Load first 2 chars
                        ; Print first char
  mov ah, 0x0e          ; Set interrupt to BIOS teletype routine (tty)
  mov al, cl            ; Get first char
  int 0x10              ; Trigger interrupt
                        ; Return if next char is null terminator
  cmp ch, 0
  je return
                        ; Otherwise loop again
  inc bx                ; Increment memory address to access next char
  jmp print_str_loop
return:
  popa
  ret

message:
  db "Booting HarryOS...", 0

; Fill with 510 zeroes minus the size of the previous code
; $$ is beginning of current section, $-$$ is size of section so far.
times 510 - ($-$$) db 0
; Magic number that indicates this is a boot sector
dw 0xaa55
