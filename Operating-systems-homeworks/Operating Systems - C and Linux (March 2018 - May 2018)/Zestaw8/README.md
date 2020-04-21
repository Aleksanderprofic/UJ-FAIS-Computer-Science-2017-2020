# ***Autor: Aleksander Profic***

## **ZESTAW 8**

## **22. maja 2018r.**

---

### *Zawartość:*

---

- ***Algorytm piekarni***
  - Przed wejściem do sekcji krytycznej proces otrzymuje numer.
  - Posiadacz najmniejszego numeru wchodzi do sekcji krytycznej.
  - Jeżeli procesy Pi i Pj otrzymały ten sam numer oraz i < j, to Pi będzie obsłużony najpierw.
  - Schemat numerowania generuje niemalejące ciągi kolejnych liczb naturalnych, tzn. 1, 2, 3, 3, 3, 4, 5, 5, ...
  - Notacja: (a,b) < (c,d), jeżeli a < c lub jeżeli a = c i b < d.

---

### *Jak skompilować, zlinkować i uruchomić programy/biblioteki w terminalu:*

---

1. ***Biblioteka pamięci dzielonej***
    - Aby utworzyć bibliotekę pamięci dzielonej nalezy wpisać w terminalu:
      - make libshmem.so
2. ***Algorytm piekarni (main.c i process.c)***
    - Aby skompilować i uruchomić program, nalezy wpisać w terminalu:
      - make
      - ./main.x
    - Aby zakończyć program nalezy uzyć sekwencji klawiszy "CTRL + C".

---