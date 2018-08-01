
; print_str prints a null-terminated 
; string to the screen. 
; long.
; --parameters--
; ax: address of string
print_str:
  pusha
  mov bx, ax            ; Need ax for interrupt
  mov ah, 0x0e          ; Set interrupt to BIOS teletype routine  (tty)
print_str_loop:
  mov al, [bx]          ; Get first char
  cmp al, 0             ; Check if null-termination
  je return             ; Return if so
  int 0x10              ; Otherwise print it
  inc bx                ; Increment pointer to next char
  jmp print_str_loop    ; and loop.

; print_nl prints a newline to the
; screen. A newline consists of a
; newline character + a carriage
; return.
print_nl:
  pusha
  mov ah, 0x0e          ; Set interrupt to BIOS teletype routine (tty)
  mov al, 0x0a          ; Newline character
  int 0x10              ; Print char
  mov al, 0x0d          ; Carriage return
  int 0x10              ; Print char
  jmp return

print_hex:
  mov bx, 4
  push ax
  mov ax, '0'
  call print_char
  mov ax, 'x'
  call print_char
  pop ax
  push esp
print_hex_loop:
  rol ax, 4
  push ax
  call print_hex_char
  pop ax
  dec bx
  cmp bx, 0
  jne print_hex_loop
  pop esp
  jmp return

; --parameters--
; ax: character to print
print_char:
  pusha
  mov ah, 0x0e
  int 0x10
  jmp return

; --parameters--
; ax: character to print
print_hex_char:
  pusha
  and ax, 0b1111
  add al, 48
  cmp al, 57
  jle skip_offset
  add al, 7
skip_offset:
  mov ah, 0x0e
  int 0x10
  jmp return

; return (as a subroutine) is
; needed for conditional
; returns.
return:
  popa
  ret
