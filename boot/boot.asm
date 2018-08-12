[org 0x7c00]
KERNEL_OFFSET equ 0x1000     ; The memory offet where we'll load the kernel

  mov [BOOT_DRIVE], dl
  
  mov bp, 0x9000
  mov sp, bp
  
  mov ax, BOOT_MSG_REAL
  call print_str
  call print_nl
  
  call load_kernel

  ; Change to video mode
  call change_to_video
  ; Draw a pixel
  push 0xa000
  pop es
  mov di, 50
  mov ax, 55
  mov [es:di], ax

  call switch_to_protected
  
  jmp $

; Imports
%include "print/print.asm"
%include "pm/gdt.asm"
%include "pm/print_pm.asm"
%include "pm/switch_to_protected.asm"
%include "disk/disk_load.asm"

[bits 16]
load_kernel:
  mov ax, MSG_LOAD_KERNEL
  call print_str

  mov bx, KERNEL_OFFSET
  mov dh, 15
  mov dl, [BOOT_DRIVE]
  call disk_load

  ret

[bits 16]
change_to_video:
  ; See https://stackoverflow.com/questions/38268762/write-graphics-pixels-in-16-bit-assembly
  mov ax, 0x13 ; Video
  int 0x10
  ret
 
[bits 32]
begin_pm:
  mov ebx, BOOT_MSG_PROT
  call print_str_pm
  call KERNEL_OFFSET         ; Jump to address of loaded kernel code
  jmp $

; Vars
BOOT_DRIVE:      db 0
BOOT_MSG_REAL:   db "Started in 16-bit Real Mode", 0
BOOT_MSG_PROT:   db "Loaded 32-bit Protected Mode", 0
MSG_LOAD_KERNEL: db "Loading kernel into memory...", 0

; Bootsector padding
times 510 - ($ - $$) db 0
dw 0xaa55
