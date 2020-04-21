# ***Autor: Aleksander Profic***

## ***9. kwietnia 2018r.***

---

### *Zawartość:*

---

-   ***POTOKI NIENAZWANE***
    - Przy pomocy potoków nienazwanych zaimplementowany problem Producenta i Konsumenta.
    - Producent pobiera surowiec z pliku tekstowego magazyn.txt (*fgets*) i wstawia go jako towar do potoku (*write*). Konsument umieszcza pobrany z potoku towar (*read*) w innym pliku tekstowym schowek.txt (*fputs*).
    - Po zakończeniu działania tych funkcji oba pliki tekstowe są identyczne.
    - Oba procesy drukują odpowiednie komunikaty na ekranie, w tym towar, który przesyłają. Do zasymulowania różnych szybkości działania programów została użyta funkcja *usleep()* z losowym czasem usypiania (*rand*).
    - Producent i Konsument to dwa procesy tego samego programu. Aby otrzymać proces potomny została użyta funkcja *fork()*. Przed wykonaniem funkcji *fork()* został stworzony potok nienazwany przy użyciu funkcji *pipe()*.


-   ***POTOKI NAZWANE***
     - Przy pomocy potoków nazwanych zaimplementowany problem Producenta i Konsumenta z zadania 1.
     - Producent i Konsument to dwa niezależne programy.
     - Nazwa potoku jest przekazana jako argument programu.
     - Tworzy potok z poziomu programu (*mkfifo*), a następnie uruchamia procesy Producenta i Konsumenta w tym samym programie.

---
### *Jak uruchomić programy w terminalu:*
---

Upewnij się, że istnieją pliki "magazyn.txt", który zawiera jakieś dane, oraz "schowek.txt" w tym samym katalogu, co program, który wywołujesz.

1.  ***POTOKI NIENAZWANE***
     W terminalu wpisać:
     - **make prodkons.x**
     - **./prodkons.x**
2.  ***POTOKI NAZWANE***
     W terminalu wpisać:
     - Z poziomu programu
          - **make fifo.x producent.x konsument.x**
          - **./fifo.x**
     - Z poziomu powłoki
          - **make producent.x konsument.x**
          - utwórz potok np. **"mkfifo -m 0666 nazwa_potoku"**
          - otwórz drugi terminal:
               - w pierwszym uruchom np. proces producenta podając w argumencie nazwe utworzonego potoku: **./producent.x nazwa_potoku**
               - w drugim uruchom proces konsumenta podając w argumencie nazwę utworzonego potoku: **./konsument.x nazwa_potoku**
          - Pamiętaj, aby po zakończeniu programu usunąć plik potoku.

---
### *Odpowiedzi na pytania z zestawu 3*
---
#### Pytanie: Co zwraca funkcja pipe()?

###### Odpowiedź:
- Funkcja **pipe()** zwraca dwa deskryptory plików, które odnoszą się do dwóch strumieni danych (zapisu i odczytu).

#### Pytanie: Czym się różni funkcja pipe() od mkfifo()? Co robią te funkcje?

###### Odpowiedź:
- Funkcja **pipe()** tworzy dwa deskryptory plików: jeden do odczytu z potoku, a drugi do zapisu do potoku. Potok utworzony przez pipe może łączyć tylko procesy pokrewne.
- Funkcja **mkfifo()** tworzy plik potoku we wskazanej ścieżce. Potok ten może być wykorzystywany do przesyłania danych przez programy.
- Różnią się tym, że potoki stworzone przez funkcje **pipe()** nie są plikami oraz mogą łączyć tylko procesy pokrewne, natomiast tym stworzonym przez **mkfifo()** towarzyszą wpisy w wykazach plików odpowiednich katalogów. Zatem są traktowane jak zwykłe pliki i mogą też łączyć niezależne procesy.

#### Pytanie: Co oznacza akronim FIFO?

###### Odpowiedź:
- First in, first out - oznacza, że pierwsza rzecz, która wejdzie do bufora, pierwsza z niego wyjdzie.

#### Pytanie: Co to jest deskryptor?

###### Odpowiedź:
- Jest to pewna nieujemna liczba całkowita. Służy do odwoływania się do plików poprzez niektóre funkcje systemowe. Może zostać utworzony przy pomocy funkcji **open()**, która otwiera plik i zwraca jego deskryptor.

#### Pytanie: Jak i dlaczego zamykamy deskryptory w zadaniu 1.?

###### Odpowiedź:
- W zadaniu 1. zamykamy deskryptory przy pomocy funkcji **close()**, jeden, który jest nieużywany przez dany proces, na początku funkcji oraz drugi - używany przez proces, na końcu funkcji, gdy już jest niepotrzebny.
- Robimy to dlatego, że w przeciwnym wypadku program by się nie zakończył, bo czekałby na zamknięcie deskryptora.

#### Pytanie: Proszę sprawdzić co się stanie jeżeli nie zamkniemy deskryptorów w zadaniu 1.?

###### Odpowiedź:
- Program się nie zakończy, ponieważ nie zamknięcie deskryptora świadczy o tym, że powinny być przez niego dostarczone jakieś informacje, więc program czeka, aż deskryptor zostanie zamknięty.

#### Pytanie: Jak utworzyć i usunąć potok nazwany z linii komend a jak z poziomu programu?

###### Odpowiedź:
- Potok nazwany z linii komend można utworzyć wpisując komendę: **mkfifo [-m mode] nazwa_potoku**, gdzie mode jest opcjonalny i są to prawa dostępu do pliku, (np. 0666 domyślnie) tj. dla kogo ma być możliwy odczyt, zapis, wykonywanie.
Usunąć go można wpisując komendę z poziomu katalogu zawierającego plik potoku: **rm nazwa_potoku**.
- Potok nazwany z poziomu programu można utworzyć za pomocą funkcji **mkfifo("ścieżka_potoku", mode)**.
Usunąć go można za pomocą funkcji **unlink("ścieżka_potoku")** lub poprzez funkcję **execl("/bin/sh", "sh", "-c", "rm nazwa_potoku", NULL)**, która wywołuje komendę **rm nazwa_potoku** z poziomu powłoki.

---
