## **Stacks and queues**

## **07. października 2018r.**

---

### *Zawartość:*

---

1. ***Stack***
     - Klasa Stack przechowująca elementy typu int w oparciu o tablicę o ustalonym rozmiarze (w naszym przypadku 1,000,000).
     - Operacje stosu mają złożoność O(1).
     - Program stack.cxx wczytuje dane wygenerowane przez program genList.cxx ze standardowego wejścia (std::cin) i wypisuje wynik odpowiednich operacji na stosie na standardowe wyjście (std::cout).
     - Program stdstack.cxx wykorzystujący kontener std::stack\<int> sprawdza poprawność działania programu.
     - Maksymalnie naraz na stosie może się znajdować 10^6 elementów.

2. ***Queue***
     - Klasa Queue, która implementuje kolejkę w oparciu o bufor cykliczny.
     - Wszystkie operacje działają w czasie O(1).
     - Kolejka przechowuje elementy typu int.
     - Program queue.cxx wczytuje dane wygenerowane przez program genList.cxx ze standardowego wejścia (std::cin) i wypisuje wynik odpowiednich operacji na stosie na standardowe wyjście (std::cout).
     - Program stdqueue.cxx wykorzystujący kontener std::queue\<int> sprawdza poprawność działania programu.

3. ***Bracket sentence***
     - Program bracketSentence.cxx słuzy do generowania testowych danych wejściowych, czyli poprawne bądź błędne wyrażenie nawiasowe (napisów złożonych wyłącznie z nawiasów okrągłych '(' i ')' oraz kwadratowych '[' i ']' ).
     - Nawias zamykający musi odpowiadać nawiasowi otwierającemu tego samego typu.
     - Program sentenceChecker.cxx sprawdza czy zadane wyrażenie nawiasowe jest poprawne.

---

### *Jak skompilować, zlinkować i uruchomić programy w terminalu:*

---

1. ***Stack***
     - Aby skompilować i uruchomić program oraz sprawdzić poprawność wyników, nalezy wejść do folderu "Stos" i wpisać w terminalu:
          - make
          - ./genList.x 1000 > input.txt
          - ./stack.x < input.txt > stack.txt
          - ./stdstack.x < input.txt > stdstack.txt
          - diff -s stack.txt stdstack.txt
2. ***Queue***
     - Aby skompilować i uruchomić program oraz sprawdzić poprawność wyników, nalezy wejść do folderu "Kolejka" i wpisać w terminalu:
          - make
          - ./genList.x 1000 > input.txt
          - ./queue.x < input.txt > queue.txt
          - ./stdqueue.x < input.txt > stdqueue.txt
          - diff -s queue.txt stdqueue.txt
3. ***Bracket sentence***
     - Aby skompilować i uruchomić program oraz sprawdzić poprawność wyników, nalezy wejść do folderu "Wyrazenie nawiasowe" i wpisać w terminalu:
          - make
          - ./bracketSentence.x > input.txt
          - ./sentenceChecker.x < input.txt

---

### *Odpowiedzi na pytania z zestawu 1*

---

#### Pytanie: Opisz trzy sposoby obsługi cykliczności bufora

##### Odpowiedź

- Dwie zmienne kontrolujące początek i koniec. Jeśli jedna z nich jest równa rozmiarowi kolejki, to ustawiamy jej wartość na 0.
- Modulo. Gdy wstawiamy element do kolejki to nowa wartość tail jest równa tail+1%(rozmiar kolejki).
- Maska bitowa. Dwie zmienne - początek i koniec kolejki. Polega na tym, ze cykliczność kolejki jest kontrolowana przez funkcje mask, wykonującą działanie iloczynu bitowego.

#### Pytanie: Omów przykłady zastosowania stosu

##### Odpowiedź

- Iterator w pętli for
- Przy tworzeniu zmiennej lokalnej

#### Pytanie: Omów przykłady zastosowania kolejki

##### Odpowiedź

- Sklep z jedną kasą i bardzo dużą ilością klientów - klienci zaczną się ustawiać w kolejkę i właśnie w ten sposób będą podchodzić do kasy.
- Procesy do wykonania. Będą wykonywane jeden po drugim w kolejności "pierwszy ten, który przyszedł wcześniej".

#### Pytanie: Dlaczego operacja pop() z std::stack i std::queue nie zwraca wartości elementu?

##### Odpowiedź

- Poniewaz chcemy usunąć element, a nie potrzebujemy zwracać wartości.
  
#### Pytanie: Dlaczego operacja pop() z std::stack i std::queue nie zwraca referencji do elementu?

##### Odpowiedź

- Korzytamy z dynamicznej alokacji pamięci, a więc skoro usuwamy element z kolejki/stosu, to nie chcemy, aby jakakolwiek zmienna miała dostęp do tego obszaru pamięci.

---
