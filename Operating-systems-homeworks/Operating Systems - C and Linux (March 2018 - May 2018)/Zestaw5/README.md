# ***Autor: Aleksander Profic***

## **ZESTAW 5**

## **07. maja 2018r.**

---

### *Zawartość:*

---

- ***Biblioteka dynamiczna libshmem.so***
  - Biblioteka dynamiczna zawierająca implementację następujących funkcji do obsługi pamięci dzielonej:
    - shmCreate(int id, int size) - tworzy pamięć dzieloną o rozmiarze size. Funkcja zwraca identyfikator pamięci dzielonej shmid.
    - shmOpen(int id) - uzyskuje dostęp do pamięci dzielonej i zwraca identyfikator pamięci dzielonej.
    - shmRm(int shmid) - usuwa dany segment pamięci dzielonej shmid.
    - shmAt(int shmid) - dowiązuje segment pamięci dzielonej shmid. Zwraca adres odwzorowania.
    - shmDt(int shmid) - usuwa dowiązanie do segmentu pamięci dzielonej dowiązanej pod adres.
    - shmSize(int shmid) - zwraca rozmiar pamięci dzielonej shmid.
    - shmInfo(int shmid) - wypisuje informacje o pamięci dzielonej: prawa dostępu, rozmiar, pid twórcy, liczbę dowiązań.
    - print() - wypisuje informacje o prawidlowym uzyciu programu
  - Funkcje korzystają z odpowiednich funkcji systemowych i informują o wykonywanych operacjach.

- ***SHMUSE***
  - Program, który używa powyższej biblioteki. Program przyjmuje 1 jednoliterowy argument i ewentualnie drugi argument:
    - ./shmuse.x c size - tworzy segment pamięci dzielonej o rozmiarze size bajtów.
    - ./shmuse.x d - Usuwa segment pamięci dzielonej
    - ./shmuse.x r - Wypisuje zawartość pamięci dzielonej na standardowe wyjście.
    - ./shmuse.x w < input.txt - Kopiuje zawartość standardowego wejścia do pamięci dzielonej. Sprawdzić rozmiar segmentu.
    - ./shmuse.x i - Wypisuje informacje o pamięci dzielonej.
    - ./shmuse.x - Wypisuje informacje o użyciu tego programu.
  - Makefile tworzy dwie wersje shmuse1.x i shmuse2.x dla obu sposobów wskazywania lokalizacji biblioteki dymaicznej.

- ***PRODUCENT I KONSUMENT***
  - Przy pomocy pamięci dzielonej oraz semaforów systemu UNIX zaimplementowany problem ,,Producenta i Konsumenta’’ dla N-elementowego bufora cyklicznego (tzn. po dojściu do końca bufora wracamy na jego początek) umieszczonego w pamięci dzielonej, gdzie elementem bufora jest pewna ustalona porcja bajtów.
  - Producent pobiera ,,surowiec’’ z pliku tekstowego magazyn.txt i wstawia go jako towar do bufora, a Konsument umieszcza pobrany z bufora towar w innym pliku tekstowym schowek.txt.
  - Po zakończeniu działania programów (wyczerpaniu zasobów ,,surowca“) oba pliki tekstowe są identyczne.
  - Oba procesy drukują odpowiednie komunikaty na ekranie, w tym towar, który przesyłają. Do zasymulowania różnych szybkości działania programów użyta funkcja usleep z losowym czasem usypiania.
  - Uzyte trzy semafory, pierwszy blokuje zapis (producent), gdy bufor cykliczny jest pełny, drugi blokuje odczyt (konsument), gdy bufor cykliczny jest pusty, a trzeci jest uzyty do zasygnalizowania konca procesu kopiowania.

---

### *Jak skompilować, zlinkować i uruchomić programy/biblioteki w terminalu:*

---

1. ***BIBLIOTEKA DYNAMICZNA LIBSHMEM.SO***
    - Aby utworzyć bibliotekę dzieloną libshmem.so należy wpisać w terminalu:
      - **make libshmem.so**
2. ***SHMUSE***
    - W terminalu wpisać:
      - **make libshmem.so shmuse.x**
      - I jedna opcja z:
        - ./shmuse.x c size
        - ./shmuse.x d
        - ./shmuse.x r
        - ./shmuse.x w < input.txt
        - ./shmuse.x i
3. ***PRODUCENT I KONSUMENT***
    - W terminalu wpisać:
      - **make libsem.a libshmem.so glowny.x producent.x konsument.x**
      - **./glowny.x**

---

### *Odpowiedzi na pytania z zestawu 5*

---

#### Pytanie: Szczegółowo opisz działanie semaforów z zadania 3

##### Odpowiedź

- Pierwszy semafor synchronizuje dostęp procesu producenta do bufora. Jeśli producent zapisze wszystkie komórki bufora cyklicznego, a konsument nie odczyta ani jednego z nich, producent zostanie zablokowany do momentu az konsument odczyta jakiś znak z pamięci dzielonej.
- Podobnie w przypadku drugiego semafora, który synchronizuje dostęp procesu konsumenta do bufora. Jeśli konsument odczyta wszystkie znaki zapisane przez producenta w buforze, będzie czekał, az znowu będą mozliwe znaki do odczytania lub ilość znaków odczytanych przez niego będzie równa ilości znaków zapisanych do bufora oraz wartość semafora 0 będzie równa wartości początkowej.

#### Pytanie: W jaki sposób niezależne procesy mają dostęp do tego samego segmentu pamięci dzielonej

##### Odpowiedź

- Poprzez uzyskanie dowiązania, czyli wskaźnika do pamięci dzielonej mogą wykonywać na niej operacje. Mogą go uzyskać, jeśli znają klucz, który w tym przypadku jest tworzony funkcją ftok.

#### Pytanie: Czym jest biblioteka dynamiczna? Jakie są jej zalety

##### Odpowiedź

- Rodzaj biblioteki, która łączona jest z programem wykonywalnym dopiero w momencie jego wykonania. Dane z bibliotek dynamicznych mogą być współdzielone przez różne programy jednocześnie. Biblioteki są ładowane do pamięci tylko raz, nawet jeśli są równocześnie współużytkowane. Nie są, tak jak w przypadku bibliotek statycznych, dołączane do programu w momencie kompilacji.

#### Pytanie: Jak utworzyć bibliotekę statyczną? Jak jej używać? Jakie są nazwy plików, które są bibliotekami dynamicznymi

##### Odpowiedź

- W poleceniu jest pytanie jak utworzyć bibliotekę statyczną. Wydaję mi się, ze chodziło o bibliotekę dynamiczną, poniewaz w poprzednim zestawie było pytanie o statyczną, dlatego napiszę o dynamicznej.
- Aby utworzyć bibliotekę dynamiczną, należy:
  - Stworzyć plik nazwa_biblioteki.h z prototypami wszystkich funkcji oraz nazwa_biblioteki.c z implementacją tych funkcji.
  - Skompilować plik źródłowy biblioteki (nazwa_biblioteki.c) do pliku obiektowego (nazwa_biblioteki.o).
  - Zlinkować plik obiektowy biblioteki z opcją -shared:
    - gcc -std=c99 -shared -o libnazwa_biblioteki.so nazwa_biblioteki.o
- Aby użyć własnej biblioteki libnazwa_biblioteki.so należy do pliku źródłowego naszego programu dołączyć plik nagłówkowy "nazwa_biblioteki.h" oraz przy linkowaniu dołączyć opcje: -L. -lnazwa_biblioteki przed nazwami bibliotek oraz -Wl,-rpath . (-R . na linuxie) po nazwach bibliotek.
- Nazwy plików, które są bibliotekami dynamicznymi mają przedrostek lib oraz rozszerzenie .so

---