###### Treść zadań jest umieszczona na [stronie dr Görlicha](http://th.if.uj.edu.pl/~atg/SO/ "Zadania")
---
## Autor: Aleksander Profic

### *Zawartość:*

1.  ***KOPIOWANIE PLIKÓW***
    - Program, który kopiuje zawartość jednego pliku do drugiego
    za pomocą funkcji open, read i write.
    - Obsługuje wszystkie możliwe błędy przy pomocy funkcji perror.
    - Program przyjmuje nazwy plików z linii komend, a w przypadku złej
    liczby argumentów wypisuje komunikat o prawidłowym użyciu programu.
    - Program składa się z jednego pliku źródłowego:
        - kopiuj.c
2.  ***MAKEFILE***
    - Zestaw poleceń automatyzujących kompilację i linkowanie programów.
    - Posiada funkcję all, która kompiluje wszystkie programy w zestawie przy pomocy komendy "make" oraz clean, która usuwa pliki tymczasowe, obiektowe i wykonywalne.
3.  ***INFORMACJE O PROCESIE***
    - Funkcja, która wypisuje identyfikatory UID, GID, PID, PPID i PGID dla aktualnego procesu oraz nazwę programu przekazaną jako argument.
    - Implementacja funkcji jest umieszczona w pliku źródłowym, a deklaracja znajduje się w pliku nagłówkowym.
    - Funkcja jest używana przez inne programy w zestawie.
    - Funkcja składa się z dwóch plików:
        - procinfo.c - plik źródłowy
        - procinfo.h - plik nagłówkowy
4.  ***PROCESY***
    - Program wypisujący identyfikatory UID, GID, PID, PPID i PGID dla danego procesu.
    - Tworzy procesy potomne w pętli przy pomocy funkcji fork() i wypisuje powyższe identyfikatory dla wszystkich procesów potomnych.
    - Przy użyciu kilku funkcji sleep() sprawia, że procesy potomne są adoptowane przez proces init oraz pojawiają się na ekranie grupowane pokoleniami od najstarszego do najmłodszego.
    - Nazwa programu argv[0] zostaje zmieniona na "parent" dla procesu macierzystego oraz "child" dla procesu potomnego. Została do tego użyta funkcja strcpy.
    - Aby procesy wypisywane były pokoleniami, ale nie były adoptowane przez proces init należy np. zostawić 2 funkcje sleep(1), jedną zaraz za pętlą for, a drugą w switchu, w case 0 po funkcji procinfo().
    - Aby procesy były adoptowane przez init, ale nie były wypisywane pokoleniami należy sprawić, żeby procesy potomne żyły dłużej od procesów macierzystych. Aby to wykonać wystarczy np. w switchu, w case 0 wstawić funkcję sleep(4), zaraz przed funkcją procinfo().
    - Program składa się z trzech plików:
        - procesy.c
        - procinfo.c oraz procinfo.h z zadania III.
5.  ***DRZEWKA PROCESÓW***
    - Zmodyfikowany program 4. tak, aby generował procesy w przedstawiony
    na stronie Pana dr Görlicha sposób.
    - W programie drzewko1 proces macierzysty generuje 3 procesy potomne, natomiast w programie drzewko2 proces macierzysty tworzy jeden proces potomny, który tworzy kolejny proces potomny, który tworzy kolejny proces potomny.
    - Program składa się z czterech plików:
        - drzewko1.c
        - drzewko2.c,
        - procinfo.c oraz procinfo.h z zadania III.
6.  ***PROCESY I EXECV***
    - Zmodyfikowany program 4. tak, aby komunikaty procesów były wypisywane przez program uruchamiany funkcją execv.
    - potomny.c zawiera jedynie funkcję main(), która wywołuje procinfo(), aby wypisać informacje o procesie.
    - macierzysty.c wywołuje w pętli, w procesach potomnych, program potomny.x (for + fork + execv), dodatkowo na samym początku wypisuje informacje o procesie używając procinfo().
    - Program składa się z czterech plików:
        - macierzysty.c
        - potomny.c, które tylko wywołuje procinfo()
        - procinfo.c oraz procinfo.h z zadania III.

---

### *Jak uruchomić programy w terminalu:*

1.  ***KOPIOWANIE***
    - make kopiuj.x
    - ./kopiuj.x nazwa_programu_kopiowanego nazwa_programu_docelowego
2.  ***MAKEFILE***
    - Aby skompilować i zlinkować wszystkie programy, a potem usunąć zbędne pliki obiektowe należy wykonać komendę: **make**
    - Aby wyczyścić zawartość katalogu (usunąć zbędne pliki obiektowe, tymczasowe i wykonywalne), należy wykonać: **make clean**
3.  ***INFORMACJE O PROCESIE***
    - Funkcja jest używana i kompilowana automatycznie przez inne programy.
4.  ***PROCESY***
    - make procesy.x
    - ./procesy.x
5.  ***DRZEWKA PROCESÓW***
    - make drzewko1.x drzewko2.x
    - ./drzewko1.x
    - ./drzewko2.x
6.  ***PROCESY I EXECV***
    - make macierzysty.x potomny.x
    - ./macierzysty.x ./potomny.x

---
**Odpowiedzi na pytania z zestawu 1**
---

#### Pytanie: Ile powstaje procesów w programie "Procesy" i dlaczego?

###### Odpowiedź:
- Funkcja fork działa w ten sposób, że tworzy kopię danego procesu i ta kopia zaczyna swoje działanie od następnej linii skopiowanego procesu macierzystego, np. jeśli proces utworzy swoją kopię w pierwszej iteracji pętli for, to proces potomny będzie miał do wykonania to, co pozostało do wykonania po wywołaniu funkcji fork oraz jeszcze 2 iteracje pętli.
Przechodząc do sedna...
- Proces macierzysty utworzy 3 kopie samego siebie, po jednej kopii w każdej iteracji pętli. Daje to 3 procesy potomne:
    1. proces potomny (z pierwszej iteracji pętli) utworzy w drugiej i trzeciej iteracji po jednej kopii. Pierwsza z jej kopii utworzy w trzeciej iteracji jeszcze jedną kopię. Daje to kolejne 3 procesy potomne.
    2. proces potomny (z drugiej iteracji pętli) utworzy w trzeciej iteracji jedną kopię. Daje to dodatkowy 1 proces potomny.
    3. proces potomny (z trzeciej iteracji pętli) nie utworzy już żadnej kopii.

**Łącznie daje to 7 procesów potomnych utworzonych przez funkcję fork.**

#### Pytanie: Ile powstaje procesów w programie "macierzysty" i dlaczego?

###### Odpowiedź:
- Funkcja execv uruchamia program potomny.x, on się wykonuje, a na końcu proces się kończy i nie powraca już do programu macierzysty.x.
Oznacza to, że proces macierzysty tworzy 3 procesy potomne w 3 iteracjach pętli for, natomiast procesy potomne wywołują program potomny.x, a po nim ich działanie się kończy i nie tworzą już innych procesów.

**Łącznie daje to 3 procesy potomne utworzone przez funkcję fork.**

---
