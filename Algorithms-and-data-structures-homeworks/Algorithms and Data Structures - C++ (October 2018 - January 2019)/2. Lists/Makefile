#=========================================================
#				Makefile do zestawu 2
#=========================================================

CPPFLAGS := -O2 -Wall -c
RM := rm -f

.PHONY: all

all: genList.x ArrayList.x LinkedList.x CursorList.x stdList.x

#=========================================================
# 			LINKOWANIE WYKONYWALNYCH PLIKÓW
#=========================================================

%.x: %.o
	g++ -std=c++11 -o $@ $^

#=========================================================
# 			KOMPILOWANIE OBIEKTOWYCH PLIKÓW
#=========================================================

%.o: %.cxx
	g++ -std=c++11 $(CPPFLAGS) -o $@ $^

#=========================================================
# 	Czyści katalog z plików obiektowych i wykonywalnych
#=========================================================

.PHONY: clean

clean:
	$(RM) *.o *.x a.out *.txt
