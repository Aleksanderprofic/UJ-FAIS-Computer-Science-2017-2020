package firstSimplePrograms;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Print {

    public static void main(String[] args) {

        if(args.length != 1) {
            System.out.println("Error: enter just the file name");
            System.exit(0);
        }

        File file = new File(args[0]);   // tworzenie zmiennej plikowej

        print(file);
    }

    public static void print(File file) {
        Scanner scanner = null;    // ustawienie referencji typu Scanner na null
        try {
            scanner = new Scanner(file);       // stworzenie obiektu typu Scanner
        } catch (FileNotFoundException e) {       // wyjątek, gdy plik nie istnieje
            e.printStackTrace();
        }

        String line;

        while (scanner.hasNextLine()) {       // petla dziala dopoki plik posiada nastepna nieprzeczytana linie
            line = scanner.nextLine();        // odczytanie kolejnych linii z pliku
            System.out.println(line);         // wypisanie na ekran
        }
    }
}
