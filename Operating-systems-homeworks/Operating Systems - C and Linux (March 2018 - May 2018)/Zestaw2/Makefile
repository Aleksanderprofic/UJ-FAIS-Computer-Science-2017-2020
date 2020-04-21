#=========================================================
#				  Makefile do zestawu 2
#=========================================================

CFLAGS := -O2 -Wall -c
RM := rm -f

.PHONY: all clean

all: obsluga.x wysylaj.x grupa.x

#=========================================================
# 			LINKOWANIE WYKONYWALNYCH PLIKÓW
#=========================================================

%.x: %.o procinfo.o
	gcc -std=c99 -s -o $@ $^

#=========================================================
# 			KOMPILOWANIE OBIEKTOWYCH PLIKÓW
#=========================================================

%.o: %.c procinfo.h
	gcc -std=c99 $(CFLAGS) -o $@ $<

#=========================================================
# 	Czyści katalog z plików obiektowych i wykonywalnych
#=========================================================
clean:
	$(RM) *.o *.x a.out
