WARNINGS = -Wall -Wpedantic -Wextra -Wshadow -Wconversion
CFLAGS = $(WARNINGS) -std=c99 -g3 -O0

NASM = nasm
NASMFLAGS = -f elf64

all: ex3_c ex3_S ex3_N

ex3_c: ex3.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $<
ex3_S: ex3.S
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $<
ex3_N: ex3_N.o
	$(CC) $(CFLAGS) -o $@ $<
ex3_N.o: ex3.nasm
	$(NASM) $(NASMFLAGS) -o $@ $<

clean:
	$(RM) ex3_*

