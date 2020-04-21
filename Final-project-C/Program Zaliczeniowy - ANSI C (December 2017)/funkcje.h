#ifndef FUNKCJE_H
#define FUNKCJE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* kolory w terminalu */
#define KG "\x1B[32m"   /* zielony */
#define KY "\x1B[33m"   /* zolty */
#define KR "\x1B[31m"   /* czerwony */
#define KB "\x1B[34m"   /* niebieski */
#define CY "\x1B[36m"   /* jasny niebieski */
#define LP "\x1B[35m"   /* fioletowy */
#define RESET "\x1B[0m" /* powrot do normalnego koloru */

/* struktura Student, na ktorej opiera sie program */
typedef struct Student {
    char name[20], lastName[20];
    int ID, age;
    float avg;
    struct Student* next;
} Student;

/* wczytanie z pliku danych studentow i zapisanie ich do listy l */
Student* load(FILE *fPointer, Student *l) {
    if(!feof(fPointer)) {
        l = malloc(sizeof(Student));
        fscanf(fPointer, "%i %s %s %i %f ", &l->ID, l->name, l->lastName, &l->age, &l->avg);
        l->next = load(fPointer, l->next);
        return l;
    }
    else return NULL;
    return l;
}

/* zapisanie listy do pliku tekstowego, zeby nie stracic danych po zamknieciu programu */
void save(FILE *fPointer, Student *l) {
        if(l != NULL) {
            fprintf(fPointer, "%i %s %s %i %.2f\n", l->ID, l->name, l->lastName, l->age, l->avg);
            save(fPointer, l->next);
        }
}

/* wypisanie menu, czyli wszystkich mozliwosci uzytkownika */
void printMenu() {
    printf("\n1. Lista studentow\n");
    printf("2. Dodaj studenta do listy\n");
    printf("3. Usun studenta z listy\n");
    printf("4. Wyszukaj studenta\n");
    printf("5. Zapisz zmiany\n\n");
    printf("6. ZAMKNIJ PROGRAM\n");
    printf("(Jesli nie chcesz utracic wprowadzonych danych, zapisz program przed zamknieciem!)\n");
    printf(KR "Wybierz akcje: " RESET);
}

/* wypisanie wszystkich studentow, znajdujacych sie na liscie jednokierunkowej */
void printList(Student *l) {
    if(l != NULL) {
        printf("|    \x1b[1m %-7d \x1b[22m%-20s %-21s %-10d%-12.2f |\n", l->ID, l->name, l->lastName, l->age, l->avg);
        printList(l->next);
    }
}

/* uzyskanie ID od uzytkownika */
int getID() {
    char temp[30];  /* pomocnicza tablica do przechowania lancucha znakow wpisanego przez uzytkownika */
    do {
        printf("Podaj ID studenta: ");
        scanf(" %s", temp);

        if(strlen(temp) <= 3) {     /* sprawdzenie czy wpisana wartosc ma dlugosc 3, bo ma nalezec do przedzialu [1,999] */
            if(isdigit(temp[0]) && temp[0] != '0') {    /* sprawdzenie czy 1. znak jest cyfrą i rozny od 0 */
                if(temp[1] == '\0') {
                    return (temp[0] - '0');   /* jesli uzytkownik wpisal cyfre to zwraca 1. znak z tablicy jako int */
                }
                else {
                    if(isdigit(temp[1])) {
                        if(temp[2] == '\0') {
                            /* jesli uzytkownik wpisal liczbe dwucyfrowa to zwraca ((1. znak * 10) + 2.znak) jako int  */
                            return ((temp[0] - '0')*10 + (temp[1] - '0'));
                        }
                        else {
                            if(isdigit(temp[2])) {
                                /* jesli uzytkownik wpisal liczbe trzycyfrową to zwraca ((1. znak * 100) + (2.znak * 10) + 3. znak) jako int  */
                                return ((temp[0] - '0')*100 + (temp[1] - '0')*10 + (temp[2] - '0'));
                            }
                            else {
                                printf(KR "ID musi sie skladac z cyfr i zawierac w przedziale [1;999]! Sprobuj ponownie!\n" RESET);
                            }
                        }
                    }
                    else {
                        printf(KR"ID musi sie skladac z cyfr i zawierac w przedziale [1;999]! Sprobuj ponownie!\n"RESET);
                    }
                }
            }
            else {
                printf(KR"ID musi sie skladac z cyfr i zawierac w przedziale [1;999]! Sprobuj ponownie!\n"RESET);
            }
        }
        else {
            printf(KR"ID musi sie skladac z cyfr i zawierac w przedziale [1;999]! Sprobuj ponownie!\n"RESET);
        }
    } while (1);
}

/* funkcja sprawdzajaca czy lancuch ma odpowiednia dlugosc */
void checkString(char temp[]) {
    char letter;    /* 1 gdy znak w tablicy jest litera, 0 gdy nie jest */
    int i;
    do {
        letter = 1;
        scanf(" %s", temp);
        while(strlen(temp) > 20) {
            printf(KR"Zbyt dlugi lancuch! Mozesz uzyc max 20 liter. Sprobuj ponownie!\n"RESET);
            scanf(" %s", temp);
        }
        for(i = 0; temp[i] != '\0'; i++) {
            if(!isalpha(temp[i]))  {
                printf(KR"Niepoprawny lancuch, zawierajacy znak niebedacy litera. Sprobuj ponownie!\n"RESET);
                letter = 0;
                break;
            }
        }
    } while(letter == 0);
}

/* dodanie imienia studenta do komorki l->name */
void addName(Student *l) {
    char temp[50];
    checkString(temp);
    strcpy(l->name, temp);
}

/* dodanie imienia studenta do komorki l->name */
void addLastName(Student *l) {
    char temp[50];
    checkString(temp);
    strcpy(l->lastName, temp);
}

/* dodanie sredniej studenta do komorki l->avg */
float addAverage(Student *l) {
    char temp[30];
    int i;
    float pom;
    do {
        printf("Srednia ocen: ");
        scanf(" %s", temp);
        if(strlen(temp) <= 4) {
            if(isdigit(temp[0])) {
                if(temp[1] == '.' || temp[1] == '\0') {
                    /* gdy temp[1] == '\0' czyli wpisana liczba to cyfra */
                    if(temp[1] == '\0') {
                        /* sprawdza czy 1. znak tablicy to cyfra 2, 3, 4 lub 5 */
                        if(temp[0] > 53 || temp[0] < 50) {
                            printf(KR"Srednia powinna zawierac sie w przedziale [2.0, 5.0]! Sprobuj ponownie!\n"RESET);
                        }
                        else {
                            /* zwraca 1 znak z tablicy jako float */
                            return (float)(temp[0]-'0');
                        }
                    }
                    /* gdy temp[1] == '.' */
                    else {
                        pom = (float)(temp[0] - '0');
                        for(i = 2; i < 4; i++) {
                            if(isdigit(temp[i])) {
                                if (i == 2) pom += (float)(temp[2]-'0')/10;
                                if (i == 3) pom += (float)(temp[3]-'0')/100;
                            }
                            else if (temp[i] == '\0') {
                                break;
                            }
                            else {
                                printf(KR"Srednia powinna skladac sie z samych liczb i kropki! Sprobuj ponownie!\n"RESET);
                                break;
                            }
                        }
                        if(i == 4 || temp[i] == '\0') {
                            if(pom < 2.0 || pom > 5.0) {
                                printf(KR"Srednia powinna zawierac sie w przedziale [2.0, 5.0]! Sprobuj ponownie!\n"RESET);
                            }
                            else return pom;
                        }
                    }
                }
                else {
                    printf(KR"Srednia powinna zawierac sie w przedziale [2.0, 5.0]! Sprobuj ponownie!\n"RESET);
                }
            }
            else {
                printf(KR"Srednia powinna zawierac sie w przedziale [2.0, 5.0]! Sprobuj ponownie!\n"RESET);
            }
        }
        else {
            printf(KR"Srednia powinna skladac sie z samych liczb i kropki! Sprobuj ponownie!\n"RESET);
        }
    } while (1);
}

/* dodanie wieku studenta do komorki l->age */
void addAge(Student *l) {
    char temp[30];
    int i;
    do {
        printf("Wiek: ");
        scanf(" %s", temp);

        if(temp[2] == '\0') {
            for(i = 0; i < 2; i++) {
                if(!isdigit(temp[i])) {
                    printf(KR"Wiek powinien zawierac sie w przedziale [13; 99]! Sprobuj ponownie!\n"RESET);
                    temp[2] = 1;
                    break;
                }
            }
            if(i == 2) {
                /* przepisanie wieku z tablicy temp do inta */
                if((l->age = (temp[0]-'0')*10 + (temp[1]-'0')) < 13) {
                    printf(KR"Wiek powinien zawierac sie w przedziale [13; 99]! Sprobuj ponownie!\n"RESET);
                    temp[2] = 1;
                }
            }
        }
        else {
            printf(KR"Wiek powinien zawierac sie w przedziale [13; 99]! Sprobuj ponownie!\n"RESET);
        }
    } while (temp[2] != '\0' || l->age < 13);
}

/* dodawanie studenta do listy */
Student* addStudent(int id, Student *l) {
    if(l == NULL) {
        /* alokowanie pamieci do nowej komorki w liscie */
        l = malloc(sizeof(Student));
        l->next = NULL;
        l->ID = id;

        /* wpisywanie imienia studenta */
        printf("Imie: ");
        addName(l);

        /* wpisywanie nazwiska studenta */
        printf("Nazwisko: ");
        addLastName(l);

        /* wpisywanie wieku studenta */
        addAge(l);

        /* wpisywanie sredniej studenta */
        l->avg = addAverage(l);
        printf("\x1b[3m\n\nStudent dodany do listy!\n\n\x1b[23m"RESET);
        return l;
    }
    else {
        if(l->ID > id) {
            Student *nl = NULL;

            /* alokowanie pamieci do nowej komorki w liscie i kopiowanie wartosci z l do niej*/
            nl = malloc(sizeof(Student));
            nl->ID = l->ID;
            strcpy(nl->name, l->name);
            strcpy(nl->lastName, l->lastName);
            nl->age = l->age;
            nl->avg = l->avg;
            nl->next = l->next;

            /* przekazywanie nowych wartosci do listy */
            l->ID = id;

            /* wpisywanie imienia studenta */
            printf("Imie: ");
            addName(l);

            /* wpisywanie nazwiska studenta */
            printf("Nazwisko: ");
            addLastName(l);

            /* wpisywanie wieku studenta */
            addAge(l);

            /* wpisywanie sredniej studenta */
            l-> avg = addAverage(l);

            l->next = nl;
            printf("\x1b[3m\n\nStudent dodany do listy!\n\n\x1b[23m"RESET);
            return l;
        }
        else if (l->ID < id) {
            l->next = addStudent(id, l->next);
            return l;
        }
        else {
            printf(KR"\nNa liscie jest juz student z takim ID!\n"RESET);
            return l;
        }
    }
}

/* wyszukiwanie studenta na liscie poprzez jego ID */
Student* findStudentByID(int id, Student *l) {
    if (l == NULL) {
        printf("\n __________________________________________________________________\n");
        printf("%-67s|\n", "|");
        printf("%-67s|\n|", "|");
        printf(KR"\t\tNA LISCIE NIE MA STUDENTA Z ID %i!\t\t   "RESET, id);
        printf("|\n%-67s|\n", "|");
        printf("|__________________________________________________________________|\n\n");
        return NULL;
    }
    else {
        /* jesli wpisane id jest rowne ID w liscie to zwraca wskaznik do tego elementu */
        if(l->ID == id) {
            return l;
        }
        else return findStudentByID(id, l->next);
    }
}

/* wyszukiwanie na liscie studenta o podanym nazwisku */
void findStudentByLastName(int check, char temp[], Student *l) {
    if (l == NULL){
        if(check == 0) {
            printf("|");
            printf(KR"\t    NA LISCIE NIE MA ANI JEDNEGO STUDENTA O PODANYM NAZWISKU"RESET);
            printf("\t\t|\n");
        }
    }
    else {
        /* jesli nazwisko podane przez uzytkownika zgadza sie z nazwiskiem w liscie to wypisuje wszystkie dane */
        if(strcasecmp(l->lastName, temp) == 0) {    /* sprawdzenie bez wzgledu na wielkosc liter */
            check = 1;
            printf("|");
            printf(KG"\t ID:"RESET);
            printf(" %-4i", l->ID);
            printf(KY"Imie:"RESET);
            printf(" %-21s ", l->name);
            printf(KB"Wiek:"RESET);
            printf(" %-3i", l->age);
            printf(CY"Srednia ocen:"RESET);
            printf(" %.2f\t|\n", l->avg);
            findStudentByLastName(check, temp, l->next);
        }
        else findStudentByLastName(check, temp, l->next);
    }
}

/* wyszukiwanie na liscie studenta o podanym imieniu */
void findStudentByName(int check, char temp[], Student *l) {
    if (l == NULL) {
        if(check == 0) {
            printf("|");
            printf(KR"\t     NA LISCIE NIE MA ANI JEDNEGO STUDENTA O PODANYM IMIENIU"RESET);
            printf("\t\t|\n");
        }
    }
    else {
        /* jesli imie podane przez uzytkownika zgadza sie z imieniem w liscie to wypisuje wszystkie dane */
        if(strcasecmp(l->name, temp) == 0) {    /* sprawdzenie bez wzgledu na wielkosc liter czy lancuchy sa takie same */
            check = 1;

            printf("|");
            printf(KG"      ID:"RESET);
            printf(" %-4i", l->ID);
            printf(KR"Nazwisko:"RESET);
            printf(" %-21s ", l->lastName);
            printf(KB"Wiek:"RESET);
            printf(" %-3i", l->age);
            printf(CY"Srednia ocen:"RESET);
            printf(" %.2f\t|\n", l->avg);
            findStudentByName(check, temp, l->next);
        }
        else findStudentByName(check, temp, l->next);
    }
}

/* glowna funkcja zarzadzajaca wyszukiwaniem studentow */
void find(Student *l) {
    char answer[5], temp[20];
    Student *pom;
    int id;

    printf("\x1b[3m\nWyszukiwanie studenta...\n\x1b[23m");
    printf("1. Przez ID\n");
    printf("2. Przez nazwisko\n");
    printf("3. Przez imie\n");
    printf("4. Wroc do menu\n");
    scanf(" %s", answer);
    /* sprawdzenie czy dlugosc wpisanej wartosci jest rowna 1, a jesli tak to czy to cyfra 1, 2, 3 lub 4 */
    while(strlen(answer) != 1 || answer[0] < 49 || answer [0] > 52) {
        printf("\x1b[3m\n\nWpisano niepoprawna wartosc, sprobuj ponownie :) \n\n\x1b[23m"RESET);
        printf("1. Przez ID\n");
        printf("2. Przez nazwisko\n");
        printf("3. Przez imie\n");
        printf("4. Wroc do menu\n");
        scanf(" %s", answer);
    }

    switch(answer[0]) {
        /* wyszukiwanie przez ID */
        case '1':
            id = getID();
            pom = findStudentByID(id, l);
            if(pom != NULL) {
                printf("\n __________________________________________________________________\n");
                printf("%-67s|\n", "|");
                printf("|\t\tDANE STUDENTA POSIADAJACEGO");
                printf(KG" ID"RESET);
                printf(" %i:\t\t   |\n", id);
                printf("%-67s|\n|", "|");
                printf(KY"\t%-16s"RESET, "Imie:");
                printf(" %-42s|\n|", pom->name);
                printf(KR"\t%-16s"RESET, "Nazwisko:");
                printf(" %-42s|\n|", pom->lastName);
                printf(KB"\t%-16s"RESET, "Wiek:");
                printf(" %-42i|\n|", pom->age);
                printf(CY"\t%-16s"RESET, "Srednia ocen:");
                printf(" %-42.2f|\n", pom->avg);
                printf("%-67s|\n", "|");
                printf("|__________________________________________________________________|\n\n");
            }
            break;
        /* wyszukiwanie przez nazwisko */
        case '2':
            printf("Podaj nazwisko: ");
            checkString(temp);
            printf("\n _______________________________________________________________________________\n");
            printf("%-80s|\n", "|");
            printf("%-80s|\n", "|");
            printf("|\t       Dane studentow posiadajacych");
            printf(KR" nazwisko"RESET);
            printf(": %c", toupper(temp[0]));    /* w razie gdyby uzytkownik wpisal pierwsza litere mala */
            printf("%-25s|\n", &temp[1]);
            printf("%-80s|\n", "|");
            findStudentByLastName(0, temp, l);
            printf("%-80s|\n", "|");
            printf("|_______________________________________________________________________________|\n\n");
            break;
        /* wyszukiwanie przez imie */
        case '3':
            printf("Podaj imie: ");
            checkString(temp);
            printf("\n _______________________________________________________________________________\n");
            printf("%-80s|\n", "|");
            printf("%-80s|\n", "|");
            printf("|\t        Dane studentow posiadajacych");
            printf(KY" imie"RESET);
            printf(" %c", toupper(temp[0]));    /* w razie gdyby uzytkownik wpisal pierwsza litere mala */
            printf("%-29s|\n", &temp[1]);
            printf("%-80s|\n", "|");
            findStudentByName(0, temp, l);
            printf("%-80s|\n", "|");
            printf("|_______________________________________________________________________________|\n\n");
            break;
        default:
            printf("\x1b[3m\n\nWrociles do menu! \n\n\x1b[23m"RESET);
            break;
    }
}

/* usuwanie studenta z listy */
Student* deleteStudent(int id, Student *l, Student *pom) {
    if(l->next != NULL) {
        if(l->next->ID == id) {
            l->next = pom->next;
            free(pom);
            return l;
        }
        else {
            l->next = deleteStudent(id, l->next, pom);
        }
    }
    return l;
}

/* GLOWNA funkcja pozwalajaca wybierac odpowiednie akcje uzytkownikowi */
void choice(Student *l) {
    char answer[100] = "";
    FILE *fP;
    Student *pom;
    int id;

    while(answer[0] != '6') {
        printMenu();

        scanf(" %s", answer);
        while(strlen(answer) != 1 || answer[0] < 49 || answer [0] > 54) {
            printf("\x1b[3m\n\nWpisano niepoprawna wartosc, sprobuj ponownie :) \n\n\x1b[23m"RESET);
            printMenu();
            scanf(" %s", answer);
        }

        switch (answer[0]) {
            /* wypisywanie listy studentow */
            case '1':
                printf("\n _______________________________________________________________________________\n");
                printf("%-80s|", "|");
                printf("\n%-80s|\x1b[1m \n|\t\t    LISTA STUDENTOW UMIESZCZONYCH W BAZIE DANYCH:\x1b[22m\t\t|\n", "|");
                printf("%-80s|\n", "|");
                if(l != NULL) {
                    printf("|");
                    printf(KG"    %-8s "RESET, " ID");
                    printf(KY"%-21s"RESET, "IMIE");
                    printf(KR"%-21s"RESET, "NAZWISKO");
                    printf(KB"%-7s"RESET, "WIEK");
                    printf(CY"%-17s"RESET, "SREDNIA OCEN");
                    printf("|\n%-80s|\n", "|");
                    printList(l);
                    printf("%-80s|\n", "|");
                    printf("|_______________________________________________________________________________|\n\n");
                }
                else {
                    printf("%-80s|\n|", "|");
                    printf(KR"\t\t\t\t%-32s"RESET, "LISTA JEST PUSTA!");
                    printf("\t\t|\n%-80s|\n", "|");
                    printf("|_______________________________________________________________________________|\n\n");
                }
                break;
            /* dodawanie studenta */
            case '2':
                printf("\x1b[3m\nDodawanie studenta... \n\n\x1b[23m");
                id = getID();

                l = addStudent(id, l);
                break;
            /* usuwanie elementu lub calej listy */
            case '3':
                if(l == NULL) {
                    printf("\n __________________________________________________________________\n");
                    printf("%-67s|\n", "|");
                    printf("%-67s|\n|", "|");
                    printf(KR"\tNIE MOZNA USUNAC NIKOGO, PONIEWAZ LISTA JEST PUSTA!\t   "RESET);
                    printf("|\n%-67s|\n", "|");
                    printf("|__________________________________________________________________|\n\n");
                }
                else {
                    printf("\n1. Usun jednego studenta\n");
                    printf("2. Wykasuj cala liste studentow\n");
                    printf("3. Wroc do menu\n");

                    scanf(" %s", answer);
                    while(strlen(answer) != 1 || answer[0] < 49 || answer [0] > 51) {
                        printf("\x1b[3m\n\nWpisano niepoprawna wartosc, sprobuj ponownie :) \n\n\x1b[23m"RESET);
                        printf("1. Usun jednego studenta\n");
                        printf("2. Wykasuj cala liste studentow\n");
                        printf("3. Wroc do menu\n");
                        scanf(" %s", answer);
                    }

                    if(answer[0] == '1') {
                        id = getID();

                        pom = findStudentByID(id, l);
                        if(pom != NULL) {
                            if(pom == l) {
                                l = l->next;
                                free(pom);
                            }
                            else {
                                l = deleteStudent(id, l, pom);
                            }
                            printf("\x1b[3m\n\nStudent usuniety z listy pomyslnie!\n\n\x1b[23m");
                        }
                    }
                    else if (answer[0] == '2') {
                        while(l != NULL) {
                            /* zwalnianie pamieci uzytej na liste struktur*/
                            pom = l->next;
                            free(l);
                            l = pom;

                        }
                        printf("\x1b[3m\n\nWykasowano cala liste studentow! \n\n\x1b[23m"RESET);
                    }
                    else printf("\x1b[3m\n\nWrociles do menu! \n\n\x1b[23m"RESET);
                }
                break;
            /* wyszukiwanie na liscie */
            case '4':
                if(l == NULL) {
                    printf("\n __________________________________________________________________\n");
                    printf("%-67s|\n", "|");
                    printf("%-67s|\n|", "|");
                    printf(KR"\tLISTA JEST PUSTA, WIEC NIEMOZLIWE JEST WYSZUKIWANIE!\t   "RESET);
                    printf("|\n%-67s|\n", "|");
                    printf("|__________________________________________________________________|\n\n");
                }
                else find(l);
                break;
            /* zapisywanie listy do pliku */
            case '5':
                printf("\n\x1b[3m\nWszystkie zmiany zostaly zapisane!\n\n\x1b[23m");
                fP = fopen("save.txt", "w");
                save(fP, l);
                fclose(fP);
                break;
            /* zwolnienie pamieci przed zamknieciem programu */
            case '6':
                printf("\x1b[3m\nZamykanie programu... \n\n\x1b[23m");

                /* zwalnianie pamieci uzytej na liste struktur */
                while(l != NULL) {
                    pom = l->next;
                    free(l);
                    l = pom;
                }
                break;
            default:
                break;
        }
    }
}

#endif