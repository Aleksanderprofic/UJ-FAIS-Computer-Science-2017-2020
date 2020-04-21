#=========================================================
#				Makefile do zestawu 6
#=========================================================

CFLAGS := -O2 -Wall -c
RM := rm -f

.PHONY: all

all: libMsg.a libMsg.so klient.x serwer.x

#=========================================================
# 			LINKOWANIE WYKONYWALNYCH PLIKÓW
#=========================================================

klient.x: klient.o libmsg.so
	gcc -std=c99 -L. -lmsg -o $@ $^ -Wl,-rpath .

serwer.x: serwer.o libmsg.a
	gcc -std=c99 -L. -lmsg -o $@ $^ 

#=========================================================
# 			KOMPILOWANIE OBIEKTOWYCH PLIKÓW
#=========================================================

%.o: %.c
	gcc -std=c99 $(CFLAGS) -o $@ $<

#=========================================================
# 			        BIBLIOTEKI
#=========================================================

libMsg.so: Msg.o
	gcc -std=c99 -shared -o $@ $<

lib%.a: %.o
	ar rv $@ $^

Msg.o: Msg.c
	gcc -std=c99 $(CFLAGS) -fPIC -o $@ $<

#=========================================================
# 	       Czyści katalog ze zbędnych plików
#=========================================================
.PHONY: clean

clean:
	$(RM) *.o *.x a.out *.a *.so
