#=========================================================
#				Makefile do zestawu 5
#=========================================================

CFLAGS := -O2 -Wall -c
RM := rm -f

NAME1 := shmuse
NAME2 := glowny

OBJ1 := $(NAME1).o
OBJ2 := $(NAME2).o

EXEC1d1 := $(NAME1)d1.x
EXEC1d2 := $(NAME1)d2.x
EXEC2d1 := $(NAME2)d1.x
EXEC2d2 := $(NAME2)d2.x

LIBSONAME := shmem
LIBSO := lib$(LIBSONAME).so


.PHONY: all

all: libsem.a libshmem.so glowny.x producent.x konsument.x shmused1.x shmused2.x

#=========================================================
# 			LINKOWANIE WYKONYWALNYCH PLIKÓW
#=========================================================

$(EXEC1d1): $(OBJ1) libshmem.so
	gcc -std=c99 -L. -lshmem -o $@ $^ -Wl,-rpath .

$(EXEC1d2): $(OBJ1) libshmem.so
	gcc -std=c99 -L. -lshmem -o $@ $^
	export LD_LIBRARY_PATH=.

%.x: %.o libshmem.so libsem.a
	gcc -std=c99 -L. -lshmem -lsem -o $@ $^ -Wl,-rpath .

#=========================================================
# 			KOMPILOWANIE OBIEKTOWYCH PLIKÓW
#=========================================================

%.o: %.c
	gcc -std=c99 $(CFLAGS) -o $@ $<

#=========================================================
# 			        BIBLIOTEKI
#=========================================================

$(LIBSO): $(LIBSONAME).o
	gcc -std=c99 -shared -o $@ $<

$(LIBSONAME).o: $(LIBSONAME).c
	gcc -std=c99 $(CFLAGS) -fPIC -o $@ $<

lib%.a: %.o
	ar rv $@ $^

#=========================================================
# 	       Czyści katalog ze zbędnych plików
#=========================================================
.PHONY: clean

clean:
	$(RM) *.o *.x a.out *.a *.so
