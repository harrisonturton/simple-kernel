#!/bin/bash
echo "Attemping to compile..."
make
echo "Finished compiling."
echo "Running..."
qemu-system-x86_64 -drive file=main.bin,index=0,media=disk,format=raw
