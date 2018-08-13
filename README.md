# 🔧 Simple Kernel
This is a learning project to understand the theory & implementation of operating systems.
The bootloader is written in x86 NASM, and the kernel in C.

**Learning Resources:**
- [OSDev Wiki](https://wiki.osdev.org/Main_Page)
- ["Writing a Simple Operating System - from Scratch"](http://www.cs.bham.ac.uk/%7Eexr/lectures/opsys/10_11/lectures/os-dev.pdf) (Nick Blundall)
    - [cfenollosa's guide](https://github.com/cfenollosa/os-tutorial)
- [Operating Systems, 3 Easy Pieces](http://pages.cs.wisc.edu/~remzi/OSTEP/) (Remzi, Andrea of UWisc)

## Installation
Tested on Ubuntu - doesn't work on Mac without painful environment setup.
See [cfenollosa's notes](https://github.com/cfenollosa/os-tutorial) and install
various `_i3686` replacements for `qemu`, `gcc` and `ld` if you go down this path.


**Requirements:**
- `gcc`
- `qemu`
- `ld`

```
$ git clone https://github.com/harrisonturton/simple-kernel.git
```

## Usage

```
$ cd simple-kernel
$ make run
```
You can also `make clean` to remove object files, binaries & disk images from the project folders.

## Goals

- [x] Load bootloader
- [x] Print character in BIOS
- [x] Print words in BIOS
- [x] Switch to 32-bit protected mode from 16-bit real mode
- [x] Load kernel
- [x] Print to screen
- [x] Setup system interrupt service routines (ISRs)
- [x] Setup interrupt requests (IRQs)
- [x] Handle timer interrupts
- [x] Handle keyboard interrupts
- [x] Display basic graphics
- [ ] Write a simple `fetch-decode-execute` terminal
- [ ] Basic filesystem
- [ ] Write utilities for terminal (i.e. `cd`, `ls`, text editor, etc.)
- [ ] Basic multitasking
- [ ] Swap to VESA
- [ ] Some sort of interactive GUI
- [ ] Long mode?
