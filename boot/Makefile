bootblock: start.S main.c asm.h boot.h
	gcc -c -m32 -ggdb start.S
	gcc -c -m32 -O1 -ggdb main.c
	ld -melf_i386 -e start -Ttext 0x7C00 start.o main.o -o bootblock.o
	@objcopy -S -O binary -j .text bootblock.o bootblock
	@./genboot.pl bootblock

clean:
	rm -rf bootblock *.o
