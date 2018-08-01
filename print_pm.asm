
[bits 32]
; Some constants
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

; Prints a null-terminated string pointed to by EDX
print_str_pm:
  pusha
  mov edx, VIDEO_MEMORY
print_str_pm_loop:
  mov al, [ebx]        ; Store char at EBX in AL
  mov ah, WHITE_ON_BLACK
  cmp al, 0            ; If al is null, then end of string
  je done
  mov [edx], ax
  add ebx, 1
  add edx, 2
  jmp print_str_pm_loop
done:
  popa
  ret
