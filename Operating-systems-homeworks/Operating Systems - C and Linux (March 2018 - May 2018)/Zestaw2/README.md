###### Treść zadań jest umieszczona na [stronie dr Görlicha](http://th.if.uj.edu.pl/~atg/SO/ "Zadania")
---
## Autor: Aleksander Profic

### *Zawartość:*

1.  ***OBSŁUGA SYGNAŁÓW***
    - Program do obsługi sygnałów z możliwościami:
    - wykonania operacji domyślnej dla sygnału
    - ignorowania sygnału
    - przechwycenia i własnej obsługi sygnału
    - Program przyjmuje dwa argumenty z linii komend: rodzaj akcji (d/i/p) i numer sygnału.
    - W przypadku złej liczby argumentów wypisuje komunikat o prawidłowym użyciu programu.
    - Program składa się z trzech plików:
        - obsluga.c
        - procinfo.c oraz procinfo.h z Zestawu 1.
2.  ***WYSYŁANIE SYGNAŁÓW***
    - Uruchamia program obsluga.x poprzez funkcję execl() w procesie potomnym i wysyła do niego sygnały poprzez funkcję systemową kill() z procesu macierzystego.
    - Numer sygnału oraz opcję obsługi przekazuje jako argumenty programu.
    - Przed wysłaniem sygnału sprawdza czy dany proces istnieje.
    - Program składa się z czterech plików:
        - wysylaj.c
        - obsluga.c
        - procinfo.c oraz procinfo.h z Zestawu 1.
3.  ***GRUPA***
    - Uruchamia grupę kilku procesów i wysyła sygnały do całej grupy po uprzednim sprawdzeniu jej istnienia. Użyte są funkcje sleep() i wait().
    - Uodparnia proces macierzysty, poprzez ustawienie ignorowania sygnałów, ponieważ też należy on do tej grupy procesów.
    - Program składa się z jednego pliku:
        - grupa.c

---

### *Jak uruchomić programy w terminalu:*

1.  ***OBSŁUGA SYGNAŁÓW***
    - make obsluga.x
    - ./obsluga.x rodzaj_akcji(d/i/p) nr_sygnalu
2.  ***WYSYŁANIE SYGNAŁÓW***
    - make wysylaj.x obsluga.x
    - ./wysylaj.x rodzaj_akcji(d/i/p) nr_sygnalu
3.  ***GRUPA***
    - make grupa.x
    - ./grupa.x rodzaj_akcji(d/p) nr_sygnalu


---
**Odpowiedzi na pytania z zestawu 2**
---

#### Pytanie: Co robi, a czego nie robi funkcja signal()?
###### Odpowiedź:
- Funkcja signal() jest używana do modyfikowania sposobu w jaki proces zareaguje na sygnał. Ustala obsługę danego sygnału.
- Funkcja signal() nie wysyła sygnałów.

#### Pytanie: Jak działa funkcja kill()? Jaką rolę pełni jej pierwszy argument?
###### Odpowiedź:
- Funkcja kill wysyła sygnał do procesu lub grupy procesów oraz sprawdza, czy dany proces lub grupa procesów istnieją.
- Pierwszy argument funkcji mówi, gdzie sygnał ma zostać wysłany.

#### Pytanie: Jak i dlaczego należy uodpornić proces macierzysty w programie grupa.c na sygnał?
###### Odpowiedź:
- Należy uodpornić go poprzez wywołanie, w miejscu dostępnym tylko dla procesu macierzystego, funkcji signal
- Należy go uodpornić, ponieważ np. wysłanie sygnału SIGINT do grupy procesów spowodowałoby zakończenie działania procesu macierzystego przed kilkoma procesami potomnymi. W efekcie powstałoby kilka procesów osieroconych, bo macierzysty nie czekałby na zakończenie ich pracy.

#### Pytanie: Jak wznowić proces zatrzymany sygnałem SIGSTOP?
###### Odpowiedź:
- Należy wysłać do procesu sygnał SIGCONT.

#### Pytanie: Opisać sygnał SIGCHLD.
###### Odpowiedź:
- Gdy proces kończy swoje działanie lub zatrzymuje się, sygnał zostaje wysłany do jego procesu rodzicielskiego. Ponieważ SIGCHLD jest domyślnie ignorowany, procesy muszą go jawnie przechwycić i obsłużyć, jeśli są zainteresowane tym, co dzieje się z ich potomkami. Procedura obsługi tego sygnału wywołuje zazwyczaj funkcję wait(), aby ustalić id procesu oraz kod powrotu dla potomka.

---
