# ***Autor: Aleksander Profic***

## **ZESTAW 6**

## **12. maja 2018r.**

---

### *Zawartość:*

---

- ***Biblioteka statyczna libMsg.a i dynamiczna libMsg.so (Msg.c, Msg.h)***
  - Biblioteki dynamiczna i statyczna zawierające implementację następujących funkcji do obsługi pamięci dzielonej:
    - msgCreate(int id) - Tworzy kolejkę komunikatów. Funkcja zwraca identyfikator kolejki komunikatów.
    - msgRm(int msqid) - usuwa kolejkę komunikatów o identyfikatorze msqid.
    - msgSend(int msqid, komunikat *msg) - wysyła komunikat wskazywany przez msg do kolejki o identyfikatorze msqid.
    - msgRecv(int msqid, komunikat *msg, int mtype) - odbiera z kolejki msqid komunikat typu mtype i zapisuje do msg.
    - msgInfo(int msqid) - wypisuje informacje o kolejce komunikatów.
  - Biblioteka dynamiczna została uzyta do programu klient.x, natomiast biblioteka statyczna do programu serwer.x.

- ***Serwer i klient (serwer.c, klient.c)***
  - Programy realizujące zadanie typu klient-serwer.
    - Proces klient wczytuje z klawiatury ciąg znaków i wysyła go do procesu serwera.
    - Serwer odbiera ten ciąg znaków i przetwarza go zamieniając w nim wszystkie litery na wielkie (toupper()), a następnie wysyła tak przetworzony ciąg znaków z powrotem do klienta.
    - Klient odbiera przetworzony ciąg znaków i wypisuje go na ekranie.
  - Serwer obsługuje wielu klientów naraz.

---

### *Jak skompilować, zlinkować i uruchomić programy/biblioteki w terminalu:*

---

1. ***Biblioteka statyczna libMsg.a i dynamiczna libMsg.so***
    - Aby utworzyć bibliotekę dzieloną libMsg.so należy wpisać w terminalu:
      - **make libMsg.so**
    - Aby utworzyć bibliotekę statyczną libMsg.a należy wpisać w terminalu:
      - **make libMsg.a**
2. ***Serwer i klient***
    - W terminalu wpisać:
      - **make**
    - Uruchomić kilka terminali (tyle ile procesów klienta chcemy uruchomić) oraz jeden na proces serwera.
    - Uruchomić proces serwera komendą: ./serwer.x.
    - Uruchomić procesy klienta komendą: ./klient.x.
    - W kazdym terminalu klienta wpisać ciąg znaków, który chcemy wysłać do serwera.

---

### *Odpowiedzi na pytania z zestawu 6*

---

#### Pytanie: Opisać działanie, argumenty i wartość zwracaną przez funkcję msgget()

##### Odpowiedź

- Zakończona sukcesem funkcja msgget tworzy kolejkę komunikatów (lub uzyskuje do niej dostęp, jezeli taka juz istnieje) dla danego klucza key (który mozna utworzyć np funkcją ftok()) i zwraca identyfikator tej kolejki, będący pewną liczbą całkowitą nieujemną. Zakończona porazką zwraca wartość -1. Parametr msgflg określa sposób wykonania funkcji oraz prawa dostępu do kolejki komunikatów.
- Flagi msgflg (ze skryptu prof. Płaczka):
  - IPC_CREAT - utworzenie kolejki komunikatów, jeśli nie istnieje lub uzyskanie dostępu do istniejącej juz kolejki
  - IPC_EXCL - uzyta w polączeniu z IPC CREAT zwraca błąd, jezeli dla danego klucza istnieje juz kolejka komunikatów
  - Prawa dostępu - podobnie jak dla plików, np. 0666: mozliwość wykonywania operacji czytania i pisania przez wszystkie procesy.

#### Pytanie: Opisać znaczenie pól w strukturze komunikatów

##### Odpowiedź

- long mtype to zmienna typu long int, która przechowuje typ komunikatu. Jest ona po to, aby mozna było selekcjonować, które wiadomości dany proces ma odebrać.
- long pid to zmienna typu long int, która przechowuje id procesu, który wysłał komunikat. Jest ona po to, aby proces serwera wiedział, gdzie powinien odesłać komunikat.
- char mtext[SIZE] to tablica znaków o rozmiarze SIZE, która jest właściwą treścią komunikatu.

#### Pytanie: Jaką rolę pełni argument msgtyp w funkcji msgrcv()

##### Odpowiedź

- Określa, jakie komunikaty dany proces moze odbierać.
  - Jeśli msgtyp = 0 to proces będzie pobierał pierwszy komunikat dowolnego typu
  - Jeśli msgtyp > 0 to proces będzie pobierał pierwszy komunikat, którego typ będzie równy wartości msgtyp;
  - Jeśli msgtyp < 0 to proces będzie pobierał pierwszy komunikat, którego typ będzie mniejszy lub równy wartości bezwzględnej msgtyp.

---