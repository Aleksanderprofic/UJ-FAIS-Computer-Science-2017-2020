#=========================================================
#				Makefile do zestawu 6.4
#=========================================================

FLAGS := -Wall -c -O2
RM := rm -f

.PHONY: all

all: 1przywodca.x 2suma.x 3maxDlugoscRozOdc.x 4maxSegment.x

#=========================================================
# 			LINKOWANIE WYKONYWALNYCH PLIKÓW
#=========================================================

%.x: %.o
	g++ -std=c++11 -o $@ $^

#=========================================================
# 			KOMPILOWANIE OBIEKTOWYCH PLIKÓW
#=========================================================

%.o: %.cpp
	g++ -std=c++11 $(FLAGS) -o $@ $^

#=========================================================
# 	Czyści katalog z plików obiektowych i wykonywalnych
#=========================================================

.PHONY: clean
clean:
	$(RM) *.o *.x a.out *.txt
