package firstSimplePrograms;

public class Hello {
    public Hello() {
        System.out.println("Constructor");
    }

    static {
        System.out.println("Klasa zostala zaladowana");
    }

    public static void main(String[] args) {

        System.out.println("Hello world");
        int i;

        for(i = 0; i < args.length; i++) {
            System.out.println(args[i]);
        }

        Hello hello = new Hello();
    }
}

