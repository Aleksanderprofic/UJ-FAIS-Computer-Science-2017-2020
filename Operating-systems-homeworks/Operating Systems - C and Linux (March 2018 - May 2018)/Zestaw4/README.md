# ***Autor: Aleksander Profic***

## **ZESTAW 4**

## **22. kwietnia 2018r.**

---

### *Zawartość:*

---

- ***nazwa_biblioteki SEMAFOR***
  - nazwa_biblioteki statyczna **sem** zawierająca implementację następujących funkcji do obsługi semafora ogólnego:
    - semDecl(int id) - tworzy semafor. Zwraca identyfikator semafora semid.
    - semInit(int semid, int val) - inicjalizuje semafor wartością val.
    - semRm(int semid) - usuwa semafor.
    - semP(int semid) - opuszcza semafor: zmniejsza wartość semafora o 1 lub czeka.
    - semV(int semid) - podnosi semafor: zwiększa wartość semafora o 1 lub wznawia czekający proces.
    - semZ(int semid) - funkcja czeka na wyzerowanie semafora.
    - semInfo(int semid) - funkcja wypisuje wartość semafora oraz liczbę procesów czekających na opuszczenie i podniesienie.
    - semInfo2(int semid) - funkcja wypisuje wartość semafora oraz liczbę procesów czekających na podniesienie.
  - Funkcje korzystają z odpowiednich funkcji systemowych i informują o wykonywanych operacjach.
  - Gdy zainicjalizujemy semafor wartością 1, otrzymamy semafor binarny.
  - Gdy zainicjalizujemy semafor wartością większą niż 1, pozwolimy na jednoczesny dostęp do sekcji krytycznej więcej niż jednemu procesowi.

- ***SEMUSE***
  - Program, który używa powyższej biblioteki. Program przyjmuje 1 jednoliterowy argument:
    - 'i' - inicjalizuje semafor i wypisuje o nim informacje.
    - 'r' - usuwa semafor.
    - 'p' - opuszcza semafor i wypisuje o nim informacje.
    - 'v' - podnosi semafor i wypisuje o nim informacje.
    - 'z' - wykonuje operacje Z (czeka na wyzerowanie, opuszczenie semafora) i wypisuje informacje o semaforze.
    - 'q' - wypisuje informacje o semaforze.

- ***POWIELACZ***
  - Zadanie wzajemnego wykluczenia dla procesów. Jednocześnie co najwyżej jeden proces programu prog.x znajduje się w sekcji krytycznej.
  - Czas operacji na wspólnym zasobie jest symulowany za pomocą funkcji usleep().
  - Specjalny program powielacz.x do powielania procesów realizujących wzajemne wykluczanie w oparciu o funkcje fork() i execl() (nazwę programu do inicjowania procesów oraz liczbę procesów przekazuje przez argumenty programu ,,powielacza’’), np:
    - ./powielacz.x ./prog.x 4
  - Program ten na początku tworzy i inicjuje semafor, a na końcu go usuwa (kiedy wszystkie jego procesy potomne kończą swoje działanie).

---

### *Jak skompilować, zlinkować i uruchomić programy/biblioteki w terminalu:*

---

1. ***nazwa_biblioteki SEMAFOR***
    - Żeby utworzyć bibliotekę libsem.a, nalezy wpisać w terminalu:
      - **make libsem.a**
2. ***SEMUSE***
    - W terminalu wpisać:
      - **make libsem.a semuse.x**
      - **./semuse.x**
3. ***POWIELACZ***
    - W terminalu wpisać:
      - **make libsem.a powielacz.x prog.x**
      - **./powielacz.x ./prog.x ilość_procesów**

---

### *Odpowiedzi na pytania z zestawu 4*

---

#### Pytanie: Do czego służą semafory w systemach UNIX?

##### Odpowiedź:

- Semafory są strukturami danych wspólnie użytkowanymi przez kilka procesów. Najczęściej znajdują one zastosowanie w synchronizowaniu działania kilku procesów korzystających ze wspólnego zasobu, przez co zapobiegają niedozwolonemu wykonaniu operacji na określonych danych jednocześnie przez większą liczbę procesów.

#### Pytanie: Opisz operacje, które można wykonać na semaforach.

##### Odpowiedź:

- Na semaforach mozna wykonać następujące operacje:
  - opuszczenie semafora P(S) - kiedy proces próbuje uzyskać dostęp do sekcji krytycznej, sprawdza czy jest dostępne miejsce poprzez zmniejszenie wartości semafora. Jeśli jego wartość jest mniejsza niz to ile proces potrzebuje miejsca lub równa 0, to proces jest blokowany do czasu, az zwolni sie dla niego miejsce.
  - podniesienie semafora V(S) - kiedy proces opuszcza sekcję krytyczną zwiększa wartość semafora o tyle ile potrzebował, zeby uzyskac do niego dostep.
  - operacja Z(S) - wstrzymanie działania procesu do momentu, az wartość semafora będzie równa 0.

#### Pytanie: W jaki sposób niezależne procesy mogą korzystać ze wspólnych semaforów?

##### Odpowiedź:

- Semafory są strukturami danych wspólnie użytkowanymi przez kilka procesów korzystających ze wspólnego zasobu. Zapobiega to niedozwolonemu wykonaniu operacji na określonych danych jednocześnie przez większą ilość procesów. Przez odpowiednie wykorzystywanie semaforów można zapobiec sytuacji w której wystąpi zakleszczenie lub zagłodzenie.

#### Pytanie: Czym jest biblioteka statyczna? Jakie są jej zalety?

##### Odpowiedź:

- Biblioteka statyczna jest to rodzaj biblioteki funkcji, która łączona jest z programem w momencie linkowania. Zawiera funkcje, które potrzebne są do prawidłowego wykonywania programu.
- Jej zaletą jest to, ze jest od razu kompilowana i tak jakby wklejana do programu, dzięki czemu program moze byc uzywany wszędzie, bez względu na to, czy nazwa_biblioteki znajduje się na komputerze czy nie.

#### Pytanie: Jak utworzyć bibliotekę statyczną? Jak jej używać?

##### Odpowiedź:

- Aby utworzyć bibliotekę statyczną, należy:
  - Stworzyć plik nazwa_biblioteki.h z prototypami wszystkich funkcji oraz nazwa_biblioteki.c z implementacją tych funkcji.
  - Skompilować plik źródłowy biblioteki (nazwa_biblioteki.c) do pliku obiektowego (nazwa_biblioteki.o).
  - Dodać plik obiektowy biblioteki do biblioteki
    - ar rv libnazwa_biblioteki.a nazwa_biblioteki.o
- Aby użyć własnej biblioteki libnazwa_biblioteki.a należy do pliku źródłowego naszego programu dołączyć plik nagłówkowy "nazwa_biblioteki.h" oraz przy linkowaniu użyć opcji -l oraz wskazać katalog, gdzie ona się znajduję, np. aktualny opcją -L.
  - gcc test.c -L. -lnazwa_biblioteki

---