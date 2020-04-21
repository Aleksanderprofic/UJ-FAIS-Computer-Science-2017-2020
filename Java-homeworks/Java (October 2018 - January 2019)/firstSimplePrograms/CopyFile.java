package firstSimplePrograms;

import java.io.*;

public class CopyFile {
    public static void main(String[] args) {

        if(args.length != 2) {
            System.out.println("Error: enter two file names");
            System.exit(0);
        }

        // stworzenie obiektów plikowych
        File fileinput = new File(args[0]);
        File fileoutput = new File(args[1]);

        copyFile(fileinput, fileoutput);

    }


    private static void copyFile(File fileinput, File fileoutput) {


        try {
            FileInputStream inputStream = new FileInputStream(fileinput);     // stworzenie obiektu FileInputStream
            FileOutputStream outputStream = new FileOutputStream(fileoutput);   // stworzenie obiektu FileOutputStream

            byte[] data = new byte[8];                          // tablica bajtow

            while ((inputStream.read(data)) != -1) {         // dopoki zwrocona ilosc bajtow z funkcji read jest rozna od -1
                outputStream.write(data);                   // zapisujemy te odczytane bajty do pliku poprzez write
            }

            inputStream.close();                            // zamykamy strumien

            outputStream.close();                           // zamykamy strumien
        } catch(FileNotFoundException e) {
            e.printStackTrace();
        } catch(IOException ex) {                            // wyjatek wejscia/wyjscia
            System.out.println("Input/output exception");
        }
    }
}
