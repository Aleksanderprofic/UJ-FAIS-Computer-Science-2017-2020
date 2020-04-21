#====================================================================
#				        Makefile do zestawu 1
#====================================================================

CFLAGS := -O2 -Wall -c
RM := rm -f

.PHONY: all clean

all: kopiuj.x procesy.x drzewko1.x drzewko2.x macierzysty.x potomny.x

#====================================================================
# 			       LINKOWANIE WYKONYWALNYCH PLIKÓW
#====================================================================

# wszystko oprócz kopiuj.x
%.x: %.o procinfo.o
	gcc -std=c99 -s -o $@ $^

# kopiuj.x
%.x: %.o
	gcc -std=c99 -s -o $@ $<

#====================================================================
# 			       KOMPILOWANIE OBIEKTOWYCH PLIKÓW
# np.
# procinfo.o: procinfo.c procinfo.h
#	gcc -std=c99 -O2 -Wall -c -o procinfo.o procinfo.c
#====================================================================

# wszystko oprócz kopiuj.o
%.o: %.c procinfo.h
	gcc -std=c99 $(CFLAGS) -o $@ $<

# kopiuj.o
%.o: %.c
	gcc -std=c99 $(CFLAGS) -o $@ $<

#====================================================================
# Czyści katalog z plików obiektowych, tymczasowych i wykonywalnych
#====================================================================
clean:
	$(RM) *.o *.x *~
