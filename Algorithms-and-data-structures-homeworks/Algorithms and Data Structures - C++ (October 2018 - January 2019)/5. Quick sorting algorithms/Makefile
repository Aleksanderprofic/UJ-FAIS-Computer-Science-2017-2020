#=========================================================
#				Makefile do zestawu 5
#=========================================================

FLAGS := -Wall -c -O3 -march=native
RM := rm -f

.PHONY: all

all: genRandom.x qsort.x std_sort.x iterative_quick_sort.x recursive_quick_sort.x recursive_merge_sort.x heap_sort.x genSorted.x genReverse.x genSortedFirst.x genSortedLast.x

#=========================================================
# 			LINKOWANIE WYKONYWALNYCH PLIKÓW
#=========================================================

%.x: %.o
	g++ -std=c++11 -o $@ $^

qsort.x: qsort.o
	gcc -o $@ $^

#=========================================================
# 			KOMPILOWANIE OBIEKTOWYCH PLIKÓW
#=========================================================

%.o: %.cxx
	g++ -std=c++11 $(FLAGS) -o $@ $^

%.o: %.cpp
	g++ -std=c++11 $(FLAGS) -o $@ $^

qsort.o: qsort.c
	gcc $(FLAGS) -o $@ $^

#=========================================================
# 	Czyści katalog z plików obiektowych i wykonywalnych
#=========================================================

.PHONY: clean
clean:
	$(RM) *.o *.x a.out *.txt
