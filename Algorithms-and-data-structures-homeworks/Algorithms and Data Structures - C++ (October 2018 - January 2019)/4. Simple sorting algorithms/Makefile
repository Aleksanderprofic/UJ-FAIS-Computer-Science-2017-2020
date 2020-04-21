#=========================================================
#				Makefile do zestawu 4
#=========================================================

CPPFLAGS := -O2 -Wall -c
RM := rm -f

.PHONY: all

all: genRandom.x bubble_sort.x counting_sort.x insertion_sort.x selection_sort.x std_sort.x

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
