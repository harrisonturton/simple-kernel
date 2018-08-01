
; disk_load loads the DH sectors to ES:BX
; from drive DL.
; --paramaters--
; bx: offset. E.g. 0x9000 reads from 0x0000:0x9000.
; dh: number of sectors to read
; dl: boot drive
disk_load:
  pusha
  push dx          ; Store DX so we can recall how many sectors we
                   ; requested to read.
  mov ah, 0x02     ; BIOS read sector function
  mov al, dh       ; Read DH sectors
  mov ch, 0        ; Cylinder 0
  mov dh, 0        ; Head 0
  mov cl, 2        ; Start reading from second sector
                   ; (i.e. after boot sector)
  int 0x13         ; BIOS interrupt to read the disk
                   ; [es:bx] <- pointer to buffer with data

  jc disk_error    ; Jump if error (i.e. carry flag set)

  pop dx           ; Restore number of sectors we requested
  cmp dh, al       ; If didn't read the right number of sectors...
  jne sector_error ; Error

  popa
  ret              ; Otherwise return

; disk_error prints the disk error message
; and hangs.
disk_error:
  mov bx, DISK_ERROR_MESSAGE
  call print_str
  call print_nl
  call print_hex
  call print_nl
  mov bx, 0
  mov bh, ah       ; ah = error code
  mov ax, bx
  call print_hex
  jmp $

; sector_error prints the sector error
; message, and then hands
sector_error:
  mov ax, SECTOR_ERROR_MESSAGE
  call print_str
  call print_nl
  jmp $

; %include "lib_str.asm"

DISK_ERROR_MESSAGE:   db "Disk read error!", 0
SECTOR_ERROR_MESSAGE: db "Sector read error!", 0
