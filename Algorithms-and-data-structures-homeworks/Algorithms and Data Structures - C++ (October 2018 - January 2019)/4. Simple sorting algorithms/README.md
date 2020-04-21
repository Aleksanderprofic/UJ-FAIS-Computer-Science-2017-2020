## **Simple sorting algorithms**

## **15. listopada 2018r.**

---

### *Zawartość:*

---

1. ***Proste sortowanie***
     - Zaimplementowane następujące algorytmy sortowania dla liczb całkowitych:
          - Sortowanie bąbelkowe -> bubble_sort.cxx
          - Sortowanie przez wstawianie -> insertion_sort.cxx
          - Sortowanie przez zliczanie -> counting_sort.cxx
          - Sortowanie przez wybieranie -> selection_sort.cxx
     - Program, który używa funkcji bibliotecznej std::sort -> std_sort.cxx

2. ***Złozoność obliczeniowa***
     1. ***Bubble sort***
          - O(n^2)
     2. ***Insertion sort***
          - O(n^2)
     3. ***Counting sort***
          - O(n)
     4. ***Selection sort***
          - O(n^2)
     5. ***Std::sort***
          - O(n*logn)
     - Liczba porównań algorytmów dla n danych wejściowych:
          - W przypadku optymistycznym:
               1. ***Bubble sort***
                    - n*(n+1)/2
               2. ***Insertion sort***
                    - n-1
               3. ***Counting sort***
                    - 0
               4. ***Selection sort***
                    - 
               5. ***Std::sort***
                    - 
          - W Przypadku pesymistycznym:
               1. ***Bubble sort***
                    - n*(n+1)/2
               2. ***Insertion sort***
                    - (n-1)*n/2
               3. ***Counting sort***
                    - 
               4. ***Selection sort***
                    - 
               5. ***Std::sort***
          - Średnia liczba porównań w przypadku losowym:
               1. ***Bubble sort***
                    - n*(n+1)/2
               2. ***Insertion sort***
                    - (n^2+n-2)/2
               3. ***Counting sort***
                    - 
               4. ***Selection sort***
                    - 
               5. ***Std::sort***

Wyznaczyć liczbę porównań wykonanych przez każdy z algorytmów z Zadania 1. w przypadku pesymistycznym i optymistycznym w funkcji rozmiaru danych wejściowych n.
Oszacować średnią liczbę porównań wykonanych przez każdy z algorytmów z Zadania 1. w przypadku losowym.
Jaka jest złożoność obliczeniowa tych algorytmów?

---

### *Jak skompilować, zlinkować i uruchomić programy w terminalu:*

---

Nalezy wejść do folderu "Zestaw 4" i wpisać w terminalu komendę "make" oraz np. ./genRandom 10 100 > input.txt, a następnie dla:

1. ***Bubble sort***
     - ./bubble_sort.x "liczba elementów" < input.txt > bubble.txt
2. ***Insertion sort***
     - ./insertion_sort.x "liczba elementów" < input.txt > insertion.txt
3. ***Counting sort***
     - ./counting_sort.x "liczba elementów" < input.txt > counting.txt
4. ***Selection sort***
     - ./selection_sort.x "liczba elementów" < input.txt > selection.txt
5. ***Std::sort***
     - ./std_sort.x "liczba elementów" < input.txt > std.txt

---
