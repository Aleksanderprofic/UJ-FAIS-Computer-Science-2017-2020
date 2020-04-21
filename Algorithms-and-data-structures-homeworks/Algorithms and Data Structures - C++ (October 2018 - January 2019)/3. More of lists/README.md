## **More of lists**

## **02. listopada 2018r.**

---

### *Zawartość:*

---

1. ***Implementacja tablicowa listy uporządkowanej***
     - Klasa SortedArrayList, będąca implementacją tablicową listy, której elementy typu int są posortowane rosnąco.

2. ***Implementacja wskaźnikowa listy uporządkowanej***
     - Klasa SortedLinkedList ma implementować listę podwójnie wiązaną w reprezentacji wskaźnikowej o elementach typu int, które są umieszczone w porządku rosnącym. Operacje identyczne jak dla SortedArrayList.

3. ***Łączenie list***
     - Generuje przypadkowy zestaw danych wejściowych, w postaci:
          1. Liczba l1 oznaczająca liczbę elementów w pierwszej liście
          2. l1 liczb, posortowane elementy pierwszej listy
          3. Liczba l2 oznaczająca liczbę elementów w drugiej liście
          4. l2 liczb, posortowane elementy drugiej listy
     - Jako argument przyjmuje maksymalny rozmiar obu list (łącznie).
     - Wypisuje listę powstałą po scaleniu dwóch list z powtórzeniami, t.j. wszystkie jej elementy (posortowane)
     - Wypisuje listę powstałą po scaleniu dwóch list bez powtórzeń (posortowane)

4. ***Wydajność***
     - Powtórzony eksperyment opisany w pierwszych 40s prezentacji Bjarna Stroustrupa, twórcy języka C++, dotyczącej różnicy w wydajności między implementacją tablicową i wskaźnikową listy.
     - Dla n = 50k elementów porównałem czas wykonania zadania dla obu implementacji. To znaczy:
          - Dodanie n liczb losowych do listy uporządkowanej (metodą push())
          - Usunięcie n elementów podając losową pozycję. Pozycja musi być mniejsza od aktualnej liczby elementów (metodą erase())
          - Zmierzenie czasu wykonania zadania

---

### *Jak skompilować, zlinkować i uruchomić programy w terminalu:*

---

Nalezy wejść do folderu "Zestaw 3" i wpisać w terminalu komendę "make" oraz np. ./generator 30 > input.txt, a następnie dla:

1. ***Implementacja tablicowa listy uporządkowanej***
     - ./sortedArrayList.x < input.txt
2. ***Implementacja wskaźnikowa listy uporządkowanej***
     - ./sortedLinkedList.x < input.txt
3. ***Łączenie list***
     - ./merging.x < input.txt
4. ***Wydajność***
     - time ./sortAddRemoveA.x
     - time ./sortAddRemoveL.x

---
