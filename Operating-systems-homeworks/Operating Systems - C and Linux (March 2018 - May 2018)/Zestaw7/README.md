# ***Autor: Aleksander Profic***

## **ZESTAW 7**

## **16. maja 2018r.**

---

### *Zawartość:*

---

- ***Wykluczanie wątków za pomocą muteksów***
  - Przy pomocy muteksów zaimplementowane zadanie wzajemnego wykluczania dla wątków.
  - Wątek wykonując swoją sekcję prywatną wypisuje odpowiedni komunikat po lewej stronie okna konsoli, natomiast będąc w sekcji krytycznej, drukuje informacje po prawej stronie (w tym samym wierszu).
  - Każdy wątek kilka razy (ile dokładnie zdefiniowane za pomocą stałej LOOPS_NR) powtarza powyższy cykl.
  - Po prawej stronie okna konsoli w danym momencie zgłasza się co najwyżej jeden wątek, pozostałe natomiast zgłaszają się po lewej stronie.
  - Każdy z wątków na początku sekcji krytycznej przypisuje wartość zmiennej globalnej globalCounter swojemu prywatnemu licznikowi localCounter, następnie zwiększa wartość prywatnego licznika o 1, a po kilku sekundach przypisuje jego wartość wspólnemu licznikowi.
  - Po zakończeniu działania wszystkich wątków, wartość tego wspólnego licznika jest taka, jaka powinna być.

---

### *Jak skompilować, zlinkować i uruchomić program w terminalu:*

---

1. ***Wykluczanie wątków za pomocą muteksów (wykluczanie.c)***
    - Wpisać w terminalu:
      - make && ./wykluczanie.x (linux)
      - make; and ./wykluczanie.x (mac)

---

### *Odpowiedzi na pytania z zestawu 7*

---

#### Pytanie: Czym się różni wątek od procesu

##### Odpowiedź

- Wątek jest takim jakby podprocesem, czyli rozwidleniem procesu w jego przestrzeni adresowej, posiada własny stos, zestaw rejestrów, licznik programowy, indywidualne dane, zmienne lokalne, maskę sygnałów i informacje o stanie.

#### Pytanie: Opisać działanie, argumenty i wartość zwracaną przez funkcję pthread_create()

##### Odpowiedź

- Funkcja pthread_create dodaje do procesu nowy wątek.
- Argumenty funkcji:
  1. Wskaźnik na obiekt typu pthread_t (liczba całkowita bez znaku)
  2. Wskaźnik na dynamicznie rezerwowaną strukturę atrybutów wątku. Dla domyślnych wartości trzeba wpisać NULL.
  3. Wskaźnik na zdefiniowaną funkcję, która będzie wykonana jako nowy wątek. Funkcja powinna przyjmować jeden parametr w postaci wskaźnika na void i zwracać wskaźnik na void.
  4. Wskaźnik na void - rzeczywisty argument przekazywany do funkcji z pkt. 3.
- Wartość zwracana przez tę funkcję to w przypadku powodzenia wartość 0 i unikalny identyfikator do obiektu wskazywanego przez wskaźnik pierwszego argumentu, a w przypadku niepowodzenia wartość niezerowa.

#### Pytanie: Funkcja pthread_join() jest odpowiednikiem której funkcji dla procesów

##### Odpowiedź

- Jest odpowiednikiem funkcji wait().

#### Pytanie: Czym się różnią muteksy od semaforów

##### Odpowiedź

- Tym, ze dla muteksu wartość 0 oznacza, ze jest otwarty (dla semafora to była wartość dodatnia), natomiast 1 oznacza, ze jest zamknięty (dla semafora to była wartość 0).
- Muteks moze zostać zamknięty przez dowolny wątek będący w jego zasięgu, natomiast moze zostać otwarty tylko przez wątek, który go zamknął.
- Operacje wykonywane na muteksach są niepodzielne (atomowe).
- Muteksy posiadają równiez pewien zbiór atrybutów.

#### Pytanie: Jak stworzyć muteks

##### Odpowiedź

- Muteks mozna zadeklarować za pomocą zdefiniowanej zmiennej pthread_mutex_t, a zainicjować go np. za pomocą funkcji systemowej pthread__mutex_init(), gdzie jako pierwszy argument podajemy wskaźnik do wcześniej stworzonego muteksa, a jako drugi argument wskaźnik do struktury pthread_mutexattr_t, w której podane są atrybuty muteksa lub dla domyślnych wartości - NULL.

#### Pytanie: Opisać działanie operacji, które możemy wykonać na muteksach

##### Odpowiedź

- pthread_mutex_init słuzy do inicjowania muteksów, gdzie pierwszy argument jest wskaźnikiem na muteks, a drugi argument wskaźnikiem na obiekt atrybutów lub NULL dla domyślnych wartości.
- pthread_mutex_lock słuzy do zamykania muteksu. Wywołanie jej dla muteksu, który juz jest zamknięty spowoduje zablokowanie wątku do czasu otwarcia muteksu.
- pthread_mutex_unlock słuzy do otwierania muteksu, ale tylko przez wątek, który zamknął dany muteks. Wywołanie jej przez inny wątek moze mieć nieprzewidywalne skutki.
- pthread_mutex_trylock działa podobnie jak pthread_mutex_lock, ale nie powoduje blokowania wywołującego ją wątku, jeśli dany muteks jest juz zamknięty.
- pthread_mutex_destroy usuwa wskazany muteks - sprawia, ze staje się niezainicjowany, uzytkownik musi zadbać o zwolnienie pamięci wskazywanej przez wskaźnik muteksu.

#### Pytanie: Dlaczego musimy zdefiniować makro _REENTRANT

##### Odpowiedź

- Ta dyrektywa oznacza dany kod, jako kod wielokrotnego uzytku, czyli taki, do którego mozna wiele razy wchodzić.

#### Pytanie: Co oznacza typ void * (*) ()

##### Odpowiedź

- Wskaźnik do funkcji, która zwraca wskaźnik typu void.

#### Pytanie: Co to sa operacje atomowe? Czy są konieczne

##### Odpowiedź

- Są to operacje niepodzielne i są istotne w niektórych przypadkach, np: (źródło: wikipedia)
  - w przetwarzaniu równoległym zmiana obiektów współdzielonych przez różne procesy musi być atomowa, z punktu widzenia procesu niepodzielna (patrz: sekcja krytyczna, fetch-and-add, compare-and-swap) tak jak w naszym zadaniu wzajemnego wykluczania się wątków, choć w naszym przypadku uzyty został mechanizm synchronizacji.
  - w systemach baz danych wszystkie zmiany w obrębie transakcji muszą zostać w całości albo zatwierdzone, albo odrzucone, inni użytkownicy bazy danych nie mogą otrzymać danych niekompletnych
  - w niektórych systemach plików zmiany muszą zostać w całości zatwierdzone albo odrzucone, aby w przypadku awarii (np. zaniku zasilania) system plików pozostał spójny.

---