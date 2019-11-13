
asembler = i686-elf-as
gcc = i686-elf-gcc 
gcc_parametry = -std=gnu99 -ffreestanding -O2 -Wall -Wextra

pliki = boot.o kernel.o terminal.o gdt.o stdio.o

myos.bin: linker.ld $(pliki)
	$(gcc) -T $< -o $@ -ffreestanding -O2 -nostdlib $(pliki) -lgcc

boot.o: boot.s
	$(asembler) -o $@ $<

kernel.o: kernel.c 
	$(gcc) -c $< -o $@ $(gcc_parametry)
stdio.o : stdio.c
	$(gcc) -c $< -o $@ $(gcc_parametry)
terminal.o: terminal.c
	$(gcc) -c $< -o $@ $(gcc_parametry)

gdt.o: gdt.c terminal.h
	$(gcc) -c $< -o $@ $(gcc_parametry)


.PHONY: all clean
# .PHONY: all clean dist check testdrivers todolist


clean:
	rm -f $(pliki)


