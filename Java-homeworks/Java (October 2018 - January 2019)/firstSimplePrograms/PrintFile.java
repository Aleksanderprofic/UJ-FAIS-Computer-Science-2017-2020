package firstSimplePrograms;

import java.io.*;

public class PrintFile {

    public static void main(String[] args) {

        if(args.length != 1) {
            System.out.println("Error: enter just the file name");
            System.exit(0);
        }

        File file = new File(args[0]);  // stworzenie zmiennej plikowej od argumentu wprowadzonego przez uzytkownika

        printFile(file);
    }

    public static void printFile(File file) {
        BufferedReader br = null;   // stworzenie referencji do obiektu BufferedReader, ktora wskazuje na null
        try {
            br = new BufferedReader(new FileReader(file));  // stworzenie nowego obiektu BufferedReader,
            // którego argumentem jest obiekt FileReader
            // (bo nigdzie indziej go nie wykorzystujemy)
            // przyjmujacy jako argument obiekt File

        } catch (FileNotFoundException e) {                 // wyjatek, gdy plik nie istnieje
            e.printStackTrace();
        }

        String line;                                        // string, do ktorego beda zapisywane odczytane linijki z pliku
        int i = 0;                                          // iterator

        try {
            while ((line = br.readLine()) != null) {        // odczytanie kolejnych linii z pliku file
                System.out.println((i++)+1 + "\t" + line);  // wypisanie na ekran nr linii i zawartosci pliku
            }
        } catch(IOException e) {                            // wyjatek dla wejscia/wyjscia
            e.printStackTrace();
        }
    }
}