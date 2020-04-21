# ***Autor: Aleksander Profic***

## **ZESTAW 2**

## **23. października 2018r.**

---

### *Zawartość:*

---

1. ***AbstractList***
     - Wirtualna klasa definiująca kilka operacji, które klasa dziedzicząca, musi zaimplementować.

2. ***ArrayList***
     - Klasa ArrayList, będąca implementacją tablicową listy.
     - Przyjęty sztywny maksymalny rozmiar listy/tablicy.
     - Elementy tablicy przechowują jedynie wartości elementów.
     - Z góry zaznaczone, aby nie uzywac klasy std::vector.

3. ***CursorList***
     - Klasa CursorList, będąca implementacją kursorową listy.
     - Przyjęty sztywny maksymalny rozmiar listy/tablicy.
     - Podobnie jak w implementacji tablicowej, węzły są umieszczone w tablicy, jednak oprócz przechowywanego obiektu węzeł pamięta również indeks kolejnego węzła.
     - Z góry zaznaczone, aby nie uzywać klasy std::vector.

4. ***LinkedList***
     - Klasa LinkedList, która implementuje listę dwukierunkową w reprezentacji wskaźnikowej dla elementów typu int.
     - Konstruktor domyślny, który tworzy pusta listę.
     - Klasa Node przechowuje liczbę typu int i wskaźniki do poprzedniego i następnego elementu w liście.

5. ***stdList***
     - Program, który do realizacji listy uzywa klasy szablonowej std::list.

---

### *Jak skompilować, zlinkować i uruchomić programy w terminalu:*

---

1. ***ArrayList***
     - Aby skompilować i uruchomić program oraz sprawdzić poprawność wyników, nalezy wejść do folderu "Zestaw 2" i wpisać w terminalu:
          - make
          - ./genList.x 1000 > input.txt
          - ./ArrayList.x < input.txt > ArrayList.txt
          - ./stdList.x < input.txt > stdList.txt
          - diff -s ArrayList.txt stdList.txt
2. ***CursorList***
     - Aby skompilować i uruchomić program oraz sprawdzić poprawność wyników, nalezy wejść do folderu "Zestaw 2" i wpisać w terminalu:
          - make
          - ./genList.x 1000 > input.txt
          - ./CursorList.x < input.txt > CursorList.txt
          - ./stdList.x < input.txt > stdList.txt
          - diff -s CursorList.txt stdList.txt
3. ***LinkedList***
     - Aby skompilować i uruchomić program oraz sprawdzić poprawność wyników, nalezy wejść do folderu "Zestaw 2" i wpisać w terminalu:
          - make
          - ./genList.x 1000 > input.txt
          - ./LinkedList.x < input.txt > LinkedList.txt
          - ./stdList.x < input.txt > stdList.txt
          - diff -s LinkedList.txt stdList.txt
4. ***stdList***
     - Aby skompilować i uruchomić program nalezy wejść do folderu "Zestaw 2" i wpisać w terminalu:
          - make
          - ./genList.x 1000 > input.txt
          - ./stdList.x < input.txt > stdList.txt
          - ./stdList.x < input.txt

---