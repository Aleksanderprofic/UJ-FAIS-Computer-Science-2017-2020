## Program na zaliczenie kursu Języka C

Autor: **Aleksander Profic**

##### *Zawartość:*

1.  bazadanych.c
    - Zawiera funkcje main, w której wywołane są funkcje potrzebne do działania programu.

2.  funkcje.h
    - Implementacja wszystkich funkcji, składających się na działanie programu.

---
##### *Jak uruchomić program:*

Kompilacja:
- gcc -ansi -pedantic -Wall bazadanych.c -o bazadanych

Uruchomienie:
- ./bazadanych

---
##### *Działanie programu:*

- Program to baza danych studentów, w której możemy umieszczać kolejne osoby.
- Po uruchomieniu ukazuje się menu, w którym należy wybrać interesującą nas opcję:
    1.  Wypisuje wszystkich studentów na liście.
    2.  Dodawanie studenta do listy.
    3.  Usuwanie studenta z listy.
    4.  Wyszukiwanie studenta na liście.
    5.  Zapisywanie zmian.
    6.  Zamykanie programu.
- Przy zapisywaniu zmian tworzony jest plik, w którym umieszczane są wszystkie dane, aby nie zostały utracone po wyłączeniu programu.

---
